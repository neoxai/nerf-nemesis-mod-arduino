#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#define OLED_BLACK 0
#define OLED_WHITE 1
#define OLED_RESET 4
Adafruit_SSD1306 display(OLED_RESET);

#define LOGO16_GLCD_HEIGHT 16 
#define LOGO16_GLCD_WIDTH  16 
static const unsigned char PROGMEM logo16_glcd_bmp[] =
{ B00000000, B11000000,
  B00000001, B11000000,
  B00000001, B11000000,
  B00000011, B11100000,
  B11110011, B11100000,
  B11111110, B11111000,
  B01111110, B11111111,
  B00110011, B10011111,
  B00011111, B11111100,
  B00001101, B01110000,
  B00011011, B10100000,
  B00111111, B11100000,
  B00111111, B11110000,
  B01111100, B11110000,
  B01110000, B01110000,
  B00000000, B00110000 };

#if (SSD1306_LCDHEIGHT != 64)
#error("Height incorrect, please fix Adafruit_SSD1306.h!");
#endif

void setupOled(){
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);  // initialize with the I2C addr 0x3D (for the 128x64)
  display.clearDisplay();
  drawBattery(100);
  drawInt(99);
}

void drawAmmo(uint8_t i){
  display.clearDisplay();
  drawBattery(100);
  drawInt(99);
}
void drawFireMode(){
  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.setCursor(10,48);
  switch (firingMode){
    case FIREMODE_NONE:
      display.println("---SAFE---");
      break;
    case FIREMODE_SINGLE:
      display.println("SINGLE");
      break;
    case FIREMODE_BURST:
      display.println("3 - BURST");
      break;
    case FIREMODE_FULL:
      display.println("FULL AUTO");
      break;
  }

  display.display();
  delay(1);
}

#define BOX_HEIGHT 16
#define BOX_WIDTH 124
#define BOX_X 2
#define BOX_ROF_OFFSET 14
#define BOX_VELOCITY_OFFSET 44
void drawConfig(uint8_t fly, uint8_t push){
  display.clearDisplay();
  writeText();
  drawConfigBox(push,BOX_ROF_OFFSET);
  drawConfigBox(fly,BOX_VELOCITY_OFFSET);
}
void writeText(){
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(10,0);
  display.println("RATE OF FIRE");
  display.setCursor(10,34);
  display.println("VELOCITY");
  display.display();
  delay(1);
}
void drawConfigBox(uint8_t fill, uint8_t offset){
  display.fillRect(BOX_X, offset, BOX_WIDTH, BOX_HEIGHT,OLED_BLACK);
  display.fillRect(BOX_X, offset, BOX_WIDTH, BOX_HEIGHT,OLED_WHITE);
  display.fillRect(BOX_X+3, offset+3, BOX_WIDTH-6, BOX_HEIGHT-6,OLED_BLACK);
  display.fillRect(BOX_X, offset, fill/2, BOX_HEIGHT,OLED_WHITE);
  display.display();
}
















void drawInt(uint8_t i){
  drawNumberXY(10,10,i/10);
  drawNumberXY(10+36+5, 10,i%10);
}
#define Battery_X 100
#define Battery_Y 6
#define Battery_Width 20
#define Battery_Height 10
#define Battery_NubWidth 2
#define Battery_NubHeight 6
#define Battery_FrameStroke 1
#define Battery_NubPosition 0
#define Battery_Rotate 1

#define NumWidth 36
#define NumHeight 30
#define NumRadius 4
#define NumSegWidth 10
#define NumSegHeight 8
uint8_t NumSegGapWidth;
uint8_t NumSegGapHeight;
void drawNumberXY(uint8_t x, uint8_t y, uint8_t Num){
  NumSegGapWidth = (NumWidth - (3* NumSegWidth))/2;
  NumSegGapHeight = (NumHeight - (3* NumSegHeight))/2;
  display.fillRect(x, y, NumWidth, NumHeight,OLED_BLACK);
  if(Num == 0){
    display.fillRoundRect(x,y, NumWidth, NumHeight, NumRadius, OLED_WHITE);
    display.fillRect(CalcNumWidth(1,0,x), CalcNumHeight(1,0,y), CalcNumWidth(1,2,0), CalcNumHeight(1,2,0),OLED_BLACK);
  }
  else if(Num ==1){
  //Bottom line
  display.fillRect(CalcNumWidth(0,0,x), CalcNumHeight(2,2,y), CalcNumWidth(3,2,0), CalcNumHeight(1,0,0), OLED_WHITE);
  //Upright center
  display.fillRect(CalcNumWidth(1,1,x), CalcNumHeight(0,0,y), CalcNumWidth(1,0,0), CalcNumHeight(3,2,0), OLED_WHITE);
  //top hook
  display.fillRect(CalcNumWidth(0,1,x), CalcNumHeight(0,0,y), CalcNumWidth(2,0,0), CalcNumHeight(1,0,0), OLED_WHITE);
  }
  else if (Num ==2){
    //3 horizontal Lines
    display.fillRoundRect(CalcNumWidth(0,0,x), CalcNumHeight(0,0,y), CalcNumWidth(3,2,0), CalcNumHeight(1,0,0),NumRadius, OLED_WHITE);
    display.fillRoundRect(CalcNumWidth(0,0,x), CalcNumHeight(1,1,y), CalcNumWidth(3,2,0), CalcNumHeight(1,0,0),NumRadius, OLED_WHITE);
    display.fillRoundRect(CalcNumWidth(0,0,x), CalcNumHeight(2,2,y), CalcNumWidth(3,2,0), CalcNumHeight(1,0,0),NumRadius, OLED_WHITE);

    //lower left bridge
    display.fillRoundRect(CalcNumWidth(0,0,x), CalcNumHeight(1,1,y), CalcNumWidth(1,0,0), CalcNumHeight(2,1,0),NumRadius, OLED_WHITE);
    //upper right bridge
    display.fillRoundRect(CalcNumWidth(2,2,x), CalcNumHeight(0,0,y), CalcNumWidth(1,0,0), CalcNumHeight(2,1,0),NumRadius, OLED_WHITE);

    DeroundCorner(x,y,0,0);
    DeroundCorner(x,y,2,2);

  }
  else if (Num==3){
    //3 horizontal Lines
    display.fillRoundRect(CalcNumWidth(0,0,x), CalcNumHeight(0,0,y), CalcNumWidth(3,2,0), CalcNumHeight(1,0,0),NumRadius, OLED_WHITE);
    display.fillRoundRect(CalcNumWidth(0,0,x), CalcNumHeight(1,1,y), CalcNumWidth(3,2,0), CalcNumHeight(1,0,0),NumRadius, OLED_WHITE);
    display.fillRoundRect(CalcNumWidth(0,0,x), CalcNumHeight(2,2,y), CalcNumWidth(3,2,0), CalcNumHeight(1,0,0),NumRadius, OLED_WHITE);
    // right bridge
    display.fillRoundRect(CalcNumWidth(2,2,x), CalcNumHeight(0,0,y), CalcNumWidth(1,0,0), CalcNumHeight(3,2,0),NumRadius, OLED_WHITE);

    DeroundCorner(x,y,0,0);
    DeroundCorner(x,y,0,1);
    DeroundCorner(x,y,0,2);
  }
  else if (Num==4){
    //3 horizontal Lines
    display.fillRoundRect(CalcNumWidth(0,0,x), CalcNumHeight(1,1,y), CalcNumWidth(3,2,0), CalcNumHeight(1,0,0),NumRadius, OLED_WHITE);
    // right bridge
    display.fillRect(CalcNumWidth(2,2,x), CalcNumHeight(0,0,y), CalcNumWidth(1,0,0), CalcNumHeight(3,2,0), OLED_WHITE);
    //left vertical
    display.fillRoundRect(CalcNumWidth(0,0,x), CalcNumHeight(0,0,y), CalcNumWidth(1,0,0), CalcNumHeight(2,1,0) ,NumRadius,OLED_WHITE);
    DeroundCorner(x,y,0,0);
  }
  else if (Num==5){
    //3 horizontal Lines
    display.fillRoundRect(CalcNumWidth(0,0,x), CalcNumHeight(0,0,y), CalcNumWidth(3,2,0), CalcNumHeight(1,0,0),NumRadius, OLED_WHITE);
    display.fillRoundRect(CalcNumWidth(0,0,x), CalcNumHeight(1,1,y), CalcNumWidth(3,2,0), CalcNumHeight(1,0,0),NumRadius, OLED_WHITE);
    display.fillRoundRect(CalcNumWidth(0,0,x), CalcNumHeight(2,2,y), CalcNumWidth(3,2,0), CalcNumHeight(1,0,0),NumRadius, OLED_WHITE);

    
    display.fillRoundRect(CalcNumWidth(2,2,x), CalcNumHeight(1,1,y), CalcNumWidth(1,0,0), CalcNumHeight(2,1,0),NumRadius, OLED_WHITE);
    
    display.fillRoundRect(CalcNumWidth(0,0,x), CalcNumHeight(0,0,y), CalcNumWidth(1,0,0), CalcNumHeight(2,1,0),NumRadius, OLED_WHITE);
    DeroundCorner(x,y, 0,2);
    DeroundCorner(x,y,0,0);
    DeroundCorner(x,y,2,0);
    display.fillRect(CalcNumWidth(3,0,x), CalcNumHeight(0,0,y), CalcNumWidth(0,2,0), CalcNumHeight(1,0,0),OLED_BLACK);
  }
  else if (Num==6){
    //3 horizontal Lines
    display.fillRoundRect(CalcNumWidth(0,0,x), CalcNumHeight(0,0,y), CalcNumWidth(3,2,0), CalcNumHeight(1,0,0),NumRadius, OLED_WHITE);
    display.fillRoundRect(CalcNumWidth(0,0,x), CalcNumHeight(1,1,y), CalcNumWidth(3,2,0), CalcNumHeight(1,0,0),NumRadius, OLED_WHITE);
    display.fillRoundRect(CalcNumWidth(0,0,x), CalcNumHeight(2,2,y), CalcNumWidth(3,2,0), CalcNumHeight(1,0,0),NumRadius, OLED_WHITE);
    
    display.fillRoundRect(CalcNumWidth(0,0,x), CalcNumHeight(0,0,y), CalcNumWidth(1,0,0), CalcNumHeight(3,2,0),NumRadius, OLED_WHITE);
    
    display.fillRoundRect(CalcNumWidth(2,2,x), CalcNumHeight(1,1,y), CalcNumWidth(1,0,0), CalcNumHeight(2,1,0),NumRadius, OLED_WHITE);
    DeroundCorner(x,y,2,0);
  }
  else if (Num==7){
    //Upright center
  display.fillRoundRect(CalcNumWidth(2,1,x), CalcNumHeight(0,0,y), CalcNumWidth(1,0,0), CalcNumHeight(3,2,0), NumRadius, OLED_WHITE);
  //top hook
  display.fillRoundRect(CalcNumWidth(0,0,x), CalcNumHeight(0,0,y), CalcNumWidth(3,1,0), CalcNumHeight(1,0,0), NumRadius, OLED_WHITE);
  DeroundCorner(x,y,0,0);
  display.fillRect(CalcNumWidth(2,1,x),CalcNumHeight(1,1,y), CalcNumWidth(1,0,0), CalcNumHeight(2,1,0), OLED_WHITE);
  }
  else if (Num==8){
    display.fillRoundRect(x,y, NumWidth, NumHeight, NumRadius, OLED_WHITE);
    display.fillRect(CalcNumWidth(1,0,x), CalcNumHeight(1,0,y), CalcNumWidth(1,2,0), CalcNumHeight(1,2,0),OLED_BLACK);
    display.fillRect(CalcNumWidth(1,1,x), CalcNumHeight(1,1,y), CalcNumWidth(2,1,0), CalcNumHeight(1,0,0),OLED_WHITE);
  }
  else if (Num==9){
    //3 horizontal Lines
    display.fillRoundRect(CalcNumWidth(0,0,x), CalcNumHeight(0,0,y), CalcNumWidth(3,2,0), CalcNumHeight(1,0,0),NumRadius, OLED_WHITE);
    display.fillRoundRect(CalcNumWidth(0,0,x), CalcNumHeight(1,1,y), CalcNumWidth(3,2,0), CalcNumHeight(1,0,0),NumRadius, OLED_WHITE);
    display.fillRoundRect(CalcNumWidth(0,0,x), CalcNumHeight(2,2,y), CalcNumWidth(3,2,0), CalcNumHeight(1,0,0),NumRadius, OLED_WHITE);
    // right bridge
    display.fillRoundRect(CalcNumWidth(2,2,x), CalcNumHeight(0,0,y), CalcNumWidth(1,0,0), CalcNumHeight(3,2,0),NumRadius, OLED_WHITE);

    display.fillRoundRect(CalcNumWidth(0,0,x), CalcNumHeight(0,0,y), CalcNumWidth(1,0,0), CalcNumHeight(2,1,0),NumRadius, OLED_WHITE);
    DeroundCorner(x,y,0,2);
  }

  
    display.display();
}

uint8_t CalcNumWidth(uint8_t segs, uint8_t gaps, uint8_t x){
  return x + (segs * NumSegWidth) + (gaps * NumSegGapWidth);
}

uint8_t CalcNumHeight(uint8_t segs, uint8_t gaps, uint8_t y){
  return y + (segs * NumSegHeight) + (gaps * NumSegGapHeight);
}
void DeroundCorner(uint8_t x, uint8_t y, uint8_t vertexX, uint8_t vertexY){
  uint8_t xOffset = CalcNumWidth(vertexX ,vertexX,x);
  uint8_t yOffset =CalcNumHeight(vertexY,vertexY,y);;
  display.fillRect(xOffset, yOffset, NumSegWidth, NumSegHeight, OLED_WHITE);
}




void drawBattery(uint8_t percent){
   
   display.fillRect(Battery_X, Battery_Y, Battery_Width, Battery_Height,OLED_WHITE);
   
   
   //NUB
#if(Battery_NubPosition == 0 && Battery_Rotate==0) //TOP
   {display.fillRect(Battery_X + ((Battery_Width - Battery_NubWidth)/2), Battery_Y-Battery_NubHeight, Battery_NubWidth, Battery_NubHeight, OLED_WHITE);}
#endif
#if(Battery_NubPosition ==1 && Battery_Rotate ==0) //Bottom
   {display.fillRect(Battery_X + ((Battery_Width - Battery_NubWidth)/2), Battery_Y + Battery_Height, Battery_NubWidth, Battery_NubHeight, OLED_WHITE);}
#endif
#if (Battery_NubPosition==0 && Battery_Rotate ==1) //LEFT
   {display.fillRect(Battery_X - Battery_NubWidth, Battery_Y+ ((Battery_Height - Battery_NubHeight)/2), Battery_NubWidth, Battery_NubHeight, OLED_WHITE);}
#endif
#if(Battery_NubPosition ==1 && Battery_Rotate ==1) //RIGHT
   {display.fillRect(Battery_X+Battery_Width, Battery_Y +((Battery_Height - Battery_NubHeight)/2), Battery_NubWidth, Battery_NubHeight, OLED_WHITE);}
#endif

   //EMPTY BATTERY/ALL OLED_BLACK
   display.fillRect(Battery_X + Battery_FrameStroke, Battery_Y + Battery_FrameStroke, Battery_Width - (2* Battery_FrameStroke),Battery_Height - (2*Battery_FrameStroke),OLED_BLACK);


   //FILL CAPACITY
   uint8_t MaxCapacityHeight =Battery_Height - (4*Battery_FrameStroke);
   uint8_t MaxCapacityWidth = Battery_Width - (4*Battery_FrameStroke);
   uint8_t FillCapacityHeight=MaxCapacityHeight;
   uint8_t FillCapacityWidth =MaxCapacityWidth;
   float multiplier = (float)percent/(float)100;
   if (percent ==0 && Battery_Rotate ==0){FillCapacityHeight=0;}
   else if (percent ==0 && Battery_Rotate ==1) {FillCapacityWidth =0;}
   else if (percent < 100 && Battery_Rotate ==0){
    FillCapacityHeight = MaxCapacityHeight * multiplier;
   }
   else if (percent < 100 && Battery_Rotate ==1){
     FillCapacityWidth = MaxCapacityWidth * multiplier;
   }
   //start with default fill offsets for x and y
   uint8_t FillXOffset=Battery_X + (2*Battery_FrameStroke);
   uint8_t FillYOffset=Battery_Y + (2*Battery_FrameStroke);
   if(Battery_NubPosition ==0 && Battery_Rotate ==0){//TOP
    FillYOffset=Battery_Y + (2*Battery_FrameStroke) + MaxCapacityHeight - FillCapacityHeight;
   }
   else if (Battery_NubPosition==0 && Battery_Rotate ==1){//LEFT
    FillXOffset=Battery_X + (2*Battery_FrameStroke) + MaxCapacityWidth - FillCapacityWidth;
   }
   display.fillRect(FillXOffset, FillYOffset, FillCapacityWidth,FillCapacityHeight,OLED_WHITE);
   display.display();
}
