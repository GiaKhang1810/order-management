# Online Order Management

Project quản lý đơn đặt hàng trực tuyến sử dụng C++ và Queue được triển khai bằng Linked List.

## 1. Cấu trúc thư mục

```text
order-management/
├── include/
│   ├── Manager.hpp
│   ├── Order.hpp
│   ├── Queue.hpp
│   └── Statistics.hpp
│
├── source/
│   ├── Manager.cpp
│   ├── Order.cpp
│   ├── Queue.cpp
│   └── Statistics.cpp
│
├── main.cpp
├── .gitignore
└── README.md
```

## 2. Cài đặt và kiểm tra môi trường

### Windows - MinGW-w64

Cách đơn giản là cài **MinGW-w64** thông qua MSYS2.

1. Cài MSYS2 từ trang chủ:
   https://www.msys2.org/

2. Mở **MSYS2 UCRT64** và cập nhật hệ thống:

```bash
pacman -Syu
```

Nếu MSYS2 yêu cầu đóng cửa sổ, hãy đóng lại, mở lại **MSYS2 UCRT64**, rồi chạy tiếp:

```bash
pacman -Su
```

3. Cài GCC/G++:

```bash
pacman -S mingw-w64-ucrt-x86_64-gcc
```

4. Kiểm tra:

```bash
g++ --version
```

### Thêm G++ vào PATH trên Windows

Nếu lệnh `g++` chỉ chạy trong MSYS2 nhưng không chạy trong Command Prompt / PowerShell, cần thêm thư mục chứa `g++.exe` vào biến môi trường `Path`.

Với MSYS2 UCRT64, thư mục thường là:

```text
C:\msys64\ucrt64\bin
```

Các bước:

1. Nhấn `Win + S`, tìm **Environment Variables**.
2. Chọn **Edit the system environment variables**.
3. Chọn **Environment Variables...**
4. Trong phần **User variables** hoặc **System variables**, chọn `Path`.
5. Chọn **Edit** → **New**.
6. Thêm:

```text
C:\msys64\ucrt64\bin
```

7. Nhấn **OK** để lưu.
8. Đóng Command Prompt / PowerShell đang mở và mở lại.
9. Kiểm tra:

```bash
g++ --version
```

Nếu hiện phiên bản GCC/G++, môi trường đã sẵn sàng.

## 3. Biên dịch project

Mở Terminal tại thư mục `order-management/`.

Khuyến nghị dùng:

```bash
g++ -std=c++17 -Wall -Wextra -pedantic main.cpp source/*.cpp -Iinclude -o main
```

Giải thích:

```text
-std=c++17
    → sử dụng chuẩn C++17

-Wall
    → bật các cảnh báo phổ biến

-Wextra
    → bật thêm cảnh báo

-pedantic
    → kiểm tra chặt chẽ theo chuẩn C++

main.cpp
    → file chương trình chính

source/*.cpp
    → biên dịch tất cả file .cpp trong source/

-Iinclude
    → cho compiler tìm các file .hpp trong include/

-o main
    → tên file chương trình sau khi biên dịch
```

## 4. Chạy chương trình

### Windows

```bash
.\main.exe
```

### Linux / macOS

```bash
./main
```

## 5. Biên dịch bản Debug

Nếu cần debug:

```bash
g++ -std=c++17 -Wall -Wextra -pedantic -g main.cpp source/*.cpp -Iinclude -o main
```

## 6. Quy trình làm việc

```text
Chỉnh sửa code
      ↓
Biên dịch
      ↓
Nếu không có lỗi
      ↓
Chạy chương trình
      ↓
Kiểm tra kết quả
```

Lệnh biên dịch:

```bash
g++ -std=c++17 -Wall -Wextra -pedantic main.cpp source/*.cpp -Iinclude -o main
```

Lệnh chạy trên Windows:

```bash
.\main.exe
```

## 7. Một số lỗi thường gặp

### Không tìm thấy file `.hpp`

Ví dụ:

```text
fatal error: Order.hpp: No such file or directory
```

Kiểm tra:

```text
include/
└── Order.hpp
```

và đảm bảo lệnh biên dịch có:

```bash
-Iinclude
```

### `undefined reference`

Đảm bảo tất cả file `.cpp` trong `source/` được biên dịch:

```bash
source/*.cpp
```
