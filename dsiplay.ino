/*YF- S201 water Flow sensor code for Arduino */
#include <LiquidCrystal.h>
LiquidCrystal lcd(4, 7, 9, 10, 11, 12);
const int Output_Pin = 2;

volatile int  Pulse_Count;
unsigned int  Liter_per_hour;
unsigned long Current_Time, Loop_Time;

// Declare a new variable to store the total number of liters
unsigned long totalLiters;

void setup()
{ 
   pinMode(Output_Pin, INPUT);
   Serial.begin(9600); 
   attachInterrupt(0, Detect_Rising_Edge, FALLING);
                                     
   Current_Time = millis();
   Loop_Time = Current_Time;
   lcd.begin(16, 2);
   lcd.clear();
   lcd.setCursor(0,0);
   lcd.print("Water Flow Meter");
   lcd.setCursor(0,1);
   lcd.print("Microcontrollers Lab");
} 

void loop ()    
{
   Current_Time = millis();
   if(Current_Time >= (Loop_Time + 1000))
   {
      Loop_Time = Current_Time;
      Liter_per_hour = (Pulse_Count * 60 / 7.5);
      
      // Calculate the total number of liters that have flowed through the sensor
      totalLiters += (Pulse_Count * 60 / 450.0);
      
      if(Pulse_Count != 0){
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("Rate: ");
      lcd.print(Liter_per_hour);
      lcd.print(" L/M");
      
      // Display the total number of liters on the second line of the LCD
      lcd.setCursor(0,1);
      lcd.print("Total: ");
      lcd.print(totalLiters);
      lcd.print(" L");
      
      Pulse_Count = 0;
      Serial.print(Liter_per_hour, DEC);
      Serial.println(" Liter/hour");
       }
    else {
      Serial.println(" flow rate = 0 ");
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("Rate: ");
      lcd.print( Liter_per_hour );
      lcd.print(" L/M");
      
      // Display the total number of liters on the second line of the LCD
      lcd.setCursor(0,1);
      lcd.print("Total: ");
      lcd.print(totalLiters);
      lcd.print(" L");
    }
   }
   
}
void Detect_Rising_Edge ()
{ 
   Pulse_Count++;
} 


/* The sketch uses the LiquidCrystal library to display the flow rate in liters per minute on an LCD display, and also prints the flow rate to the serial monitor.

The sketch starts by including the LiquidCrystal library and setting up the LCD display using the lcd object. It then defines the output pin of the water flow sensor as a constant and sets it as an input. The serial port is also set up with a baud rate of 9600.

Next, an interrupt service routine (ISR) called "Detect_Rising_Edge" is attached to interrupt 0 (digital pin 2), which will be triggered on a falling edge (when the pin goes from high to low). The ISR simply increments the Pulse_Count variable by one each time it is called.

In the setup() function, the LCD display is initialized and a welcome message is displayed.

In the loop() function, the flow rate is calculated and displayed on the LCD and serial monitor every second. 
The flow rate is calculated by multiplying the Pulse_Count (which is the number of pulses detected by the sensor in the last second) 
by 60 and dividing by 7.5, which is a conversion factor specific to the YF-S201 sensor. The flow rate is then displayed on the LCD and serial monitor in liters per minute. 
If the Pulse_Count is zero (indicating no flow), a message is displayed on the LCD and serial monitor indicating that the flow rate is zero. 
------------------------------------------
In the line totalLiters += (Pulse_Count * 60 / 450.0);, the total number of liters is being updated by adding the number of liters that have flowed through the sensor in the last second.

Here's how the calculation works:

    Pulse_Count is the number of pulses detected by the sensor in the last second.
    The water flow sensor produces 450 pulses per liter of water, so Pulse_Count / 450.0 gives the number of liters that have flowed through the sensor in the last second.
    The value is multiplied by 60 to convert from liters per second to liters per minute.
    The resulting value is added to the totalLiters variable, which keeps track of the total number of liters that have flowed through the sensor.
-------------------------------------------
The YF-S201 water flow sensor produces 450 pulses per liter of water. This is a specific characteristic of the sensor, and is included in the documentation provided by the manufacturer.

The pulse rate of a water flow sensor is usually expressed in pulses per unit of volume (e.g. pulses per liter). The pulse rate can vary depending on the specific design and characteristics of the sensor. 
In the case of the YF-S201, it produces 450 pulses per liter of water.

 
the flow rate is calculated by dividing the number of pulses detected by the sensor in the last second (Pulse_Count) by 450 and multiplying by 60. 
This converts the flow rate from pulses per second to liters per minute.


*/