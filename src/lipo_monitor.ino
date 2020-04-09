#include <Wire.h>
#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Smoothed.h>
#include <Adafruit_NeoPixel.h>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

#define OLED_MOSI   11
#define OLED_CLK   13
#define OLED_DC    9
#define OLED_CS    10
#define OLED_RESET 8
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT,
  OLED_MOSI, OLED_CLK, OLED_DC, OLED_RESET, OLED_CS);

const int buttonPin = 2;
const int buzzerPin = 4;
const int LEDPin = 5;
const int LoadPin = 6;
const int nPixels =1;

Adafruit_NeoPixel pixels(nPixels, LEDPin, NEO_GRB + NEO_KHZ800);


#define LOGO_HEIGHT   64
#define LOGO_WIDTH    128
const uint8_t logo_bmp[] PROGMEM = {
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x38, 0xC0, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0xC0, 0x60, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0x00, 0x20, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x38, 0x00, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0xC0, 0x00, 0x18, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x0C, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xE0, 0x00, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x30, 0x00, 0x01, 0x80, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0E, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x80, 0x0E, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xC0, 0x06, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x38, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0E, 0x00, 0x80, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1C, 0x00, 0x40, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1E, 0x00, 0x00, 0xC0, 0x00, 0x30, 0x00, 0x00, 0x00, 0x00,
0x0F, 0x00, 0x3C, 0x3F, 0xD8, 0x01, 0xFF, 0xC0, 0x00, 0x40, 0x00, 0x08, 0x00, 0x00, 0x00, 0x00,
0x0F, 0x00, 0x3C, 0x3F, 0xFC, 0x03, 0xFF, 0xE0, 0x00, 0x30, 0x00, 0x0C, 0x00, 0x00, 0x00, 0x00,
0x0F, 0x00, 0x3C, 0x3D, 0xFE, 0x05, 0xFF, 0xE8, 0x00, 0x0E, 0x00, 0x03, 0x00, 0x00, 0x00, 0x00,
0x0F, 0x00, 0x3C, 0x3E, 0x1F, 0x0B, 0xE1, 0x70, 0x00, 0x01, 0x80, 0x01, 0x80, 0x00, 0x00, 0x00,
0x0F, 0x00, 0x3C, 0x3E, 0x1F, 0x0F, 0x00, 0xBC, 0x00, 0x00, 0xC0, 0x01, 0x80, 0x00, 0x00, 0x00,
0x0F, 0x00, 0x3C, 0x3E, 0x0E, 0x1F, 0x00, 0x18, 0x00, 0x00, 0x38, 0x0C, 0x00, 0x00, 0x00, 0x00,
0x0F, 0x00, 0x3C, 0x3E, 0x0F, 0x1E, 0x00, 0x3E, 0x00, 0x00, 0x06, 0x06, 0x00, 0x00, 0x00, 0x00,
0x0F, 0x00, 0x3C, 0x3E, 0x1F, 0x1E, 0x00, 0x3E, 0x00, 0x00, 0x07, 0x82, 0x00, 0x00, 0x00, 0x00,
0x0F, 0x00, 0x3C, 0x3E, 0x2F, 0x1E, 0x00, 0x1E, 0x00, 0x00, 0x1C, 0x01, 0x00, 0x00, 0x00, 0x00,
0x0F, 0x00, 0x3C, 0x3F, 0xFE, 0x1E, 0x00, 0x1E, 0x00, 0x00, 0x18, 0x00, 0x80, 0x00, 0x00, 0x00,
0x0F, 0x00, 0x3C, 0x3F, 0xFC, 0x1E, 0x00, 0x3E, 0x00, 0x00, 0x0C, 0x00, 0x40, 0x00, 0x00, 0x00,
0x0F, 0x00, 0x3C, 0x3D, 0xF0, 0x1E, 0x00, 0x3E, 0x00, 0x00, 0x01, 0x80, 0x20, 0x00, 0x00, 0x00,
0x0F, 0x00, 0x3C, 0x3E, 0x00, 0x1F, 0x00, 0x18, 0x00, 0x00, 0x00, 0x60, 0x10, 0x00, 0x00, 0x00,
0x0F, 0x00, 0x3C, 0x3E, 0x00, 0x0F, 0x80, 0x7C, 0x00, 0x00, 0x00, 0x38, 0x18, 0x00, 0x00, 0x00,
0x0F, 0x00, 0x3C, 0x3E, 0x00, 0x0B, 0xE1, 0x70, 0x00, 0x00, 0x00, 0x06, 0x04, 0x00, 0x00, 0x00,
0x0E, 0xFC, 0x3C, 0x3E, 0x00, 0x05, 0xFF, 0xF8, 0x00, 0x00, 0x00, 0x01, 0xC2, 0x00, 0x00, 0x00,
0x0F, 0xFC, 0x3C, 0x3E, 0x00, 0x03, 0xFF, 0xD0, 0x00, 0x00, 0x00, 0x00, 0x63, 0x00, 0x00, 0x00,
0x0F, 0xFC, 0x3C, 0x3E, 0x00, 0x01, 0xBF, 0x40, 0x00, 0x00, 0x00, 0x00, 0x18, 0x80, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1E, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0x40, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0xE0, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x70, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0x80, 0x00, 0x00, 0x04, 0x00, 0x00,
0x00, 0x00, 0x1E, 0x00, 0xF0, 0x00, 0x00, 0x00, 0x00, 0x07, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x1F, 0x01, 0xF0, 0x00, 0x00, 0x00, 0x00, 0x07, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x1F, 0x01, 0xF8, 0x00, 0x00, 0x00, 0x00, 0x07, 0x87, 0x80, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x3F, 0x81, 0xF8, 0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0x80, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x3F, 0x83, 0xF8, 0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0x80, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x3F, 0x87, 0xF8, 0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0x80, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x3F, 0xC7, 0xF8, 0x01, 0xE0, 0x0F, 0x1C, 0x07, 0x8B, 0xF0, 0x1E, 0x00, 0xF1, 0x80,
0x00, 0x00, 0x3F, 0xC7, 0xF8, 0x0F, 0xF4, 0x0F, 0x7D, 0x07, 0x8F, 0xF0, 0xFF, 0xC0, 0xF7, 0x80,
0x00, 0x00, 0x39, 0xCF, 0x38, 0x1F, 0xFC, 0x0F, 0xFF, 0x87, 0x8F, 0xF1, 0xFF, 0xE0, 0xFF, 0x80,
0x00, 0x00, 0x39, 0xEF, 0x38, 0x0D, 0x17, 0x0F, 0x8F, 0x87, 0x87, 0x82, 0xE1, 0xD0, 0xF0, 0x00,
0x00, 0x00, 0x78, 0xFE, 0x3C, 0x3C, 0x0E, 0x0F, 0x07, 0x87, 0x87, 0x83, 0x80, 0xF0, 0xF0, 0x00,
0x00, 0x00, 0x78, 0xFE, 0x3C, 0x3C, 0x07, 0x0F, 0x07, 0x87, 0x87, 0x87, 0xC0, 0xF0, 0xF0, 0x00,
0x00, 0x00, 0x78, 0xFE, 0x3C, 0x3C, 0x07, 0x8F, 0x07, 0x87, 0x87, 0x87, 0xC0, 0xF0, 0xF0, 0x00,
0x00, 0x00, 0x78, 0x7C, 0x3C, 0x3C, 0x07, 0x0F, 0x07, 0x87, 0x87, 0x87, 0xC0, 0xF0, 0xF0, 0x00,
0x00, 0x00, 0xF8, 0x78, 0x3C, 0x3C, 0x0F, 0x0F, 0x07, 0x87, 0x87, 0x83, 0xC0, 0xF0, 0xF0, 0x00,
0x00, 0x00, 0xF8, 0x70, 0x3C, 0x0E, 0x07, 0x0F, 0x07, 0x87, 0x87, 0x83, 0xE0, 0x70, 0xF0, 0x00,
0x00, 0x00, 0xF0, 0x38, 0x3C, 0x1F, 0xEC, 0x0F, 0x07, 0x87, 0x87, 0x81, 0xDF, 0xE0, 0xF0, 0x00,
0x00, 0x00, 0xF0, 0x30, 0x3C, 0x0F, 0xFC, 0x0F, 0x07, 0x87, 0x87, 0x80, 0xFF, 0xC0, 0xF0, 0x00,
0x00, 0x00, 0xF0, 0x30, 0x1E, 0x07, 0xF8, 0x0F, 0x07, 0x87, 0x87, 0x80, 0x7F, 0x80, 0xF0, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};


int buttonState = LOW;
long lastDebounceTime = 0;  // the last time the output pin was toggled
long debounceDelay = 300;    // the debounce time; increase if the output flickers

Smoothed <float> a2d1; 
Smoothed <float> a2d2; 
Smoothed <float> a2d3; 
Smoothed <float> a2d4;

float a2d1r;
float a2d2r;
float a2d3r;
float a2d4r;
float last_screen_update = 0.0;
float mode_storage_tstart =0.0;

//float battpc[]={3.27,3.61,3.69,3.71,3.73,3.75,3.77,3.79,3.8,3.82,3.84,3.85,3.87,3.91,3.95,3.98,4.02,4.08,4.11,4.15,4.2};
//float mindelta=100.0;
//unsigned int min=0;


float cellv[4];
float vbat,vcellave,vp,vcelldelta;
unsigned int ncellmax,ncellmin;
float r1ratio=1.0;
float r2ratio=(6770.0+10090.0)/6770.0;
float r3ratio=(6770.0+19800.0)/6770.0;
float r4ratio=(6770.0+30000.0)/6770.0;

float vcorr[4]={1.002683,1.003354,1.005609,1.003901};
float vcellmin=3.3;
float vcellminp=3.5;
float vcellmax=4.2;
float vcellstore=3.85;
float vcelldeltalimit=0.2;

int allSeconds;
int secsRemaining;
int  runMinutes;
int  runSeconds;

int mode=1;
int nmodes=3;
//mode=1 monitor, mode=2 delta v, mode=3 storage;
unsigned int checks1=0; //vbat is above storage
unsigned int checks2=0; //delta v min to max is less than 0.1v
//unsigned int checks3=0;
unsigned int ok_to_store=0;
int rectsize;


#define gbuffersize 30
#define graph_update_freq 2000
# define led_update_freq 100
unsigned int graph_buffer[gbuffersize];
unsigned int graphloop=0;

float last_buffer_update;
float last_led_update;
float led_offset=0.0;

//// SETUP ////////////////////////////////
void setup() {
  Serial.begin(9600);
  pinMode(buttonPin, INPUT);
  pixels.begin();
  if(!display.begin(SSD1306_SWITCHCAPVCC)) {
    Serial.println(F("SSD1306 allocation failed"));
    for(;;); // Don't proceed, loop forever
  }
  display.clearDisplay();

  memset(graph_buffer, 0, gbuffersize * sizeof(unsigned int));
  
  drawbitmap();
 
  a2d1.begin(SMOOTHED_EXPONENTIAL, 10);
  a2d2.begin(SMOOTHED_EXPONENTIAL, 10);
  a2d3.begin(SMOOTHED_EXPONENTIAL, 10);
  a2d4.begin(SMOOTHED_EXPONENTIAL, 10);
  a2d1.clear();
  a2d2.clear();
  a2d3.clear();
  a2d4.clear();
  pixels.clear();  
  pixels.setPixelColor(0, pixels.Color(255, 0, 0)); 
  pixels.show(); 
  tone(buzzerPin,1000,100);
  delay(100);
  pixels.clear();
  pixels.show();
  noTone(buzzerPin);
}


//// MAIN ////////////////////////////////
void loop() {

// Measure pins
read_inputs();

// Convert to Voltages
convert_volts();

//Update screen

if (millis()-last_screen_update>100){
  if(mode==1){
  update_screen1_2();
  }
  else if(mode==2){
    update_screen1_2();   
  }
  else if(mode==3 && (millis()-mode_storage_tstart) <= 5000.0 ){   
    check_storage();
    storage_start_screen();   
    if(checks1==1 & checks2==1){
    ok_to_store=1;}
    else{
    ok_to_store=0;
  }    
  }
  else if(mode==3 && (millis()-mode_storage_tstart) > 5000.0 ){
    if(ok_to_store==1){
    check_storage();
    update_graph_buffer();
    update_screen3();
    if((millis()-last_led_update) > led_update_freq){
    pixels.setPixelColor(0, pixels.Color(0, 0, 255));
    pixels.setBrightness(255-led_offset);
    pixels.show();
    led_offset=led_offset+50;
    if(led_offset>255){
      led_offset=0;
    }
    last_led_update=millis();
    }

    // Set load pin on
     digitalWrite(LoadPin, HIGH);
    
    if(checks1==0 || checks2==0){
      mode=5;
    }
    
  }
    else{
      mode=4;
      mode_storage_tstart=0.0;      
    }   
  }
  else if(mode==4){
    pixels.clear();  
    pixels.setPixelColor(0, pixels.Color(255, 0, 0)); 
    pixels.show(); 
    tone(buzzerPin,500,1000);
    delay(1000);
    pixels.clear();
    pixels.show();
    noTone(buzzerPin);
    storage_start_screen();   
  }
  else if (mode==5){

    digitalWrite(LoadPin, LOW);
    ok_to_store=0;
    update_graph_buffer();
    update_screen3();

    if(checks1==0){
    //pixels.clear();  
    pixels.setPixelColor(0, pixels.Color(0, 255, 0)); 
    pixels.show();
    }

    if(checks2==0){
    pixels.setPixelColor(0, pixels.Color(255, 0, 0));
    tone(buzzerPin,500,1000); 
    pixels.show(); 
    }
     
  }
  
  
  last_screen_update = millis();
  }

buttonState = digitalRead(buttonPin);

  //filter out any noise by setting a time buffer
  if ( (millis() - lastDebounceTime) > debounceDelay) {
    if ( (buttonState == HIGH)) { 
      mode=mode+1; 
      lastDebounceTime = millis();
      if (mode > nmodes){
        mode=1;   
    }
      for (int i=0; i<=mode-1; i++){
      pixels.clear();  
      pixels.setPixelColor(0, pixels.Color(0, 150, 0)); 
      pixels.show(); 
      tone(buzzerPin,1000,100);
      delay(100);
      pixels.clear();
      pixels.show();
      noTone(buzzerPin);
      delay(50);
      }
      if (mode==3){
        mode_storage_tstart=millis();
      }
      
    }
  } 

}//end loop




//// READ INPUTS ////////////////////////////////
void read_inputs(void){
float a2d1t = analogRead(A0);
float a2d2t = analogRead(A1);
float a2d3t = analogRead(A2);
float a2d4t = analogRead(A3);

a2d1.add(a2d1t);
a2d2.add(a2d2t);
a2d3.add(a2d3t);
a2d4.add(a2d4t);

a2d1r=a2d1.get();
a2d2r=a2d2.get();
a2d3r=a2d3.get();
a2d4r=a2d4.get();

}


//// CONVERT VOLTS ////////////////////////////////
void convert_volts(void){
  cellv[0]=(vcorr[0]*(r1ratio*(5.0*float(a2d1r)/1023.0f)));
  cellv[1]=(vcorr[1]*(r2ratio*(5.0*float(a2d2r)/1023.0f)))-cellv[0];
  cellv[2]=(vcorr[2]*(r3ratio*(5.0*float(a2d3r)/1023.0f)))-cellv[0]-cellv[1];
  cellv[3]=(vcorr[3]*(r4ratio*(5.0*float(a2d4r)/1023.0f)))-cellv[0]-cellv[1]-cellv[2];
  
  vbat=cellv[0]+cellv[1]+cellv[2]+cellv[3];
  vcellave=(cellv[0]+cellv[1]+cellv[2]+cellv[3])/4;
  vp=((((cellv[0]+cellv[1]+cellv[2]+cellv[3])/4)-vcellminp)/(vcellmax-vcellminp))*100;
  if(vp<0.0){
    vp=0.0;
  }

//  vcellave=3.85;
//  mindelta=100.0;
//  min=0;
//  for(int i=0; i<20; i++){
//    
//    if(abs(battpc[i]-vcellave)<mindelta){
//      min=i;
//      mindelta=battpc[i]-vcellave;
//    }
//    vp=float(i*5);
//  Serial.print(i);
//  Serial.print(",");
//  Serial.print(min);
//  Serial.print(",");
//  Serial.print(mindelta);
//  Serial.print(",");
//  Serial.println(battpc[i]);
//  }
//  Serial.print(vcellave);
//  Serial.print(",");
//  Serial.println(vp);

  ncellmin=getMin(cellv, 4);
  ncellmax=getMax(cellv, 4);
  vcelldelta=cellv[ncellmax]-cellv[ncellmin];
  
   if(mode==2){
    cellv[0]=cellv[0]-vcellave;
    cellv[1]=cellv[1]-vcellave;
    cellv[2]=cellv[2]-vcellave;
    cellv[3]=cellv[3]-vcellave;
   }
}


//// UPDATE SCREEN 1 2 ////////////////////////////////
void update_screen1_2(void){

  display.clearDisplay();
  display.setTextSize(1);             
  display.setTextColor(SSD1306_WHITE);        
  display.setCursor(0,10);             
  display.print(F("V1:"));
  display.setCursor(20,10);
  display.print(cellv[0],2);
  display.println(F("v"));
  
  display.setCursor(0,20);
  display.print(F("V2:"));
  display.setCursor(20,20);
  display.print(cellv[1],2);
  display.println(F("v"));
  
  display.setCursor(0,30);
  display.print(F("V3:"));
  display.setCursor(20,30);
  display.print(cellv[2],2);
  display.println(F("v"));
  
  display.setCursor(0,40);
  display.print(F("V4:"));
  display.setCursor(20,40);
  display.print(cellv[3],2);
  display.println(F("v"));

  display.setTextSize(1);
  display.setCursor(0,0);
  if(mode==1){ 
   display.print(F("MONITOR"));
   display.drawRect(60, 5, 61, 46, SSD1306_WHITE);
   display.drawLine(60, 1, 60, 5, SSD1306_WHITE);
   display.drawLine(60+int(((vcellstore-vcellmin)/(vcellmax-vcellmin))*60), 1, 60+int(((vcellstore-vcellmin)/(vcellmax-vcellmin))*60), 50, SSD1306_WHITE);
   display.drawLine(120, 1, 120, 5, SSD1306_WHITE);
   display.drawRect(60, 10, int(((cellv[0]-vcellmin)/(vcellmax-vcellmin))*60), 8, SSD1306_WHITE);
   display.drawRect(60, 20, int(((cellv[1]-vcellmin)/(vcellmax-vcellmin))*60), 8, SSD1306_WHITE);
   display.drawRect(60, 30, int(((cellv[2]-vcellmin)/(vcellmax-vcellmin))*60), 8, SSD1306_WHITE);
   display.drawRect(60, 40, int(((cellv[3]-vcellmin)/(vcellmax-vcellmin))*60), 8, SSD1306_WHITE);
   }
  else if(mode==2){
   display.print(F("DELTA V"));
   display.drawRect(60, 5, 61, 46, SSD1306_WHITE);
   display.drawLine(60, 1, 60, 50, SSD1306_WHITE);
   display.drawLine(90, 1, 90, 50, SSD1306_WHITE);
   display.drawLine(120, 1, 120, 5, SSD1306_WHITE);

   //drawdeltabar(cellv[0],0,10);
   
   if (cellv[0]<0){
   rectsize=int(((-1.0*cellv[0])/(vcelldeltalimit/2.0))*30);
    if (ncellmax==0 || ncellmin==0){
    display.fillRect(90-rectsize+1, 10, rectsize, 8, SSD1306_WHITE);
    }
    else {
    display.drawRect(90-rectsize+1, 10, rectsize, 8, SSD1306_WHITE);
    }
   }
   else{
    rectsize=int((cellv[0]/(vcelldeltalimit/2.0))*30);
    if (ncellmax==0 || ncellmin==0){
   display.fillRect(90, 10, rectsize, 8, SSD1306_WHITE);
    }
    else{
     display.drawRect(90, 10, rectsize, 8, SSD1306_WHITE); 
    }
   }

   if (cellv[1]<0){
   rectsize=int(((-1.0*cellv[1])/(vcelldeltalimit/2.0))*30);
    if (ncellmax==1 || ncellmin==1){
    display.fillRect(90-rectsize+1, 20, rectsize, 8, SSD1306_WHITE);
    }
    else {
    display.drawRect(90-rectsize+1, 20, rectsize, 8, SSD1306_WHITE);
    }
   }
   else{
    rectsize=int((cellv[1]/(vcelldeltalimit/2.0))*30);
    if (ncellmax==1 || ncellmin==1){
   display.fillRect(90, 20, rectsize, 8, SSD1306_WHITE);
    }
    else{
     display.drawRect(90, 20, rectsize, 8, SSD1306_WHITE); 
    }
   }

  if (cellv[2]<0){
   rectsize=int(((-1.0*cellv[2])/(vcelldeltalimit/2.0))*30);
    if (ncellmax==2 || ncellmin==2){
    display.fillRect(90-rectsize+1, 30, rectsize, 8, SSD1306_WHITE);
    }
    else {
    display.drawRect(90-rectsize+1, 30, rectsize, 8, SSD1306_WHITE);
    }
   }
   else{
    rectsize=int((cellv[2]/(vcelldeltalimit/2.0))*30);
    if (ncellmax==2 || ncellmin==2){
   display.fillRect(90, 30, rectsize, 8, SSD1306_WHITE);
    }
    else{
     display.drawRect(90, 30, rectsize, 8, SSD1306_WHITE); 
    }
   }

   if (cellv[3]<0){
   rectsize=int(((-1.0*cellv[3])/(vcelldeltalimit/2.0))*30);
    if (ncellmax==3 || ncellmin==3){
    display.fillRect(90-rectsize+1, 40, rectsize, 8, SSD1306_WHITE);
    }
    else {
    display.drawRect(90-rectsize+1, 40, rectsize, 8, SSD1306_WHITE);
    }
   }
   else{
    rectsize=int((cellv[3]/(vcelldeltalimit/2.0))*30);
    if (ncellmax==3 || ncellmin==3){
   display.fillRect(90, 40, rectsize, 8, SSD1306_WHITE);
    }
    else{
     display.drawRect(90, 40, rectsize, 8, SSD1306_WHITE); 
    }
   }

  
  }
  else{
  }

  if(mode==1){ 
  display.setTextSize(1);
  display.setCursor(0,55); 
  display.print(vcellave,2);
  display.println(F("v"));
  }
  else if(mode==2){
  display.setTextSize(1);
  display.setCursor(0,55); 
  display.print(vcelldelta,2);
  display.println(F("dv")); 
  }
  display.setTextSize(1);
  display.setCursor(50,55);
  display.print(vbat,2);
  display.println(F("v"));
  display.setCursor(100,55);
  display.print(vp,0);
  display.println(F("%"));
  display.display();
 
}


//// UPDATE SCREEN 3 ////////////////////////////////
void update_screen3(void){
  display.clearDisplay();
  display.setTextSize(1);
  display.setCursor(85,0);
  display.print(F("STORAGE"));
  display.setTextSize(1);
  display.setCursor(95,10); 
  display.print(vbat,1);
  display.println(F("v"));
  display.setCursor(95,20);
  display.print(vcellave,2);
  display.println(F("v"));
  display.setCursor(95,30);
  display.print(vcelldelta,2);
  display.println(F("v"));
  display.setCursor(95,40);
  display.print(vp,0);
  display.println("%");
  display.setCursor(30,0);
  allSeconds=(millis()-mode_storage_tstart-5000.0)/1000;
  secsRemaining=allSeconds%3600;
  runMinutes=secsRemaining/60;
  runSeconds=secsRemaining%60;
  display.print(runMinutes);
  display.print(F("m"));
  display.print(runSeconds);
  display.println(F("s"));

  // graph vbat history

  //plot axes
  display.setCursor(0,0);
  display.println(F("v"));
  display.drawLine(8, 4, 8, 57, SSD1306_WHITE);
  display.drawLine(6, 55, 90, 55, SSD1306_WHITE);
  display.drawPixel(6, 10, SSD1306_WHITE);
  display.drawPixel(7, 10, SSD1306_WHITE);

  for(int i=0; i<=(90-6); i=i+3){
   display.drawPixel(6+i, 45, SSD1306_WHITE);
  }

  for(int i=0; i<=(90-6); i=i+3){
   display.drawPixel(6+i, 10, SSD1306_WHITE);
  }

  for(int i=0; i<gbuffersize; i++){
    display.drawPixel((70-(2*gbuffersize))+(2*i), graph_buffer[i], SSD1306_WHITE);
    display.drawPixel((70-(2*gbuffersize))+(2*i)-1, graph_buffer[i], SSD1306_WHITE);
  }
  display.drawCircle(70, graph_buffer[gbuffersize-1], 2, SSD1306_WHITE);

  for(int i=6; i<90; i=i+10){
    display.drawPixel(6+i-(2*graphloop), 56, SSD1306_WHITE);
    display.drawPixel(6+i-(2*graphloop), 57, SSD1306_WHITE);
  }

  if(checks1==0){
    display.setTextSize(1);             
    display.setTextColor(SSD1306_WHITE);        
    display.setCursor(30,15);             
    display.print(F("STORAGE"));
    display.setCursor(30,25);
    display.print(F("COMPLETE"));
    }
   if(checks2==0){
    display.setTextSize(1);             
    display.setTextColor(SSD1306_WHITE);        
    display.setCursor(30,15);             
    display.print(F("Cell dV"));
    display.setCursor(30,25);
    display.print(F("Error"));
    }
   
  display.display();  
}


//// STORAGE CHECKS ////////////////////////////////
void check_storage(void){
  if(vcellave>vcellstore){
    checks1=1;}
    else {
    checks1=0;
    }
  
  if(vcelldelta<vcelldeltalimit){
    checks2=1;}
    else{
      checks2=0;
    }
}


//// STORAGE START SCREEN ////////////////////////////////
void storage_start_screen(void){
  display.clearDisplay();
  display.setTextSize(1);
  display.setCursor(0,0);
  display.print(F("Storage Start Checks"));
  display.setCursor(0,12);
  display.print(F("VCell Av"));
  display.setCursor(50,12);
  display.print(F("= "));
  display.print(vcellave,2);
  display.print(F("v "));
  display.setCursor(100,12);
  if(checks1==1){
    display.print(F("OK"));
  }
  else{
    display.print(F("FAIL"));
  }
  display.setCursor(0,24);
  display.print(F("Store dV"));
  display.setCursor(50,24);
  display.print(F("= "));
  display.print((vcellave-vcellstore),2);
  display.print(F("v "));
  display.setCursor(100,24);
  if(checks1==1){
    display.print(F("OK"));
  }
  else{
    display.print(F("FAIL"));
  }
  display.setCursor(0,36);
  display.print(F("Cell dV"));
  display.setCursor(50,36);
  display.print(F("= "));
  display.print((vcelldelta),2);
  display.print(F("v "));
  display.setCursor(100,36);
  if(checks2==1){
    display.print(F("OK"));
  }
  else{
    display.print(F("FAIL"));
  }
  display.setCursor(100,54);
  display.setTextSize(1);
  display.print(5.0-((millis()-mode_storage_tstart)/1000.0),0);
  display.display();

  //level the graph buffer
  for (int i = 0; i<gbuffersize; i++){
    graph_buffer[i]=int(45.0-((vcellave-vcellstore)/0.0129));
  }

}





//// DRAW BITMAP ////////////////////////////////
void drawbitmap(void) {
  display.clearDisplay();

  display.drawBitmap(
    (display.width()  - LOGO_WIDTH ) / 2,
    (display.height() - LOGO_HEIGHT) / 2,
    logo_bmp, LOGO_WIDTH, LOGO_HEIGHT, 1);
  display.setTextSize(1);             
  display.setTextColor(SSD1306_WHITE);        
  display.setCursor(95,0);             
  display.print(F("V1.0"));
  
  display.display();
  delay(800);
}


//// UPDATE GRAPH BUFFER ////////////////////////////////
void update_graph_buffer(void){
//j10=4.2v
//j45=3.85v

if(millis()-last_buffer_update>graph_update_freq){
 for(int i=1; i<gbuffersize; i++){
  graph_buffer[i-1]=graph_buffer[i];
 }
 graph_buffer[gbuffersize-1]=int(45.0-(vcellave-vcellstore)/0.0129);
 last_buffer_update=millis();
 graphloop=graphloop+1;
 if(graphloop > 10){
  graphloop=0; 
 }
 }
}


//// FUNCTION MIN ////////////////////////////////
int getMin(float* array, int size){
int minIndex = 0;
 float min = array[minIndex];
 for (int i=1; i<size; i++){
   if (array[i] < min){           
     minIndex = i;
     min = array[i];
   }
 }
 return minIndex;
}


//// FUNCTION MAX ////////////////////////////////
int getMax(float* array, int size){
int maxIndex = 0;
 float max = array[maxIndex];
 for (int i=1; i<size; i++){
   if (array[i] > max){         
     maxIndex = i;
     max = array[i];
   }
 }
 return maxIndex;
}
