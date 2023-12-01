ll#include <util/atomic.h>

/********Defining Motor & Encoder Pins**********/

const int motorPWMPin = 9;
const int motorDirectionPin1 = 10;
const int motorDirectionPin2 = 11;
const int encoderAPin = 4;
const int encoderBPin = 5;

/**********Initializing Variables************/

volatile int posi = 0;
long prevT = 0;
float eprev = 0;
float eintegral = 0;


/***************Void Setup*****************/

void setup() {
  pinMode(encoderAPin, INPUT);
  pinMode(encoderBPin, INPUT);
  attachInterrupt(digitalPinToInterrupt(encoderAPin),readEncoder,RISING);
  pinMode(motorPWMPin, OUTPUT);
  pinMode(motorDirectionPin1, OUTPUT);
  pinMode(motorDirectionPin2, OUTPUT);
  Serial.begin(115200);
  Serial.println("Enter Target posi: ");
}

/***************Void Loop*****************/

void loop() {
/**********set target position********/
//  int target = 250*sin(prevT/1e6);     //int target = 1200;
if(Serial.available()){
  int target = Serial.parseInt();
/******PID constants******/
  float kp = 1;
  float kd = 0.025;
  float ki = 0.0;
/*******time difference********/
  long currT = micros();
  float deltaT = ((float) (currT - prevT))/( 1.0e6 );
  prevT = currT;
/********Read the position in an atomic block to avoid a potential********/
  int pos = 0; 
  ATOMIC_BLOCK(ATOMIC_RESTORESTATE) {
    pos = posi;
  }
/********error calculation*********/
  int e = pos - target;
/************derivative************/
  float dedt = (e-eprev)/(deltaT);
/************integral*************/
   eintegral = eintegral + e*deltaT;
/************control signal*************/
  float u = kp*e + kd*dedt + ki*eintegral;
/************motor power*************/
  float pwr = fabs(u);
  if( pwr > 255 ){
    pwr = 255;
  }
/************motor direction*************/
  int dir = 1;
  if(u<0){
    dir = -1;
  }
/************signal the motor*************/
  setMotor(dir,pwr,motorPWMPin,motorDirectionPin1,motorDirectionPin2);
/************store previous error*************/
  eprev = e;

  Serial.print(target);
  Serial.print(" ");
  Serial.print(pos);
  Serial.println();
 }
}
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
