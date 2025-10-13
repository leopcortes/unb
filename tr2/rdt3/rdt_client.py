
import argparse, os, socket, time
from rdt_protocol import MAX_PAYLOAD, RECV_BUFSIZE, TIMEOUT, FLAG_DATA, FLAG_ACK, FLAG_FIN, make_packet, parse_packet

def send_and_wait_ack(sock, addr, seq, pkt, verbose):
    retrans = 0
    while True:
        sock.sendto(pkt, addr)
        if verbose:
            print(f"envio_seq={seq} len={len(pkt)}")
        try:
            data, _ = sock.recvfrom(RECV_BUFSIZE)
        except socket.timeout:
            retrans += 1
            if verbose:
                print(f"timeout_seq={seq} retrans={retrans}")
            continue
        ack = parse_packet(data)
        if ack and ack["checksum_ok"] and (ack["flags"] & FLAG_ACK) and ack["seq"] == seq:
            if verbose and retrans > 0:
                print(f"ack_ok_seq={seq} retrans_total={retrans}")
            return retrans

def run(server_host: str, server_port: int, infile: str, payload: int, rate_mbps: float, verbose: bool):
    sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
    sock.settimeout(TIMEOUT)
    addr = (server_host, server_port)
    seq = 0
    size = os.path.getsize(infile)
    sent = 0
    total_retrans = 0
    interval = (payload * 8) / (rate_mbps * 1e6) if rate_mbps and rate_mbps > 0 else 0.0
    next_send = time.time()
    t0 = time.time()
    with open(infile, "rb") as f:
        while True:
            chunk = f.read(payload)
            if not chunk:
                break
            if interval > 0:
                now = time.time()
                if now < next_send:
                    time.sleep(next_send - now)
                next_send = max(now, next_send) + interval
            pkt = make_packet(seq, FLAG_DATA, chunk)
            r = send_and_wait_ack(sock, addr, seq, pkt, verbose)
            total_retrans += r
            sent += len(chunk)
            seq ^= 1
    fin = make_packet(seq, FLAG_FIN, b"")
    send_and_wait_ack(sock, addr, seq, fin, verbose)
    t1 = time.time()
    th_mbps = (sent * 8) / (max(1e-6, (t1 - t0)) * 1e6)
    print(f"bytes_enviados={sent} tempo_seg={(t1-t0):.3f} th_put_mbps={th_mbps:.3f} retrans_total={total_retrans}")

if __name__ == "__main__":
    ap = argparse.ArgumentParser()
    ap.add_argument("--host", required=True)
    ap.add_argument("--port", type=int, default=5001)
    ap.add_argument("--in", dest="infile", required=True)
    ap.add_argument("--payload", type=int, default=MAX_PAYLOAD)
    ap.add_argument("--rate-mbps", type=float, default=0.0)
    ap.add_argument("--verbose", action="store_true")
    args = ap.parse_args()
    run(args.host, args.port, args.infile, args.payload, args.rate_mbps, args.verbose)
