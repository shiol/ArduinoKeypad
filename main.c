#include <Keypad.h>

char valor[6];
char senha[6] = {'1','2','3','4','5','6'};
int position = 0;

const byte ROWS = 4;
const byte COLS = 4;

char hexaKeys[ROWS][COLS] = {
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};

byte rowPins[ROWS] = {9, 8, 7, 6};
byte colPins[COLS] = {5, 4, 3, 2};

//Keypad customKeypad = Keypad(makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS);

void setup()
{
  pinMode(12, 1);
  pinMode(10, 1);
  digitalWrite(12, 1);
  Serial.begin(9600);
  Serial.println();
  Serial.println("senha:");
 
  for(int i = 0; i < 4; i++){
    pinMode(rowPins[i], 1);
  digitalWrite(rowPins[i], 1);
    digitalWrite(colPins[i], 1);
  }
}

void loop()
{
  //char customKey = customKeypad.getKey();
  char customKey = tecla();
 
  if (customKey != 0){
Serial.print(customKey);
    delay(500);

    valor[position] = customKey;
  position++;
   
    if(position == 6){
      position = 0;
      Serial.println();
      if(igual(valor, senha)){
        Serial.println("OK");
        senhaOk();
      }
      else Serial.println("ERRO");
      Serial.println("senha:");
    }
  }
}

bool igual(char x[6], char y[6]){
  for(int i = 0; i < 6; i++){
    if(valor[i] != senha[i])
      return false;
  }
  return true;
}

void senhaOk(){
  digitalWrite(12, 0);
 
  for(int i = 0; i < 3; i++)
  {
    digitalWrite(10, 1);
    delay(500);
    digitalWrite(10, 0);
    delay(500);
  }
 
  digitalWrite(12, 1);
}

char tecla()
{
  for(int i = 0; i < 4; i++){
    digitalWrite(rowPins[i], 0);
    for(int j = 0; j < 4; j++){
      if(digitalRead(colPins[j]) == 0)
        return hexaKeys[i][j];
    }
    digitalWrite(rowPins[i], 1);
  }
  return 0;
}  