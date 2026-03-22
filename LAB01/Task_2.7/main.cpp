#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
using namespace std;

// Hàm mã hóa Rail Fence
string encryptRailFence(string text, int key) {
    if (key <= 1) return text;

    // Tạo mảng 2 chiều đại diện cho các hàng rào
    vector<string> rail(key);
    bool dir_down = false;
    int row = 0;

    // Duyệt qua từng ký tự và xếp vào hàng rào
    for (int i = 0; i < text.length(); i++) {
        rail[row].push_back(text[i]);

        // Đổi hướng đi (lên/xuống) khi chạm đỉnh hoặc đáy rào
        if (row == 0 || row == key - 1)
            dir_down = !dir_down;

        dir_down ? row++ : row--;
    }

    // Đọc từng hàng ghép lại thành bản mã
    string result = "";
    for (int i = 0; i < key; i++) {
        result += rail[i];
    }
    return result;
}

// Hàm giải mã Rail Fence
string decryptRailFence(string cipher, int key) {
    if (key <= 1) return cipher;

    // Tạo ma trận giả để đánh dấu vị trí zig-zag bằng dấu '*'
    vector<vector<char>> rail(key, vector<char>(cipher.length(), '\n'));
    bool dir_down = false;
    int row = 0, col = 0;

    for (int i = 0; i < cipher.length(); i++) {
        if (row == 0) dir_down = true;
        if (row == key - 1) dir_down = false;

        rail[row][col++] = '*';
        dir_down ? row++ : row--;
    }

    // Điền chữ cái từ bản mã vào các vị trí '*' trên từng hàng
    int index = 0;
    for (int i = 0; i < key; i++) {
        for (int j = 0; j < cipher.length(); j++) {
            if (rail[i][j] == '*' && index < cipher.length()) {
                rail[i][j] = cipher[index++];
            }
        }
    }

    // Đọc lại ma trận theo đường zig-zag để khôi phục bản rõ
    string result = "";
    row = 0; col = 0;
    for (int i = 0; i < cipher.length(); i++) {
        if (row == 0) dir_down = true;
        if (row == key - 1) dir_down = false;

        result += rail[row][col++];
        dir_down ? row++ : row--;
    }
    return result;
}

int main() {
    string file = "./input.txt";
    string plaintext = "";
    ifstream inputFile(file);
    if (!inputFile.is_open()) return 1;
    stringstream buffer;
    buffer << inputFile.rdbuf();
    plaintext = buffer.str();
    inputFile.close();
    int key = -1;
    cout <<"NHAP KEY > 0: ";
    while (key <= 0) {
        cin >> key;
    }

    cout << "=== RAIL FENCE CIPHER ===" << endl;
    cout << "DA NHAP VAO: " << plaintext << endl;
    cout << "Khoa (So hang rao): " << key << endl;
    int choice = 0;
    cout <<"0.MA HOA\n1.GIAI MA\nNHAP LUA CHON CUA BAN: ";
    cin >> choice;
    switch (choice) {
        case 0: {
            string ciphertext = encryptRailFence(plaintext, key);
            cout << "\nSau khi MA HOA: " << ciphertext << endl;
            break;
        }
        case 1: {
            string decryptedtext = decryptRailFence(plaintext, key);
            cout << "\nSau khi GIAI MA: " << decryptedtext << endl;
            break;
        }
    }



    return 0;
}