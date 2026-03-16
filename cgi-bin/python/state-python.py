#!/usr/bin/env python3
import os, sys, secrets, urllib.parse

COOKIE = "CSE135_SESSION_ID"

def parse_cookies(h):
    out = {}
    if not h:
        return out
    for part in h.split(";"):
        if "=" in part:
            k, v = part.split("=", 1)
            out[k.strip()] = v.strip()
    return out

def read_body():
    try:
        n = int(os.environ.get("CONTENT_LENGTH", "0"))
    except ValueError:
        n = 0
    return sys.stdin.read(n) if n > 0 else ""

# --- session id ---
cookies = parse_cookies(os.environ.get("HTTP_COOKIE", ""))
sid = cookies.get(COOKIE)
if not sid:
    sid = secrets.token_hex(16)

path = f"/tmp/cse135_state_{sid}"

# --- clear ---
if "clear=1" in os.environ.get("QUERY_STRING", ""):
    try:
        os.remove(path)
    except FileNotFoundError:
        pass

    print("Status: 302 Found")
    print(f"Set-Cookie: {COOKIE}={sid}; Path=/")
    print("Location: state-python.py")
    print()
    sys.exit(0)

# --- save name ---
if os.environ.get("REQUEST_METHOD") == "POST":
    body = read_body()
    form = urllib.parse.parse_qs(body, keep_blank_values=True)
    name = form.get("name", [""])[0]
    if name:
        with open(path, "w") as f:
            f.write(name)

# --- load name ---
name = "(nothing set yet)"
if os.path.exists(path):
    name = open(path).read()

# --- output ---
print("Content-Type: text/html")
print(f"Set-Cookie: {COOKIE}={sid}; Path=/")
print()
print(f"""<!doctype html>
<html>
<head><meta charset="utf-8"><title>State (Python)</title></head>
<body>
  <h1>State Page (Python)</h1>

  <p><b>Saved name:</b> {name}</p>

  <p>
    <a href="/session/python-cgiform.html">Back to form</a> |
    <a href="/index.html">Home</a> |
    <a href="state-python.py?clear=1">Clear</a>
  </p>
</body>
</html>""")
