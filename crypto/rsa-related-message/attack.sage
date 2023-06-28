from Crypto.Util.number import bytes_to_long, long_to_bytes
message = bytes_to_long(b"hell world")
exp_pub = 3
while True:
    p = random_prime(2^64, lbound=2^63)
    q = random_prime(2^64, lbound=2^63)
    phi_pq = (p - 1) * (q - 1)
    if gcd(phi_pq, exp_pub) == 1:
        break
N = p * q
print(f"[+] p = {p}, q = {q}, N = {N}")
alpha = 2
beta = 3
d_priv = inverse_mod(exp_pub, phi_pq)
ciphertext = pow(message, exp_pub, N)
message_padded = alpha * message + beta
ciphertext_padded = pow(message_padded, exp_pub, N)

Z_N = Zmod(N)
R.<x> = PolynomialRing(Z_N)
eq_original = x^exp_pub - ciphertext
eq_padded = (alpha * x + beta)^exp_pub - ciphertext_padded

a = eq_original
b = eq_padded
while b != 0:
    a, b = b, a % b
common_poly = a / a.lc()
print(f"[+] GCD = {common_poly}")

common_poly_roots = common_poly.roots(multiplicities=False)
assert len(common_poly_roots) == 1
message_recovered = common_poly_roots[0]
print(f"[+] Recovered plaintext: {long_to_bytes(int(message_recovered))}")
