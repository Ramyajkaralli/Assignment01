/********Defining Motor & Encoder Pins**********/

const int motorPWMPin = 9;
const int motorDirectionPin1 = 10;
const int motorDirectionPin2 = 11;
const int encoderAPin = 4;
const int encoderBPin = 5;

/**********Initializing Variables************/

volatile int posi,pos = 0;

/***************Set Motor***************/

void setMotor(int dir, int pwmVal, int pwm, int in1, int in2){
  analogWrite(pwm,pwmVal);
  if(dir == 1){
    digitalWrite(motorDirectionPin1,HIGH);
    digitalWrite(motorDirectionPin2,LOW);
  }
  else if(dir == -1){
    digitalWrite(motorDirectionPin1,LOW);
    digitalWrite(motorDirectionPin2,HIGH);
  }
  else{ 
    digitalWrite(motorDirectionPin1,LOW);
    digitalWrite(motorDirectionPin2,LOW);
  }
}

/***************Read Encoder Input***************/

void readEncoder(){
  int b = digitalRead(encoderBPin);
  if(b > 0){
    posi++;
  }
  else{
    posi--;
  }
}

/***************Void Setup*****************/

void setup() {
  pinMode(encoderAPin, INPUT);
  pinMode(encoderBPin, INPUT);
//  attachInterrupt(digitalPinToInterrupt(encoderAPin),readEncoder,RISING);
  pinMode(motorPWMPin, OUTPUT);
  pinMode(motorDirectionPin1, OUTPUT);
  pinMode(motorDirectionPin2, OUTPUT);
  Serial.begin(115200);
  Serial.println("Enter Target posi: ");
}

/***************Void Loop*****************/

void loop() {
  if(Serial.available()){
    pos = Serial.parseInt();
    posi = pos;
    if( pos > 255 ){
      pos = 255;
    }
    else if(pos < -255){
      pos = -255;
    }
  }
/************motor direction*************/
  int dir = 1;
  if(pos<0){
    dir = -1;
  }
/************signal the motor*************/
  setMotor(dir,pos,motorPWMPin,motorDirectionPin1,motorDirectionPin2);
/************store previous error*************/
  Serial.print(dir);
  Serial.print(" ");
  Serial.print(pos);
  Serial.println();
 }
