#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <algorithm>
#include <cctype>
#include <fstream>
#include <sstream>

using namespace std;

// Hàm đếm n-gram (1 cho ký tự đơn, 2 cho bigram, 3 cho trigram)
void printNgrams(const string& text, int n, int topK, const string& title) {
    map<string, int> freq;
    string cleanText = "";
    int totalCount = 0;

    // Lọc lấy toàn bộ chữ cái và chuyển thành viết hoa
    for (char c : text) {
        if (isalpha(c)) {
            cleanText += toupper(c);
        }
    }

    if (cleanText.length() < n) return;

    // Trượt qua chuỗi để đếm các cụm n ký tự
    for (size_t i = 0; i <= cleanText.length() - n; ++i) {
        freq[cleanText.substr(i, n)]++;
        totalCount++;
    }

    // Chuyển sang vector để sort theo tần suất giảm dần
    vector<pair<string, int>> sortedFreq(freq.begin(), freq.end());
    sort(sortedFreq.begin(), sortedFreq.end(), [](const pair<string, int>& a, const pair<string, int>& b) {
        return a.second > b.second;
    });

    cout << "\n--- " << title << " ---" << (n == 1 ? " (Tổng: " + to_string(totalCount) + ")" : "") << "\n";
    int limit = min(topK, (int)sortedFreq.size());
    for (int i = 0; i < limit; ++i) {
        cout << sortedFreq[i].first << ": " << sortedFreq[i].second;
        if (n == 1) { // Chỉ in phần trăm cho ký tự đơn
            cout << " (" << (sortedFreq[i].second * 100.0 / totalCount) << "%)";
        }
        cout << "\n";
    }
}

// Hàm áp dụng giả thuyết (keyMap) vào văn bản
string applySubstitution(const string& cipher, const map<char, char>& keyMap) {
    string result = "";
    for (char c : cipher) {
        if (isalpha(c)) {
            char upperC = toupper(c);
            // Nếu ký tự này đã có trong từ điển giả thuyết
            if (keyMap.count(upperC)) {
                result += tolower(keyMap.at(upperC)); // In thường để biết là đã giải mã
            } else {
                result += upperC; // Giữ in hoa cho ký tự chưa biết
            }
        } else {
            result += c; // Giữ nguyên dấu câu, khoảng trắng
        }
    }
    return result;
}

int main() {
    // Copy nội dung file 2.2_cipher_text paste vào đây (ví dụ minh họa vài chữ)
    string file = "./input.txt";
    string ciphertext = "";
    ifstream inputFile(file);
    if (!inputFile.is_open()) return 1;

    stringstream buffer;
    buffer << inputFile.rdbuf();
    ciphertext = buffer.str();
    inputFile.close();
    map<char, char> currentKey;
    char cipherChar, plainChar;

    cout << "=== TOOL HỖ TRỢ PHÁ MÃ MONO-ALPHABETIC ===" << endl;

    while (true) {
        // Gọi hàm đếm: in toàn bộ ký tự đơn (top 26), top 5 cặp và top 5 bộ ba
        printNgrams(ciphertext, 1, 26, "TẦN SUẤT KÝ TỰ (UNIGRAM)");
        printNgrams(ciphertext, 2, 5, "TOP 5 CẶP KÝ TỰ (BIGRAM)");
        printNgrams(ciphertext, 3, 5, "TOP 5 BỘ BA KÝ TỰ (TRIGRAM)");
        cout << "\n--- VĂN BẢN HIỆN TẠI ---\n";
        cout << applySubstitution(ciphertext, currentKey) << "\n";
        cout << "------------------------\n";

        cout << "\nNhập ký tự bản MÃ muốn thay thế (hoặc '0' để thoát): ";
        cin >> cipherChar;
        if (cipherChar == '0') break;

        cout << "Đoán nó là ký tự bản RÕ nào: ";
        cin >> plainChar;

        // Lưu vào map (chuẩn hóa: key là HOA, value là thường)
        currentKey[toupper(cipherChar)] = tolower(plainChar);
    }

    return 0;
}
