Task 2.1:
    Mục đích: Chương trình mã hóa và giải mã theo thuật toán RSA. Chương trình có thể sinh ra cặp khóa ngẫu nhiên hoặc nhận một cặp khóa có trước để mã hóa/giải mã một thông điệp và in ra màn hình.
    Cách chạy: Chương trình dùng kiểu dữ liệu BIGNUM từ thư viện OpenSSL để lưu trữ các thông điệp và các cặp khóa vô cùng lớn. Để mã hóa/giải mã một thông điệp:
        B1: Truyền dữ liệu vào một biến con trỏ BIGNUM thông qua các hàm hỗ trợ có sẵn của thư viện OpenSSL tương ứng: dữ liệu dạng thập phân dùng hàm BN_dec2bn, thập lục dùng hàm BN_hex2bn... hoặc đối với các dữ liệu đặc biệt như ở câu 4: base64, binary ở dạng chuỗi văn bản thì dùng các hàm được cài đặt như base64ToBN, binStringToBN để nhận thông điệp
        B2: Dùng hàm generateKeyPairs để sinh ra một cặp khóa public key và private key từ các số p, q, e. Nếu không có sẵn các số này thì có thể dùng hàm generateRandomParams để sinh ra một bộ ba số p, q, e hợp lệ.
        B3: Dùng hàm rsaProcess để mã hóa/giải mã thông điệp. Truyền vào hàm thông điệp (thông qua một con trỏ BIGNUM) và một KeyPair.
        B4: Có thể in ra nội dung đã mã hóa, giải mã thông qua các hàm printBNDec (in dưới hệ thập phân), printBNHex (hệ thập lục), printBNString (một chuỗi) hoặc dưới dạng base64 qua hàm printBNBase64.
