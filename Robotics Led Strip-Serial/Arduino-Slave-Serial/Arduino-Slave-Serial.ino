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
  Serial.begin(9600);          

  pinMode(redPin,OUTPUT);
  pinMode(greenPin,OUTPUT);
  pinMode(bluePin,OUTPUT);  

  pinMode(commandReceivedLedOnboardArduino, OUTPUT); 
  toggleCommandArrivedLed(); 
    
  //Serial.write("Arduino-Slave-I2C Initialization Complete. \n");
}

void loop()
{
  // Nothing Needed
}


void serialEvent()
{
  while (Serial.available()) 
  {
    
   toggleCommandArrivedLed(); 
   
   char state = (char) Serial.read();
//   Serial.write("Received Char: <");
//   Serial.write(state);
//   Serial.write("> \n");
    //not sure if it should be a normal or unsigned char
    switch (state)
    {
    case 'r':
      //Serial.write("Commanded RED. \n");
      setColor(255,0,0);
      break;

    case 'g':
      //Serial.write("Commanded GREEN. \n");
      setColor(0,255,0);
      break;

    case 'b':
      //Serial.write("Commanded BLUE. \n");
      setColor(0,0,255);
      break;

    case 'p':
      //Serial.write("Commanded PINK. \n");
      setColor(255,0,127);
      break;

    case 't':
      //Serial.write("Commanded TEAL. \n");
      setColor(0,255,255);
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


