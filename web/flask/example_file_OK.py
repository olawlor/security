#!/usr/bin/env python3
from flask import Flask, escape, send_from_directory
app=Flask(__name__)

@app.route('/staticfile/<path:tofile>')
def get_static_file(tofile):
    return send_from_directory("static",tofile)

app.run()

