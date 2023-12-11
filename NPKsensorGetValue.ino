#include <SoftwareSerial.h>
#include <B_LUX_V30.h> 
#include<WiFi.h>
#include <HTTPClient.h>
const char ssid[]=""; //修改為你家的WiFi網路名稱
const char pwd[]=""; //修改為你家的WiFi密碼


B_LUX_V30 lux(4,5);//SDA=4; SCL=5 

SoftwareSerial mySerial(16, 17);  // RX, TX

void setup() {
  Serial.begin(9600);
  mySerial.begin(9600);
  connectWifi();
  while (!Serial) ;;;
  Serial.print("OK!");
}

void loop() {
  byte queryData[] = {0x01, 0x03, 0x00, 0x00, 0x00, 0x08, 0x44, 0x0C};
  byte receivedData[21];

  mySerial.write(queryData, sizeof(queryData));  // Send the query data to the NPK sensor
  delay(1000);  // Wait for 1 second

  if (mySerial.available() >= sizeof(receivedData)) {  // Check if there are enough bytes available to read
    mySerial.readBytes(receivedData, sizeof(receivedData));  // Read the received data into the receivedData array

    // Parse and print the received data in decimal format
    unsigned int soilTemperature = (receivedData[3] << 8) | receivedData[4];
    unsigned int soilHumidity = (receivedData[5] << 8) | receivedData[6];
    unsigned int soilSalty = (receivedData[7] << 8) | receivedData[8];
    unsigned int soilConductivity = (receivedData[9] << 8) | receivedData[10];
    unsigned int soilPH = (receivedData[11] << 8) | receivedData[12];
    unsigned int nitrogen = (receivedData[13] << 8) | receivedData[14];
    unsigned int phosphorus = (receivedData[15] << 8) | receivedData[16];
    unsigned int potassium = (receivedData[17] << 8) | receivedData[18];
    unsigned double light = lux.read();
    Serial.println("=======start from here==========");
    Serial.print("Soil Humidity: ");
    Serial.print((float)soilHumidity / 10.0);
    Serial.println("%");
    Serial.print("Soil Temperature: ");

    Serial.print((float)soilTemperature / 10.0);
        Serial.println("°C");
    Serial.print("Soil salty: ");
    Serial.print(soilSalty);
    Serial.println("μS/cm");
   
    Serial.print("Soil Conductivity: ");
    Serial.print(soilConductivity);
    Serial.println("μS/cm");
    Serial.print("Soil pH: ");
    Serial.println((float)soilPH / 100.0);
    Serial.print("Nitrogen: ");

    Serial.print(nitrogen);
    Serial.println("mg/kg");
    Serial.print("Phosphorus: ");
    Serial.print(phosphorus);
    Serial.println("mg/kg");
    Serial.print("Potassium: ");
    Serial.print(potassium);
    Serial.println("mg/kg");
	  Serial.print("light: ");
    Serial.println(light);

    delay(3000);
  }
}
void connectWifi(){
  WiFi.mode(WIFI_STA); //設置WiFi模式
  WiFi.begin(ssid,pwd); 

  Serial.print("WiFi connecting");

  //當WiFi連線時會回傳WL_CONNECTED，因此跳出迴圈時代表已成功連線
  while(WiFi.status()!=WL_CONNECTED){
    Serial.print(".");
    delay(500);   
  }

  Serial.println("");
  Serial.print("IP位址:");
  Serial.println(WiFi.localIP()); //讀取IP位址
  Serial.print("WiFi RSSI:");
  Serial.println(WiFi.RSSI()); //讀取WiFi強度
}
