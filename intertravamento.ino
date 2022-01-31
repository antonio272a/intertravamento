#define RELAY_IN_1 2
#define RELAY_IN_2 3
#define RELAY_IN_3 4
#define RELAY_IN_4 5
#define RELAY_OUT_1 A3
#define RELAY_OUT_2 A2
#define RELAY_OUT_3 A1
#define RELAY_OUT_4 A0
#define INPUT_TYPE_SWITCH 7
#define CONTROL_INPUT_1 6
#define CONTROL_INPUT_2 8
#define CONTROL_INPUT_3 9
#define CONTROL_INPUT_4 10
#define TURN_OFF_INPUT_1 A4
#define TURN_OFF_INPUT_2 A5
#define TURN_OFF_INPUT_3 A6
#define TURN_OFF_INPUT_4 A7

#define NUMBER_OF_INPUTS 4

#define RELAY_ACTIVE_TIME 500
#define ACTIVATED_SECURE_DELAY 5000

int inputArray[NUMBER_OF_INPUTS][2] = {
  {RELAY_IN_1, RELAY_OUT_1}, {RELAY_IN_2, RELAY_OUT_2}, {RELAY_IN_3, RELAY_OUT_3}, {RELAY_IN_4, RELAY_OUT_4}
};

int controlInputsArray[NUMBER_OF_INPUTS] = { CONTROL_INPUT_1, CONTROL_INPUT_2, CONTROL_INPUT_3, CONTROL_INPUT_4 };

int turnOffNumbersArray[NUMBER_OF_INPUTS] = { TURN_OFF_INPUT_1, TURN_OFF_INPUT_2, TURN_OFF_INPUT_3, TURN_OFF_INPUT_4 };

bool turnOffArray[NUMBER_OF_INPUTS] = {false, false, false, false};

bool activated = false;
bool isOpen = false;
int activeRelayIn;
int activeRelayOut;
int type;

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
  pinMode(CONTROL_INPUT_1, INPUT_PULLUP);
  pinMode(CONTROL_INPUT_2, INPUT_PULLUP);
  pinMode(CONTROL_INPUT_3, INPUT_PULLUP);
  pinMode(CONTROL_INPUT_4, INPUT_PULLUP);
  pinMode(TURN_OFF_INPUT_1, INPUT_PULLUP);
  pinMode(TURN_OFF_INPUT_2, INPUT_PULLUP);
  pinMode(TURN_OFF_INPUT_3, INPUT_PULLUP);
  pinMode(TURN_OFF_INPUT_4, INPUT_PULLUP);
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
  for (int i = 0; i < NUMBER_OF_INPUTS; i++) {
    if ((!turnOffArray[i]) && (digitalRead(inputArray[i][0]) == LOW)) {
      triggerRelay(inputArray[i][1]);
      activated = true;
      activeRelayIn = inputArray[i][0];
      activeRelayOut = inputArray[i][1];
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

void checkActiveRelay() {
  for (int i = 0; i < NUMBER_OF_INPUTS; i++) {
    if (turnOffArray[i] && inputArray[i][0] == activeRelayIn) {
      return;
    }
  }

  if (digitalRead(activeRelayIn) == LOW) {
    triggerRelay(activeRelayOut);
  }
}

void checkIsOpen() {
  for (int i = 0; i < NUMBER_OF_INPUTS; i++) {
    if (!turnOffArray[i] && digitalRead(controlInputsArray[i]) == type) {
      isOpen = true;
      break;
    } else {
      isOpen = false;
    }
  }
}

void checkTurnOff() {
  for (int i = 0; i < NUMBER_OF_INPUTS; i++) {
    turnOffArray[i] = (digitalRead(turnOffNumbersArray[i]) == HIGH);
  }
}

void loop() {
  type = digitalRead(INPUT_TYPE_SWITCH);

  checkIsOpen();

  if (!isOpen) {
    checkTurnOff();
    checkInputs();
    checkActivated();
  }

  if (isOpen) {
    checkActiveRelay();
  }

  checkActivated();

}
