#include <cox.h>

Timer tPrint;
bool isToning;

static void printTask(void *) {
  System.ledToggle(0);
  printf("[%lu usec] Hi!\n", micros());

  if (isToning) {
    noTone(23);
    isToning = false;
  } else {
    tone(23, 262);
    isToning = true;
  }
}

static void keyboard(SerialPort&) {
  System.ledToggle(0);
  printf("[%lu usec] Keyboard input\n", micros());
}

static void button() {
  System.ledToggle(0);
  printf("[%lu usec] User button pressed\n", micros());
}

void setup() {
  System.ledOn(0);
  System.ledOn(3);
  Serial.begin(115200);
  printf("\n*** Serial test for nRF51-DK ***\n");

  tPrint.onFired(printTask, NULL);
  tPrint.startPeriodicMicros(1000000);

  Serial.listen();
  Serial.onReceive(keyboard);

  pinMode(23, OUTPUT);
  tone(23, 262);
  isToning = true;
  //analogWrite(23, 254);
}
