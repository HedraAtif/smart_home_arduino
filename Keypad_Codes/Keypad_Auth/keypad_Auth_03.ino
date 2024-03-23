#include <Keypad.h> //include header file

// Define the rows and columns of the keypad 4x4
const byte ROWS = 4; // Four rows
const byte COLS = 4; // Four columns

// Define the symbols on the buttons of the keypad using two diementions array
char keys[ROWS][COLS] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};

// Connect keypad ROW0, ROW1, ROW2 and ROW3 to these Arduino pins.(digital pins)
byte rowPins[ROWS] = {9, 8, 7, 6}; // Rows 0 to 3

// Connect keypad COL0, COL1 and COL2 to these Arduino pins.(digital pins)
byte colPins[COLS] = {5, 4, 3, 2}; // Columns 0 to 3

// Create the Keypad object
Keypad mykeypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);//takes function that takes keys as a map
//////////////////////////////////GLOBAL VARIABLES//////////////////////////////////////////
char enteredPassword[4];//store entered password entered by user in an array
byte i = 0;//global counter to  iterate over entered password
char correctPassword[4] = {'1','2','3','4'};// store correct password in an array
byte countWrong = 0; // counts wrong digits entered
char symbols[6] = {'A','B','C','D','#','*'};

//////////////////////////////GLOBAL FUNCTIONS/////////////////////////////////////
void optionMenu(char symbol);
void enterPassword();
bool passwordCheck();
void confirmPassword();
void resetPassword();
void clearPassword();
//////////////////////////////////SETUP FUNCTION///////////////////////////////////
void setup() {
  Serial.begin(9600);//initate bandwidth of data to 9600 with serial monitor
  Serial.println("Enter a Password of 4 numeric digits please :");
  
}
////////////////////////////LOOP FUNCTION///////////////////////////////////////////
void loop() {
  enterPassword();
  // passwordCheck();
  
}
////////////////////////////////////FUNCTIONS IMPLEMENTATIONS////////////////////////////////////

void optionMenu(char symbol)
{
    switch (symbol)
    {
      case 'A':
        resetPassword();//changes in correct password array
        break;
      case 'B':
        // confirmPassword();// no confirm but only check 
        break;
      case 'C':
        clearPassword();
        break;
      case 'D':
        passwordCheck();
        break;
    }
}

void enterPassword()
{
  
  label:
  char key = mykeypad.getKey();
  // Check if a key is pressed
  if (key) {
    // Print the key to the serial monitor
    Serial.println(key);
    for(byte rows = 0;rows < ROWS;rows++)
    {
      if(key == keys[rows][3])
      {
        // Serial.println("Enter only numeric Values from 0 to 9");
        optionMenu(key);//goes to option menu to choose from it a key
   		  goto label;
        // break;
      }
      else if(key == keys[3][2] || key == keys[3][0])
      {
        Serial.println("Enter only numeric Values from 0 to 9");
        // optionMenu(key);//goes to option menu to choose from it a key
   		  goto label;
        break;
      }
    }
    
    enteredPassword[i] = key;
    i++;
    
  }
}

bool passwordCheck()
{
  if(i >= 4) // must be 4 casuse less than 4 will not store 4 digits
  {
      for(byte j = 0;j < 4;j++)
  	  {
        // Serial.print(enteredPassword[j]);
        if(enteredPassword[j] != correctPassword[j])
        {
          countWrong++;
          break;
        }
  
      }
    Serial.println();
    i = 0;
    bool check = false; // return final value
    if(countWrong)
    {
      Serial.println("Password is Wrong");
      check = false;
    }
        
    else
    {
      Serial.println("Password is Correct");
      check = true;
    }
    countWrong = 0;//reset count to zero
    return check;
    
	}
}

void resetPassword()
{
  Serial.println("Enter old password to check : ");
  while(i < 4)
  {
    enterPassword();
  }
  
  // for(byte p = 0;p < 4;p++)
  // {
  //   Serial.print(enteredPassword[p]);
  // }
  // for(byte p = 0;p < 4;p++)
  // {
  //   Serial.print(correctPassword[p]);
  // }
  // Serial.println(i);i = 4
  if(passwordCheck())
  {
    i = 0;
    Serial.println("Enter new password : ");
    while(i < 4)
    {
      char key = mykeypad.getKey();
    // Check if a key is pressed
      if (key) 
      {
        // Print the key to the serial monitor
        Serial.println(key);
        correctPassword[i] = key;
        i++;
    
      }
    }
    
  }
  i = 0;
  Serial.print("Your New Password is : ");
  for(byte p = 0;p < 4;p++)
  {
    Serial.print(correctPassword[p]);
  }
  Serial.println();
}

void clearPassword()
{
  for(byte k = 0; k < 4;k++)
  {
    enteredPassword[k] = '\0';//empty array
  }
  for(byte p = 0;p < 4;p++)
  {
     Serial.print(enteredPassword[p]);
  }
  i = 0;
  Serial.println("Password is Cleared");
  Serial.println("Enter a Password of 4 numeric digits please :");
}
void confirmPassword()
{

}