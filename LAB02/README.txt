LAB02 NT101.Q22.1
Thành viên:
24521010 Phạm Đức Long
24520961 Ngô Nhật Linh
#Task_2.1:
Mục đích: Mã hóa hai bản rõ M1 = 0xAB và M2 = 0xAC (chỉ khác nhau 1 bit cuối) bằng cấu trúc Feistel từ đó biết được sự khác biệt giữa qua từng vòng.
Cách chạy: Chương trình tự động in ra sự khác biệt của 2 bản rõ sau từng vòng mã hóa, sự thay đổi tăng dần.
#Task_2.2:
Mục đích: Mã hóa chuỗi văn bản có tính lặp lại cao: "UIT_LAB_UIT_LAB_UIT_LAB_UIT_LAB" bằng cả 2 chế độ AES-ECB và AES-CBC (với IV cố định) từ đó so sánh các khối 16-byte của bản mã.
Cách chạy: Chương trình sẽ tự động in ra 2 khối mã hóa của chuỗi văn bản qua của từng chế độ, và so sánh xem có sự khác nhau này trong 2 khối dó hay không.
#Task_2.3:
Mục đích: Mã hóa 2 văn bản khác nhau 1 chi tiết ký tự ở cuối, đếm số bit khác nhau và tỉ lệ thay đổi
Cách chạy: Chương  trình sẽ tự động in ra các thông tin, thay đổi văn bản và key bằng cách sửa các biến p1, p2 và key.
#Task_2.4:
Mục đích: Tạo ra dữ liệu ngẫu nhiên, mã hóa bằng AES, đảo một bit sau đó giải mã, đếm số block bị thay đổi với các mode như ECB, CBC, CFB, hoặc OFB.
#Task_2.5: So sánh độ mạnh và sự khác biệt của DES, Triple-DES (3DES) và AES. Và tại sao chúng ta không nên sử dụng mã hóa double-DES (2DES).
Cách chạy: Chương trình sẽ tự động in ra số khối bị lỗi, thay đổi mode bằng cách sửa mode trong các biến cipher và decipher.
#Task_2.6:
Mục đích:   • Tạo ra một số nguyên tố ngẫu nhiên có 8 bits, 16 bits, 64 bits
            • Xác định 10 số nguyên tố lớn nhất nhỏ hơn số nguyên tố Mersenne thứ 10.
            • Kiểm tra xem một số nguyên tùy ý nhỏ hơn 289 − 1 có phải là số nguyên tố hay không?
            • Xác định ước số chung lớn nhất (GCD) của 2 số nguyên lớn tùy ý
            • Tính toán lũy thừa theo module a^x mod p
Cách chạy: Chương trình sẽ tự in các thông tin, để thay đổi số nguyên lớn nhất và kiểm tra xem nó có là số nguyên tố hãy chỉnh sửa biến test_num. Để thay đổi 2 số nguyên a và b trong việc xác định GCD của chúng, sửa 2 biến num1 và num2. Để tính lũy thừa a^x mod p, chỉnh sửa các biến tương ứng a, x và p trong chương trình.
