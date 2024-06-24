#include <Robojax_L298N_DC_motor.h>
#include <Servo.h> 
//-------------L298(1)---------------------------------------------------
// motor 1 settings
#define CHA_1 0
#define ENA_1 2 // this pin must be PWM enabled pin if Arduino board is used
#define IN1_1 30
#define IN2_1 32
// motor 2 settings
#define IN3_1 34
#define IN4_1 36
#define ENB_1 7// this pin must be PWM enabled pin if Arduino board is used
#define CHB_1 1
//-------------L298(2)---------------------------------------------------
// motor 3 settings
#define CHA_2 0
#define ENA_2 2 // this pin must be PWM enabled pin if Arduino board is used
#define IN1_2 38
#define IN2_2 40
// motor 4 settings
#define IN3_2 42
#define IN4_2 44
#define ENB_2 7// this pin must be PWM enabled pin if Arduino board is used
#define CHB_2 1

const int CCW = 2; // do not change
const int CW  = 1; // do not change

#define motor1 1 
#define motor2 2 

// for two motors without debug information // Watch video instruciton for this line: https://youtu.be/2JTMqURJTwg
Robojax_L298N_DC_motor motors1(IN1_1, IN2_1, ENA_1, CHA_1,  IN3_1, IN4_1, ENB_1, CHB_1);
Robojax_L298N_DC_motor motors2(IN1_2, IN2_2, ENA_2, CHA_2,  IN3_2, IN4_2, ENB_2, CHB_2);

#define Pin22   22
#define Pin23   23
#define Pin24   24
#define Pin25   25
 
Servo servo1;  //底座   定義舵機對象，最多八個 
Servo servo2;  //左臂
Servo servo3;  //右臂
Servo servo4;  //夾子

void setup() 
{
  Serial.begin(9600);
  pinMode(Pin22,  INPUT);
  pinMode(Pin23,  INPUT);
  pinMode(Pin24,  INPUT);
  pinMode(Pin25,  INPUT);
  Serial.println(F("init"));
  pinMode(IN1_1, OUTPUT);
  pinMode(IN2_1, OUTPUT);
  pinMode(IN3_1, OUTPUT);
  pinMode(IN4_1, OUTPUT);
  pinMode(ENA_1, OUTPUT);
  pinMode(ENB_1, OUTPUT);
  pinMode(IN1_2, OUTPUT);
  pinMode(IN2_2, OUTPUT);
  pinMode(IN3_2, OUTPUT);
  pinMode(IN4_2, OUTPUT);
  pinMode(ENA_2, OUTPUT);
  pinMode(ENB_2, OUTPUT);
  servo1.attach(8);  // 設置舵機控制腳位
  servo2.attach(9);
  servo3.attach(10);
  servo4.attach(11);

  servo1.write(30);
  servo2.write(50);
  servo3.write(20);
  servo4.write(20);
}

void loop() 
{
  char key = 0;
  int a=1,b=1,c=1,d=1;
  int fg = 0;
  boolean flag= false;
 
  while(1) 
  {  
    if ( Serial.available()) 
    {
      key = Serial.read();
      flag=true;
    }

    a= digitalRead (Pin22);
    b= digitalRead (Pin23);
    c= digitalRead (Pin24);
    d= digitalRead (Pin25);

    Serial.print(digitalRead(22)) ;  //purple >  14
    Serial.print(digitalRead(23)) ;  //blue 2
    Serial.print(digitalRead(24)) ;  //yellow > 13
    Serial.println(digitalRead(25)); //15
    

    if (flag==false) 
    {
       if (a==1 and b==0 and c==1 and d==0) {
          key ='f';
       }
       else if (a==0 and b==1 and c==0 and d==1) {
          key ='b';
       }
       else if (a==1 and b==0 and c==0 and d==1) {
          key ='x';
       }
       else if (a==0 and b==1 and c==1 and d==0) {
         key ='y';
       }
       else if (a==0 and b==0 and c==1 and d==1) {
         key ='a';
       }
       else if (a==1 and b==1 and c==0 and d==0) {
         key ='c';
       }
       else if (a==0 and b==0 and c==0 and d==0) {
         key ='s';
       }
       else if (a==1 and b==1 and c==1 and d==1) {
         key ='s';
       }
       else if (a==0 and b==0 and c==0 and d==1) { //---servo action 1 A1 Stretch
         key ='1';
       }
       else if (a==0 and b==0 and c==1 and d==0) { //---servo action 2 A2 Clip
         key ='2';
       }
       else if (a==0 and b==1 and c==0 and d==0) { //---servo action 3 A3 Retract
         key ='3';
       }
       else if (a==1 and b==0 and c==0 and d==0) { //---servo action 4 A4 Turn
         key ='4';
       }
       else if (a==1 and b==1 and c==1 and d==0) { //---servo action 5 A5 Release<
         key ='5';
       }
       else if (a==1 and b==1 and c==0 and d==1) { //---servo action 6 A6 Origin
         key ='6';
       }
       else if (a==1 and b==0 and c==1 and d==1) { //---servo action 7
         key ='7';
       }
       else if (a==0 and b==1 and c==1 and d==1) { //---servo action 8
         key ='8';
       }
    }

    switch ( key ) {
      case 'f': // 前進
        Serial.println(F("Forward"));
        Forward();
        break;
      case 'b': // 後退
        Serial.println(F("Reverse"));
        Reverse();
        break;
      case 'l': // 左移 
        Serial.println(F("Left"));
        Left();
        break;
      case 'r': // 右移
        Serial.println(F("Right"));
        Right();
        break;  
      case 'a': // 左平移 
        Serial.println(F("ShiftLeft"));
        S_Left();
        break;
      case 'c': // 右平移
        Serial.println(F("ShiftRight"));
        S_Right();
        break;  
      case 'x': // 逆左旋轉
        Serial.println(F("X"));
        Xtrun();
        break;  
      case 'y': // 順右旋轉
        Serial.println(F("Y"));
        Ytrun();
        break;  
      case '1': // 伸爪
        Serial.println(F("3"));
        servo3.write(40);
        delay(500);
        Serial.println(F("1"));
        servo1.write(50);
        delay(500);
        servo1.write(70);
        delay(500);
        servo1.write(90);
        delay(500);
        servo1.write(130);
        delay(500);
        servo1.write(160);
        delay(500);
        break;  
      case '2': // 夾
        Serial.println(F("2"));
        servo2.write(70);
        delay(500);
        servo2.write(100);
        delay(500);
        servo2.write(140);
        delay(500);
        break;  
      case '3':  //收爪
        Serial.println(F("1"));
        servo1.write(110);
        delay(500);
        servo1.write(90);
        delay(500);
        servo1.write(50);
        delay(500);
        servo1.write(30);
        delay(500);
        break;  
      case '4':  //後轉
        Serial.println(F("4"));
        servo4.write(60);
        delay(500);
        servo4.write(90);
        delay(500);
        servo4.write(120);
        delay(500);
        servo4.write(160);
        delay(500);
        servo4.write(180);
        delay(500);
        break; 
      case '5':  //放夾
        Serial.println(F("2"));
        servo2.write(120);
        delay(500);
        servo2.write(90);
        delay(500);
        servo2.write(50);
        delay(500);
        /**
        Serial.println(F("4"));
        servo4.write(160);
        delay(500);;
        servo4.write(120);
        delay(500);
        servo4.write(80);
        delay(500);
        servo4.write(40);
        delay(500);
        servo4.write(20);
        delay(500);**/
        break;   
      case '6': //回原點
        Serial.println(F("4"));
        servo4.write(160);
        delay(500);;
        servo4.write(120);
        delay(500);
        servo4.write(80);
        delay(500);
        servo4.write(40);
        delay(500);
        servo4.write(20);
        delay(500);
        break; 
      case 's': // 前進
        //Serial.println(F("Stop"));
        Stop();
        break;
      default:
        Stop();
        flag= false;
        break;

    }
   
  } //---while(1) 
}

void Forward() //電機前進
{
  motors1.brake(1);  
  motors1.brake(2);  
  motors2.brake(1);  
  motors2.brake(2);  

  motors1.rotate(motor1, 70, CW);//run motor1 at 60% speed in CW direction (1)
  motors1.rotate(motor2, 70, CCW);//run motor2 at 60% speed in CCW direction (2)
  motors2.rotate(motor1, 70, CCW);//run motor1 at 60% speed in CCW direction (3)
  motors2.rotate(motor2, 70, CW);//run motor2 at 60% speed in CW direction  (4)
}

void Reverse(){
  motors1.brake(1);  
  motors1.brake(2);  
  motors2.brake(1);  
  motors2.brake(2); 
  motors1.rotate(motor1, 70, CCW);
  motors1.rotate(motor2, 70, CW);
  motors2.rotate(motor1, 70, CW);
  motors2.rotate(motor2, 70, CCW);
}
void Left()
{
  motors1.brake(1);  
  motors1.brake(2);  
  motors2.brake(1);  
  motors2.brake(2);  
  motors1.rotate(motor1, 70, CW);//run motor1 at 60% speed in CW direction (1)
  //motors1.rotate(motor2, 70, CCW);//run motor2 at 60% speed in CCW direction (2)
  //motors2.rotate(motor1, 70, CCW);//run motor1 at 60% speed in CCW direction (3)
  motors2.rotate(motor2, 70, CW);//run motor2 at 60% speed in CW direction  (4)
}
void S_Left()  //左平移
{
  motors1.brake(1);  
  motors1.brake(2);  
  motors2.brake(1);  
  motors2.brake(2);  
  motors1.rotate(motor1, 70, CW);//run motor1 at 60% speed in CW direction (1)
  motors1.rotate(motor2, 70, CW);//run motor2 at 60% speed in CCW direction (2)
  motors2.rotate(motor1, 70, CW);//run motor1 at 60% speed in CCW direction (3)
  motors2.rotate(motor2, 70, CW);//run motor2 at 60% speed in CW direction  (4)
}
void S_Right()  //右平移
{
  motors1.brake(1);  
  motors1.brake(2);  
  motors2.brake(1);  
  motors2.brake(2);  
  motors1.rotate(motor1, 70, CCW);//run motor1 at 60% speed in CW direction (1)
  motors1.rotate(motor2, 70, CCW);//run motor2 at 60% speed in CCW direction (2)
  motors2.rotate(motor1, 70, CCW);//run motor1 at 60% speed in CCW direction (3)
  motors2.rotate(motor2, 70, CCW);//run motor2 at 60% speed in CW direction  (4)
}
void Right()  //右
{
  motors1.brake(1);  
  motors1.brake(2);  
  motors2.brake(1);  
  motors2.brake(2);  
  //motors1.rotate(motor1, 70, CW);//run motor1 at 60% speed in CW direction (1)
  motors1.rotate(motor2, 70, CCW);//run motor2 at 60% speed in CCW direction (2)
  motors2.rotate(motor1, 70, CCW);//run motor1 at 60% speed in CCW direction (3)
  //motors2.rotate(motor2, 70, CW);//run motor2 at 60% speed in CW direction  (4)
}

void Ytrun() // 逆右旋轉
{
  motors1.brake(1);  
  motors1.brake(2);  
  motors2.brake(1);  
  motors2.brake(2);  

  motors1.rotate(motor1, 70, CCW);//run motor1 at 60% speed in CW direction (1)
  motors1.rotate(motor2, 70, CW);//run motor2 at 60% speed in CCW direction (2)
  motors2.rotate(motor1, 70, CCW);//run motor1 at 60% speed in CCW direction (3)
  motors2.rotate(motor2, 70, CW);//run motor2 at 60% speed in CW direction  (4)
}

void Xtrun() // 逆左旋轉
{
  motors1.brake(1);  
  motors1.brake(2);  
  motors2.brake(1);  
  motors2.brake(2);  

  motors1.rotate(motor1, 70, CW);//run motor1 at 60% speed in CW direction (1)
  motors1.rotate(motor2, 70, CCW);//run motor2 at 60% speed in CCW direction (2)
  motors2.rotate(motor1, 70, CW);//run motor1 at 60% speed in CCW direction (3)
  motors2.rotate(motor2, 70, CCW);//run motor2 at 60% speed in CW direction  (4)
}

void Stop() //電機停止
{
  motors1.brake(1);
  motors1.brake(2);  
  motors2.brake(1);
  motors2.brake(2);  
}
