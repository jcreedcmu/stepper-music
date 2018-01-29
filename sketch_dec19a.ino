
int LED = 13;
int BLUE = 7;
int BLACK = 6;
int RED = 5;
int YELLOW = 4;
int BUTTON = 10;

void setup() {
  Serial.begin(9600);
  pinMode(LED, OUTPUT);
  pinMode(BLUE, OUTPUT);
  pinMode(BLACK, OUTPUT);
  pinMode(RED, OUTPUT);
  pinMode(YELLOW, OUTPUT);
  pinMode(BUTTON, INPUT);
}


void send(int y, int r, int k, int b, int pause) {
  if (pause) {
    digitalWrite(LED, HIGH);
    digitalWrite(YELLOW, y);
    digitalWrite(RED, r);
    digitalWrite(BLUE, b);
    digitalWrite(BLACK, k);
    delay(3);
    digitalWrite(LED, LOW);
    digitalWrite(YELLOW, LOW);
    digitalWrite(RED, LOW);
    digitalWrite(BLUE, LOW);
    digitalWrite(BLACK, LOW);
    delayMicroseconds(pause);
  }
}

void loop() {
  int state = 0;
  int pause = 0;
  char buf[100];
  buf[1] = 0;
  int values[4][4] = {{LOW, HIGH, HIGH, LOW},
                      {LOW, LOW, HIGH, HIGH},
                      {HIGH, LOW, LOW, HIGH},
                      {HIGH, HIGH, LOW, LOW}};

  while(1) {

    while (Serial.available() > 0) {
      int bytesRead = Serial.readBytesUntil('\n', buf, sizeof(buf));
      if (bytesRead < sizeof(buf))
        buf[bytesRead] = 0;
      pause = atoi(buf);
      Serial.print(bytesRead, DEC);
      Serial.write(" - ");
      Serial.println(pause, DEC);
    }

    send(values[state][0],
         values[state][1],
         values[state][2],
         values[state][3], pause);
    state++;
    state = state % 4;
  }

}
