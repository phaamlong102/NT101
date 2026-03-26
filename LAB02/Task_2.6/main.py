from sympy import randprime, isprime, prevprime

print("--- 1. TẠO VÀ KIỂM TRA SỐ NGUYÊN TỐ ---")

# Tạo ra số nguyên tố ngẫu nhiên có 8 bits, 16 bits, 64 bits
prime_8 = randprime(2**7, 2**8 - 1)
prime_16 = randprime(2**15, 2**16 - 1)
prime_64 = randprime(2**63, 2**64 - 1)

print(f"Số nguyên tố ngẫu nhiên 8-bit: {prime_8}")
print(f"Số nguyên tố ngẫu nhiên 16-bit: {prime_16}")
print(f"Số nguyên tố ngẫu nhiên 64-bit: {prime_64}")

# Xác định 10 số nguyên tố lớn nhất nhỏ hơn số nguyên tố Mersenne thứ 10
mersenne_10 = (2**89) - 1
print(f"\n10 số nguyên tố lớn nhất nhỏ hơn Mersenne thứ 10 ({mersenne_10}):")

current_num = mersenne_10
for i in range(10):
    # Hàm prevprime tìm số nguyên tố lớn nhất nhỏ hơn số truyền vào
    current_num = prevprime(current_num)
    print(f"{i+1}: {current_num}")

test_num = 12345678987654321
print(f"\nSố {test_num} có phải là số nguyên tố không? -> {isprime(test_num)}")


print("\n--- 2. TÌM ƯỚC SỐ CHUNG LỚN NHẤT (GCD) ---")

# Sử dụng thuật toán Euclid để tính GCD
def gcd_euclid(a, b):
    while b != 0:
        a, b = b, a % b
    return a

num1 = 98765432109876543210
num2 = 12345678901234567890
print(f"GCD của {num1} và {num2} là: {gcd_euclid(num1, num2)}")

print("\n--- 3. TÍNH LŨY THỪA MODULE ---")


def modular_exponentiation(a, x, p):
    result = 1
    a = a % p

    while x > 0:
        if x % 2 == 1:
            result = (result * a) % p
        a = (a * a) % p
        x = x // 2

    return result


a, x, p = 7, 400, 19
result = modular_exponentiation(a, x, p)

print(f"Kết quả của {a}^{x} mod {p} = {result}")