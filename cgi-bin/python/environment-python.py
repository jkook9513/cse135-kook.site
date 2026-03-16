#!/usr/bin/env python3
import os

print("Content-type: text/html \n")

# print HTML file top
print("""
<!DOCTYPE html>
<html><head><title>Environment Variables</title>
</head><body><h1 align="center">Python Environment Variables</h1>
<hr>
""")

# Loop over the environment variables and print each variable and its value
for key,value in os.environ.items():
    print(f"<li><b>{key}</b> = {value}</li>")

# Print the HTML file bottom
print("</body></html>")