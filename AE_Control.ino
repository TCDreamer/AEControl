
const int buttonPin = 1;//x;
const int actuatorPin = 2;//y;

const int led1Pin = 3;//a;
const int led2Pin = 4;//b;
const int buttonPressTime = 500; //In Milliseconds

int actuatorState = 0;
int maxActuatorState = 2;

long buttonUpTime = 0;
long buttonDownTime = 0;

int buttonVal;


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);

  pinMode(buttonPin, INPUT);
  pinMode(actuatorPin, OUTPUT);
  pinMode(led1Pin, OUTPUT);
  pinMode(led2Pin, OUTPUT);

}

void loop() {

  bool check = buttonPressed();

  updateState(check);
  
  Serial.print("Button: " + check + " State: " + actuatorState);


}

bool buttonPressed() {

  buttonVal = digitalRead(buttonPin);
  
  if(buttonVal == 0)
    buttonUpTime = millis();
  else if(buttonVal == 1)
    buttonDownTime = millis();

  return (buttonDownTime - buttonUpTime) > 500;
  
}

void updateState(bool next){

  if(next)
    actuatorState++;

  if(actuatorState > maxActuatorState)
    acuatorState = 0;

}
