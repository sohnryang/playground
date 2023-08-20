import secrets

p = 0xffffffff00000001000000000000000000000000ffffffffffffffffffffffff
Fp = GF(p)
a = 0xffffffff00000001000000000000000000000000fffffffffffffffffffffffc
b = 0x5ac635d8aa3a93e7b3ebbd55769886bc651d06b0cc53b0f63bce3c3e27d2604b
E = EllipticCurve(Fp, [a, b])
G = E(0x6b17d1f2e12c4247f8bce6e563a440f277037d812deb33a0f4a13945d898c296,
      0x4fe342e2fe1a7f9b8ee7eb4a7c0f9e162bce33576b315ececbb6406837bf51f5)

KEYPAIR_COUNT = 8
key_pairs = []
for i in range(KEYPAIR_COUNT):
    print(f"[+] Key pair id={i}")
    privkey = secrets.randbits(256)
    pubkey = privkey * G
    print(f"[+] private key: {privkey}")
    print(f"[+] public key: {pubkey}")
    key_pairs.append((privkey, pubkey))

print("[+] Public key lists:")
for i, (_, pubkey) in enumerate(key_pairs):
    print(f"[+] Public key id={i}: {pubkey}")
