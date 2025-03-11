/* 
 * Project: Dark Magician's Staff
 * Author:  Ahmad Musleh   |   https://github.com/a7madmusle7
 * Date:    2025-March-04
 */

/*
 * This is a rought draft / psuedo code as comments for the midterm project.
 * The minimum goal is to control the hue lights and Wemo switches in the classroom. I am also required to use certain parts like the OLED display.
 * I will be using buttons to run different controls. The buttons will be attached along the length of a wooden dowel.
 * Larger parts will be housed in the end of the rod in an enclosure.
 * Upon first glance, the staff will look like a regular decoration, without any functionality.
 * Stretch goals: I have a couple of outside components. One is a tornado lamp that changes colors when a button on it is pressed.
 * The other item is a toy top which lights up when it spins. I might attach it to the end of the staff, where the particle is.
 * The tornado light has a button on it which swtiches the light modes. I can press this button with the servo motor.
*/

/* 
 * Project: L08_04_Hue
 * Description: Connecting to and using the Phillips Hue bulbs
 * Author: Last edit at 19:30
 * Date: 27 FEB 2025
 */

 #include "Particle.h"
 #include "IoTClassroom_CNM.h"
 #include <Encoder.h>
 #include "Colors.h"
 #include "hue.h"
 #include "wemo.h"
 #include "button.h"
 
 SYSTEM_MODE(MANUAL);


  int brightness;


  const int BULB1=1;
  const int BULB2=2; 
  const int BULB3=3;
  const int BULB4=4; 
 const int BULB5=5; 
 int color =maroon;
 int prevBrightness;
 bool onOff = false;
 
 const int BUTTONPIN = D14;
 Button myButton(BUTTONPIN);
 const int OTHERBUTTONPIN = D19;
 Button myOtherButton(OTHERBUTTONPIN);
 
 Encoder myEncoder(D8, D9);
 int position;
 
 IoTTimer timer;
 
 void setup() {
   Serial.begin(9600);
   waitFor(Serial.isConnected,15000);
 
   WiFi.on();
   WiFi.clearCredentials();
   WiFi.setCredentials("IoTNetwork");
   
   WiFi.connect();
   while(WiFi.connecting()) {
     Serial.printf(".");
   }
   Serial.printf("\n\n");
 }
 
 void loop() {
  
   // brightness control
   brightness = myEncoder.read();

    setHue(BULB1, true, HueBlue, brightness, 255);
    setHue(BULB2, true, rainbow[color%7], brightness, 255);
    setHue(BULB3, true, rainbow[color%7], brightness, 255);
    setHue(BULB4, true, rainbow[color%7], brightness, 255);
    setHue(BULB5, true, rainbow[color%7], brightness, 255);

    delay (500);

    if (brightness>255){
      brightness=255;
      myEncoder.write (255);
    }
    if (brightness<0){
      brightness=0;
      myEncoder.write(0);
    }

   }

