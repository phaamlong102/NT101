def F(right, subkey):
    # Hàm nội bộ kết hợp XOR và dịch bit (đã cho trong ảnh)
    return (right ^ subkey) & 0x0F

def feistel_round(L_in, R_in, subkey):
    """
    Triển khai một vòng Feistel:
    LE_i = RE_{i-1}
    RE_i = LE_{i-1} XOR F(RE_{i-1}, K_i)
    """
    L_out = R_in
    R_out = L_in ^ F(R_in, subkey)
    return L_out, R_out

def track_avalanche(msg, key):
    # Tách msg 8-bit thành 2 nửa 4-bit (L và R)
    L = (msg >> 4) & 0x0F
    R = msg & 0x0F
    
    # Tạo danh sách các khóa con (subkeys) như trong gợi ý
    subkeys = [
        key & 0x0F, 
        (key >> 4) & 0x0F, 
        (key + 1) & 0x0F, 
        (key + 2) & 0x0F
    ]
    
    print(f"Khoi tao: L={format(L, '04b')}, R={format(R, '04b')}")
    
    # Chạy 4 vòng mã hóa
    for i in range(4):
        L, R = feistel_round(L, R, subkeys[i])
        print(f"Vong {i+1}: L={format(L, '04b')}, R={format(R, '04b')}")
    
    # Kết hợp lại thành kết quả 8-bit cuối cùng
    return (L << 4) | R

# --- Chạy thử với 2 bản rõ khác nhau 1 bit ---
key_input = 0x12

print("--- Ma hoa M1 (0xAB) ---")
m1 = 0xAB
result1 = track_avalanche(m1, key_input)

print("\n--- Ma hoa M2 (0xAC) ---")
m2 = 0xAC
result2 = track_avalanche(m2, key_input)