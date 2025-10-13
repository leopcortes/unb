
import argparse, socket
from rdt_protocol import MAX_PAYLOAD, RECV_BUFSIZE, FLAG_DATA, FLAG_ACK, FLAG_FIN, make_packet, parse_packet

def run(host: str, port: int, outfile: str, verbose: bool):
    sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
    sock.bind((host, port))
    expected = 0
    last_ack = 1
    with open(outfile, "wb") as f:
        while True:
            data, addr = sock.recvfrom(RECV_BUFSIZE)
            pkt = parse_packet(data)
            if not pkt or not pkt["checksum_ok"]:
                if verbose:
                    print("pkt_invalido_ou_checksum")
                continue
            if pkt["flags"] & FLAG_FIN:
                ack = make_packet(pkt["seq"] & 1, FLAG_ACK, b"")
                sock.sendto(ack, addr)
                if verbose:
                    print(f"fin_rx_seq={pkt['seq']} ack_enviado={pkt['seq'] & 1}")
                break
            if pkt["flags"] & FLAG_DATA:
                if verbose:
                    print(f"data_rx_seq={pkt['seq']} len={pkt['length']}")
                if pkt["seq"] == expected:
                    f.write(pkt["payload"])
                    last_ack = expected
                    expected ^= 1
                ack = make_packet(last_ack, FLAG_ACK, b"")
                sock.sendto(ack, addr)
                if verbose:
                    print(f"ack_tx_seq={last_ack}")

if __name__ == "__main__":
    ap = argparse.ArgumentParser()
    ap.add_argument("--host", default="0.0.0.0")
    ap.add_argument("--port", type=int, default=5001)
    ap.add_argument("--out", required=True)
    ap.add_argument("--verbose", action="store_true")
    args = ap.parse_args()
    run(args.host, args.port, args.out, args.verbose)
