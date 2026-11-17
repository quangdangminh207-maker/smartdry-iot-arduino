# 🧺 SmartDry IoT - Giàn Phơi Quần Áo Thông Minh Tự Động

Dự án **Hệ thống Giàn Phơi Quần Áo Thông Minh (Smart Drying Rack)** sử dụng vi điều khiển **Arduino Uno**, tích hợp cảm biến mưa, cảm biến ánh sáng LDR, màn hình LCD 16x2 I2C, động cơ Servo SG90 và **Giao diện Web Dashboard điều khiển trực tiếp qua Web Serial API** có tính năng xác thực tài khoản quản trị.

---

## 🌟 Tính Năng Nổi Bật

1. **Vận hành Tự Động (Auto Mode):**
   * **Phơi đồ ra (Góc 0°):** Khi trời tạnh ráo (`Mưa >= 500`) **VÀ** trời sáng (`LDR = LOW`).
   * **Thu đồ vào (Góc 90°):** Khi phát hiện trời mưa (`Mưa < 500`) **HOẶC** khi trời tối ban đêm (`LDR = HIGH`).
2. **Điều khiển Từ Xa Qua Web (Manual Mode):**
   * Bấm **`☀️ PHƠI ĐỒ RA`** hoặc **`🏠 THU ĐỒ VÀO`** trực tiếp trên trang web.
   * Chuyển đổi linh hoạt giữa chế độ **Tự Động (Auto)** và **Thủ Công (Manual)**.
   * Thanh trượt điều chỉnh góc mở của động cơ Servo tùy ý ($0^\circ \leftrightarrow 90^\circ$).
3. **Bảo Mật Bằng Tên Đăng Nhập & Mật Khẩu:**
   * Bảng điều khiển web tự động khóa an toàn khi chưa đăng nhập.
   * Tài khoản mặc định: `admin` / Mật khẩu: `123`.
4. **Kết Nối Trực Tiếp Qua Web Serial API:**
   * Cắm cáp USB nối Arduino với máy tính, mở file `index.html` trên Google Chrome/Edge và bấm **"Kết nối Arduino"** là điều khiển được ngay mà không cần cài thêm phần mềm trung gian.
5. **Mô Phỏng Trực Quan Trên Wokwi:**
   * Đầy đủ file cấu hình mạch `diagram.json` để chạy mô phỏng 100% online trên Wokwi.

---

## 🔌 Sơ Đồ Đấu Nối Phần Cứng (Hardware Pinout)

| Linh Kiện | Chân Linh Kiện | Chân Trên Arduino Uno | Ghi Chú |
| :--- | :--- | :--- | :--- |
| **Màn hình LCD 16x2 I2C** | GND / VCC | GND / 5V | Nguồn cấp |
| | SDA | **A4** | Đường truyền dữ liệu I2C |
| | SCL | **A5** | Xung nhịp I2C |
| **Cảm biến Mưa** | AO (Analog Out) | **A1** | Đọc giá trị độ ẩm |
| | VCC / GND | 5V / GND | Nguồn |
| **Cảm biến Ánh sáng LDR** | DO (Digital Out) | **D2** | Mức 0 (Sáng) / 1 (Tối) |
| | VCC / GND | 5V / GND | Nguồn |
| **Động cơ Servo SG90** | Dây Cam (PWM) | **D3** | Chân điều khiển góc |
| | Dây Đỏ (VCC) / Dây Nâu (GND) | 5V / GND | Cấp nguồn Servo |

---

## 📁 Cấu Trúc Thư Mục Dự Án

```text
gian-phoi-iot/
├── GianPhoiTuDong.ino   # Mã nguồn Arduino C++ điều khiển hệ thống
├── index.html           # Giao diện Web Dashboard điều khiển (HTML5, Tailwind, Web Serial)
├── diagram.json         # Sơ đồ mạch linh kiện và dây nối trên Wokwi
├── libraries.txt        # Danh sách thư viện cần thiết (LiquidCrystal I2C, Servo)
└── README.md            # Tài liệu hướng dẫn sử dụng chi tiết
```

---

## 🚀 Hướng Dẫn Sử Dụng

### Cách 1: Chạy mô phỏng online trên Wokwi
1. Mở trang [Wokwi Arduino Uno](https://wokwi.com/projects/new/arduino-uno).
2. Dán nội dung file `GianPhoiTuDong.ino` vào tab **sketch.ino**.
3. Dán nội dung file `diagram.json` vào tab **diagram.json**.
4. Thêm thư viện `LiquidCrystal I2C` vào tab **Library Manager**.
5. Bấm nút **Play (▶️)** để bắt đầu mô phỏng!

### Cách 2: Nạp vào mạch thật và điều khiển qua Web
1. Mở file `GianPhoiTuDong.ino` bằng **Arduino IDE**.
2. Chọn Board **Arduino Uno** và cổng COM tương ứng, sau đó bấm **Upload**.
3. Mở file `index.html` bằng trình duyệt **Google Chrome** hoặc **Microsoft Edge**.
4. Bấm nút **"🔑 Đăng nhập"** (Tài khoản: `admin` / Mật khẩu: `123`).
5. Bấm nút **"🔌 Kết nối Arduino"**, chọn cổng COM vừa cắm mạch.
6. Thưởng thức bảng điều khiển thông minh với đồ thị và phản hồi thời gian thực!

---

## 👤 Tác Giả & Bản Quyền
* Tác giả: **Quang Nguyễn**
* Dự án mã nguồn mở phục vụ mục đích học tập và nghiên cứu công nghệ IoT / Nhúng.
