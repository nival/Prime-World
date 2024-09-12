#!/bin/bash
SESSION=`basename $PWD`

tmux new-session -d -s main 'exec bash ./log_show_sa.89.sh'
tmux select-window -t main:0
tmux split-window -h 'exec bash ./log_search_error.sh'
tmux split-window -v -t 0 'exec bash ./log_show_ss.88.sh'
tmux split-window -v -t 1 'exec bash ./log_show_ss.888.8888.sh'

tmux -2 attach-session -t main