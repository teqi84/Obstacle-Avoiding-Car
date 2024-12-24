#include<Servo.h>

const int eA = 9, i1 = 5, i2 = 6;
const int eB = 10, i3 = 7, i4 = 8;
const int trig = 4, echo = 3;
int dis_value = 100;
boolean check = false;
Servo sv;

void setup(){
  Serial.begin(9600);
  for(int i=5;i<11;i++){pinMode(i,OUTPUT);}
  pinMode(trig,OUTPUT); pinMode(echo,INPUT);
  sv.attach(2);
  sv.write(89); delay(2000);
  dis_value = read_data(); delay(100);
  dis_value = read_data(); delay(100);
  dis_value = read_data(); delay(100);
  dis_value = read_data(); delay(100);
  analogWrite(eA, 70);  analogWrite(eB, 70);
}

void loop(){
  int right_value = 0, left_value = 0; delay(50);

  if(dis_value<=20){
    dunglai(); delay(300);
    dilui(); delay(400);
    dunglai(); delay(300);
    right_value = check_phai(); delay(300);
    left_value = check_trai(); delay(300);
    if (dis_value >= left_value){xoayphai();dunglai();}
    else{xoaytrai();dunglai();}
  }
  else{thang();}
  dis_value = read_data();
}

int read_data(){
  int dis_val,time_value;
  digitalWrite(trig,LOW); delayMicroseconds(2);
  digitalWrite(trig,HIGH); delayMicroseconds(10);
  digitalWrite(trig,LOW); 
  time_value = pulseIn(echo,HIGH);
  dis_val = int(time_value/2/29.412);
  return dis_val;
}

int check_phai(){
  sv.write(10); delay(500);
  int dis_value = read_data(); delay(100);
  sv.write(89);
  return dis_value;
}

int check_trai(){
  sv.write(170); delay(500);
  int dis_value = read_data(); delay(100);
  sv.write(89);
  return dis_value;
}

void dithang(){
  digitalWrite(i1,HIGH); digitalWrite(i2,LOW);
  digitalWrite(i3,HIGH); digitalWrite(i4,LOW);
}

void dunglai(){
  digitalWrite(i1,LOW); digitalWrite(i2,LOW);
  digitalWrite(i3,LOW); digitalWrite(i4,LOW);
}

void xoayphai(){
  digitalWrite(i1,HIGH); digitalWrite(i2,LOW);
  digitalWrite(i3,LOW); digitalWrite(i4,HIGH);
  delay(300);
  dithang();
}

void xoaytrai(){
  digitalWrite(i1,LOW); digitalWrite(i2,HIGH);
  digitalWrite(i3,HIGH); digitalWrite(i4,LOW);
  delay(300);
  dithang();
}

void thang(){
  if(!check){check = true; dithang();}
}

void dilui(){
  check = false;
  digitalWrite(i1,LOW); digitalWrite(i2,HIGH);
  digitalWrite(i3,LOW); digitalWrite(i4,HIGH);
}
