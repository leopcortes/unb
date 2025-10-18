import json, time, random, urllib.request, urllib.error, os

SERVER = os.environ.get("SERVER_URL","http://127.0.0.1:8080/ingest")
DEVICE_ID = os.environ.get("DEVICE_ID","sensor-001")
ROOM = os.environ.get("ROOM","sala-01")
PERIOD = float(os.environ.get("PERIOD","3"))

def post(payload):
    data = json.dumps(payload).encode("utf-8")
    req = urllib.request.Request(SERVER, data=data, headers={"Content-Type":"application/json"}, method="POST")
    with urllib.request.urlopen(req, timeout=5) as r:
        return r.read()

def gen():
    t = round(random.uniform(18.0, 30.0),2)
    h = round(random.uniform(30.0, 80.0),2)
    d = round(random.uniform(5.0, 80.0),2)
    return {"device_id": DEVICE_ID, "room": ROOM, "ts": int(time.time()), "temp": t, "hum": h, "dust": d}

if __name__ == "__main__":
    while True:
        payload = gen()
        try:
            post(payload)
        except Exception:
            pass
        time.sleep(PERIOD)
