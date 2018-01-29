#define DEBUG 0

// Using this stepper motor:
// https://www.jameco.com/webapp/wcs/stores/servlet/Product_10001_10001_2138812_-1
// https://www.jameco.com/Jameco/Products/ProdDS/2138812.pdf

// The data sheet says to do
//     1 2 3 4
// YEL - -
// RED     - -
// BLK   - -
// BLU -     -

// (where "-" is ground and " " is +7V, and orange wire is always tied to +7V)
// but that didn't seem to work for me; I needed to do
//     1 2 3 4
// YEL -     -
// RED - -
// BLK   - -
// BLU     - -
//
// instead, which seems at least consistent with the diagram on the
// data sheet, since yellow and black are never activated together,
// nor are red and blue.


int LED = 13;
int BLUE = 7;
int BLACK = 6;
int RED = 5;
int YELLOW = 4;

void setup() {
  Serial.begin(9600);
  pinMode(LED, OUTPUT);
  pinMode(BLUE, OUTPUT);
  pinMode(BLACK, OUTPUT);
  pinMode(RED, OUTPUT);
  pinMode(YELLOW, OUTPUT);
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
      // read in a line of text, and use its numeric value (or zero,
      // if atoi fails to find a parseable number) to set 'pause', a
      // microsecond delay on top of the 3ms pulse we spend powering
      // the motor. When pause is zero, we just don't run the motor.
      int bytesRead = Serial.readBytesUntil('\n', buf, sizeof(buf));
      if (bytesRead < sizeof(buf))
        buf[bytesRead] = 0;
      pause = atoi(buf);
#if DEBUG
      Serial.print(bytesRead, DEC);
      Serial.write(" - ");
      Serial.println(pause, DEC);
#endif
    }

    send(values[state][0],
         values[state][1],
         values[state][2],
         values[state][3], pause);
    state++;
    state = state % 4;
  }

}
