#!/bin/sh
# Prepare with:
#   pip3 install gunicorn flask
# (you may need to add $HOME/.local/bin to your $PATH)

killall gunicorn
gunicorn -w 2 -b 127.0.0.1:8192 overflowity_server:app
