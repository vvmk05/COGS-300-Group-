import processing.serial.*;
Serial myPort;
int speed = 150;
String movement = "STOPPED";

void setup() {
  size(500, 300);
  printArray(Serial.list());
  // CHANGE [0] IF YOUR ARDUINO USES ANOTHER PORT
  myPort = new Serial(this, Serial.list()[0], 9600);
}

void draw() {
  background(240);
  fill(0);
  textAlign(CENTER);
  textSize(25);
  text("ROBOT CONTROLLER", width/2, 50);
  textSize(18);
  text("W = Forward", width/3, 100);
  text("S = Backward", width/3, 130);
  text("A = Left", (2*width)/3, 100);
  text("D = Right", (2*width)/3, 130);
  text("R = Rotate", width/2, 160);
  text("UP = Faster | DOWN = Slower", width/2, 190);
  text("SPACE = Stop", width/2, 220);
  textSize(22);
  text("Speed: " + speed + " / 255", width/2, 250);
  text("Movement: " + movement, width/2, 280);
}

void keyPressed() {
  if (key == 'w' || key == 'W') {
    myPort.write('W');
    movement = "FORWARD";
  }
  else if (key == 's' || key == 'S') {
    myPort.write('S');
    movement = "BACKWARD";
  }
  else if (key == 'a' || key == 'A') {
    myPort.write('A');
    movement = "LEFT";
  }
  else if (key == 'd' || key == 'D') {
    myPort.write('D');
    movement = "RIGHT";
  }
  else if (key == ' ' || key == 'x' || key == 'X') {
    myPort.write('X');
    movement = "STOPPED";
  }
  else if (key == 'r' || key == 'R') {
    myPort.write('R');
    movement = "ROTATE";
  }
  else if (key == CODED) {
    if (keyCode == UP) {
      speed = min(speed + 15, 255);
      myPort.write('U');
    }
    else if (keyCode == DOWN) {
      speed = max(speed - 15, 0);
      myPort.write('D');
    }
  }
}

void dispose() {
  if (myPort != null) {
    myPort.write('X');
    myPort.stop();
  }
  super.dispose();
}
