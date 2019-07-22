# Data-Center-Temperature-Alert-System-with-ssmtp-email-notifications
I created this system because we had an issue with our HVAC unit in our Data Center.

Hardware: Arduino YUN REV2, Gikfun DS18B20 Temperature Sensors, 2 LEDs, 2 220ohm Resistors, and 1 4.7Kohm resistor.

steps: 
  start getting familiar with your YUN. The Arduino YUN comes with 2 Interfaces. the Linux interface and the Arduino interface.
Connect your YUN to your PC and access the web interface.

  A lot of the YUN functions can be modified through the IDE and the YUN web interface.
Set up your wifi connection/ethernet and your root credentials and memorize your YUN localhost 
then access the Linux realm through ssh. I used Putty to do that.
 
 If you are planning to use gmail to send your ssmtp notifications then you need to
create a gmail account, enable 2 factor authentication, and create an app password  


The Linux Realm
---------------

After you ssh-ed to the device you need to install the ssmtp package through command line

$opkg update

$opkg install ssmtp  

Configure your ssmtp configuration file by using vi

$vi  /etc/ssmtp/ssmtp.conf

  root=username@gmail.com 
  
  mailhub=smtp.gmail.com:587
  
  rewriteDomain= 
  
  hostname=” your YUN IP” 
  
  UseSTARTTLS=YES 
  
  AuthUser= username@gmail.com 
  
  AuthPass=GmailAppPassword 
  
  FromLineOverride=YES

Save your vi file

create a text file as a place holder for the code in the root directory and name it email.txt

The Arduino Realm
-----------------

  I provided the code for this project 😊 have a blast with it

The Circuit
-----------

  I provided a picture for wiring the sensor. I also used 2 LEDs to notify me when the temperature is over the previously set threshold
and when the YUN is sending the ssmtp email 
