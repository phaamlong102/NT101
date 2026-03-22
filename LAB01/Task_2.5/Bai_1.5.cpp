// Bai_1.5.cpp : Defines the entry point for the application.
//

#include "Bai_1.5.h"

using namespace std;

/**
 * Hàm thực hiện mã hóa hoặc giải mã Vigenere
 * mode = 1: Mã hóa (Encryption)
 * mode = -1: Giải mã (Decryption)
 */
string vigenereCipher(string text, string key, int mode) {
    string result = "";
    string cleanKey = "";

    // 1. Chuẩn hóa khóa: Chỉ lấy các chữ cái và chuyển sang viết hoa
    for (char c : key) {
        if (isalpha((unsigned char)c)) cleanKey += toupper((unsigned char)c);
    }

    if (cleanKey.empty()) return "Loi: Khoa phai chua it nhat mot chu cai!";

    int keyIndex = 0;
    int keyLen = cleanKey.length();

    // 2. Duyệt qua từng ký tự trong bản rõ/bản mã
    for (char c : text) {
        if (isalpha((unsigned char)c)) {
            // Xác định gốc (A=65 hoặc a=97) để giữ nguyên định dạng hoa/thường
            char base = isupper((unsigned char)c) ? 'A' : 'a';

            // Lấy giá trị dịch chuyển từ khóa (0-25)
            int k = cleanKey[keyIndex % keyLen] - 'A';

            // Áp dụng công thức:
            // Ma hoa: (P + K) mod 26
            // Giai ma: (C - K + 26) mod 26
            int shift = (mode == 1) ? k : -k;
            char transformed = (char)((c - base + shift + 26) % 26 + base);

            result += transformed;

            // Chỉ tăng vị trí của khóa khi chúng ta xử lý một chữ cái
            keyIndex++;
        }
        else {
            // Giữ nguyên khoảng trắng, số, và dấu câu
            result += c;
        }
    }
    return result;
}

int main() {
    int choice;
    string text, key;

    cout << "--- CHUONG TRINH MA HOA VIGENERE ---\n";
    cout << "1. Ma hoa (Encrypt)\n";
    cout << "2. Giai ma (Decrypt)\n";
    cout << "Chon nhiem vu (1-2): ";
    cin >> choice;
    cin.ignore();

    cout << "Nhap khoa (Key): ";
    getline(cin, key);

    cout << "Nhap van ban: ";
    getline(cin, text);

    if (choice == 1) {
        string encrypted = vigenereCipher(text, key, 1);
        cout << "\n--- KET QUA MA HOA ---\n" << encrypted << endl;
    }
    else if (choice == 2) {
        string decrypted = vigenereCipher(text, key, -1);
        cout << "\n--- KET QUA GIAI MA ---\n" << decrypted << endl;
    }
    else {
        cout << "Lua chon khong hop le!" << endl;
    }

    return 0;
}