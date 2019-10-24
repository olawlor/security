#!/usr/bin/env python3
from flask import Flask, escape
app=Flask(__name__)

@app.route('/get<RAWthingy>')
def get_page(RAWthingy):
    thingy=escape(RAWthingy)
    return 'Yes, we have '+thingy

app.run()

