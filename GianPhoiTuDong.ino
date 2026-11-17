#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <Servo.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);
Servo myServo;

// Khai báo chân kết nối phần cứng
const int RAIN_PIN  = A1;   // Cảm biến mưa (Chân AO)
const int LDR_PIN   = 2;    // Cảm biến ánh sáng LDR (Chân DO)
const int SERVO_PIN = 3;    // Servo SG90 (Chân PWM)

// Cấu hình tham số
const int THRESHOLD   = 500; // Dưới 500: CÓ MƯA | Trên 500: TẠNH MƯA
const int SPEED_DELAY = 25;  // ms/độ - thời gian trễ giữa mỗi bước quay (chống giật)

const int POS_OUT = 0;       // Góc phơi đồ ra (0 độ)
const int POS_IN  = 90;      // Góc thu đồ vào (90 độ)

int currentAngle = POS_IN;
int lastAction = -1;         // -1: Khởi tạo, 0: Thu đồ, 1: Phơi đồ
bool isAutoMode = true;      // true: Tự động theo cảm biến, false: Điều khiển thủ công từ Web

// Hàm điều khiển Servo quay chậm mượt mà
void moveServoSlow(int targetAngle) {
  if (currentAngle == targetAngle) return;
  if (currentAngle < targetAngle) {
    for (int pos = currentAngle; pos <= targetAngle; pos++) {
      myServo.write(pos);
      delay(SPEED_DELAY);
    }
  } else {
    for (int pos = currentAngle; pos >= targetAngle; pos--) {
      myServo.write(pos);
      delay(SPEED_DELAY);
    }
  }
  currentAngle = targetAngle;
}

void setup() {
  Serial.begin(9600);
  pinMode(LDR_PIN, INPUT);

  myServo.attach(SERVO_PIN);
  myServo.write(POS_IN); // Trạng thái ban đầu: thu đồ vào

  lcd.init();
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("Gian Phoi Tu Dong");
  lcd.setCursor(0, 1);
  lcd.print("Ket noi Web IoT ");
  delay(1200);
  lcd.clear();
}

void loop() {
  // 1. KIỂM TRA LỆNH TỪ GIAO DIỆN WEB (QUA SERIAL 9600 BAUD)
  if (Serial.available() > 0) {
    char cmd = Serial.read();
    if (cmd == 'A' || cmd == 'a') {
      isAutoMode = true;
      lastAction = -1; // Ép cập nhật lại theo cảm biến
      Serial.println("[WEB]: Da bat che do TU DONG");
    } else if (cmd == 'O' || cmd == 'o') {
      isAutoMode = false;
      Serial.println("[WEB]: Lenh THU CONG -> PHOI DO RA");
      lcd.setCursor(0, 1);
      lcd.print("[M] Web: Phoi ra");
      moveServoSlow(POS_OUT);
    } else if (cmd == 'I' || cmd == 'i') {
      isAutoMode = false;
      Serial.println("[WEB]: Lenh THU CONG -> THU DO VAO");
      lcd.setCursor(0, 1);
      lcd.print("[M] Web: Thu vao");
      moveServoSlow(POS_IN);
    }
  }

  // 2. ĐỌC CẢM BIẾN MÔI TRƯỜNG
  int rainValue = analogRead(RAIN_PIN);
  int ldrState = digitalRead(LDR_PIN);
  bool isRaining = (rainValue < THRESHOLD);
  bool isDark = (ldrState == HIGH);

  // In Telemetry cho giao diện Web đọc và vẽ biểu đồ thời gian thực
  Serial.print("Mua:"); Serial.print(rainValue);
  Serial.print("|AS:"); Serial.print(ldrState);
  Serial.print("|Goc:"); Serial.println(currentAngle);

  // 3. HIỂN THỊ HÀNG 1 LCD: CẢM BIẾN
  lcd.setCursor(0, 0);
  lcd.print(isRaining ? "M:MUA " : "M:TANH");
  lcd.setCursor(8, 0);
  lcd.print(isDark ? "| AS:TOI " : "| AS:SANG");

  // 4. LOGIC ĐIỀU KHIỂN TỰ ĐỘNG (CHỈ CHẠY KHI isAutoMode == true)
  if (isAutoMode) {
    if (!isRaining && !isDark) {
      if (lastAction != 1) {
        lastAction = 1;
        lcd.setCursor(0, 1);
        lcd.print("[A] Phoi do ra  ");
        moveServoSlow(POS_OUT);
      }
    } else {
      if (lastAction != 0) {
        lastAction = 0;
        lcd.setCursor(0, 1);
        lcd.print("[A] Thu do vao  ");
        moveServoSlow(POS_IN);
      }
    }
  }

  delay(200);
}
