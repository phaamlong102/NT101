Task 2.1:
    Mục đích: Chương trình mã hóa và giải mã theo thuật toán RSA. Chương trình có thể sinh ra cặp khóa ngẫu nhiên hoặc nhận một cặp khóa có trước để mã hóa/giải mã một thông điệp và in ra màn hình.
    Cách chạy: Chương trình dùng kiểu dữ liệu BIGNUM từ thư viện OpenSSL để lưu trữ các thông điệp và các cặp khóa vô cùng lớn. Để mã hóa/giải mã một thông điệp:
        B1: Truyền dữ liệu vào một biến BIGNUM thông qua các hàm hỗ trợ có sẵn của thư viện OpeanSSL tương ứng: dữ liệu dạng thập phân dùng hàm BN_dec2bn, thập lục dùng hàm BN_hex2bn
