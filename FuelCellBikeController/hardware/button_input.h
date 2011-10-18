int button_down() {
  if (digitalRead(BUTTON_1) == LOW) return 1;
  if (digitalRead(BUTTON_2) == LOW) return 2;
  if (digitalRead(BUTTON_3) == LOW) return 3;
  if (digitalRead(BUTTON_4) == LOW) return 4;
  if (digitalRead(BUTTON_5) == LOW) return 5;
  return 0;
}
