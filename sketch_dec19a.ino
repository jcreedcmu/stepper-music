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

#define DURATION 3

int YELLOW = 4;
int RED = 7;
int BLACK = 6;
int BLUE = 5;

int LED = 13;


void setup() {
  Serial.begin(9600);
  pinMode(LED, OUTPUT);
  pinMode(BLUE, OUTPUT);
  pinMode(BLACK, OUTPUT);
  pinMode(RED, OUTPUT);
  pinMode(YELLOW, OUTPUT);
}

void reallySend(int y, int r, int k, int b, int delayMs, long int pause) {
    /* Serial.write("\n(1) "); */
    /* Serial.print(millis(), DEC); */
    digitalWrite(LED, HIGH);
    digitalWrite(YELLOW, y);
    digitalWrite(RED, r);
    digitalWrite(BLACK, k);
    digitalWrite(BLUE, b);
    delay(delayMs);
    /* Serial.write("\n(2) "); */
    /* Serial.print(millis(), DEC); */
    digitalWrite(LED, LOW);
    digitalWrite(YELLOW, LOW);
    digitalWrite(RED, LOW);
    digitalWrite(BLACK, LOW);
    digitalWrite(BLUE, LOW);
    if (pause > 1000)
      delay(pause / 1000);
    else
      delayMicroseconds(pause);
    /* Serial.write("\n(3) m"); */
    /* Serial.print(millis(), DEC); */
    /* Serial.write("pause / 1000 = "); */
    /* Serial.print(pause / 1000, DEC); */
}

void send(int y, int r, int k, int b, int delayMs, long int pause) {
  if (pause)
    reallySend(y, r, k, b, delayMs, pause);
}


int values[4][4] = {
  {LOW, HIGH, HIGH, LOW},
  {LOW, HIGH, LOW, HIGH},
  {HIGH, LOW, LOW, HIGH},
  {HIGH, LOW, HIGH, LOW},
};


int valuesCW[4][4] = {
  {HIGH, LOW, HIGH, LOW},
  {HIGH, LOW, LOW, HIGH},
  {LOW, HIGH, LOW, HIGH},
  {LOW, HIGH, HIGH, LOW},
};

/* int values[4][4] = { */
/*   {HIGH, LOW, LOW, LOW}, */
/*   {LOW, LOW, HIGH, LOW}, */
/*   {LOW, HIGH, LOW, LOW}, */
/*   {LOW, LOW, LOW, HIGH}, */
/* }; */

void single(int x[4]) {
  reallySend(x[0], x[1], x[2], x[3], DURATION, 0);
}

void loop() {
  int state = 0;
  long int pause = 0;
  char buf[100];
  //  buf[1] = 0;

  while(1) {

    while (Serial.available() > 0) {
      // read in a line of text, and use its numeric value (or zero,
      // if atol fails to find a parseable number) to set 'pause', a
      // microsecond delay on top of the 3ms pulse we spend powering
      // the motor. When pause is zero, we just don't run the motor.
      int bytesRead = Serial.readBytesUntil('\n', buf, sizeof(buf));
      if (bytesRead < sizeof(buf))
        buf[bytesRead] = 0;
      if (buf[0] == 'a') {
        single(values[0]);
       }
      else if (buf[0] == 'b') {
        single(values[1]);
       }
      else if (buf[0] == 'c') {
        single(values[2]);
      }
      else if (buf[0] == 'd') {
        single(values[3]);
      }
      else {
        pause = atol(buf);
#if DEBUG
        Serial.print(bytesRead, DEC);
        Serial.write(" - pause = ");
        Serial.println(pause, DEC);
#endif
      }
    }

    send(values[state][0],
         values[state][1],
         values[state][2],
         values[state][3], DURATION, pause);
    state++;
    state = state % 4;
  }

}
