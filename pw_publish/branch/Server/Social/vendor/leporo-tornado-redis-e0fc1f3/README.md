Tornado-Redis
=============

Asynchronous [Redis](http://redis.io/) client for the [Tornado Web Server](http://tornadoweb.org/).

This is a fork of [brükva](https://github.com/evilkost/brukva) redis client
modified to be used via Tornado's native 'tornado.gen' interface instead
of 'adisp' call dispatcher.

Tornado-Redis is licensed under the Apache Licence, Version 2.0
(http://www.apache.org/licenses/LICENSE-2.0.html).

Installation
------------

To install:

    python setup.py build
    sudo python setup.py install

Tornado-Redis has been tested on Python 2.6 and 2.7.

You may also install it using pip or easy_install with:

    pip install tornado-redis

or

    easy_install install tornado-redis


Usage
-----

	import tornadoredis
	import tornado.web
	import tornado.gen

	...	
	
	c = tornadoredis.Client()
	c.connect()

	...

	class MainHandler(tornado.web.RequestHandler):
	    @tornado.web.asynchronous
	    @tornado.gen.engine
	    def get(self):
	        foo = yield tornado.gen.Task(c.get, 'foo')
	        bar = yield tornado.gen.Task(c.get, 'bar')
	        zar = yield tornado.gen.Task(c.get, 'zar')
	        self.set_header('Content-Type', 'text/html')
	        self.render("template.html", title="Simple demo", foo=foo, bar=bar, zar=zar)

Running Tests
-------------

The redis server must be started on the default (:6379) port.

Use this command to run the test suite:

	python -m tornado.testing tornadoredis.tests


Credits and Contributors
------------------------
The [brükva](https://github.com/evilkost/brukva) project has been started
by [Konstantin Merenkov](https://github.com/kmerenkov)
but seem to be not maintained any more. 

[evilkost](https://github.com/evilkost)

[Matt Dawson](https://github.com/mattd)

[maeldur](https://github.com/maeldur)

[Olivier Yiptong](https://https://github.com/oyiptong)

[Juarez Bochi](https://github.com/jbochi)

[Jakub Roztocil](https://github.com/jkbr)

[nizox](https://github.com/nizox)

The Tornado-Redis project's source code and 'tornado-redis' PyPI package
are maintained by [Vlad Glushchuk](https://github.com/leporo).

Tornado is an open source version of the scalable, non-blocking web server
and and tools that power FriendFeed. Documentation and downloads are
available at http://www.tornadoweb.org/
