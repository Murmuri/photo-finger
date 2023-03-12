#include <IRremote.h>
#include <Servo.h>

#define SERVO_PIN 3
#define IR_PIN 2

#define A 9
#define B 8
#define C 4
#define D 6
#define E 5
#define F 10
#define G 7

#define D1 A4
#define D2 A3
#define D3 A2
#define D4 A1

#define START_CODE 16761405
#define TIME_MINUS 16769055
#define TIME_PLUS 16754775
#define TIME_STEP_PLUS 16712445
#define TIME_STEP_MINUS 16720605

#define DEFAULT_ANGLE 0
#define PUSH_ANGLE 35

IRrecv irRecv(IR_PIN);
Servo servoFinger;

const int timerStepsLength = 3;
const int timeSteps[timerStepsLength] = {1,10,60};
int time = 60;
int timer = time;
int i = 0;
int timeStepIndex = 0;
int timeStep = timeSteps[timeStepIndex];

decode_results irResults;


void setup() 
{
  Serial.begin(9600);

  servoFinger.attach(SERVO_PIN);
  servoFinger.write(DEFAULT_ANGLE);
  delay(1000);

  irRecv.enableIRIn();

  pinMode(A, OUTPUT);
  pinMode(B, OUTPUT);
  pinMode(C, OUTPUT);
  pinMode(D, OUTPUT);
  pinMode(E, OUTPUT);
  pinMode(F, OUTPUT);
  pinMode(G, OUTPUT);

  pinMode(D1, OUTPUT);
  pinMode(D2, OUTPUT);
  pinMode(D3, OUTPUT);
  pinMode(D4, OUTPUT);
}

void loop() 
{
  showTime(time);

  if ( irRecv.decode( &irResults ) ) 
  {
    executeCommand();
    irRecv.resume(); 
  }
}

void executeCommand() 
{
  switch (irResults.value) 
  {
    case START_CODE: startTimer();  
      break;
    case TIME_MINUS: setTime(-1);  
      break;
    case TIME_PLUS: setTime(1);  
      break;
    case TIME_STEP_PLUS: setTimeStep(1);  
      break;
    case TIME_STEP_MINUS: setTimeStep(-1);  
      break;
  }
}

void showTime(int x)
{
  clearLEDs();
  pickDigit(0); 
  pickNumber(x / 600 % 6);
  delay(5);

  clearLEDs();
  pickDigit(1); 
  pickNumber(x % 600 / 60);
  delay(5);

  clearLEDs();
  pickDigit(2); 
  pickNumber(x % 60 / 10);
  delay(5);

  clearLEDs();
  pickDigit(3); 
  pickNumber(x % 10);
  delay(5);

  clearLEDs();
}

void startTimer() 
{
  servoFinger.write(PUSH_ANGLE);
  timer = time;

  while (timer != 0) 
  {
    showTime(timer);
    i++;

    if (i % 50 == 0) 
    {
      timer--;
    }
  }

  servoFinger.write(DEFAULT_ANGLE);
  delay(500);
}

void setTime(int x)
{
  time += timeStep * x;
}

void setTimeStep(int x)
{
  timeStepIndex = (timeStepIndex + x) < 0
    ? timerStepsLength - 1
    : (timeStepIndex + x) % 3;
  timeStep = timeSteps[timeStepIndex];
}

void pickDigit(int x) 
{
  digitalWrite(D1, HIGH);
  digitalWrite(D2, HIGH);
  digitalWrite(D3, HIGH);
  digitalWrite(D4, HIGH);

  switch (x) 
  {
    case 0: digitalWrite(D1, LOW);  
      break;
    case 1: digitalWrite(D2, LOW);  
      break;
    case 2: digitalWrite(D3, LOW);  
      break;
    default: digitalWrite(D4, LOW); 
      break;
  }
}

void pickNumber(int x) 
{
  switch (x) 
  {
    default: zero();   
      break;
    case 1: one();     
      break;
    case 2: two();     
      break;
    case 3: three();  
      break;
    case 4: four();    
      break;
    case 5: five();    
      break;
    case 6: six();       
      break;
    case 7: seven(); 
      break;
    case 8: eight();  
      break;
    case 9: nine();  
      break;
  }
}

void clearLEDs() 
{
  digitalWrite(A, LOW);
  digitalWrite(B, LOW);
  digitalWrite(C, LOW);
  digitalWrite(D, LOW);
  digitalWrite(E, LOW);
  digitalWrite(F, LOW);
  digitalWrite(G, LOW);
}

void zero() 
{
  digitalWrite(A, HIGH);
  digitalWrite(B, HIGH);
  digitalWrite(C, HIGH);
  digitalWrite(D, HIGH);
  digitalWrite(E, HIGH);
  digitalWrite(F, HIGH);
  digitalWrite(G, LOW);
}

void one() 
{
  digitalWrite(A, LOW);
  digitalWrite(B, HIGH);
  digitalWrite(C, HIGH);
  digitalWrite(D, LOW);
  digitalWrite(E, LOW);
  digitalWrite(F, LOW);
  digitalWrite(G, LOW);
}

void two() 
{
  digitalWrite(A, HIGH);
  digitalWrite(B, HIGH);
  digitalWrite(C, LOW);
  digitalWrite(D, HIGH);
  digitalWrite(E, HIGH);
  digitalWrite(F, LOW);
  digitalWrite(G, HIGH);
}

void three() 
{
  digitalWrite(A, HIGH);
  digitalWrite(B, HIGH);
  digitalWrite(C, HIGH);
  digitalWrite(D, HIGH);
  digitalWrite(E, LOW);
  digitalWrite(F, LOW);
  digitalWrite(G, HIGH);
}

void four() 
{
  digitalWrite(A, LOW);
  digitalWrite(B, HIGH);
  digitalWrite(C, HIGH);
  digitalWrite(D, LOW);
  digitalWrite(E, LOW);
  digitalWrite(F, HIGH);
  digitalWrite(G, HIGH);
}

void five() 
{
  digitalWrite(A, HIGH);
  digitalWrite(B, LOW);
  digitalWrite(C, HIGH);
  digitalWrite(D, HIGH);
  digitalWrite(E, LOW);
  digitalWrite(F, HIGH);
  digitalWrite(G, HIGH);
}

void six() 
{
  digitalWrite(A, HIGH);
  digitalWrite(B, LOW);
  digitalWrite(C, HIGH);
  digitalWrite(D, HIGH);
  digitalWrite(E, HIGH);
  digitalWrite(F, HIGH);
  digitalWrite(G, HIGH);
}

void seven() 
{
  digitalWrite(A, HIGH);
  digitalWrite(B, HIGH);
  digitalWrite(C, HIGH);
  digitalWrite(D, LOW);
  digitalWrite(E, LOW);
  digitalWrite(F, LOW);
  digitalWrite(G, LOW);
}

void eight() 
{
  digitalWrite(A, HIGH);
  digitalWrite(B, HIGH);
  digitalWrite(C, HIGH);
  digitalWrite(D, HIGH);
  digitalWrite(E, HIGH);
  digitalWrite(F, HIGH);
  digitalWrite(G, HIGH);
}

void nine() 
{
  digitalWrite(A, HIGH);
  digitalWrite(B, HIGH);
  digitalWrite(C, HIGH);
  digitalWrite(D, HIGH);
  digitalWrite(E, LOW);
  digitalWrite(F, HIGH);
  digitalWrite(G, HIGH);
}
