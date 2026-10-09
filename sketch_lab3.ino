// RIGHT MOTOR
const int ENA = 9;
const int IN1 = 2;
const int IN2 = 3;
// LEFT MOTOR
const int ENB = 10;
const int IN3 = 4;
const int IN4 = 5;
// SPEED CONTROL
int motorSpeed = 150;
// 0 = stopped
// 1 = forward
// -1 = backward
// 2 = left
// 3 = right
int direction = 0;

void setup() {
  Serial.begin(9600);
  pinMode(ENA, OUTPUT);
  pinMode(ENB, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  stopMotors();
}

void loop() {
  if (Serial.available() > 0) {
    char command = Serial.read();
    if (command == 'W') {
      direction = 1;
    }
    else if (command == 'S') {
      direction = -1;
    }
    else if (command == 'X') {
      direction = 0;
    }
    else if (command == 'A') {
      direction = 2;
    }
    else if (command == 'D') {
      direction = 3;
    }
    else if (command == 'R') {
      direction = 4;
    }
    else if (command == 'U') {
      motorSpeed = min(motorSpeed + 15, 255);
    }
    else if (command == 'D') {
      motorSpeed = max(motorSpeed - 15, 0);
    }
    updateMotors();
  }
}

void updateMotors() {
  if (direction == 0 || motorSpeed == 0) {
    stopMotors();
    return;
  }

  // FORWARD (DIRECTION CORRECTED)
  if (direction == 1) {
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, HIGH);
    digitalWrite(IN3, HIGH);
    digitalWrite(IN4, LOW);
    analogWrite(ENA, motorSpeed);
    analogWrite(ENB, motorSpeed);
  }
  // BACKWARD (DIRECTION CORRECTED)
  else if (direction == -1) {
    digitalWrite(IN1, HIGH);
    digitalWrite(IN2, LOW);
    digitalWrite(IN3, LOW);
    digitalWrite(IN4, HIGH);
    analogWrite(ENA, motorSpeed);
    analogWrite(ENB, motorSpeed);
  }
  // LEFT
  else if (direction == 2) {
    analogWrite(ENA, motorSpeed * 0.5);
    analogWrite(ENB, motorSpeed);
  }
  // RIGHT
  else if (direction == 3) {
    analogWrite(ENA, motorSpeed);
    analogWrite(ENB, motorSpeed * 0.5);
  }
  // LOOP
  else if (direction == 4) {
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, HIGH);
    digitalWrite(IN3, LOW);
    digitalWrite(IN4, HIGH);
    analogWrite(ENA, motorSpeed);
    analogWrite(ENB, motorSpeed);
  }
}

void stopMotors() {
  analogWrite(ENA, 0);
  analogWrite(ENB, 0);
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
}
