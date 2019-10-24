#!/usr/bin/env python3
from flask import Flask, escape, Markup
app=Flask(__name__)

@app.route('/ultrabad/<path:tofile>')
def get_file_ultrabad(tofile):
    f=open(tofile,'r') # <- file path injection here!
    data=escape(f.read())
    pre=Markup('<html><body>File data: <pre>')
    post=Markup('</pre>File ends.</body></html>')
    return pre+data+post
app.run()

