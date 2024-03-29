#define NOTE_E3 165
#define NOTE_F3 175
#define NOTE_G3 196
#define NOTE_A3 220
#define NOTE_B3 246
#define NOTE_G4 415
#define NOTE_F4 369
#define NOTE_E 329
#define  NOTE_Eb 311
#define  NOTE_F 349
#define  NOTE_D 293
#define  NOTE_C 261
#define  NOTE_B 246

int melody1[] = {
  NOTE_G4,NOTE_F4,NOTE_E , NOTE_B3, NOTE_E,NOTE_F4,NOTE_G4,
  NOTE_E,NOTE_E3,NOTE_G3,NOTE_A3,NOTE_F3
};

int melody2[] = {
  NOTE_Eb,NOTE_F,NOTE_D,NOTE_Eb,NOTE_D,NOTE_C,NOTE_B
};

int noteDurations[] = {
  4,4,4,4,4,4,4,4,4,4,4,4
};

int noteDurations2[] = {
  4,4,4,4,4,4,4
};

int thisNote = -1, thisNote2 = -1, noteDuration = 0;
long previousTime = 0,presentTime = 0,pauseBetweenNotes = 0;
int latchPin = 8,clockPin = 12,dataPin = 11,button1 = 2,button2 = 3;

byte previousState = 1, presentState = 1, pattern = 0;
byte previousState2 = 1, presentState2 = 1, song = 0;

byte colDataMatrix[8] = {
  B11111110,
  B11111101,
  B11111011,
  B11110111,
  B11101111,
  B11011111,
  B10111111,
  B01111111
};

byte rowDataMatrix[8] = {
  B00111100,
  B00111100,
  B00111100,
  B00000000,
  B00000000,
  B00000000,
  B00111100,
  B00111100
};
byte rowDataMatrix2[8] = {
  B11000011,
  B10111101,
  B01111110,
  B01111110,
  B01111110,
  B01111110,
  B10111101,
  B11000011
};       

void setup() {
  pinMode(latchPin,OUTPUT);
  pinMode(clockPin,OUTPUT);
  pinMode(dataPin,OUTPUT); 
  pinMode(button1,INPUT_PULLUP); 
  pinMode(button2,INPUT_PULLUP); 
}

void Button1()
{
  presentState = digitalRead(button1);
  if(presentState == 0 && previousState == 1)
  {
    pattern ++;
    if(pattern > 1)
    {
      pattern = 0;
    }
  }
  delay(3);
  previousState = presentState;
}

void Button2()
{
  presentState2 = digitalRead(button2);
  if(presentState2 == 0 && previousState2 == 1)
  {
    song ++;
    if(song > 1)
    {
      song = 0;
    }
  }
  delay(3);
  previousState2 = presentState2;
}
void checkToPlay1()
{
  presentTime = millis();
  if(presentTime - previousTime >= pauseBetweenNotes)
  {
    thisNote++;
    if(thisNote >= 12)
    {
      thisNote = -1;
      pauseBetweenNotes = 100;
      previousTime = millis();
    }
    else
    {
      noteDuration = 500/ noteDurations[thisNote];
      tone(9, melody1[thisNote], noteDuration);
      pauseBetweenNotes = noteDuration * 1.2;
      previousTime = millis();
    }
  }
}
void checkToPlay2()
{
  presentTime = millis();
  if(presentTime - previousTime >= pauseBetweenNotes)
  {
    thisNote2++;
    if(thisNote2 >= 7)
    {
      thisNote2 = -1;
      pauseBetweenNotes = 100;
      previousTime = millis();
    }
    else
    {
      noteDuration = 500/ noteDurations2[thisNote2];
      tone(9, melody2[thisNote2], noteDuration);
      pauseBetweenNotes = noteDuration * 1.2;
      previousTime = millis();
    }
  }
}
void loop() {
  Button1();
  Button2();
  for(int i = 0; i < 8 ; i++){
    digitalWrite(latchPin,LOW);
    shiftOut(dataPin,clockPin,MSBFIRST,colDataMatrix[i]);
    if(pattern == 0) shiftOut(dataPin,clockPin,MSBFIRST,rowDataMatrix[i]);
    else shiftOut(dataPin,clockPin,MSBFIRST,rowDataMatrix2[i]);
    digitalWrite(latchPin,HIGH);
    if(song == 0) checkToPlay1();
    else checkToPlay2();
    delay(1);
  }
  
}








