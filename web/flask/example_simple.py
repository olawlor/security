#!/usr/bin/env python3
from flask import Flask
app=Flask(__name__)

@app.route('/spartan')
def spartan_page():
    return 'This page is simple but clear.'

app.run()


