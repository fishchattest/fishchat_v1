//SG90://http://yehnan.blogspot.tw/2013/09/arduinotower-pro-sg90.html

#include <Servo.h> 
#include <Timer>
Servo myservo;

const int LED_R=9;
const int LED_G=10;
const int LED_B=11;
const int MOTOR=6;
const int HC_SR501=4;
const int BEEP = 13;
const int Received_ESP01 = 2;
int cnt_timer=0;
int cnt_LED=0;
int cnt_MOTOR=0;

void LED_turnoff(){
  digitalWrite(LED_R, LOW);
  digitalWrite(LED_G, LOW);
  digitalWrite(LED_B, LOW);
}

void MOTOR_C(int a)
{
  if (a == 0)
  {
    for(int i = 0; i <= 180; i+=1)
    {
      myservo.write(i); // 使用write，傳入角度，從0度轉到180度
      delay(10);
    }
  }
  else if (a==1)
  {
    for(int i = 180; i >= 0; i-=1)
    {
      myservo.write(i);// 使用write，傳入角度，從180度轉到0度
      delay(10);
    }
  }
  else
  {
    myservo.write(90); // 一開始先置中90度
  }  
}

void setup() 
{ 
  Serial.begin(9600);   
  myservo.attach(MOTOR, 500, 2400); // 修正脈衝寬度範圍
  myservo.write(90); // 一開始先置中90度
  pinMode(LED_R, OUTPUT);
  pinMode(LED_G, OUTPUT);
  pinMode(LED_B, OUTPUT);
  pinMode(HC_SR501, INPUT); 
  pinMode(BEEP, OUTPUT);
  pinMode(Received_ESP01, INPUT);
  LED_turnoff(); 
  delay(3000);
} 

void loop() 
{
  int Det_IR=0;
  int Det_Motor=0;
  Det_IR = digitalRead(HC_SR501);  
  Serial.print("Det_IR:");
  Serial.println(Det_IR);
  if (Det_IR == 1)
  {
    digitalWrite(BEEP,HIGH);
    cnt_timer++;
    if (cnt_timer>2)
      digitalWrite(BEEP, LOW);
      cnt_timer =0;
  }
  else
  {
      digitalWrite(BEEP, LOW);
      cnt_timer =0;    
  }
  Det_Motor = digitalRead(Received_ESP01);
  Serial.print("Det_MOTOR:");
  Serial.println(Det_Motor);
  if (Det_Motor == 1)
  {
    if (cnt_MOTOR == 0)
    {
      MOTOR_C(1);
      cnt_MOTOR = 1;
    }
    else
    {
      MOTOR_C(0);
      cnt_MOTOR=0;
    }
  }


  if (cnt_LED==0)
  {
    LED_turnoff();
    digitalWrite(LED_R, HIGH);
  }else if(cnt_LED==1)
  {
    LED_turnoff();
    digitalWrite(LED_G, HIGH);
  }else if(cnt_LED==2)
  {
    LED_turnoff();
    digitalWrite(LED_B, HIGH);
  }else if(cnt_LED==3)
  {  
    LED_turnoff();
    digitalWrite(LED_R, HIGH);
    digitalWrite(LED_G, HIGH);
  }else if(cnt_LED==4)
  {
    LED_turnoff();
    digitalWrite(LED_G, HIGH);
    digitalWrite(LED_B, HIGH);
  }else if(cnt_LED==5)
  {  
    LED_turnoff();
    digitalWrite(LED_B, HIGH);
    digitalWrite(LED_R, HIGH);
  }else if(cnt_LED==6)
  {
    cnt_LED=0;
  }
  cnt_LED++;
  delay(1000);  
  digitalWrite(BEEP, LOW);    
}

