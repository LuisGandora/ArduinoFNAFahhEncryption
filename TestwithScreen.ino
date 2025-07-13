#include <IRremote.h>
#include <LiquidCrystal.h>
//ps needs liquid crystal

//Tutorials used:
//Tutorial for the IR sensor: https://www.youtube.com/watch?v=0DgALFDwouA
//Tutorial for the LED board: https://www.youtube.com/watch?v=s_-nIgo71_w

//Goal:
//Make a arduino board to parse through a amazon bucket

//for IR
IRrecv IR(3); // pin setup for IR

//for LED pins
const int rs = 12, en = 11, d4 = 7, d5 = 6, d6 = 5, d7 = 4;//pins that go in the slot
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

//for the game "H is wall, N is Door opened by 0, 0 is key and 1 is the master signature"
char lis[8][16] = {
    {'_','/','_','_','H','H','H','H','H','H','H','H','_','_','0','/'},
    {'_','/','_','_','H','~','~','~','1','~','~','H','_','_','_','/'},
    {'_','/','_','_','H','~','~','~','~','~','~','H','_','_','_','/'},
    {'_','/','_','_','H','~','~','~','~','~','~','H','_','_','_','/'},
    {'_','/','_','_','H','~','~','~','~','~','~','H','_','_','_','/'},
    {'_','/','_','_','H','H','H','N','N','H','H','H','_','_','_','/'},
    {'/','_','_','_','_','_','_','_','_','/','_','_','/','_','_','_'},
    {'_','/','_','_','/','_','_','_','/','_','/','_','_','_','_','/'},
  };
const int rows = 8;
const int cols = 16;
int curr = 7; //for printing at 1
int nex = 6; // for printing at 0

//bool for gme
bool canPassN = false;
int amount = 0;

//Custom Programs
int horzInt = 0; //moves left and right via fast forward and rewind buttons
int vertInt = 1; //moves up and down via vol up and down buttons


//gets a char by finding the characters place on the lis
char getChar(int x, int xsub, int y)
{
  int tempVert = (xsub == 1) ? 0: 1; //to account for displacement via LCD calc;s
  //Debugging Code
  // Serial.print("Data");
  // Serial.print(" ");
  // Serial.print(curr);
  // Serial.print(" ");
  // Serial.print(tempVert);
  // Serial.print(" ");
  // Serial.print(horzInt);
  // Serial.println(" ");
  
  return lis[x-tempVert][y];
}

//board program-prints board you stupid 
void printBoard(int i, int l)
{
  for(int j = 0; j < 16; j++)
  {
    lcd.setCursor(j,l);
    lcd.print(lis[i][j]);
   
  }
}

void setup() {
  // put your setup code here, to run once:
  
  //IR enabler
  IR.enableIRIn();
  // set up for the LCD's number of columns
  lcd.begin(16,2); 

  //print instructions
  lcd.setCursor(0,0);
  lcd.print("N&H are walls");
  lcd.setCursor(0,1);
  lcd.print("1=goal, 0=key");
  delay(1500);

  lcd.setCursor(0,0);
  lcd.print("Complete with");
  lcd.setCursor(0,1);
  lcd.print("Least moves");
  delay(1500);

  //Not only to set up intervals, but also to set up the intervals for the LEDPin
  printBoard(curr,1);
  printBoard(nex,0);
  Serial.begin(9600);
  
}

void loop() {
  // put your main code here, to run repeatedly:

  

  //For the IR decoder 
  if(IR.decode()){
    // Serial.println(IR.decodedIRData.decodedRawData); //testing code
    if(IR.decodedIRData.decodedRawData == 0xBC43FF00)
    {
      if(getChar(curr, vertInt, horzInt+1) != 'H' && getChar(curr, vertInt, horzInt+1) != 'N')
      {
        horzInt = (horzInt >= 15) ? 0: horzInt+1;
        amount++;
      }
      else if(canPassN && getChar(curr, vertInt, horzInt) == 'N')
      {
        horzInt = (horzInt >= 15) ? 0: horzInt+1;
        amount++;
      }

      
      // Serial.println(IR.decodedIRData.decodedRawData, HEX);
    }
    else if(IR.decodedIRData.decodedRawData == 0xBB44FF00)
    {
      if(getChar(curr, vertInt, horzInt-1) != 'H' && getChar(curr, vertInt, horzInt-1) != 'N')
      {
        horzInt = (horzInt <=0) ? 15: horzInt-1;
        amount++;
      }
      else if(canPassN && getChar(curr, vertInt, horzInt) == 'N')
      {
        horzInt = (horzInt <=0) ? 15: horzInt-1;
        amount++;
      }
     
    }
    else if(IR.decodedIRData.decodedRawData == 0xEA15FF00)
    {
      
      if(vertInt >=2)
      {
          
          if(curr < 7)
          {
            nex = curr;
            curr++;
          }
          if(getChar(curr, 0, horzInt) != 'H' && getChar(curr, 0, horzInt) != 'N')
          {
            vertInt = 0;
            amount++;
            
          }
          else if(canPassN && getChar(curr, 0, horzInt) == 'N')
          {
            vertInt = 0;
            amount++;
          }
          else
          {
            curr--;
          }
      }
      else
      {
        if(getChar(curr, vertInt+1, horzInt) != 'H' && getChar(curr, vertInt+1, horzInt) != 'N')
        {
          vertInt++;
          amount++;
        }
        else if(canPassN &&getChar(curr, vertInt+1, horzInt) == 'N')
        {
          vertInt++;
          amount++;
        }
        
      }
    }
    else if(IR.decodedIRData.decodedRawData == 0xB946FF00)
    {
      if(vertInt <=0)
      {
        if(nex > 0)
        {
          curr = nex;
          nex--;
        }
        if(getChar(curr, 1, horzInt) != 'H' && getChar(curr, 1, horzInt) != 'N')
        {
          vertInt = 1;
          amount++;
          
        }
        else if(canPassN && getChar(curr, 1, horzInt) == 'N')
        {
          vertInt = 1;
          amount++;
        }
        else
        {
          curr++;
          nex++;
        }
        
      }
      else
      {
        if(getChar(curr, vertInt-1, horzInt) != 'H' && getChar(curr, vertInt-1, horzInt) != 'N')
        {
          vertInt--;
          amount++;
          
        }
        else if(canPassN && getChar(curr, vertInt-1, horzInt) == 'N')
        {
          vertInt--;
          amount++;
        }
        
      }
    }
    IR.resume();
  }
  printBoard(curr,1);
  printBoard(nex,0);
  lcd.setCursor(horzInt,vertInt);
  //signal that the player got the key for the gate
  if(getChar(curr, vertInt, horzInt) == '0')
  {
    canPassN = true;
  }
  //signal that the level is complete and record high score
  if(getChar(curr,vertInt,horzInt) == '1')
  {
    Serial.print("Finished Level ");
    Serial.println(amount);
  }
  lcd.print("P");

  
  
  
  delay(1200); //for delay, approx 1.5 s
  lcd.clear();
  //Got it right, just doenst want to work with me cause its stupid, error with IReciever.Resume()???
}
