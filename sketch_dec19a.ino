
int LED = 13;
int BLUE = 7;
int BLACK = 6;
int RED = 5;
int YELLOW = 4;
int BUTTON = 10;

void setup() {
  pinMode(LED, OUTPUT);
  pinMode(BLUE, OUTPUT);
  pinMode(BLACK, OUTPUT);
  pinMode(RED, OUTPUT);
  pinMode(YELLOW, OUTPUT);
  pinMode(BUTTON, INPUT);
}

/* // a b c d */
/* // a b d c */
/* // a d b c */

/* void send(int a, int d, int b, int c) { */
/*   if (digitalRead(BUTTON) == HIGH) { */
/*     digitalWrite(YELLOW, a); */
/*     digitalWrite(RED, b); */
/*     digitalWrite(BLACK, c); */
/*     digitalWrite(BLUE, d); */
/*   } */
/* } */

// y r k b

void send(int y, int r, int k, int b) {
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
    delay(1);
}

void loop() {
  int state = 0;
  int values[4][4] = {{LOW, HIGH, HIGH, LOW},
                      {LOW, LOW, HIGH, HIGH},
                      {HIGH, LOW, LOW, HIGH},
                      {HIGH, HIGH, LOW, LOW}};

  /* digitalWrite(LED, HIGH);   // turn the LED on (HIGH is the voltage level) */
  /* delay(1000);               // wait for a second */
  /* digitalWrite(LED, LOW);    // turn the LED off by making the voltage LOW */
  /* delay(1000);               // wait for a second */
  while(1) {
    if (digitalRead(BUTTON) == HIGH) {
      send(values[state][0],
           values[state][1],
           values[state][2],
           values[state][3]);
      state++;
      state = state % 4;
    }
  }
}


    /* send(LOW, HIGH, HIGH, LOW); */
    /* send(LOW, LOW, HIGH, HIGH); */
    /* send(HIGH, LOW, LOW, HIGH); */
    /* send(HIGH, HIGH, LOW, LOW); */
