#!/usr/bin/env python3
from flask import Flask, escape, request
app=Flask(__name__)

@app.route('/getstats')
def stats_page():
    buffs=request.args.get("buffs","none")
    return 'Your stats include buffs='+escape(buffs)

app.run()


