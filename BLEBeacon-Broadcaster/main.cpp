#include <cox.h>

Timer timerPrint, timerBlink;
BLEBeacon &Beacon = getBLEBeaconInstance();

static void taskPrint(void *) {
  printf("[%lu usec] Hi! (button:%s)\n",
         micros(),
         (digitalRead(17) == HIGH) ? "released" : "pressed");
}

static void taskBlink(void *) {
  if (digitalRead(21) == HIGH) {
    digitalWrite(21, LOW);
    timerBlink.startOneShot(10);
  } else {
    digitalWrite(21, HIGH);
    timerBlink.startOneShot(990);
  }
}

void setup() {
  uint8_t advAddr[6] = { 'C', 'O', 'X', 'L', 'A', 'B' };
  uint8_t uuid[16] = {
      0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07,
      0x08, 0x09, 0x0A, 0x0B, 0x0C, 0x0D, 0x0E, 0x0F,
    };
  uint16_t companyId = 0xABCD;
  uint16_t major = 0x0000;
  uint16_t minor = 0x1111;
  int8_t txPower = 0;

  /* LED 1 */
  pinMode(21, OUTPUT);
  digitalWrite(21, HIGH);

  /* Button 1 */
  pinMode(17, INPUT_PULLUP);

  Serial.begin(115200);
  printf("\n*** BLE Beacon (Broadcaster) Example for nRF51-DK ***\n");

  nRFRadio.begin();
  Beacon.begin(nRFRadio, advAddr, companyId, uuid, major, minor, txPower);

  timerPrint.onFired(taskPrint, NULL);
  timerPrint.startPeriodic(1000);

  timerBlink.onFired(taskBlink, NULL);
  timerBlink.startOneShot(10);
}
