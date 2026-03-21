// bai_1.4.cpp : Defines the entry point for the application.
//

#include "bai_1.4.h"

using namespace std;

// Hàm chuẩn hóa chuỗi: Viết hoa, thay J bằng I, loại bỏ ký tự không phải chữ
string cleanText(string text) {
    string cleaned = "";
    for (char c : text) {
        if (isalpha(c)) {
            c = toupper(c);
            cleaned += (c == 'J') ? 'I' : c;
        }
    }
    return cleaned;
}

// Tạo ma trận 5x5 từ khóa
void generateMatrix(string key, char matrix[5][5]) {
    string combined = cleanText(key) + "ABCDEFGHIKLMNOPQRSTUVWXYZ"; // Không có J
    string finalKey = "";
    vector<bool> used(26, false);
    used['J' - 'A'] = true; // Đánh dấu J đã dùng (vì dùng chung với I)

    for (char c : combined) {
        if (!used[c - 'A']) {
            finalKey += c;
            used[c - 'A'] = true;
        }
    }

    cout << "\n--- Ma tran Playfair 5x5 ---\n";
    for (int i = 0; i < 25; i++) {
        matrix[i / 5][i % 5] = finalKey[i];
        cout << matrix[i / 5][i % 5] << " ";
        if ((i + 1) % 5 == 0) cout << endl;
    }
}

// Tìm vị trí hàng và cột của một ký tự trong ma trận
void find(char matrix[5][5], char c, int& row, int& col) {
    if (c == 'J') c = 'I';
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            if (matrix[i][j] == c) {
                row = i; col = j;
                return;
            }
        }
    }
}

// Xử lý bản rõ thành các cặp (digraphs)
string preparePlaintext(string text) {
    string p = cleanText(text);
    string prepared = "";
    for (int i = 0; i < p.length(); i++) {
        prepared += p[i];
        if (i + 1 < p.length()) {
            if (p[i] == p[i + 1]) prepared += 'X'; // Chèn X nếu 2 chữ cái giống nhau trong 1 cặp
            else {
                prepared += p[i + 1];
                i++;
            }
        }
    }
    if (prepared.length() % 2 != 0) prepared += 'X'; // Thêm X nếu độ dài lẻ
    return prepared;
}

// Hàm thực hiện mã hóa/giải mã
// mode = 1: mã hóa, mode = -1: giải mã
string transform(string text, char matrix[5][5], int mode) {
    string result = "";
    for (int i = 0; i < text.length(); i += 2) {
        int r1, c1, r2, c2;
        find(matrix, text[i], r1, c1);
        find(matrix, text[i + 1], r2, c2);

        if (r1 == r2) { // Cùng hàng: dịch phải (mã hóa) hoặc trái (giải mã)
            result += matrix[r1][(c1 + mode + 5) % 5];
            result += matrix[r2][(c2 + mode + 5) % 5];
        }
        else if (c1 == c2) { // Cùng cột: dịch xuống (mã hóa) hoặc lên (giải mã)
            result += matrix[(r1 + mode + 5) % 5][c1];
            result += matrix[(r2 + mode + 5) % 5][c2];
        }
        else { // Hình chữ nhật: tráo đổi cột
            result += matrix[r1][c2];
            result += matrix[r2][c1];
        }
    }
    return result;
}

int main() {
    string key, text;
    char matrix[5][5];
    int choice;

    cout << "1. Ma hoa\n2. Giai ma\nChon: ";
    cin >> choice;
    cin.ignore();

    cout << "Nhap khoa: ";
    getline(cin, key);
    generateMatrix(key, matrix);

    cout << "Nhap van ban: ";
    getline(cin, text);

    if (choice == 1) {
        string prepare = preparePlaintext(text);
        cout << "Ban ro sau khi xu ly: " << prepare << endl;
        cout << "Ket qua ma hoa: " << transform(prepare, matrix, 1) << endl;
    }
    else {
        string cleane = cleanText(text);
        cout << "Ket qua giai ma: " << transform(cleane, matrix, -1) << endl;
    }

    return 0;
}