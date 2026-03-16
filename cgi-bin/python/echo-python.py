#!/usr/bin/env python3
import os, sys, json, datetime, urllib.parse, socket

def read_body():
    try:
        n = int(os.environ.get("CONTENT_LENGTH", "0"))
    except ValueError:
        n = 0
    return sys.stdin.read(n) if n > 0 else ""

def parse_urlencoded(s: str):
    d = urllib.parse.parse_qs(s, keep_blank_values=True)
    return {k: (v[0] if len(v)==1 else v) for k, v in d.items()}

method = os.environ.get("REQUEST_METHOD", "GET")
ct = os.environ.get("CONTENT_TYPE", "")
ip = os.environ.get("REMOTE_ADDR", "unknown")
ua = os.environ.get("HTTP_USER_AGENT", "unknown")
host = socket.gethostname()
time_iso = datetime.datetime.now().isoformat()

query = parse_urlencoded(os.environ.get("QUERY_STRING", ""))
raw = read_body()

body = None
if method != "GET" and raw:
    if "application/json" in ct:
        try: body = json.loads(raw)
        except: body = None
    elif "application/x-www-form-urlencoded" in ct:
        body = parse_urlencoded(raw)

payload = {
  "language": "python",
  "hostname": host,
  "time": time_iso,
  "ip": ip,
  "user_agent": ua,
  "method": method,
  "content_type": ct,
  "query": query,
  "body": body,
  "raw": raw
}

print("Content-Type: application/json\n")
print(json.dumps(payload, indent=2))
