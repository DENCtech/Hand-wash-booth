int sensor = 6; // ir sensor for soap
int sensor2 = 9; // ir sensor for dryer
int detect = 0;
int detect2 = 0;
int detect3;
int relay = 4; // 12v dc pump
int relay2 = 3; // dryer
int relay3 = 2; // water pump
int button = 7; // water tank mode of operation button HIGH for external  and LOW for internal
int know; // status of the button
int slLed = 10; // empty soap level LED
int wlLed = 11; // empty water level LED
int wwlLed = 12; // full waste water level LED
int extLed = 13; // external/internal water source LED
int sensor3 = A5; // Optocoupler
int status1 = 0; // status of the optocoupler
int buzzer = 5; // the buzzer
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
  pinMode(slLed, OUTPUT);
  pinMode(wlLed, OUTPUT);
  pinMode(wwlLed, OUTPUT);
  pinMode(extLed, OUTPUT);
  pinMode(buzzer, OUTPUT);
//  Servo1.attach(servoPin);
  digitalWrite(relay, HIGH);
  digitalWrite(relay2, HIGH);
  digitalWrite(relay3, HIGH);
//  digitalWrite(buzzer, LOW);
  delay(2000);
}

void loop() {
  soapLevel();
  waterLevel();
  wasteLevel();
  detect = analogRead(sensor);
  detect2 = digitalRead(sensor2);
  detect3 = analogRead(sensor3);
  know = digitalRead(button);
//  Serial.println(know);
  if(know == LOW && state > 0 && state1 > 0 && state2 < 1023){
    digitalWrite(extLed, HIGH);
    delay(100);
    if(detect3 < 1000){
      status1 = !status1;
       if(status1 == 1){
        Serial.println("On");
          digitalWrite(relay3, LOW);
          delay(500);
        }else{
          Serial.println("Off");
          digitalWrite(relay3, HIGH);
          delay(500);
        }
      }
      while(detect == 0){
        digitalWrite(relay, LOW);
        digitalWrite(buzzer, HIGH);
        delay(200);
        digitalWrite(buzzer, LOW);
        delay(200);
        detect = digitalRead(sensor);
        delay(10);
      }
      digitalWrite(relay, HIGH);
      while(detect2 == 0){
        digitalWrite(relay2, LOW);
        digitalWrite(buzzer, HIGH);
        delay(200);
        digitalWrite(buzzer, LOW);
        delay(200);
        detect2 = digitalRead(sensor2);
        delay(10);
      }
    digitalWrite(relay2, HIGH);
    
  }
  else{
    digitalWrite(extLed, LOW);
    delay(100);
    if(state > 0 && state1 > 0 && state2 < 1023){
      while(detect == 0){
        digitalWrite(relay, LOW);
        digitalWrite(buzzer, HIGH);
        delay(200);
        digitalWrite(buzzer, LOW);
        delay(200);
        detect = digitalRead(sensor);
        delay(10);
      }
      digitalWrite(relay, HIGH);
      while(detect2 == 0){
        digitalWrite(relay2, LOW);
        digitalWrite(buzzer, HIGH);
        delay(200);
        digitalWrite(buzzer, LOW);
        delay(200);
        detect2 = digitalRead(sensor2);
        delay(10);
      }
      digitalWrite(relay2, HIGH);
    }else{
      Serial.println("Error!!! Find fault!!!");
    }
    
  }
}
void soapLevel(){
  state = analogRead(soapL);
  if(state == 0){
    digitalWrite(slLed, HIGH);
  }
  else{
    digitalWrite(slLed, LOW);
  }
}
void waterLevel(){
  state1 = analogRead(waterL);
  if(state1 == 0){
    digitalWrite(wlLed, HIGH);
  }
  else{
    digitalWrite(wlLed, LOW);
  }
}
void wasteLevel(){
  state2 = analogRead(wasteL);
  if(state2 >= 1023){
    digitalWrite(wwlLed, HIGH);
  }
  else{
    digitalWrite(wwlLed, LOW);
  }
}
