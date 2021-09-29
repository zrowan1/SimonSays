#include <Arduino.h>
#include <ezButton.h>


const int redLedPin = 2;
const int yellowLedPin = 3;
const int greenLedPin = 4;


int whichLightComputer = 0; // een int die opslaat welk lampje de computer kiest en in de array opslaat
                            // rood = 1, geel = 2, groen = 3
int whichLightPlayer = 0;

int computerSequence[8] = {0, 0, 0, 0, 0, 0, 0, 0};
int playerSequence[8] = {0, 0, 0, 0, 0, 0, 0, 0};

int turnIndicator = 1;
bool playerHasLost = false;


int redLedState = LOW;
int yellowLedState = LOW;
int greenLedState = LOW;

ezButton leftButton(7);
ezButton middleButton(8);
ezButton rightButton(12);


void turnOnRed()
{
  digitalWrite(redLedPin, HIGH);
  redLedState = HIGH;
  delay(500);
  digitalWrite(redLedPin, LOW);
  redLedState = LOW;
  delay(500);
}
void turnOnYellow()
{
  digitalWrite(yellowLedPin, HIGH);
  yellowLedState = HIGH;
  delay(500);
  digitalWrite(yellowLedPin, LOW);
  yellowLedState = LOW;
  delay(500);
}
void turnOnGreen()
{
  digitalWrite(greenLedPin,HIGH);
  greenLedState = HIGH;
  delay(500);
  digitalWrite(greenLedPin, LOW);
  greenLedState = LOW;
  delay(500);
}


void changeRedLight()
{
  if (redLedState == LOW)
  {
    if (leftButton.isPressed())
    {
      digitalWrite(redLedPin, HIGH);
      redLedState = HIGH;
      whichLightPlayer = 1;

    }
  }
  else if (redLedState == HIGH)
  {
    if (leftButton.isPressed())
    {
      digitalWrite(redLedPin, LOW);
      redLedState = LOW;
    }
  }

}
void changeYellowLight()
{
  if (yellowLedState == LOW)
  {
    if (middleButton.isPressed())
    {
      digitalWrite(yellowLedPin, HIGH);
      yellowLedState = HIGH;
      whichLightPlayer = 2;
    }
  }
  else if (yellowLedState == HIGH)
  {
    if (middleButton.isPressed())
    {
      digitalWrite(yellowLedPin, LOW);
      yellowLedState = LOW;
    }
  }
}
void changeGreenlight()
{
  if (greenLedState == LOW)
  {
    if (rightButton.isPressed())
    {
      digitalWrite(greenLedPin, HIGH);
      greenLedState = HIGH;
      whichLightPlayer = 3;
    }
  }
  else if (greenLedState == HIGH)
  {
    if (rightButton.isPressed())
    {
      digitalWrite(greenLedPin, LOW);
      greenLedState = LOW;
    }
  }

}
void chooseRandomLight()
{
  int randomNumber = random(1, 4);

  switch(randomNumber)
  {
    case 1:
     whichLightComputer = 1;
     digitalWrite(redLedPin, HIGH);
     redLedState = HIGH;
     delay(1000);
     digitalWrite(redLedPin, LOW);
     redLedState = LOW;
     delay(200);
     break;
    case 2:
     whichLightComputer = 2;
     digitalWrite(yellowLedPin, HIGH);
     yellowLedState = HIGH;
     delay(1000);
     digitalWrite(yellowLedPin, LOW);
     yellowLedState = LOW;
     delay(200);
     break;
    case 3:
     whichLightComputer = 3;
     digitalWrite(greenLedPin, HIGH);
     greenLedState = HIGH;
     delay(1000);
     digitalWrite(greenLedPin, LOW);
     greenLedState = LOW;
     delay(200);
     break;
  }
}

void turnOffLeds()
{
  digitalWrite(redLedPin, LOW);
  digitalWrite(yellowLedPin, LOW);
  digitalWrite(greenLedPin, LOW);
  redLedState = LOW;
  yellowLedState = LOW;
  greenLedState = LOW;
}




void gameStart()
{
  digitalWrite(redLedPin, HIGH);
  digitalWrite(yellowLedPin, HIGH);
  digitalWrite(greenLedPin, HIGH);
  redLedState = HIGH;
  yellowLedState = HIGH;
  greenLedState = HIGH;
  delay(750);

  digitalWrite(redLedPin, LOW);
  digitalWrite(yellowLedPin, LOW);
  digitalWrite(greenLedPin, LOW);
  redLedState = LOW;
  yellowLedState = LOW;
  greenLedState = LOW;
  delay(750);

  digitalWrite(redLedPin, HIGH);
  digitalWrite(yellowLedPin, HIGH);
  digitalWrite(greenLedPin, HIGH);
  redLedState = HIGH;
  yellowLedState = HIGH;
  greenLedState = HIGH;
  delay(750);

  digitalWrite(redLedPin, LOW);
  digitalWrite(yellowLedPin, LOW);
  digitalWrite(greenLedPin, LOW);
  redLedState = LOW;
  yellowLedState = LOW;
  greenLedState = LOW;
  delay(750);

  digitalWrite(redLedPin, HIGH);
  digitalWrite(yellowLedPin, HIGH);
  digitalWrite(greenLedPin, HIGH);
  redLedState = HIGH;
  yellowLedState = HIGH;
  greenLedState = HIGH;
  delay(750);

  digitalWrite(redLedPin, LOW);
  digitalWrite(yellowLedPin, LOW);
  digitalWrite(greenLedPin, LOW);
  redLedState = LOW;
  yellowLedState = LOW;
  greenLedState = LOW;
  delay(750);  

  
}

void computerTurnOne() 
{
  chooseRandomLight();
  computerSequence[0] = whichLightComputer;
  Serial.println(computerSequence[0]);
  whichLightComputer = 0;


}

void computerTurn()
{
  for (int i = 0; i < turnIndicator; i++)
  {

    if (computerSequence[i] > 0)
    {
      if (computerSequence[i] == 1)
      {
        turnOnRed();
      }
      else if (computerSequence[i] == 2)
      {
        turnOnYellow();
      }
      else if (computerSequence[i] == 3)
      {
        turnOnGreen();
      }    
    }
    else if (computerSequence[i] == 0)
    {
      chooseRandomLight();
      computerSequence[i] = whichLightComputer;
      whichLightComputer = 0;
    }

    

  }
}

void playerTurn()
{
  for (int i = 0; i < turnIndicator; i++)
  {
    while (whichLightPlayer == 0)
    {
      leftButton.loop();
      middleButton.loop();
      rightButton.loop();
      

      changeRedLight();
      changeYellowLight();
      changeGreenlight();
    }
    playerSequence[i] = whichLightPlayer;

    if (playerSequence[i] != computerSequence[i])
    {
      Serial.println("Sorry, wrong answer!");
      Serial.println("You Lose!");
      playerHasLost = true;
    }
    else if (playerSequence[i] == computerSequence[i])
    {
      whichLightPlayer = 0;
      delay(500);
      turnOffLeds();
     
    }
  }
delay(1000);
}



/*void playerTurnOne()
{

  Serial.println("Let's play Simon Says");
  Serial.println("Your turn!");

  while (whichLightPlayer == 0)
  {
    leftButton.loop();
    middleButton.loop();
    rightButton.loop();
    
    changeRedLight();
    changeYellowLight();
    changeGreenlight();

  }
  playerSequence[0] = whichLightPlayer;

  if (playerSequence[0] != computerSequence[0])
  {
    Serial.println("Sorry, you lose!");
  }
  else if (playerSequence[0] == computerSequence[0])
  {
    Serial.println("Good job!");
  }

  whichLightPlayer = 0;
  delay(1000);

  turnOffLeds();
  delay(2000);
  turnIndicator++;


}
*/





void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  randomSeed(analogRead(A0));


  pinMode(redLedPin, OUTPUT);
  pinMode(yellowLedPin, OUTPUT);
  pinMode(greenLedPin, OUTPUT);


  leftButton.setDebounceTime(25);
  middleButton.setDebounceTime(25);
  rightButton.setDebounceTime(25);
}

void loop() {
  // put your main code here, to run repeatedly:


  leftButton.loop();
  middleButton.loop();
  rightButton.loop();

  turnIndicator = 1;

  while (playerHasLost == false)
  {
  gameStart();

  computerTurn();
  playerTurn();
  turnIndicator++;

  computerTurn();
  playerTurn();
  turnIndicator++;

  computerTurn();
  playerTurn();
  turnIndicator++;

  computerTurn();
  playerTurn();
  turnIndicator++;

  computerTurn();
  playerTurn();
  turnIndicator++;

  computerTurn();
  playerTurn();
  turnIndicator++;

  computerTurn();
  playerTurn();
  turnIndicator++;

  computerTurn();
  playerTurn();
  turnIndicator++;
  }




  







  

}