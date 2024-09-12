# -*- coding: cp1251 -*-
#!/usr/bin/env python

import re

irc_host = '127.0.0.1'
irc_port = 6697

# для теста подключаемся к одному irc серверу
irc_poll_connect = [('127.0.0.1', 6697),('127.0.0.1', 6697)]

oper_name = 'oper'
oper_password = 'oper_PassworD8'
poll = 'simple'
poll_freq = 0.5

long_polling_enabled = True

separate_factions = False
separate_locales = True

chat_locales = ["RU", "EN", "TR"]

# для каждой пользовательской локали приводим список языков, по которым нужно выполнять фильтрацию мата (по умолчанию фильтруем свой язык + английский)
filter_locales = {
    "RU": ["RU", "EN"],
    "TR": ["TR", "EN"],
    "EN": ["EN"],
}

# A list of regular expressions of nicknames immune to flood control.
# The list elements should be re.compile() calls with 1 jr 2 parameters:
# 1) (mandatory) strings containing a regular expression
# 2) (optional) regular expression flags
# Examples:
#   re.compile('^Superadmin$')
#   re.compile(r'^Admin(?:\d+)$', re.IGNORECASE)
# Note: all regexps are checked using re.search(), so don't forget about ^ and $
# note 2: these are nicknames on IRC-server, not in-game player names.
no_flood_control_nicks = [re.compile(r'^Admin(?:Msg)\d*'),]

# Regexp(s) to find channel names
admin_mute_channels = [re.compile(r'^#(?:global|lfg|tambur_|group_)'),]


# Global flood control parameters
flood_message_weight  = 60   # how match each message add to a flood watcher
flood_max_length      = 80   # maximum length of 'one message', messages with grater length count as 'more than one'
flood_unweight_slower = 1.0  # devisor for unweight_rate during an amnesty time
flood_weight_increase = 1.0  # multiplier for flood_message_weight during an amnesty time
## flood_unweight_slower and flood_weight_increase make harder message frequency restriction for recent flooders
flood_penalty         = 0.2  # for each additional message in mute state, increase mute_time by this part
                             # (0.1 = 10%, i.e. current mute period length will be increased by 10%)
                             # Set 0 to turn this penalty off.

flood_control_groups = [
    {
        'name': 'global',
        'channel_rx': re.compile(r'^#(?:global|lfg)'),
        'unweight_rate': 1,      # flood watcher value reduce per second
        'weight_limit': 300,     # which flood watcher value indicates a flood event
        'mute_time': 10,         # mute time for a flood event, in seconds
        'mute_increase': 2.0,    # multiplier for mute_time if new flood event occur before an amnesty
        'amnesty_time': 30 * 60, # how long should flood control remember flooders
    },
    {
        'name': 'guild',
        'channel_rx': re.compile(r'^#guild_'),
        'unweight_rate': 3,      # flood watcher value reduce per second
        'weight_limit': 900,     # which flood watcher value indicates a flood event
        'mute_time': 10,         # mute time for a flood event, in seconds
        'mute_increase': 2.0,    # multiplier for flood_mute_time and flood_amnesty_time if new flood event occur before an amnesty
        'amnesty_time': 30 * 60, # how long should flood control remember flooders
    }
]

