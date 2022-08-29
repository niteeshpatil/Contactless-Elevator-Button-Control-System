# Contactless-Elevator-Button-Control-System


https://user-images.githubusercontent.com/88622611/187029202-26b92783-efd2-4a6e-ae7f-4f7cdf1be8f7.mp4

![image](https://user-images.githubusercontent.com/88622611/187030155-43413ec1-bb5d-4089-8657-1a2c5ecb8674.png)

#  Methodology
 - The Figure  represents the design proposed that consists of a panel of buttons
 with Infrared sensors mounted behind each button ,controller, OLED screen and a
 stepper motor.
 - When our finger approaches a particular button it is recognised by the IR sensor,
the digital data is sent to controller (arduino).
- The controller maps the particular IR sensor value to floor number and displays it
on OLED screen and stepper motor rotates such that the elevator cabin will move to
the designated floor.
- In case if two or more than two buttons are sensed simultaneously then arduino
resets the input and commands user to try again and the same is displayed on the
OLED screen.

# To achieve the above operation we have used -
 - Arduino IDE
 - Embedded C
 
# Components used 
- Arduino UNO 
- IR Sensor 
- OLED Display
- 28BYJ-48 Stepper Motor
- ULN2003 Motor Drive



























