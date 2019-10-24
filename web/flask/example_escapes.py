#!/usr/bin/env python3
from flask import Flask, request, escape, Markup
app=Flask(__name__)

print("Bare string<h1>with markup</h1>")
print(escape("Escaped string<h1>with markup</h1>"))
print(escape(escape("Double-escaped <h1>with markup</h1>")))
print(escape("Appended")+" to escape <h1>with markup</h1>")
print(Markup("<p>Appended")+" to markup <h1>with markup</h1>")
print("<p>Prepended "+escape("to escape"))
print("<p>Prepended "+Markup("to markup"))

