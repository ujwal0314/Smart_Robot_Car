//----------------------------SMART_CAR_Project---------------------------------------//

#include <Servo.h>
#include <AFMotor.h>
//-----------------------B------------------------------//
char value;
int speedCar=255;
boolean lightFront = false;
boolean lightBack = false;
boolean S_light = false;

//------------------------O-----------------------------//
int distance;
int Left;
int Right;
int L = 0;
int R = 0;
int L1 = 0;
int R1 = 0;

//----------Defines----------------//

#define Echo A0
#define Trig A1
#define S_motor 10
#define F_LED A4
#define B_LED A5
#define SL_LED A2
#define SR_LED A3
#define spoint 90

//-----------Motors-----------------//

Servo servo;
AF_DCMotor motor1(1);
AF_DCMotor motor2(2);
AF_DCMotor motor3(3);
AF_DCMotor motor4(4);


void setup() {
  Serial.begin(9600);
  
  pinMode(Trig,OUTPUT);//Trig A1
  pinMode(Echo,INPUT);//Echo A0
  pinMode(F_LED,OUTPUT);//F_LED A4 pin
  pinMode(B_LED,OUTPUT);//B_LED A5 pin
  pinMode(SL_LED,OUTPUT);//SL_LED A2 pin
  pinMode(SR_LED,OUTPUT);//SR_LED A3 pin
  servo.attach(S_motor);

}

void loop() {

//-----------------Change_Mode----------------//  

  blutooth_mode();
  //obstacle_mode();
  //voice_control();  


}


//---------------------------Blutooth_Mode---------------------------//
void blutooth_mode(){

if (Serial.available() > 0) {
  value = Serial.read();
  Stop();       //Initialize with motors stopped.

if (lightFront) {digitalWrite(F_LED, HIGH);
}
if (!lightFront) {digitalWrite(F_LED, LOW);
}
if (lightBack) {digitalWrite(B_LED, HIGH);
}
if (!lightBack) {digitalWrite(B_LED, LOW);
}
if (S_light) {digitalWrite(SL_LED, HIGH);
               digitalWrite(SR_LED, HIGH);
}
if (!S_light) {digitalWrite(SL_LED, LOW);
               digitalWrite(SR_LED, LOW);
}


switch (value) {
case 'F':forward();break;
case 'B':backward();break;
case 'L':left();break;
case 'R':right();break;
case 'I':forwardRight();break;
case 'G':forwardLeft();break;
case 'J':backwardRight();break;
case 'H':backwardLeft();break;
case 'S':Stop();break;
case '0':speedCar = 75;break;
case '1':speedCar = 100;break;
case '2':speedCar = 125;break;
case '3':speedCar = 150;break;
case '4':speedCar = 175;break;
case '5':speedCar = 200;break;
case '6':speedCar = 220;break;
case '7':speedCar = 230;break;
case '8':speedCar = 240;break;
case '9':speedCar = 250;break;
case 'q':speedCar = 255;break;
case 'W':lightFront = true;break;
case 'w':lightFront = false;break;
case 'U':lightBack = true;break;
case 'u':lightBack = false;break;
case 'X':S_light = true;break;
case 'x':S_light = false;break;
}}  


  
}

//------------------------Obstacle_Mode------------------------------//

void obstacle_mode(){  

  distance = ultrasonic();
  if (distance <= 25) {
    Stop();
    backward();
    delay(100);
    Stop();
    L = leftsee();
    servo.write(spoint);
    delay(200);
    R = rightsee();
    servo.write(spoint);
    if (L < R) {
      O_right();
      delay(200);
      Stop();
      delay(200);
    } else if (L > R) {
      O_left();
      delay(500);
      Stop();
      delay(200);
    }
  } else {
    forward();
  }
  
}

//-------------------------Voice_Control-----------------------------//

void voice_control(){

  if (Serial.available() > 0) {
    value = Serial.read();
    Serial.println(value);
    if (value == '^') {
      forward();
      digitalWrite(SL_LED, HIGH);
      digitalWrite(SR_LED, HIGH);
    } else if (value == '-') {
      backward();
    } else if (value == '<') {
      L = leftsee();
      servo.write(spoint);
      if (L >= 10 ) {
        O_left();
        delay(500);
        Stop();
      } else if (L < 10) {
        Stop();
      }
    } else if (value == '>') {
      R = rightsee();
      servo.write(spoint);
      if (R >= 10 ) {
        O_right();
        delay(500);
        Stop();
      } else if (R < 10) {
        Stop();
      }
    } else if (value == '*') {
      Stop();
    }
    } else if (value == '!') {
      {digitalWrite(F_LED, HIGH);
    }
    } else if (value == '@') {
      {digitalWrite(F_LED, LOW);
    }
    } else if (value == '+') {
      {digitalWrite(B_LED, HIGH);
    }
    } else if (value == '_') {
      {digitalWrite(B_LED, LOW);
    }
  }

}

//-------------------------Ultrasonic----------------------------------//
int ultrasonic(){
  digitalWrite(Trig,LOW);
  delayMicroseconds(4);
  digitalWrite(Trig,HIGH);
  delayMicroseconds(10);
  digitalWrite(Trig,LOW);
  long t = pulseIn(Echo,HIGH);
  long cm= t / 29/ 2;
  return cm;    
}
void forward()
{
  motor1.run(FORWARD);
  motor2.run(FORWARD);
  motor3.run(FORWARD);
  motor4.run(FORWARD);

  motor1.setSpeed(speedCar);
  motor2.setSpeed(speedCar);
  motor3.setSpeed(speedCar);
  motor4.setSpeed(speedCar);

  forwardview();

}
void backward()
{
  motor1.run(BACKWARD);
  motor2.run(BACKWARD);
  motor3.run(BACKWARD);
  motor4.run(BACKWARD);
  
  motor1.setSpeed(speedCar);
  motor2.setSpeed(speedCar);
  motor3.setSpeed(speedCar);
  motor4.setSpeed(speedCar);

  digitalWrite(B_LED,HIGH);

}
void left()
{
  motor1.run(BACKWARD);
  motor2.run(BACKWARD);
  motor3.run(FORWARD);
  motor4.run(FORWARD);
  motor1.setSpeed(speedCar);
  motor2.setSpeed(speedCar);
  motor3.setSpeed(speedCar);
  motor4.setSpeed(speedCar);

  digitalWrite(SL_LED, HIGH);

  leftview();

    
}
void O_left()
{
  motor1.run(BACKWARD);
  motor2.run(BACKWARD);
  motor3.run(FORWARD);
  motor4.run(FORWARD);
  motor1.setSpeed(speedCar);
  motor2.setSpeed(speedCar);
  motor3.setSpeed(speedCar);
  motor4.setSpeed(speedCar);

  digitalWrite(SL_LED, HIGH);
    
}

void right()
{
  motor1.run(FORWARD);
  motor2.run(FORWARD);
  motor3.run(BACKWARD);
  motor4.run(BACKWARD);
  motor1.setSpeed(speedCar);
  motor2.setSpeed(speedCar);
  motor3.setSpeed(speedCar);
  motor4.setSpeed(speedCar);

  digitalWrite(SR_LED, HIGH);

  rightview();

}
void O_right()
{
  motor1.run(FORWARD);
  motor2.run(FORWARD);
  motor3.run(BACKWARD);
  motor4.run(BACKWARD);
  motor1.setSpeed(speedCar);
  motor2.setSpeed(speedCar);
  motor3.setSpeed(speedCar);
  motor4.setSpeed(speedCar);

  digitalWrite(SR_LED, HIGH);
}

void forwardRight()
{
  motor1.run(FORWARD);
  motor2.run(FORWARD);
  motor3.run(FORWARD);
  motor4.run(RELEASE);
  
  motor1.setSpeed(speedCar);
  motor2.setSpeed(speedCar);
  motor3.setSpeed(speedCar);
}

void forwardLeft()
{
  motor1.run(RELEASE);
  motor2.run(FORWARD);
  motor3.run(FORWARD);
  motor4.run(FORWARD);
  
  motor1.setSpeed(speedCar);
  motor2.setSpeed(speedCar);
  motor4.setSpeed(speedCar);
}
void backwardRight()
{
  motor1.run(BACKWARD);
  motor2.run(BACKWARD);
  motor3.run(RELEASE);
  motor4.run(BACKWARD);
  motor1.setSpeed(speedCar);
  motor2.setSpeed(speedCar);
  motor4.setSpeed(speedCar);

  digitalWrite(B_LED,HIGH);

}
void backwardLeft()
{
  motor1.run(BACKWARD);
  motor2.run(RELEASE);
  motor3.run(BACKWARD);
  motor4.run(BACKWARD);
  motor1.setSpeed(speedCar);
  motor2.setSpeed(speedCar);
  motor3.setSpeed(speedCar);

  digitalWrite(B_LED,HIGH);

}
void Stop()
{
  motor1.run(RELEASE);
  motor2.run(RELEASE);
  motor3.run(RELEASE);
  motor4.run(RELEASE);
}

int rightsee(){
  servo.write(20);
  delay(500);
  Left = ultrasonic();
  return Left;
}

int leftsee(){
  servo.write(180);
  delay(500);
  Right = ultrasonic();
  return Right;
}

int leftview(){
  servo.write(180);
  
}

int rightview(){
  servo.write(20);
}

int forwardview(){
  servo.write(spoint);
}


