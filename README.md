# Lipo-Monitor

Pro Mini Controlled Lipo monitor for checking health and controlling to storage voltage. 
I've lost a number of batteries through leaving them fully charged or not noticing that one cell has gone bad only to find out when I get to the flying field and having my session cut short. This device not only offers and easy check of Lipo Health but allows a simple set up with switching a relay to a load bank to allow a controlled discharge down to a storage voltage. This can easily be used with banks of Lipos on a parallel board. 

Please make, enjoy, feedback and share improvements.

+ Measures individual cell voltages
+ Displays Data using OLED screen
+ Controls a Relay to a load bank to allow controlled discharge of Lipo to Storage voltage

![alt text](https://github.com/jrwrodgers/Lipo-Monitor/blob/master/images/Lipo1.jpg "Prototype1")

## Parts List
+ Pro Mini or Arduino Nano
+ SPI SSD1306 OLED 128x64
+ 1xPush Button Switch
+ 1xWS8121b LED
+ 1xBuzzer
+ 3x6k8 Ohm Resistors
+ 1x20k Ohm Resistors
+ 2x10k Ohm Resisitors
+ Assortment of header pins and wires

## Assembly

+ SCHEMATIC HERE
  
![alt text](https://github.com/jrwrodgers/Lipo-Monitor/blob/master/lipo.png "Logo Title Text 1")


## Set Up
+ Measure resistors accurately with ohm meter
+ Enter these into the code
+ Take a known battery and measure voltages of each cell
+ Use ratio of measured cell voltage over the displayed cell voltage and change the correction factors in the code
+ Check with a another battery of different voltage
+ Error +/-3%

## How to
+ Connect Lipo (Check polarity before connecting)
+ Button click will move between modes and screens

### Screen 1
+ Cell Voltages Measured
![alt text](https://github.com/jrwrodgers/Lipo-Monitor/blob/master/images/Screen1.jpg "Screen1")
![alt text](https://github.com/jrwrodgers/Lipo-Monitor/blob/master/images/Screen1_2.jpg "Screen1")


### Screen 2
+ Cell Voltage Delta to Average
+ Good check of balancing and potential bad cells
![alt text](https://github.com/jrwrodgers/Lipo-Monitor/blob/master/images/Screen2.jpg "Screen2")
![alt text](https://github.com/jrwrodgers/Lipo-Monitor/blob/master/images/Screen2_2.jpg "Screen2")

### Screen 3
+ Storage Mode Checks
+ Checks that the Lipo is above storage charge
+ Checks that the cells are balanced ahead of discharge
+ If all checks pass - countdown 5s before storage mode starts
![alt text](https://github.com/jrwrodgers/Lipo-Monitor/blob/master/images/Screen3_1.jpg "Screen3_checks")

### Screen 4
+ Storgage Mode
+ Glow Blue Led
+ Relay closed to Load Bank Control Line
+ Graph of Cell average voltage with time - updates every 2 seconds
+ Relay closed when storage charge acheived
![alt text](https://github.com/jrwrodgers/Lipo-Monitor/blob/master/images/Screen3_2.jpg "Screen3")
![alt text](https://github.com/jrwrodgers/Lipo-Monitor/blob/master/images/Screen3_3.jpg "Screen3")
![alt text](https://github.com/jrwrodgers/Lipo-Monitor/blob/master/images/Screen3_4.jpg "Screen3")
![alt text](https://github.com/jrwrodgers/Lipo-Monitor/blob/master/images/Screen3_5.jpg "Screen3")

## Future Features
+ 3D printed box
+ Cell Impedance Measurement
+ PCB
+ Smart discharge algorithm since the voltage under load is lower. When the load is disconnected there is a "bounce back" of resting lipo voltage. Maybe a 2 stage approach to estimate the voltage under load to give a resting voltage of the desired sotrage voltage.
+ Inbuilt Load Bank Design
+ Multiple Relay for fast discharge
+ Inbuilt relays so XT60 Connection included
+ Current meter for capacity measurements
+ Cell balancing
+ Charging Circuit to LipoBank

