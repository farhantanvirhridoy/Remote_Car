#include <IRremote.h>
#include <Servo.h>
#define up 0x61D6C03F
#define down 0x61D640BF
#define ok 0x61D6E01F
#define right 0x61D6D827
#define left 0x61D6B04F


int RECV_PIN = 11;

IRrecv irrecv(RECV_PIN);

decode_results results;
Servo myservo;

int motorpin3 = 5;
int motorpin4 = 4;
int motor2en = 6;



int ir = 7;

void car_forward(int spd)
{
  analogWrite(motor2en, spd);
  digitalWrite(motorpin3, HIGH);
  digitalWrite(motorpin4, LOW);
}

void car_backward(int spd)
{
  analogWrite(motor2en, spd);
  digitalWrite(motorpin3, LOW);
  digitalWrite(motorpin4, HIGH);
}

void car_right()
{
  myservo.write(100);
}

void car_left()
{
  myservo.write(50);

}

bool get_ir()
{
  return digitalRead(ir);
}



void setup() {
  // put your setup code here, to run once:
  pinMode(9, OUTPUT);
  digitalWrite(9, HIGH);
  pinMode(10, OUTPUT);
  digitalWrite(10, LOW);
  
  pinMode(13, OUTPUT);
  digitalWrite(13, HIGH);

  pinMode(motorpin3, OUTPUT);
  pinMode(motorpin4, OUTPUT);

  myservo.attach(8);
  myservo.write(90);
  Serial.begin(9600);
  // In case the interrupt driver crashes on setup, give a clue
  // to the user what's going on.
  Serial.println("Enabling IRin");
  irrecv.enableIRIn(); // Start the receiver
  Serial.println("Enabled IRin");
}

void loop() {
  // put your main code here, to run repeatedly:
  if (irrecv.decode(&results)) {
    Serial.println(results.value, HEX);
    // Receive the next value

    irrecv.resume();
  }
  delay(100);

  if (results.value == up)
  {
    car_forward(255);
    Serial.println("forward");
  }
  else if (results.value == down)
  {
    car_backward(255);
    Serial.println("backward");
  }

  if (results.value == left)
  {
    car_left();
    Serial.println("left");

  }
  else if (results.value == right)
  {
    car_right();
    Serial.println("right");

  }
  else
  {
    myservo.write(90);
  }

  if (results.value == ok)
  {
    analogWrite(motor2en, 0); 
    Serial.println("stop");
  }


}
