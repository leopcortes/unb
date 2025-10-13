
import struct

MAX_PAYLOAD = 1400
TIMEOUT = 0.8
RECV_BUFSIZE = 2048

FLAG_DATA = 0x01
FLAG_ACK = 0x02
FLAG_FIN = 0x04

_HDR_FMT = "!BBHH"
_HDR_SIZE = struct.calcsize(_HDR_FMT)

def _ones_complement_16bit_sum(data: bytes) -> int:
    if len(data) % 2 == 1:
        data += b"\x00"
    s = 0
    for i in range(0, len(data), 2):
        s += (data[i] << 8) + data[i + 1]
        s = (s & 0xFFFF) + (s >> 16)
    return (~s) & 0xFFFF

def checksum(header_wo_csum: bytes, payload: bytes) -> int:
    return _ones_complement_16bit_sum(header_wo_csum + payload)

def make_packet(seq: int, flags: int, payload: bytes) -> bytes:
    length = len(payload)
    hdr_wo_csum = struct.pack(_HDR_FMT, seq & 0xFF, flags & 0xFF, length & 0xFFFF, 0)
    csum = checksum(hdr_wo_csum, payload)
    return struct.pack(_HDR_FMT, seq & 0xFF, flags & 0xFF, length & 0xFFFF, csum) + payload

def parse_packet(packet: bytes):
    if len(packet) < _HDR_SIZE:
        return None
    seq, flags, length, recv_csum = struct.unpack(_HDR_FMT, packet[:_HDR_SIZE])
    payload = packet[_HDR_SIZE: _HDR_SIZE + length]
    hdr_wo_csum = struct.pack(_HDR_FMT, seq, flags, length, 0)
    ok = _ones_complement_16bit_sum(hdr_wo_csum + payload) == recv_csum
    return {"seq": seq, "flags": flags, "length": length, "checksum_ok": ok, "payload": payload}
