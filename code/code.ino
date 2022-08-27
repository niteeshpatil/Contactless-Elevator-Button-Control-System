#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Stepper.h>

#define SCREEN_WIDTH 128 // OLED display width,  in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

// declare an SSD1306 display object connected to I2C
Adafruit_SSD1306 oled(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);


int IRSensor1= 5;
int IRSensor2= 6;
int IRSensor3= 7;

const int stepsPerRevolution = 2038;
const int sp=10;
int currflore=1;
int nextflore=1;

// Creates an instance of stepper class
// Pins entered in sequence IN1-IN3-IN2-IN4 for proper step sequence
Stepper myStepper = Stepper(stepsPerRevolution, 8, 10, 9, 11);

void setup() { 
  Serial.begin(9600);

  // initialize OLED display with address 0x3C for 128x64
  if (!oled.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println(F("SSD1306 allocation failed"));
    while (true);
  }
    delay(500);         // wait for initializing
  oled.clearDisplay(); // clear display

  oled.setTextSize(3);          // text size
  oled.setTextColor(WHITE);     // text color
  oled.setCursor(0, 25);        // position to display
  oled.println("Welcome"); // text to display
  oled.display();               // show on OLED


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

void loop() { 
  myStepper.setSpeed(sp);
 int s1 = digitalRead(IRSensor1);
 int s2 = digitalRead(IRSensor2);
 int s3 = digitalRead(IRSensor3);

if((!s1&&!s2)||(!s2&&!s3)||(!s3&&!s1))
{


  oled.clearDisplay(); // clear display

  oled.setTextSize(2);          // text size
  oled.setTextColor(WHITE);     // text color
  oled.setCursor(5, 20);        // position to display
  oled.println("Try again"); // text to display
  oled.display();               // show on 
     delay(500);         // wait for initializing
}

 
else if (s1 == 0)
  {

  oled.clearDisplay(); // clear display

  oled.setTextSize(3);          // text size
  oled.setTextColor(WHITE);     // text color
  oled.setCursor(0, 25);        // position to display
  oled.println("Floor 1"); // text to display
  oled.display();               // show on 
    delay(500);         // wait for initializing
   rotate(currflore,1);
   currflore=1;
  }
  
  else if (s2 == 0)
   {  


  oled.clearDisplay(); // clear display

  oled.setTextSize(3);          // text size
  oled.setTextColor(WHITE);     // text color
  oled.setCursor(0, 25);        // position to display
  oled.println("Floor 2"); // text to display
  oled.display(); 
    delay(500);         // wait for initializing  
  rotate(currflore,2);
   currflore=2;
  }
 else if (s3 == 0)
   {  

  oled.clearDisplay(); // clear display

  oled.setTextSize(3);          // text size
  oled.setTextColor(WHITE);     // text color
  oled.setCursor(0, 25);        // position to display
  oled.println("Floor 3"); // text to display
  oled.display();               // show on 
   delay(500);         // wait for initializing
 rotate(currflore,3);
 currflore=3;
  
  }

  else
  {
  oled.clearDisplay(); // clear display

  oled.setTextSize(2);          // text size
  oled.setTextColor(WHITE);     // text color
  oled.setCursor(5  ,20);        // position to display
  oled.println("Select         Floor"); // text to display
  oled.display();               // show on 
    delay(500);         // wait for initializing
  
  }
   
}
