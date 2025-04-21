//Định vị địa chỉ blynk từ thiết bị 

#define BLYNK_TEMPLATE_ID "TMPL63b_PJpak"
#define BLYNK_TEMPLATE_NAME "Home"
#define BLYNK_AUTH_TOKEN "eKImRijv-XwHGJSAadlcjjiEWZGuZ0Pz"

//lệnh tắt các tính năng và tiết kiệm dung lượng
#define BLYNK_PRINT Serial

//khai báo các thư viện cần có để dùng blynk 
#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>

#include <DHT.h>

#include <HardwareSerial.h>


// Định nghĩa chân
#define DHTPIN 14         // Chân tín hiệu DHT11
#define DHTTYPE DHT11     // Loại cảm biến DHT
#define KY026_PIN 27      // Chân tín hiệu KY-026
#define PIR_PIN 35        // Chân tín hiệu PIR
#define BUZZER_PIN 25     // Chân tín hiệu buzzer


#define simSerial               Serial2
#define MCU_SIM_BAUDRATE        115200
#define MCU_SIM_TX_PIN              17
#define MCU_SIM_RX_PIN              16
#define MCU_SIM_EN_PIN              15

#define PHONE_NUMBER  "+84908994920"

DHT dht(DHTPIN, DHTTYPE);

//địa chỉ wifi, có thể nhận wifi phát từ điện thoại vẫn được
char ssid[] = "HCMUT1";
char pass[] = "diachi_bklms";

int stateWarning = 0;

BLYNK_WRITE(V0)
{
  int pinValue = param.asInt(); 

  if (stateWarning == 0)
  {
    if(pinValue == 1)
    {
      digitalWrite(BUZZER_PIN, HIGH);
      Serial.printf("bat coi");
    }
    if(pinValue == 0)
    {
      digitalWrite(BUZZER_PIN, LOW);
      Serial.printf("tat coi");
    }
  }
  else
  {
      Blynk.virtualWrite(V1, 0);
  }
}

void sim_at_wait()
{
    delay(100);
    while (simSerial.available()) 
    {
        Serial.write(simSerial.read());
    }
}

bool sim_at_cmd(String cmd)
{
    simSerial.println(cmd);
    sim_at_wait();
    return true;
}

bool sim_at_send(char c)
{
    simSerial.write(c);
    return true;
}

void sent_sms()
{
    sim_at_cmd("AT+CMGF=1");
    String temp = "AT+CMGS=\"";
    temp += (String)PHONE_NUMBER;
    temp += "\"";
    sim_at_cmd(temp);
    sim_at_cmd("Canh bao nguy hiem"); //có thể thay thế bằng từng trường hợp cụ thể như cháy hoặc trộm
    sim_at_send(0x1A);
    delay(5000);
}


void setup() 
{
  pinMode(MCU_SIM_EN_PIN,OUTPUT); 
  digitalWrite(MCU_SIM_EN_PIN,LOW);

  delay(20);
  Serial.begin(115200);
  Serial.println("\n\n\n\n-----------------------\nSystem started!!!!");

// tạo delay 8s để khơi động nguồn  
  delay(8000);
  simSerial.begin(MCU_SIM_BAUDRATE, SERIAL_8N1, MCU_SIM_RX_PIN, MCU_SIM_TX_PIN);

  // kiểm tra lệnh AT 
  sim_at_cmd("AT");

  // thông tin sản phẩm
  sim_at_cmd("ATI");

  // kiểm tra thẻ sim
  sim_at_cmd("AT+CPIN?");

  // kiểm tra chất lượng tín hiệu
  sim_at_cmd("AT+CSQ");

  sim_at_cmd("AT+CIMI");

  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);
  
  // Khởi tạo DHT11
  dht.begin();

  // Khởi tạo các chân
  pinMode(KY026_PIN, INPUT);
  pinMode(PIR_PIN, INPUT);
  pinMode(BUZZER_PIN, OUTPUT);

  // Tắt còi buzzer ban đầu
  digitalWrite(BUZZER_PIN, LOW);

  Serial.println("Hệ thống giám sát bắt đầu!");
}

void loop() 
{
    Blynk.run();
  // Đọc nhiệt độ và độ ẩm từ DHT11
  float temperature = dht.readTemperature();
  float humidity = dht.readHumidity();

  if (isnan(temperature) || isnan(humidity)) 
  {
    Serial.println("Khhong doc duoc du lieu tu DHT11!");
  } 
  else 
  {
    Serial.print("Nhiet do: ");
    Serial.print(temperature);
    Serial.print("°C, Đo am: ");
    Serial.print(humidity);
    Serial.println("%");
  }

  // Kiểm tra cảm biến lửa (KY-026)
  int fireDetected = digitalRead(KY026_PIN);

  // Kiểm tra cảm biến chuyển động (PIR)
  int motionDetected = digitalRead(PIR_PIN);
  Serial.print("Cam bien chuyen dong: ");
  Serial.println(motionDetected);

  Serial.print("Cam bien lua: ");
  Serial.println(fireDetected);
  

  // Kiểm tra và bật còi nếu phát hiện chuyển động hoặc lửa
  if (fireDetected == 1) 
  {
    Serial.println("Phat hien lua!");
    digitalWrite(BUZZER_PIN, HIGH); // Bật còi
    stateWarning = 1;
    sent_sms();
    delay(5000);
  } 
  else if (motionDetected == 1) 
  {
    Serial.println("Phat hien chuyen dong!");
    digitalWrite(BUZZER_PIN, HIGH); // Bật còi
    stateWarning = 1;
    sent_sms();
    delay(5000);
  } 
  else 
  {
    digitalWrite(BUZZER_PIN, LOW); // Tắt còi nếu không có sự kiện
  }

  delay(1000); // Đọc lại sau 1 giây
}
