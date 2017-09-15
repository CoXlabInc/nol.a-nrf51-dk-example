#include <cox.h>

Timer tPrint;
bool isToning;

static void printTask(void *) {
  System.ledToggle(0);
  printf("[%lu usec] Hi!\n", micros());
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
  Serial.begin(115200);
  printf("\n*** [nRF51-DK] Basic Functions ***\n");

  tPrint.onFired(printTask, NULL);
  tPrint.startPeriodic(1000);

  // Serial.listen();
  Serial.onReceive(keyboard);

  // System.onButtonPressed(0, button);
}
