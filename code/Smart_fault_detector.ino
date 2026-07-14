const int sensorPin = 2;

const int redPin = 3;
const int greenPin = 4;
const int bluePin = 5;

const int buzzer = 6;
const int relay = 7;

const int segPins[7] = {8,9,10,11,12,13,A0};

// Seven segment digits
byte digits[4][7] = {
  {0,0,0,0,0,0,1}, //0 (unused)
  {1,0,0,1,1,1,1}, //1
  {0,0,1,0,0,1,0}, //2
  {0,0,0,0,1,1,0}  //3
};

volatile int vibrationCount = 0;

unsigned long previousMillis = 0;

void countVibration()
{
  vibrationCount++;
}

void setup()
{
  pinMode(sensorPin, INPUT_PULLUP);

  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);

  pinMode(buzzer, OUTPUT);
  pinMode(relay, OUTPUT);

  digitalWrite(relay, HIGH);

  for(int i=0;i<7;i++)
    pinMode(segPins[i], OUTPUT);

  attachInterrupt(digitalPinToInterrupt(sensorPin),
                  countVibration,
                  CHANGE);

  Serial.begin(9600);
}

void displayDigit(int num)
{
  for(int i=0;i<7;i++)
    digitalWrite(segPins[i], digits[num][i]);
}

void loop()
{
  if(millis()-previousMillis>=1000)
  {
    previousMillis=millis();

    int level=1;

    if(vibrationCount<5)
      level=1;
    else if(vibrationCount<15)
      level=2;
    else
      level=3;

    Serial.print("Vibration Count: ");
    Serial.println(vibrationCount);

    vibrationCount=0;

    switch(level)
    {

      case 1:

      digitalWrite(greenPin,LOW);
      digitalWrite(redPin,HIGH);
      digitalWrite(bluePin,HIGH);

      digitalWrite(relay,HIGH);

      noTone(buzzer);

      displayDigit(1);

      break;

      case 2:

      digitalWrite(greenPin,LOW);
      digitalWrite(redPin,LOW);
      digitalWrite(bluePin,HIGH);

      digitalWrite(relay,HIGH);

      tone(buzzer,1500,250);

      displayDigit(2);

      break;

      case 3:

      digitalWrite(greenPin,HIGH);
      digitalWrite(redPin,LOW);
      digitalWrite(bluePin,HIGH);

      digitalWrite(relay,LOW);

      tone(buzzer,2000);

      displayDigit(3);

      break;
    }

  }

}
