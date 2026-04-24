cmake_minimum_required(VERSION 4.1)
project(Task_2_1)

set(CMAKE_CXX_STANDARD 20)

add_executable(Task_2_1 main.cpp)
# Tìm gói OpenSSL có sẵn trên hệ thống
find_package(OpenSSL REQUIRED)

# Link thư viện OpenSSL::Crypto vào target executable của bạn
target_link_libraries(Task_2_1 PRIVATE OpenSSL::Crypto)