int sensor = 7; // ir sensor for soap
int sensor2 = 8; // ir sensor for dryer
int sensor3 = 9; // ir sensor for water
int detect = 0;
int detect2 = 0;
int detect3;
int relay = 4; // 12v dc pump
int relay2 = 3; // dryer
int relay3 = 2; // water pump
int relay4 = 5; // solenoid valve
int button = 6; // water tank mode of operation button HIGH for external  and LOW for internal
int know; // status of the button
int powerLed = 10; // System power LED
int wlLed = 11; // empty water level LED
int wwlLed = 12; // full waste water level LED
int extLed = 13; // external/internal water source LED
int state,state1,state2; // level sensor state
int soapL = A2; // soap level monitor
int waterL = A3; // water level monitor
int wasteL= A4; // waste level monitor

void setup() {
  Serial.begin(9600);
  pinMode(sensor, INPUT);
  pinMode(sensor2, INPUT);
  pinMode(sensor3, INPUT);
  pinMode(button, INPUT);
  pinMode(relay, OUTPUT);
  pinMode(relay2, OUTPUT);
  pinMode(relay3, OUTPUT);
  pinMode(relay4, OUTPUT);
  
  pinMode(powerLed, OUTPUT);
  pinMode(wlLed, OUTPUT);
  pinMode(wwlLed, OUTPUT);
  pinMode(extLed, OUTPUT);
  pinMode(soapL, INPUT);
  pinMode(waterL, INPUT);
  pinMode(wasteL, INPUT);
  digitalWrite(powerLED, HIGH);
  digitalWrite(relay, HIGH);
  digitalWrite(relay2, HIGH);
  digitalWrite(relay3, HIGH);
  digitalWrite(relay4, HIGH);
  delay(1000);
}

void loop() {
//  soapLevel();
  waterLevel();
  wasteLevel();
  detect = digitalRead(sensor);
  detect2 = digitalRead(sensor2);
  detect3 = digitalRead(sensor3);
  know = digitalRead(button);
  if(know == LOW){
    digitalWrite(extLed, HIGH);
    digitalWrite(relay4, HIGH);
    delay(100);
//    if(detect3 < 1000){
//      status1 = !status1;
//       if(status1 == 1){
//        Serial.println("On");
//          digitalWrite(relay3, LOW);
//          delay(500);
//        }else{
//          Serial.println("Off");
//          digitalWrite(relay3, HIGH);
//          delay(500);
//        }
//      }
    while(detect3 == 0){
      digitalWrite(relay3, LOW);
      detect3 = digitalRead(sensor3);
      delay(10);
    }
    digitalWrite(relay3, HIGH);
    while(detect == 0){
      digitalWrite(relay, LOW);
      detect = digitalRead(sensor);
      delay(10);
    }
    digitalWrite(relay, HIGH);
    while(detect2 == 0){
      digitalWrite(relay2, LOW);
      detect2 = digitalRead(sensor2);
      delay(10);
    }
    digitalWrite(relay2, HIGH);   
  }
  else{
    digitalWrite(extLed, LOW);
    digitalWrite(relay4, LOW);
    delay(100);
    while(detect == 0){
      digitalWrite(relay, LOW);
      detect = digitalRead(sensor);
      delay(10);
    }
    digitalWrite(relay, HIGH);
    while(detect2 == 0){
      digitalWrite(relay2, LOW);
      detect2 = digitalRead(sensor2);
      delay(10);
    }
    digitalWrite(relay2, HIGH);
    while(detect3 == 0){
      digitalWrite(relay3, LOW);
      detect3 = digitalRead(sensor3);
      delay(10);
    }
    digitalWrite(relay3, HIGH);
//    Serial.println("Error!!! Find fault!!!");
  }   
}
//void soapLevel(){
//  state = analogRead(soapL);
//  if(state <= 0){
//    digitalWrite(slLed, HIGH);
//    state = analogRead(soapL);
//    delay(10);
//  }else{
//    digitalWrite(slLed, LOW);
//  }
//  
//}
void waterLevel(){
  state1 = analogRead(waterL);
  if(state1 <= 0){
    digitalWrite(wlLed, HIGH);
    state1 = analogRead(waterL);
    delay(10);
  }else{
    digitalWrite(wlLed, LOW);
  }
}
void wasteLevel(){
  state2 = analogRead(wasteL);
  if(state2 >= 1023){
    digitalWrite(wwlLed, HIGH);
    state2 = analogRead(wasteL);
    delay(10);
  }else{
    digitalWrite(wwlLed, LOW);
  }
}
