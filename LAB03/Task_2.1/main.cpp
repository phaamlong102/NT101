#include <iostream>
#include <string>
#include <vector>
#include <openssl/bn.h>
#include <openssl/rand.h>
#include <openssl/rsa.h>
#include <openssl/evp.h>
using namespace std;

struct KeyPair {
    BIGNUM *key; // e (Public) hoặc d (Private)
    BIGNUM *n;

    KeyPair() : key(nullptr), n(nullptr) {}

    ~KeyPair() {
        BN_free(key);
        BN_free(n);
    }
};

void printBNDec(const string& label, BIGNUM *bn) {
    char *decStr = BN_bn2dec(bn);
    if (decStr != nullptr) {
        cout << label << decStr << endl;
        OPENSSL_free(decStr);
    }
}

void printBNHex(const string& label, BIGNUM *bn) {
    char *hexStr = BN_bn2hex(bn);
    cout << label << hexStr << endl;
    OPENSSL_free(hexStr);
}

void printBNString(const string& label, BIGNUM *bn) {
    int len = BN_num_bytes(bn);
    if (len == 0) {
        cout << label << "(Rong)" << endl;
        return;
    }
    unsigned char *buf = new unsigned char[len + 1];
    BN_bn2bin(bn, buf);
    buf[len] = '\0';
    cout << label << buf << endl;
    delete[] buf;
}

void printBNBase64(const string& label, BIGNUM *bn) {
    int len = BN_num_bytes(bn);
    if (len == 0) {
        cout << label << "(Rong)" << endl;
        return;
    }
    unsigned char *binBuffer = new unsigned char[len];
    BN_bn2bin(bn, binBuffer);

    int base64Len = 4 * ((len + 2) / 3);
    unsigned char *base64Output = new unsigned char[base64Len + 1];
    EVP_EncodeBlock(base64Output, binBuffer, len);

    cout << label << base64Output << endl;
    delete[] binBuffer;
    delete[] base64Output;
}

void generateRandomParams(BIGNUM *&p, BIGNUM *&q, BIGNUM *&e) {
    p = BN_new();
    q = BN_new();
    e = BN_new();

    BN_generate_prime_ex(p, 512, 1, nullptr, nullptr, nullptr);

    do {
        BN_generate_prime_ex(q, 512, 1, nullptr, nullptr, nullptr);
    } while (BN_cmp(p, q) == 0);

    BN_set_word(e, RSA_F4); // e = 65537
}

bool generateKeyPairs(BIGNUM *p, BIGNUM *q, BIGNUM *e,
                      KeyPair &pubKey, KeyPair &privKey) {
    BN_CTX *ctx = BN_CTX_new();

    BIGNUM *n        = BN_new();
    BIGNUM *p_minus1 = BN_new();
    BIGNUM *q_minus1 = BN_new();
    BIGNUM *one      = BN_new();
    BIGNUM *phi      = BN_new();
    BIGNUM *gcd      = BN_new();
    BIGNUM *d        = BN_new();

    BN_one(one);
    BN_mul(n, p, q, ctx);           // n = p * q
    BN_sub(p_minus1, p, one);       // p - 1
    BN_sub(q_minus1, q, one);       // q - 1
    BN_mul(phi, p_minus1, q_minus1, ctx); // phi = (p-1)*(q-1)

    BN_gcd(gcd, e, phi, ctx);
    if (BN_cmp(gcd, one) != 0) {
        cerr << "[LOI] gcd(e, phi) != 1 => e khong hop le voi cap p, q nay!\n";
        BN_free(n); BN_free(p_minus1); BN_free(q_minus1);
        BN_free(one); BN_free(phi); BN_free(gcd); BN_free(d);
        BN_CTX_free(ctx);
        return false; // Báo lỗi cho caller
    }

    BN_mod_inverse(d, e, phi, ctx);

    pubKey.key  = BN_dup(e);
    pubKey.n    = BN_dup(n);
    privKey.key = BN_dup(d);
    privKey.n   = BN_dup(n);

    BN_free(n); BN_free(p_minus1); BN_free(q_minus1);
    BN_free(one); BN_free(phi); BN_free(gcd); BN_free(d);
    BN_CTX_free(ctx);
    return true;
}

BIGNUM* rsaProcess(BIGNUM *inputMsg, const KeyPair& key) {
    if (BN_cmp(inputMsg, key.n) >= 0) {
        cerr << "[LOI] inputMsg >= n! RSA khong hop le. "
             << "Can chia nho thong diep thanh cac khoi truoc.\n";
        return nullptr;
    }

    BN_CTX *ctx  = BN_CTX_new();
    BIGNUM *result = BN_new();

    BN_mod_exp(result, inputMsg, key.key, key.n, ctx);

    BN_CTX_free(ctx);
    return result;
}

BIGNUM* base64ToBN(const string& b64) {
    string padded = b64;
    // Base64 cần có độ dài là bội số của 4, nếu thiếu phải bù bằng dấu '='
    while (padded.length() % 4 != 0) {
        padded += "=";
    }

    int len = padded.length();
    unsigned char* out = new unsigned char[len];

    // Giải mã Base64
    int outLen = EVP_DecodeBlock(out, (const unsigned char*)padded.c_str(), len);

    // EVP_DecodeBlock có thể sinh ra các byte 0 ở cuối do dấu padding '=', ta cần trừ đi
    int paddingCount = 0;
    if (len > 0 && padded[len - 1] == '=') paddingCount++;
    if (len > 1 && padded[len - 2] == '=') paddingCount++;

    BIGNUM *bn = BN_bin2bn(out, outLen - paddingCount, nullptr);
    delete[] out;
    return bn;
}

BIGNUM* binStringToBN(const string& binStr) {
    BIGNUM *bn = BN_new();
    BN_zero(bn);
    for (char c : binStr) {
        BN_lshift1(bn, bn); // Dịch trái 1 bit
        if (c == '1') {
            BN_add_word(bn, 1); // Cộng 1 nếu bit là '1'
        }
    }
    return bn;
}

int main() {
    BIGNUM *p = nullptr, *q = nullptr, *e = nullptr;
    BIGNUM *p1 = nullptr, *q1 = nullptr, *e1 = nullptr;
    BIGNUM *p2 = nullptr, *q2 = nullptr, *e2 = nullptr;
    BIGNUM *p3 = nullptr, *q3 = nullptr, *e3 = nullptr;

    string message = "PhamDucLong";
    BIGNUM *M = BN_new();
    BN_bin2bn((const unsigned char*)message.c_str(), message.length(), M);

    // -------------------------------------------------------
    cout << "===== TH p, q, e khong cho truoc: =====\n";
    generateRandomParams(p, q, e);
    printBNDec("So p ngau nhien la: ", p);
    printBNDec("So q ngau nhien la: ", q);
    printBNDec("So e la: ", e);
    cout << "Thong diep duoc ma hoa: " << message << "\n";

    KeyPair pbKey, pvKey;
    generateKeyPairs(p, q, e, pbKey, pvKey);
    printBNDec("Private key:", pvKey.key);
    printBNDec("Public key:", pbKey.key);

    cout << "Ma hoa bang public key:\n";
    BIGNUM *ciphertext = rsaProcess(M, pbKey);
    printBNHex("Thong diep sau khi ma hoa ", ciphertext);
    cout << "Giai ma bang private key:\n";
    BIGNUM *plaintext = rsaProcess(ciphertext, pvKey);
    printBNString("Thong diep sau khi giai ma: ", plaintext);
    BN_free(ciphertext);
    BN_free(plaintext);

    // -------------------------------------------------------
    cout << "\n===== 1. Xac dinh khoa cong khai PU va khoa rieng PR: =====\n";

    cout << "Truong hop p1=11, q1=17, e1=7:\n";
    BN_dec2bn(&p1, "11");
    BN_dec2bn(&q1, "17");
    BN_dec2bn(&e1, "7");
    KeyPair pbKey1, pvKey1;
    if (generateKeyPairs(p1, q1, e1, pbKey1, pvKey1)) {
        printBNDec("Private key1:", pvKey1.key);
        printBNDec("Public key1:", pbKey1.key);
    }

    cout << "Truong hop p2, q2, e2=17:\n";
    BN_dec2bn(&p2, "20079993872842322116151219");
    BN_dec2bn(&q2, "676717145751736242170789");
    BN_dec2bn(&e2, "17");
    KeyPair pbKey2, pvKey2;
    if (generateKeyPairs(p2, q2, e2, pbKey2, pvKey2)) {
        printBNDec("Private key2:", pvKey2.key);
        printBNDec("Public key2:", pbKey2.key);
    }

    cout << "Truong hop p3, q3, e3 (hex):\n";
    BN_hex2bn(&p3, "F7E75FDC469067FFDC4E847C51F452DF");
    BN_hex2bn(&q3, "E85CED54AF57E53E092113E62F436F4F");
    BN_hex2bn(&e3, "0D88C3");
    KeyPair pbKey3, pvKey3;
    if (generateKeyPairs(p3, q3, e3, pbKey3, pvKey3)) {
        printBNHex("Private key3:", pvKey3.key);
        printBNHex("Public key3:", pbKey3.key);
    }

    // -------------------------------------------------------
    cout << "\n===== 2. Ma hoa va giai ma khi M=5 dung p1, q1, e1: =====\n";

    BIGNUM *M1 = BN_new();
    BN_dec2bn(&M1, "5");

    cout << "Truong hop Encryption for Confidentiality\n";
    cout << "Ma hoa bang public key:\n";
    BIGNUM *ciphertext1 = rsaProcess(M1, pbKey1);
    printBNHex("Thong diep sau khi ma hoa ", ciphertext1);
    cout << "Giai ma bang private key:\n";
    BIGNUM *plaintext1 = rsaProcess(ciphertext1, pvKey1);
    printBNHex("Thong diep sau khi giai ma: ", plaintext1);

    // FIX: Giải phóng bộ nhớ TRƯỚC khi gán lại — tránh memory leak
    BN_free(ciphertext1);
    BN_free(plaintext1);

    cout << "Truong hop Encryption for Authentication\n";
    cout << "Ma hoa bang private key:\n";
    ciphertext1 = rsaProcess(M1, pvKey1);
    printBNHex("Thong diep sau khi ma hoa ", ciphertext1);
    cout << "Giai ma bang public key:\n";
    plaintext1 = rsaProcess(ciphertext1, pbKey1);
    printBNHex("Thong diep sau khi giai ma: ", plaintext1);

    BN_free(ciphertext1);
    BN_free(plaintext1);
    BN_free(M1);

    // -------------------------------------------------------
    cout << "\n===== 3. Ma hoa thong diep dai va xac dinh duoi dang Base64: =====\n";
    string longMsg = "The University of Information Technology";
    cout << "Thong diep goc: " << longMsg << endl;
    BIGNUM *M3 = BN_new();
    BN_bin2bn((const unsigned char*)longMsg.c_str(), longMsg.length(), M3);
    BIGNUM *M3mahoa = rsaProcess(M3, pbKey);
    printBNBase64("Ban ma (Base64) :", M3mahoa);
    BIGNUM *M3giaima = rsaProcess(M3mahoa, pvKey);
    printBNString("Ban ro: ", M3giaima);
    BN_free(M3); BN_free(M3mahoa); BN_free(M3giaima);

// -------------------------------------------------------
    cout << "\n===== 4. Tim ban ro cua cac ban ma voi 3 cap khoa =====\n";

    // Khởi tạo các chuỗi bản mã
    string c1_b64 = "raUcesUlOkx/8ZhgodMoo0Uul8sC20yXlQFevSu7W/FDxly0YRHMyXcHdD9PBvIT2aUft5fCQEGomiVVPv4I";
    string c2_hex = "C87F570FC4F699CEC24020C6F54221ABAB2CE0C3";
    string c3_b64 = "Z2BUSkJcg0w4XEpgm0JcMEXEQmBIVH6dYEpNTHpMHptMQ7NgTHlgQrNMQ2BKTQ==";
    string c4_bin = "001010000001010011111111101101110010111011001010111011000110011110111111001111110110100011001111001100001001010001010100111101010100110011101110111011110101101100000100";

    // Decode Base64 (Bản 1)
    unsigned char dec1[256];
    int len1 = EVP_DecodeBlock(dec1, (const unsigned char*)c1_b64.c_str(), c1_b64.length());
    BIGNUM *C1 = BN_bin2bn(dec1, len1, nullptr);

    // Decode Hex (Bản 2)
    BIGNUM *C2 = nullptr;
    BN_hex2bn(&C2, c2_hex.c_str());

    // Decode Base64 (Bản 3 có padding ==)
    unsigned char dec3[256];
    int len3 = EVP_DecodeBlock(dec3, (const unsigned char*)c3_b64.c_str(), c3_b64.length());
    BIGNUM *C3 = BN_bin2bn(dec3, len3 - 2, nullptr);

    // Decode Binary (Bản 4)
    BIGNUM *C4 = BN_new();
    BN_zero(C4);
    for (char c : c4_bin) {
        BN_lshift1(C4, C4);
        if (c == '1') BN_add_word(C4, 1);
    }

    BIGNUM* ciphertexts[4] = {C1, C2, C3, C4};
    string ctNames[4] = {"Ban ma 1 (Base64)", "Ban ma 2 (Hex)", "Ban ma 3 (Base64)", "Ban ma 4 (Binary)"};

    KeyPair* privKeys[3] = {&pvKey1, &pvKey2, &pvKey3};
    KeyPair* pubKeys[3]  = {&pbKey1, &pbKey2, &pbKey3};
    string keyNames[3] = {"Khoa 1", "Khoa 2", "Khoa 3"};

    for (int i = 0; i < 4; i++) {
        cout << "\n--- Thu giai ma " << ctNames[i] << " ---" << endl;
        for (int j = 0; j < 3; j++) {
            bool success = false;

            // 1. Thử giải mã bằng Private Key
            if (BN_cmp(ciphertexts[i], privKeys[j]->n) < 0) {
                BIGNUM* P_priv = rsaProcess(ciphertexts[i], *privKeys[j]);
                if (P_priv) {
                    cout << "  > Voi " << keyNames[j] << " (Private Key): ";
                    printBNString("", P_priv);
                    BN_free(P_priv);
                    success = true;
                }
            }

            // 2. Thử giải mã bằng Public Key (Cho trường hợp mã hóa Authentication)
            if (BN_cmp(ciphertexts[i], pubKeys[j]->n) < 0) {
                BIGNUM* P_pub = rsaProcess(ciphertexts[i], *pubKeys[j]);
                if (P_pub) {
                    cout << "  > Voi " << keyNames[j] << " (Public Key): ";
                    printBNString("", P_pub);
                    BN_free(P_pub);
                    success = true;
                }
            }

            // In thông báo nếu cả 2 khóa đều không thỏa mãn C < n
            if (!success) {
                cout << "  > Voi " << keyNames[j] << ": That bai (C >= n)" << endl;
            }
        }
    }

    BN_free(C1); BN_free(C2); BN_free(C3); BN_free(C4);
    BN_free(M);
    BN_free(p);  BN_free(q);  BN_free(e);
    BN_free(p1); BN_free(q1); BN_free(e1);
    BN_free(p2); BN_free(q2); BN_free(e2);
    BN_free(p3); BN_free(q3); BN_free(e3);

    return 0;
}