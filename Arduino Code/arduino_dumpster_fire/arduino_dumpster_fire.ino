
int tiltSwIn = 2;         // the number of the input pin
bool tiltState = false;

int cycleTotal = 0;
int cycleTilt = 0;

int shakeCooldown = 0;

short joystickState = 0; // 0 idle, 1 is 0b,, 2 is 1b, 

int bufferIndex = 0;
int bufferKeys[] = {0,0,0,0,0,0,0,0};

void setup()
{
  Serial.begin(9600);
  pinMode(tiltSwIn, INPUT);
  pinMode(3, OUTPUT);
}
 
void loop()
{
  if(shakeCooldown>0){
    shakeCooldown--;
  }
  bool eraseLastBit = false;
  bool newTiltState = digitalRead(tiltSwIn);
  if (newTiltState != tiltState)
  {
    cycleTilt++;
    delay(2.5);
  }
  cycleTotal++;
  tiltState = newTiltState;
  if (cycleTotal > 10000)
  {
    // no shak
    cycleTilt = 0;
    cycleTotal = 0;
  }
  else if (cycleTilt > 20 && shakeCooldown == 0)
  {
    eraseLastBit = true;
    shakeCooldown = 20000;
    cycleTilt = 0;
    cycleTotal = 0;
  }

  if (eraseLastBit)
  {
    Serial.println("FUCKKKK");
    if (bufferIndex > 0) 
    {
      bufferIndex--; // tocuh grass 
      digitalWrite(3, HIGH);
      delay(100);
      digitalWrite(3, LOW);
    }
    else 
    {
      digitalWrite(3, HIGH);
      delay(100);
      digitalWrite(3, LOW);
      delay(100);
      digitalWrite(3, HIGH);
      delay(100);
      digitalWrite(3, LOW);
    }
  }
  else
  {
   short newState = 0;
   int joystickVoltage = analogRead(0);
   if (joystickVoltage > 700)
   {
    newState = 2;
   }
   else if (joystickVoltage < 200)
   {
    newState = 1;
   }
   else
   {
    newState = 0;
   }
   if (newState != joystickState)
   {
    if (newState != 0)
    {
      // write new thing to buffer
      bufferKeys[bufferIndex] = newState - 1; // TIS IS SO FUCKEd
      bufferIndex++;
    }
    joystickState = newState;
   }
   if (bufferIndex > 7)
   {
    Serial.println("");
    Serial.print(bufferKeys[0]);
    Serial.print(bufferKeys[1]);
    Serial.print(bufferKeys[2]);
    Serial.print(bufferKeys[3]);
    Serial.print(bufferKeys[4]);
    Serial.print(bufferKeys[5]);
    Serial.print(bufferKeys[6]);
    Serial.print(bufferKeys[7]);

    bufferIndex = 0;
   }
  }
}
