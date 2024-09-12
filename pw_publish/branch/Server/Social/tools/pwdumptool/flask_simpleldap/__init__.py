# -*- coding: utf-8 -*-
__all__ = ['LDAP']

from functools import wraps
import re

import ldap
from flask import abort, current_app, g, redirect, url_for

try:
    from flask import _app_ctx_stack as stack
except ImportError:
    from flask import _request_ctx_stack as stack


class LDAPException(RuntimeError):
    message = None

    def __init__(self, message):
        self.message = message

    def __str__(self):
        return self.message

    def __unicode__(self):
        return self.message


class LDAP(object):
    def __init__(self, app=None):
        self.app = app
        if app is not None:
            self.init_app(app)

    @staticmethod
    def init_app(app):
        """Initialize the `app` for use with this :class:`~LDAP`. This is
        called automatically if `app` is passed to :meth:`~LDAP.__init__`.

        :param flask.Flask app: the application to configure for use with
           this :class:`~LDAP`
        """

        app.config.setdefault('LDAP_HOST', 'localhost')
        app.config.setdefault('LDAP_PORT', 389)
        app.config.setdefault('LDAP_SCHEMA', 'ldap')
        app.config.setdefault('LDAP_USERNAME', None)
        app.config.setdefault('LDAP_PASSWORD', None)
        app.config.setdefault('LDAP_TIMEOUT', 10)
        app.config.setdefault('LDAP_USE_SSL', False)
        app.config.setdefault('LDAP_USE_TLS', False)
        app.config.setdefault('LDAP_REQUIRE_CERT', False)
        app.config.setdefault('LDAP_CERT_PATH', '/path/to/cert')
        app.config.setdefault('LDAP_BASE_DN', None)
        app.config.setdefault('LDAP_OBJECTS_DN', 'distinguishedName')
        app.config.setdefault('LDAP_USER_FIELDS', [])
        app.config.setdefault('LDAP_USER_OBJECT_FILTER',
                              '(&(objectclass=Person)(userPrincipalName={0}))')
        app.config.setdefault('LDAP_USER_GROUPS_FIELD', 'memberOf')
        app.config.setdefault('LDAP_GROUP_FIELDS', [])
        app.config.setdefault('LDAP_GROUP_OBJECT_FILTER',
                              '(&(objectclass=Group)(userPrincipalName={0}))')
        app.config.setdefault('LDAP_GROUP_MEMBERS_FIELD', 'member')
        app.config.setdefault('LDAP_LOGIN_VIEW', 'login')

        if app.config['LDAP_USE_SSL'] or app.config['LDAP_USE_TLS']:
            ldap.set_option(ldap.OPT_X_TLS_REQUIRE_CERT,
                            ldap.OPT_X_TLS_NEVER)

        if app.config['LDAP_REQUIRE_CERT']:
            ldap.set_option(ldap.OPT_X_TLS_REQUIRE_CERT,
                            ldap.OPT_X_TLS_DEMAND,
                            (ldap.OPT_X_TLS_CACERTFILE,
                             current_app.config['LDAP_CERT_PATH']))

        for option in ['USERNAME', 'PASSWORD', 'BASE_DN']:
            if app.config['LDAP_{0}'.format(option)] is None:
                raise LDAPException('LDAP_{0} cannot be None!'.format(option))

    @property
    def initialize(self):
        """Initialize a connection to the LDAP server.

        :return: LDAP connection object.
        """
        if self.app.config["LDAP_ON"]:
            try:
                conn = ldap.initialize('{0}://{1}:{2}'.format(
                    current_app.config['LDAP_SCHEMA'],
                    current_app.config['LDAP_HOST'],
                    current_app.config['LDAP_PORT']))
                conn.set_option(ldap.OPT_NETWORK_TIMEOUT,
                                current_app.config['LDAP_TIMEOUT'])
                conn.protocol_version = ldap.VERSION3
                if current_app.config['LDAP_USE_TLS']:
                    conn.start_tls_s()
                return conn
            except ldap.LDAPError as e:
                raise LDAPException(self.error(e))
        else:
            return None

    @property
    def bind(self):
        """Attempts to bind to the LDAP server using the credentials of the
        service account.

        :return: Bound LDAP connection object if successful or ``None`` if
            unsuccessful.
        """
        if self.app.config["LDAP_ON"]:
            conn = self.initialize
            try:
                conn.simple_bind_s(current_app.config['LDAP_USERNAME'],
                                   current_app.config['LDAP_PASSWORD'].encode('utf-8'))
                return conn
            except ldap.LDAPError as e:
                raise LDAPException(self.error(e))
        else:
            return None

    def bind_user(self, username, password):
        """Attempts to bind a user to the LDAP server using the credentials
        supplied.

        :param str username: The username to attempt to bind with.
        :param str password: The password of the username we're attempting to
            bind with.
        :return: Returns ``True`` if successful or ``None`` if the credentials
            are invalid.
        """
        if self.app.config["LDAP_ON"]:
            user_dn = self.get_object_details(user=username, dn_only=True)
            if user_dn is None:
                return
            try:
                conn = self.initialize
                conn.simple_bind_s(user_dn, password)
                return True
            except ldap.LDAPError:
               return
        else:
            return True

    def get_object_details(self, user=None, group=None, dn_only=False):
        """Returns a ``dict`` with the object's (user or group) details.

        :param str user: Username of the user object you want details for.
        :param str group: Name of the group object you want details for.
        :param bool dn_only: If we should only retrieve the object's
            distinguished name or not. Default: ``False``.
        """

        query = None
        fields = None
        if user is not None:
            if not dn_only:
                fields = current_app.config['LDAP_USER_FIELDS']
            query = current_app.config['LDAP_USER_OBJECT_FILTER'].format(user)
        elif group is not None:
            if not dn_only:
                fields = current_app.config['LDAP_GROUP_FIELDS']
            query = current_app.config['LDAP_GROUP_OBJECT_FILTER'].format(group)
        conn = self.bind
        try:
            records = conn.search_s(current_app.config['LDAP_BASE_DN'],
                                    ldap.SCOPE_SUBTREE, query, fields)
            conn.unbind_s()
            result = {}
            if records:
                if dn_only:
                    if current_app.config['LDAP_OBJECTS_DN'] in records[0][1]:
                        dn = records[0][1][current_app.config['LDAP_OBJECTS_DN']]
                        return dn[0]
                for k, v in records[0][1].items():
                    result[k] = v
                return result
        except ldap.LDAPError as e:
            raise LDAPException(self.error(e))

    def get_user_groups(self, user):
        """Returns a ``list`` with the user's groups or ``None`` if
        unsuccessful.

        :param str user: User we want groups for.
        """
        if current_app.config["LDAP_ON"]:
            conn = self.bind
            try:
                records = conn.search_s(current_app.config['LDAP_BASE_DN'], ldap.SCOPE_SUBTREE,
                                        current_app.config['LDAP_USER_OBJECT_FILTER'].format(user),
                                        [current_app.config['LDAP_USER_GROUPS_FIELD']])
                conn.unbind_s()
                if records:
                    if current_app.config['LDAP_USER_GROUPS_FIELD'] in records[0][1]:
                        groups = records[0][1][current_app.config['LDAP_USER_GROUPS_FIELD']]
                        result = [re.findall('(?:cn=|CN=)(.*?),', group)[0] for group in groups]
                        return result
            except ldap.LDAPError as e:
                raise LDAPException(self.error(e))
        else:
            return None

    def get_group_members(self, group):
        """Returns a ``list`` with the group's members or ``None`` if
        unsuccessful.

        :param str group: Group we want users for.
        """
        if current_app.config["LDAP_ON"]:
            conn = self.bind
            try:
                records = conn.search_s(current_app.config['LDAP_BASE_DN'], ldap.SCOPE_SUBTREE,
                                        current_app.config['LDAP_GROUP_OBJECT_FILTER'].format(group),
                                        [current_app.config['LDAP_GROUP_MEMBERS_FIELD']])
                conn.unbind_s()
                if records:
                    if current_app.config['LDAP_GROUP_MEMBERS_FIELD'] in records[0][1]:
                        members = records[0][1][current_app.config['LDAP_GROUP_MEMBERS_FIELD']]
                        return members
            except ldap.LDAPError as e:
                raise LDAPException(self.error(e))
        return None

    @staticmethod
    def error(e):
        if 'desc' in dict(e.message):
            return dict(e.message)['desc']
        else:
            return e[1]

    @staticmethod
    def login_required(func):
        """Used to decorate a view function to require LDAP login but does NOT
        require membership from a specific group.

        :param func: The view function to decorate.
        """

        @wraps(func)
        def wrapped(*args, **kwargs):
            if current_app.config["LDAP_ON"]:
                if g.user is None:
                    return redirect(url_for(current_app.config['LDAP_LOGIN_VIEW']))
            return func(*args, **kwargs)
        return wrapped

    @staticmethod
    def group_required(groups=None):
        """Used to decorate a view function to require LDAP login AND membership
        from one of the groups within the groups list.

        :param list groups: List of groups that should be able to access the view
            function.
        """

        def wrapper(func):
            @wraps(func)
            def wrapped(*args, **kwargs):
                if current_app.config["LDAP_ON"]:
                    if g.user is None:
                        return redirect(url_for(current_app.config['LDAP_LOGIN_VIEW']))
                    match = [group for group in groups if group in g.ldap_groups]
                    if not match:
                        abort(401)
                return func(*args, **kwargs)
            return wrapped
        return wrapper
