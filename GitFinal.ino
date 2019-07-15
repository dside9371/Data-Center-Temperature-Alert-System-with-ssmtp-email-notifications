/*********************************
 * Written By Khalid Muslih
 * This code is written to work on Arduino YUN REV2
 * Please open the README file first to fully understand the project
**********************************/
// First we include the libraries

#include <FileIO.h>
#include <Process.h>
#include <OneWire.h> 
#include <DallasTemperature.h>
/********************************************************************/
// Data wire is plugged into pin 2 on the Arduino 
#define ONE_WIRE_BUS 2 
/********************************************************************/
// Setup a oneWire instance to communicate with any OneWire devices  
// (not just Maxim/Dallas temperature ICs) 
OneWire oneWire(ONE_WIRE_BUS); 
/********************************************************************/
// Pass our oneWire reference to Dallas Temperature. 
DallasTemperature sensors(&oneWire);
/********************************************************************/
int sensorValue = 0;      // initial sensor value
int emailLED = 8;          //send email LED. connected to pin 8
int highTempLED = 7;       //High Temp LED. . connected to pin 7
/********************************************************************/

void setup() {
  pinMode (emailLED, OUTPUT);
  pinMode (highTempLED, OUTPUT);
  Bridge.begin();  // Initialize the Bridge
 // Serial.begin(9600);  // Initialize the Serial
  FileSystem.begin();
  sensors.begin();
  // Wait until a Serial Monitor is connected.
 // while (!Serial);
}



void loop() {
  // call sensors.requestTemperatures() to issue a global temperature 
  // request to all devices on the bus 
/********************************************************************/
 // Serial.print(" Requesting temperatures..."); 
  sensors.requestTemperatures(); // Send the command to get temperature readings 
  //Serial.println("DONE"); 
/********************************************************************/
 // Serial.print("Temperature is: "); 
  sensorValue = sensors.getTempFByIndex(0);  // Why "byIndex"? 
 // Serial.print(sensorValue);  
   // You can have more than one DS18B20 on the same bus.  
   // 0 refers to the first IC on the wire 
   if(sensorValue > 73) {
      digitalWrite(highTempLED, HIGH);
      delay(200);
      sendAlert(sensorValue);
   }
   else{
      digitalWrite(highTempLED, LOW);
   }
  delay(1000); 
  
}
void sendAlert(int tempAlert) {
  digitalWrite(emailLED, HIGH);
  Process p;
  // This command line runs the WifiStatus script, (/usr/bin/pretty-wifi-info.lua), then
  // sends the result to the grep command to look for a line containing the word
  // "Signal:"  the result is passed to this sketch:
  // p.begin();
  String dataString;
  dataString += "From: GmailUsername@gmail.com\n";
  dataString += "To: ReceivingUser@domain.com\n";
  dataString += "Subject: Temp Alert from the DATA CENTER Yun\n\n";
  dataString += "The Temp in The Data Center is: ";
  dataString += tempAlert;
  File dataFile = FileSystem.open("/root/email.txt", FILE_WRITE);
  // if the file is available, write to it:
  if (dataFile) {

    dataFile.println(dataString);
    dataFile.close();
    // print to the serial port too:
 //   Serial.println(dataString);
  }
  // if the file isn't open, pop up an error:
  else {
 //   Serial.println("error opening datalog.txt");
  }

  delay(200);
  p.runShellCommand("cat /root/email.txt | ssmtp ReceivingUser@domain.com  2>&1");

  while (p.running());
  
  // Read command output. runShellCommand() should have passed "Signal: xx&":
  delay(200);
  while (p.available() > 0) {
    char c = p.read();
  //  Serial.print(c);
  }

  // Ensure the last bit of data is sent.
//  Serial.flush();
//  Serial.println("end");
  digitalWrite(emailLED, LOW);
  delay(60000);  // wait 60 seconds before you do it again
}
