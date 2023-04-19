
#include <LiquidCrystal_I2C.h> // display
#include <EEPROM.h>
#include <SoftwareSerial.h> // serial communication for the node 
SoftwareSerial s(5,6); //5rx, 6tx

LiquidCrystal_I2C lcd(0x27,20,4); // display
 
byte statusLed    = 8; // LED physical INPUT


byte sensorInterrupt = 0;  
byte sensorPin       = 2; // Flow sensor input

// The hall-effect flow sensor outputs approximately 4.5 pulses per second per
// litre/minute of flow.
float calibrationFactor = 7.5;

volatile byte pulseCount; 

float flowS;
float flowRate;
unsigned int flowMilliLitres;
long totalMilliLitres;

unsigned long oldTime;


void setup()
{
    lcd.init();     // initialize the lcd 
    lcd.init();      // initialize the lcd 
    Serial.begin(9600);
    s.begin(9600); // Serial communication s.begin(9600);
  
  pinMode(statusLed, OUTPUT); // Power indigator LED
  digitalWrite(statusLed, HIGH);  // Power indigator LED
  pinMode(5, INPUT);
  
  pinMode(sensorPin, INPUT);
  digitalWrite(sensorPin, HIGH);
  pinMode (4,INPUT); // push button INPUT 

  pulseCount        = 0;
  flowS              = 0.0; 
  flowRate          = 0.0;
  flowMilliLitres   = 0;
  totalMilliLitres  = 0;
  oldTime           = 0;

 
  attachInterrupt(sensorInterrupt, pulseCounter, FALLING);

  lcd.backlight();
  lcd.setCursor (3,0);
  lcd.print ("Advanced");
  delay (2000);
  lcd.setCursor (2,1);
  lcd.print ("Water Meter");
  delay(2000);
  lcd.clear();
  delay(1000);

  totalMilliLitres = ((long)EEPROM.read(45) << 24) +
                   ((long)EEPROM.read(45 + 1) << 16) +
                   ((long)EEPROM.read(45 + 2) << 8) +
                   (long)EEPROM.read(45 + 3);

  
}

long l1time=millis(); // if required display on 



void loop()
{

  
//int data= analogRead(0);
//if(s.available()>0)
//{
 //s.write(data/4);
//}




    long analog; // eeprom dec
  bool r1 =  digitalRead(9);  // eeprom reset input  
  bool pushbutton; // push button variable
  pushbutton = digitalRead(4);
 
 if ( pushbutton==1 && (millis()-l1time>100)){
    l1time=millis();
    lcd.backlight();    // if required display on 
      }
  
  if (millis()-l1time>30000){ //display off timeer
    l1time=millis();
    lcd.noBacklight();    // if required display off
}


         
           
           //       EEprom


if (r1==1) { 
  {delay (2000);}
  totalMilliLitres=0;
  analog =0;
 EEPROM.write(45,0);   // RESET THE MEMORY SLOTS.
  EEPROM.write(46,0);
  EEPROM.write(47,0);
  EEPROM.write(48,0);
 lcd.clear() ;
}


analog = totalMilliLitres  ;
 
  EEPROM.write(45, (analog >> 24) & 0xFF);
  EEPROM.write(45 + 1, (analog >> 16) & 0xFF);     //  WRITE TO EEPROM
  EEPROM.write(45 + 2, (analog >> 8) & 0xFF);   
  EEPROM.write(45 + 3, analog & 0xFF);


  

     // making frequency for the frolw sensor.
   
   if((millis() - oldTime) > 1000)    // Only process counters once per second
  { 
    
    detachInterrupt(sensorInterrupt);
        
   
    flowRate = ((1000.0 / (millis() - oldTime)) * pulseCount) / calibrationFactor;
    flowS = (flowRate *100)/6;
    
       
    oldTime = millis();
        
    flowMilliLitres = (flowRate / 60) * 1000;
    totalMilliLitres += flowMilliLitres;
         
    unsigned int frac;

    
    // print the counting details 
    
    Serial.print("Flow rate: ");
    Serial.print(int(flowS));  // Print the integer part of the variable
    Serial.print("ml/Sec");
    Serial.print("\t");       // Print tab space

    // Print the cumulative total of litres flowed since starting
    Serial.print("Output Liquid Quantity: ");        
    Serial.print(totalMilliLitres);
    Serial.println("mL"); 
    Serial.print("\t");       // Print tab space
  Serial.print(totalMilliLitres/1000);
  Serial.print("L");

    lcd.setCursor (0,0);
    lcd.print ("Flow Rate:");
    lcd.setCursor (12,0);
    lcd.print (flowS);
    

    lcd.setCursor (0,1);
    lcd.print ("Units:");
    lcd.setCursor (7,1);
    lcd.print (totalMilliLitres);
    lcd.print("ml");

     if(s.available()>0)  // serial com
    {
    s.write(totalMilliLitres/1000);
    }
 
  

    // Reset the pulse counter so we can start incrementing again
    pulseCount = 0;
    
    // Enable the interrupt again now that we've finished sending output
    attachInterrupt(sensorInterrupt, pulseCounter, FALLING);
  }
}

/*
Insterrupt Service Routine
 */
void pulseCounter()
{
  // Increment the pulse counter
  pulseCount++;
}
