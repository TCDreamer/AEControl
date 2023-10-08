
#include <TimerOne.h>

const int buttonPin = 2;
const int actuatorPin = 9;            //Pin connected to the exhaust actuator circuit. Timer1 can override Pin 9 and Pin 10.

const int led1Pin = 3;
const int led2Pin = 4;
const int buttonPressTime = 500;      //In Milliseconds

int actuatorState = 0;
int maxActuatorState = 2;

unsigned long buttonUpTime = 0;
unsigned long buttonDownTime = 0;

int buttonVal;

float frequency = 100;                // Frequency in Hertz
float dutyCycle;                      // Duty cycle (pulse width) percentage
float period = 1000000 / frequency;   //1 Second in microseconds divided by the frequency

int actuatorCloseDuty = 0;
int actuatorOpenDuty = 1023;
int actuator50Duty = actuatorOpenDuty * 0.5;


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);

  pinMode(buttonPin, INPUT);
  pinMode(actuatorPin, OUTPUT);
  pinMode(led1Pin, OUTPUT);
  pinMode(led2Pin, OUTPUT);

  initializeActuator();

  Timer1.initialize(period);
  Timer1.start();
  Timer1.pwm(actuatorPin, 0);

}

void loop() {

 if(buttonPressed())
 {
  updateState(true);
  updateActuatorSignal();
  updateIndicatorLEDs();
 }

  Serial.println(actuatorState);

}

bool buttonPressed() {

  // Read button status
  buttonVal = digitalRead(buttonPin);

  // If button is not pressed, check if the time difference was reached indicating a valid press and set the current time. 
  if(buttonVal == LOW) {
    if(((long)(buttonDownTime - buttonUpTime)) > 150)
    {
      buttonUpTime = millis();
      return true;
    }
      
    buttonUpTime = millis();

  }
  else if(buttonVal == HIGH)
    buttonDownTime = millis();

  return false;
  
}

void updateState(bool next){

  if(next)
    actuatorState++;

  if(actuatorState > maxActuatorState)
    actuatorState = 0;

}

void initializeActuator(){
  //Cycles the signal sent to the actuator to allow it to self calibrate and be ready
  
  digitalWrite(led1Pin, HIGH);
  digitalWrite(led2Pin, HIGH);
  
  digitalWrite(actuatorPin, LOW);
  delay(250);

  digitalWrite(actuatorPin, HIGH);
  delay(1000);

  digitalWrite(actuatorPin, LOW);
  delay(1000);

  digitalWrite(led1Pin, LOW);
  digitalWrite(led2Pin, LOW);

}

void updateActuatorSignal(){

  switch(actuatorState){
    case 1:
      Timer1.pwm(actuatorPin, actuator50Duty);
      break;
    case 2:
      Timer1.pwm(actuatorPin, actuatorOpenDuty);
      break;
    default:
      Timer1.pwm(actuatorPin, actuatorCloseDuty);
  }
}

void updateIndicatorLEDs(){

  if(actuatorState > 0)
    digitalWrite(led1Pin, HIGH);
  else
    digitalWrite(led1Pin, LOW);
    
  if(actuatorState > 1)
    digitalWrite(led2Pin, HIGH);
   else
    digitalWrite(led2Pin, LOW);
  
}
