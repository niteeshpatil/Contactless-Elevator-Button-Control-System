#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Stepper.h>
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64 


Adafruit_SSD1306 oled(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);


int IRSensor1= 5;
int IRSensor2= 6;
int IRSensor3= 7;

const int stepsPerRevolution = 2038;
const int sp=10;
int currflore=1;


Stepper myStepper = Stepper(stepsPerRevolution, 8, 10, 9, 11);

void setup() { 
  Serial.begin(9600);

  if (!oled.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println(F("SSD1306 allocation failed"));
    while (true);
  }
    delay(500);       
  oled.clearDisplay();

  oled.setTextSize(3);          
  oled.setTextColor(WHITE);    
  oled.setCursor(0, 25);       
  oled.println("Welcome"); 
  oled.display();
  delay(4000);                


 pinMode (IRSensor1, INPUT);
 pinMode (IRSensor2, INPUT);
 pinMode (IRSensor3, INPUT);
 
}

void rotate(int currflore,int nextflore)
{
  int movevalue=abs(currflore-nextflore);

  if(currflore==nextflore)
{
 
}
 //   Rotate CW quickly 
  else if(currflore>nextflore)
  {
      for(int i=0;i<movevalue*2;i++)
      myStepper.step(stepsPerRevolution);
    
  }


  
//   Rotate CCW quickly
  else
  {
    for(int i=0;i<movevalue*2;i++)
    myStepper.step(-stepsPerRevolution);
  }
}

void disp(int i)
{
   oled.clearDisplay(); 

  oled.setTextSize(3);          
  oled.setTextColor(WHITE);     
  oled.setCursor(0, 25);  
  if(i==1)     
  oled.println("Floor 1");
  if(i==2)
   oled.println("Floor 2");
  if(i==3)
   oled.println("Floor 3");
  oled.display(); 
  delay(1000);
}

void dispslect(int i)
{
   oled.clearDisplay(); 

  oled.setTextSize(2);          
  oled.setTextColor(WHITE);     
  oled.setCursor(5, 20);  
  if(i==1)     
  oled.println("Floor 1   Selected");
  if(i==2)
   oled.println("Floor 2   Selected");
  if(i==3)
   oled.println("Floor 3   Selected");
  oled.display(); 
  delay(2000);
}

void get(int *s)
{
    for(int i=0;i<3;i++)
    {
      if(s[i]==0)
      {
         s[i]=i+1;
      }
      else
      {
        s[i]=10;
      }
    }

    int newcur=currflore;
    for(int i=0;i<3;i++)
    {
      if(s[i]!=10 && s[i]>currflore && s[i]!=currflore)
      {
        disp(s[i]);
        rotate(newcur,s[i]);
        newcur=s[i];
        s[i]=10;
      }
    }

    for(int i=2;i>=0;i--)
    {
      if(s[i]!=10 && s[i]!=currflore)
      {
        disp(s[i]);
        rotate(newcur,s[i]);
        newcur=s[i];
      }
    }
  currflore=newcur; 
}

void select(int i,int *s,int *b)
{
      if(s[i]!=0)
    {
      if(i==0)
      s[i]=digitalRead(IRSensor1);
      if(i==1)
      s[i]=digitalRead(IRSensor2);
      if(i==2)
      s[i]=digitalRead(IRSensor3);
      if(s[i]==0 && b[i]==0)
      {
        dispslect(i+1);
        b[i]=1;
      }
    }
}
void loop() { 
  myStepper.setSpeed(sp);
  int s[3];
  int b[3]={0,0,0};
  for(int i=0;i<200;i++)
  {
     for(int j=0;j<3;j++)
     {
      select(j,s,b);
     }
  }

  
if(s[0]==0 or s[1]==0 or s[2]==0)
{
  get(s);    
}
else
{
  oled.clearDisplay(); 

  oled.setTextSize(2);          
  oled.setTextColor(WHITE);    
  oled.setCursor(5  ,20);        
  oled.println("Select         Floor"); 
  oled.display();               
    delay(2000);         
}
   
}
