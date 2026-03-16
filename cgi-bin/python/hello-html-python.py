#!/usr/bin/env python3
import os, datetime

print ("Content-Type: text/html\n")

print ("<!DOCTYPE html>")
print ("<html>")
print ("<head>")
print ("<title>Hello, Python!</title>")
print ("</head>")
print ("<body>")

print ("<h1 align=center>Hello, Python!</h1><hr/>")
print ("<p>Hello World from Team Kook! </p>")
print ("<p>This page was generated with the Python programming langauge</p>")

date = datetime.datetime.now().strftime("%Y-%m-%d %H:%M:%S.%f")
print ("<p>Today's date is : " + date + "</p>")

# IP Address is an environment variable when using CGI
address = os.environ.get("REMOTE_ADDR", "unknown")
print ("<p>Your current IP Address is: " + address + "</p>")

print ("</body>")
print ("</html>")