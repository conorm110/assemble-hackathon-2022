
int tiltSwIn = 2;         // the number of the input pin
bool tiltState = false;

int cycleTotal = 0;
int cycleTilt = 0;

int shakeCooldown = 0;

void setup()
{
  Serial.begin(9600);
  pinMode(tiltSwIn, INPUT);
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
    shakeCooldown = 30000;
    cycleTilt = 0;
    cycleTotal = 0;
  }

  if (eraseLastBit)
  {
    Serial.println("test");
  }
}
