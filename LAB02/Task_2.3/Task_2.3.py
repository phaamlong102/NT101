from Crypto.Cipher import DES

def avalanche_test():
    key = b'24520961'
    p1 = b'STAYHOME'
    p2 = b'STAYHOMA'

    # TODO: Thực hiện mã hóa p1, p2 bằng DES-ECB
    cipher = DES.new(key, DES.MODE_ECB)
    c1 = cipher.encrypt(p1)
    c2 = cipher.encrypt(p2)
    print("Bản mã 1 (Hex):", c1.hex())
    print("Bản mã 2 (Hex):", c2.hex())
    # TODO: Đếm số bit khác nhau giữa hai bản mã thu được
    b1 = bin(int.from_bytes(c1, 'big'))[2:].zfill(64)
    b2 = bin(int.from_bytes(c2, 'big'))[2:].zfill(64)
    diff_bits = sum(1 for bit_a, bit_b in zip(b1, b2) if bit_a != bit_b)
    # TODO: Tính tỷ lệ % bit bị thay đổi
    percent_change = (diff_bits / 64) * 100
    print("Key ban đầu:", key)
    print("Số bit khác nhau (Hamming Distance):", diff_bits)
    print("Tỷ lệ thay đổi:", percent_change, "%")

avalanche_test()