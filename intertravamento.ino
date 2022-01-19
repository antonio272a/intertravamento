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

void checkInput() {
  
}

void loop() {
  bool isOpen = digitalRead(CONTROL_INPUT) === LOW;
  if(!isOpen) {
    checkInputs();  
  }

}
