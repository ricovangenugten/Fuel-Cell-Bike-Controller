unsigned long button_action_allowed = 0;

int button_down() {
  int button = 0;
  if (millis() > button_action_allowed) {
    if (digitalRead(BUTTON_1) == LOW) button = 1;
    if (digitalRead(BUTTON_2) == LOW) button = 2;
    if (digitalRead(BUTTON_3) == LOW) button = 3;
    if (digitalRead(BUTTON_4) == LOW) button = 4;
    if (digitalRead(BUTTON_5) == LOW) button = 5;
  }
  if (button > 0) button_action_allowed = millis()+BUTTON_DEAD_TIME;
  return button;
}
