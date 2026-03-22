// bai_1.1.cpp : Defines the entry point for the application.
//

#include "bai_1.1.h"

using namespace std;

// Hàm mã hóa/giải mã Caesar
// n là khóa (n dương để mã hóa, n âm để giải mã)
string caesarCipher(string text, int key) {
    string result = "";
    // Đảm bảo khóa nằm trong khoảng 0-25
    key = (key % 26 + 26) % 26;

    for (char& c : text) {
        if (isalpha(c)) {
            char base = isupper(c) ? 'A' : 'a';
            // Công thức: (ký tự - gốc + khóa) % 26 + gốc
            result += (char)((c - base + key) % 26 + base);
        }
        else {
            result += c; // Giữ nguyên khoảng trắng và ký tự đặc biệt
        }
    }
    return result;
}

// Hàm Brute-force: Thử tất cả 26 trường hợp
void bruteForce(string ciphertext) {
    cout << "\n--- KET QUA BRUTE-FORCE ---\n";
    for (int k = 1; k < 26; k++) {
        // Giải mã bằng cách dịch ngược lại (dùng khóa âm hoặc 26-k)
        string decrypted = caesarCipher(ciphertext, 26 - k);
        cout << "Key " << k << ": " << decrypted << endl;
    }
}

int main() {
    int choice;
    string text;
    int key;

    cout << "1. Ma hoa / Giai ma voi khoa cho truoc\n";
    cout << "2. Brute-force (Tim ban ro khi chi co ban ma)\n";
    cout << "Chon nhiem vu: ";
    cin >> choice;
    cin.ignore();

    if (choice == 1) {
        cout << "Nhap chuoi: ";
        getline(cin, text);
        cout << "Nhap khoa (so nguyen): ";
        cin >> key;

        string encrypted = caesarCipher(text, key);
        cout << "Ket qua: " << encrypted << endl;

    }
    else if (choice == 2) {
        cout << "Nhap ban ma (ciphertext): ";
        getline(cin, text);
        bruteForce(text);

        cout << "\nLuu y: Ban hay quan sat danh sach tren, dong nao co nghia "
            << "thi do la ket qua duy nhat can tim." << endl;
    }

    return 0;
}
