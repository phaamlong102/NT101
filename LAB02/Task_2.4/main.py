import os
from Crypto.Cipher import AES
from Crypto.Util.Padding import pad
#1
dulieu = os.urandom(1000)
iv = os.urandom(16)
#2
key = os.urandom(16)
cipher = AES.new(key, AES.MODE_OFB, iv= iv)
padded = pad(dulieu, AES.block_size)
ciphertext = cipher.encrypt(padded)
#3
dulieuhong = bytearray(ciphertext)
dulieuhong[25] ^= 1
dulieuhong = bytes(dulieuhong)
#4
decipher = AES.new(key, AES.MODE_OFB, iv= iv)
dulieuhong = decipher.decrypt(dulieuhong)
block_size = 16
block_hong = 0
for i in range(0, len(padded), block_size):
    block_goc = padded[i:i + block_size]
    block_sau_ma_hoa = dulieuhong[i:i + block_size]
    if block_goc != block_sau_ma_hoa:
        block_hong += 1
print("So block da bi hong: ", block_hong)
