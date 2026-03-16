#!/usr/bin/env python3
import os, datetime, json

date = datetime.datetime.now().strftime("%Y-%m-%d %H:%M:%S.%f")
address = os.environ.get("REMOTE_ADDR", "unknown")

data = {
    "title": "Hello, Python!",
    "message": "Hello World from Team Kook! This page was generated with the PHP programming language.",
    "time": date,
    "ipAddress": address
}
print("Content-Type: application/json\n")

print(json.dumps(data))