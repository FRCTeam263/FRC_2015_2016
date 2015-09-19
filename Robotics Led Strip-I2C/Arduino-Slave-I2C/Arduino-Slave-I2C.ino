#include <Wire.h>

int redPin = 3;
int greenPin = 5; 
int bluePin = 6;

int commandReceivedLedOnboardArduino = 13; 

void toggleCommandArrivedLed(int LightDuration = 200)
{
   digitalWrite(commandReceivedLedOnboardArduino, HIGH); 
   delay(LightDuration);
   digitalWrite(commandReceivedLedOnboardArduino, LOW); 
   delay(LightDuration);
}

void setup()
{
  Wire.begin(1); //communicate on this address               
  Wire.onReceive(receiveEvent);//when communication is successful,
  Serial.begin(9600);          //go to the function

  pinMode(redPin,OUTPUT);
  pinMode(greenPin,OUTPUT);
  pinMode(bluePin,OUTPUT);  

  pinMode(commandReceivedLedOnboardArduino, OUTPUT); 
  toggleCommandArrivedLed(); 
    
  Serial.write("Arduino-Slave-I2C Initialization Complete. \n");
}

void loop()
{
  //dont really need anything in here
}

void receiveEvent(int howMany)
{
  Serial.write("receiveEvent Invoked. \n");
  while (Wire.available()) //when you recieve a byte (through i2c)
  {
    
   toggleCommandArrivedLed(); 
   
   unsigned char state = Wire.read();
   Serial.write("Received Char: <");
   Serial.write(state);
   Serial.write("> \n");
    //not sure if it should be a normal or unsigned char
    switch (state)
    {
    case 'r':
      Serial.write("Commanded RED. \n");
      setColor(255,0,0);
      break;

    case 'g':
      Serial.write("Commanded GREEN. \n");
      setColor(0,255,0);
      break;

    case 'b':
      Serial.write("Commanded BLUE. \n");
      setColor(0,0,255);
      break;

    case 'p':
      Serial.write("Commanded PINK. \n");
      setColor(255,0,127);
      break;

    case 't':
      Serial.write("Commanded TEAL. \n");
      setColor(0,255,255);
      break; 

     default:
      Serial.write("Commanded not recognized. \n");
      break; 
      
    }    
  }
}

void setColor(int redColor,int greenColor, int blueColor)
{
  analogWrite(redPin,redColor);
  analogWrite(greenPin,greenColor);
  analogWrite(bluePin,blueColor);
}


