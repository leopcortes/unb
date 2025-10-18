import http.server, socketserver, json, sqlite3, time, urllib.parse, threading, logging, os

DB_PATH = os.path.join(os.path.dirname(__file__), "telemetria.db")
HTML_PATH = os.path.join(os.path.dirname(__file__), "dashboard.html")
PORT = int(os.environ.get("PORT", "8080"))

def init_db():
    con = sqlite3.connect(DB_PATH)
    cur = con.cursor()
    cur.execute("""
        CREATE TABLE IF NOT EXISTS readings(
            id INTEGER PRIMARY KEY AUTOINCREMENT,
            device_id TEXT NOT NULL,
            room TEXT NOT NULL,
            ts INTEGER NOT NULL,
            temp REAL,
            hum REAL,
            dust REAL
        )
    """)
    con.commit()
    con.close()

def insert_reading(payload):
    con = sqlite3.connect(DB_PATH)
    cur = con.cursor()
    cur.execute("""
        INSERT INTO readings(device_id, room, ts, temp, hum, dust)
        VALUES(?,?,?,?,?,?)
    """, (payload.get("device_id","unknown"), payload.get("room","sala"), int(payload.get("ts", int(time.time()))), payload.get("temp"), payload.get("hum"), payload.get("dust")))
    con.commit()
    con.close()

def query_latest(room=None, limit=100):
    con = sqlite3.connect(DB_PATH)
    cur = con.cursor()
    if room:
        cur.execute("""
            SELECT device_id, room, ts, temp, hum, dust
            FROM readings
            WHERE room=?
            ORDER BY ts DESC
            LIMIT ?
        """, (room, limit))
    else:
        cur.execute("""
            SELECT r.device_id, r.room, r.ts, r.temp, r.hum, r.dust
            FROM readings r
            JOIN (
              SELECT device_id, MAX(ts) AS max_ts
              FROM readings
              GROUP BY device_id
            ) x ON r.device_id=x.device_id AND r.ts=x.max_ts
            ORDER BY r.room ASC, r.device_id ASC
        """)
    rows = cur.fetchall()
    con.close()
    return rows

def query_last_n(device_id, n=100):
    con = sqlite3.connect(DB_PATH)
    cur = con.cursor()
    cur.execute("""
        SELECT device_id, room, ts, temp, hum, dust
        FROM readings
        WHERE device_id=?
        ORDER BY ts DESC
        LIMIT ?
    """, (device_id, n))
    rows = cur.fetchall()
    con.close()
    return rows

class Handler(http.server.BaseHTTPRequestHandler):
    def do_POST(self):
        length = int(self.headers.get("Content-Length","0"))
        body = self.rfile.read(length) if length > 0 else b""
        if self.path == "/ingest":
            try:
                payload = json.loads(body.decode("utf-8"))
                insert_reading(payload)
                self.send_response(200)
                self.send_header("Content-Type","application/json")
                self.end_headers()
                self.wfile.write(json.dumps({"status":"ok"}).encode("utf-8"))
            except Exception as e:
                self.send_response(400)
                self.send_header("Content-Type","application/json")
                self.end_headers()
                self.wfile.write(json.dumps({"status":"error","msg":str(e)}).encode("utf-8"))
        else:
            self.send_response(404)
            self.end_headers()

    def do_GET(self):
        parsed = urllib.parse.urlparse(self.path)
        if parsed.path == "/":
            try:
                with open(HTML_PATH,"rb") as f:
                    data = f.read()
                self.send_response(200)
                self.send_header("Content-Type","text/html; charset=utf-8")
                self.end_headers()
                self.wfile.write(data)
            except FileNotFoundError:
                self.send_response(404)
                self.end_headers()
        elif parsed.path == "/api/latest":
            qs = urllib.parse.parse_qs(parsed.query)
            room = qs.get("room",[None])[0]
            rows = query_latest(room=room)
            resp = [{"device_id":d,"room":r,"ts":t,"temp":te,"hum":h,"dust":du} for d,r,t,te,h,du in rows]
            self.send_response(200)
            self.send_header("Content-Type","application/json")
            self.end_headers()
            self.wfile.write(json.dumps(resp).encode("utf-8"))
        elif parsed.path == "/api/last_n":
            qs = urllib.parse.parse_qs(parsed.query)
            device_id = qs.get("device_id",[None])[0]
            n = int(qs.get("n",[100])[0])
            if not device_id:
                self.send_response(400)
                self.end_headers()
                return
            rows = query_last_n(device_id, n)
            resp = [{"device_id":d,"room":r,"ts":t,"temp":te,"hum":h,"dust":du} for d,r,t,te,h,du in rows]
            self.send_response(200)
            self.send_header("Content-Type","application/json")
            self.end_headers()
            self.wfile.write(json.dumps(resp).encode("utf-8"))
        else:
            self.send_response(404)
            self.end_headers()

class ThreadedHTTPServer(socketserver.ThreadingMixIn, http.server.HTTPServer):
    daemon_threads = True

def run():
    logging.basicConfig(level=logging.INFO, format="%(asctime)s %(levelname)s %(message)s")
    init_db()
    server = ThreadedHTTPServer(("0.0.0.0", PORT), Handler)
    logging.info("Servidor iniciado em http://0.0.0.0:%s", PORT)
    try:
        server.serve_forever()
    except KeyboardInterrupt:
        pass
    finally:
        server.server_close()

if __name__ == "__main__":
    run()
