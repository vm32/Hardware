#include <Arduino.h>
#include <mcp_can.h>
#include <mcp_can_dfs.h>

#define CANint 2
#define LED2 8
#define LED3 7

unsigned char len = 0;
unsigned char buf[8];
unsigned long ID = 0;
unsigned long line = 0;

MCP_CAN CAN0(17); // Set CS to pin 17

unsigned long time;
void setup() {
  Serial.begin(115200);
  
  while (!Serial) {
    Serial.print("I will wait here forever...");
      delay(1000);
  };
  
  pinMode(23, OUTPUT);
  digitalWrite(23, HIGH);

  pinMode(LED2, OUTPUT);
  pinMode(LED3, OUTPUT);
  pinMode(CANint, INPUT);
  digitalWrite(LED2, LOW);
  
  Serial.println("CAN init:");

  if (CAN0.begin(CAN_500KBPS) == CAN_OK) {
    Serial.println("Can Init Success");
  } else {
    Serial.println("Can Init Failed");
    while (1) {
      Serial.print("I will wait here forever...");
      delay(1000);
    }
  }

  Serial.println("Good to go!");
}

void loop() {
  time = millis();
  
  if(CAN_MSGAVAIL == CAN0.checkReceive() && line < 10000) {          // Check to see whether data is read
    CAN0.readMsgBufID(&ID, &len, buf);    // Read data
    
//Add this line back in if you want to filter traffic    if(ID == 1201) { //39
      line = line + 1;
      
      Serial.print(ID,HEX); // Output HEX Header
      Serial.print("\t");
      
      for(int i = 0; i<len; i++) { // Output 8 Bytes of data in Dec
        Serial.print(buf[i]);
        Serial.print("\t");
      }
      
      Serial.print(time); // Timestamp
      Serial.print("\t");
      Serial.println(line); // Line Number
//    }
  }
  delay(10);
}
