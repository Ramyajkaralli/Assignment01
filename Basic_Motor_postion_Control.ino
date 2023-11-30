/********Defining Motor & Encoder Pins**********/

const int motorPWMPin = 9;
const int motorDirectionPin1 = 10;
const int motorDirectionPin2 = 11;
const int encoderAPin = 4;
const int encoderBPin = 5;

/***************Void Setup*****************/

void setup() {
  pinMode(motorPWMPin, OUTPUT);
  pinMode(motorDirectionPin1, OUTPUT);
  pinMode(motorDirectionPin2, OUTPUT);
  pinMode(encoderAPin, INPUT);
  pinMode(encoderBPin, INPUT);
  Serial.begin(115200);
}

/***************Void Loop*****************/

void loop() {
  if(Serial.available()){
      int SetSpeed = Serial.parseInt();
//      Serial.println(SetSpeed);
      if(SetSpeed >= 0 && SetSpeed <= 255){
        analogWrite(motorPWMPin,SetSpeed);
        ForwardMove();
//        Serial.print("Set Speed = ");
//        Serial.println(SetSpeed); 
      }
      else if(SetSpeed >= -255 && SetSpeed <= 0){
        analogWrite(motorPWMPin,SetSpeed);
        BackwardMove();
//        Serial.print("Set Speed = ");
//        Serial.println(SetSpeed); 
      }
   }
}

/***************Move Motor in Forward Direction***************/

void ForwardMove(){
  digitalWrite(motorDirectionPin1,HIGH);
  digitalWrite(motorDirectionPin2,HIGH);
//  Serial.println("Forward Direction");
}

/***************Move Motor in Backward Direction**************/

void BackwardMove(){
  digitalWrite(motorDirectionPin1,LOW);
  digitalWrite(motorDirectionPin2,LOW);
//  Serial.println("Backward Direction");
}
