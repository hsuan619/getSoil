#include <B_LUX_V30.h> 
B_LUX_V30 lux(4,5);//SDA=4; SCL=5 
void setup() {
  Serial.begin(115200);
  while (!Serial) ;;;
  Serial.print("OK!");
}

void loop() {
	Serial.println(lux.read());
	delay(1000);
}
