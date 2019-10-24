#!/usr/bin/env python3
from flask import Flask, request, escape, Markup, send_from_directory
app=Flask(__name__)

# Front page: show HTML form
@app.route('/')
def front_page():
    return send_from_directory("static","buy_form.html")

# This will store HTML for each bid.
# FIXME: this definitely isn't a database.
database=""

# Buyit: data returned by HTML form
@app.route('/buyit')
def buyit_now():
    luser=escape(request.args.get("lusername","foo"))
    item=escape(request.args.get("item","0"))
    bid=escape(request.args.get("bid","0"))
    global database  # <- write to global variable
    database += luser+" bid "+bid+"ℚ for "+item+"?!"+Markup("<br>")
    return database;

app.run()

