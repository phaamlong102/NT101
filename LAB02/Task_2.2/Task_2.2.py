from Crypto.Cipher import AES
from Crypto.Util import Counter

# 1. Khởi tạo dữ liệu (Dựa trên Scaffold code)
key = b'1234567890123456'  # Khóa 16 bytes (AES-128)
plaintext = b"UIT_LAB_UIT_LAB_UIT_LAB_UIT_LAB_"  # 32 bytes (gồm 2 khối giống hệt nhau)

# --- 2. AES-ECB ---
cipher_ecb = AES.new(key, AES.MODE_ECB)
ct_ecb = cipher_ecb.encrypt(plaintext)

# --- 3. AES-CBC ---
# Với CBC, ta cần một vector khởi tạo (IV) cố định 16 bytes theo yêu cầu
iv = b'0000000000000000' 
cipher_cbc = AES.new(key, AES.MODE_CBC, iv=iv)
ct_cbc = cipher_cbc.encrypt(plaintext)

# --- IN KẾT QUẢ ---
def print_blocks(name, ciphertext):
    print(f"\n[{name}]")
    # Tách kết quả thành từng khối 16-byte để so sánh
    block1 = ciphertext[:16].hex()
    block2 = ciphertext[16:].hex()
    print(f"Block 1: {block1}")
    print(f"Block 2: {block2}")
    if block1 == block2:
        print("=> NHẬN XÉT: Hai khối bản mã GIỐNG HỆT NHAU (Lộ cấu trúc!)")
    else:
        print("=> NHẬN XÉT: Hai khối bản mã KHÁC NHAU (Bảo mật tốt)")

print_blocks("AES-ECB", ct_ecb)
print_blocks("AES-CBC", ct_cbc)