#include <IRremote.h>  
IRsend irsend;   
int old = 0;  //默认电视关闭状态

unsigned int L = 1800;  
unsigned int C = 800;   
unsigned int X = 300;  
unsigned long time;
unsigned int salve1[] = {
  X,L,X,C,X,C,X,C,X,C,X,C,X,L,X,L,X,C,X,L,X,C,X,C,X,C,X,L,X,C,X};
unsigned int salve2[] = {
  X,L,X,C,X,C,X,C,X,C,X,L,X,C,X,C,X,L,X,C,X,L,X,L,X,L,X,C,X,L,X};

//以上开关机信号

void setup()
{
  Serial. begin(9600);
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(13, OUTPUT);
}


void loop()
{ 
  delay(1600);   
  digitalWrite(13, HIGH);   //工作指示灯闪烁 
  delay(100);             //工作指示灯闪烁        
  digitalWrite(13, LOW);  //工作指示灯闪烁 
  
  int v1 = analogRead(A6); //读取机顶盒usb电压
  float V1 = v1*(5.0/1023.0); //计算0-5v的电压值
 
 
if (V1 > 4.5 && old == 0)  //usb有电压且电视机为关机状态

  {   
      irsend.sendRaw(salve1, 31, 38); 
      delay(30);
      irsend.sendRaw(salve2, 31, 38); 
      delay(30);
      irsend.sendRaw(salve1, 31, 38);
      
      digitalWrite(5, HIGH);   //状态指示灯闪烁
      delay(500);             //状态指示灯闪烁          
      digitalWrite(5, LOW);  //状态指示灯闪烁 

      delay(1000); 
      
      irsend.sendRaw(salve1, 31, 38); 
      delay(30);
      irsend.sendRaw(salve2, 31, 38); 
      delay(30);
      irsend.sendRaw(salve1, 31, 38);  
                  
      digitalWrite(5, HIGH);   //状态指示灯闪烁
      delay(500);             //状态指示灯闪烁          
      digitalWrite(5, LOW);  //状态指示灯闪烁
      
      old=1;  
      //打开电视机，标记为开机状态
   }
else if (V1 < 4.5 && old == 1)  //机顶盒掉电且电视机为开机状态
 
  {
      delay(2000); 
      
      irsend.sendRaw(salve1, 31, 38); 
      delay(30);
      irsend.sendRaw(salve2, 31, 38); 
      delay(30);
      irsend.sendRaw(salve1, 31, 38);  
      
      digitalWrite(5, HIGH);   //状态指示灯闪烁
      delay(500);             //状态指示灯闪烁          
      digitalWrite(5, LOW);  //状态指示灯闪烁

      delay(1000); 
   
      irsend.sendRaw(salve1, 31, 38); 
      delay(30);
      irsend.sendRaw(salve2, 31, 38); 
      delay(30);
      irsend.sendRaw(salve1, 31, 38); 
      
      digitalWrite(5, HIGH);   //状态指示灯闪烁
      delay(500);             //状态指示灯闪烁          
      digitalWrite(5, LOW);  //状态指示灯闪烁
      
      old=0;
      //关闭电视机，标记为关机状态
  
   }

}
