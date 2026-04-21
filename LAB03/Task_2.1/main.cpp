#include <iostream>
#include <string>
#include <gmpxx.h> // Thư viện xử lý số lớn GMP

using namespace std;

// Hàm tính lũy thừa modulo: result = (base^exp) mod mod_val
mpz_class rsa_mod_exp(const mpz_class& base, const mpz_class& exp, const mpz_class& mod_val) {
    mpz_class result;
    // mpz_powm là hàm tối ưu của GMP chuyên dùng cho tính a^b mod c
    mpz_powm(result.get_mpz_t(), base.get_mpz_t(), exp.get_mpz_t(), mod_val.get_mpz_t());
    return result;
}

int main() {
    cout << "=== NHIEM VU 2.1: THUAT TOAN RSA ===\n\n";

    // 1. Khai báo p1, q1, e1 (Hệ thập phân)
    // Truyền dạng chuỗi ("11") để mpz_class không bị giới hạn độ lớn
    mpz_class p1("11");
    mpz_class q1("17");
    mpz_class e1("7");

    // Tính n = p * q
    mpz_class n1 = p1 * q1;

    // Tính phi(n) = (p - 1) * (q - 1)
    mpz_class phi1 = (p1 - 1) * (q1 - 1);

    // Tính khóa riêng tư d = e^-1 mod phi(n)
    mpz_class d1;
    int res = mpz_invert(d1.get_mpz_t(), e1.get_mpz_t(), phi1.get_mpz_t());
    if (res == 0) {
        cout << "Loi: Khong ton tai nghich dao modulo (d)!" << endl;
        return 1;
    }

    cout << "1. Tinh khoa voi p1=11, q1=17, e1=7:" << endl;
    cout << " -> Public Key PU = {" << e1 << ", " << n1 << "}" << endl;
    cout << " -> Private Key PR = {" << d1 << ", " << n1 << "}" << endl;

    // 2. Mã hóa và giải mã M = 5
    mpz_class M("5");
    cout << "\n2. Xu ly ban ro M = 5:" << endl;

    // A. Mã hóa cho tính bảo mật (Confidentiality): C = M^e mod n
    mpz_class C_conf = rsa_mod_exp(M, e1, n1);
    cout << " -> [Bao mat] Ciphertext C = " << C_conf << endl;

    // Giải mã cho tính bảo mật: M = C^d mod n
    mpz_class M_dec_conf = rsa_mod_exp(C_conf, d1, n1);
    cout << " -> [Bao mat] Recovered M  = " << M_dec_conf << endl;

    cout << "-----------------------------------" << endl;

    // B. Mã hóa cho tính xác thực (Authentication): C = M^d mod n
    mpz_class C_auth = rsa_mod_exp(M, d1, n1);
    cout << " -> [Xac thuc] Ciphertext C = " << C_auth << endl;

    // Giải mã cho tính xác thực: M = C^e mod n
    mpz_class M_dec_auth = rsa_mod_exp(C_auth, e1, n1);
    cout << " -> [Xac thuc] Recovered M  = " << M_dec_auth << endl;

    return 0;
}