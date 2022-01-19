#define RELAY_IN_1 2
#define RELAY_IN_2 3
#define RELAY_IN_3 4
#define RELAY_IN_4 5
#define RELAY_OUT_1 6
#define RELAY_OUT_2 7
#define RELAY_OUT_3 8
#define RELAY_OUT_4 9
#define INPUT_TYPE_SWITCH 10
#define CONTROL_INPUT 11
#define NUMBER_OF_INPUTS 4

#define RELAY_ACTIVE_TIME 500
#define ACTIVATED_SECURE_DELAY 5000

int inputArray[NUMBER_OF_INPUTS][2] = {
  {RELAY_IN_1, RELAY_OUT_1}, {RELAY_IN_2, RELAY_OUT_2}, {RELAY_IN_3, RELAY_OUT_3}, {RELAY_IN_4, RELAY_OUT_4}
};

bool activated = false;

void setUpPins() {
  pinMode(RELAY_IN_1, INPUT_PULLUP);
  pinMode(RELAY_IN_2, INPUT_PULLUP);
  pinMode(RELAY_IN_3, INPUT_PULLUP);
  pinMode(RELAY_IN_4, INPUT_PULLUP);
  pinMode(RELAY_OUT_1, OUTPUT);
  pinMode(RELAY_OUT_2, OUTPUT);
  pinMode(RELAY_OUT_3, OUTPUT);
  pinMode(RELAY_OUT_4, OUTPUT);
  pinMode(INPUT_TYPE_SWITCH, INPUT_PULLUP);
  pinMode(CONTROL_INPUT, INPUT_PULLUP);
}

void setRelaysHigh() {
  digitalWrite(RELAY_OUT_1, HIGH);
  digitalWrite(RELAY_OUT_2, HIGH);
  digitalWrite(RELAY_OUT_3, HIGH);
  digitalWrite(RELAY_OUT_4, HIGH);
}

void setup() {
  setUpPins();
  setRelaysHigh();
}

void triggerRelay(int output) {
  digitalWrite(output, LOW);
  delay(RELAY_ACTIVE_TIME);
  digitalWrite(output, HIGH);
}

void checkInputs() {
  for (int i = 0; i <= NUMBER_OF_INPUTS; i++) {
    if (digitalRead(inputArray[i][0]) == LOW) {
      triggerRelay(inputArray[i][1]);
      activated = true;
      break;
    }
  }
}

void checkActivated() {
  if (activated) {
    delay(ACTIVATED_SECURE_DELAY);
    activated = false;
  }
}

void loop() {
  bool isOpen = digitalRead(CONTROL_INPUT) == LOW;
  if (!isOpen) {
    checkInputs();
  }

  checkActivated();

}
