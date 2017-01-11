void setup() {
  DDRB |= (1<<DDB5);        // Set led pin 13 as an output.
  DDRD |= ~(1 << DDB2);     // Set pin 2 as an input.
}

void loop() {
  if(((PIND >> 2) & 1) == 1){
    PORTB |= (1 << PORTB5);
  } else {
    PORTB &= ~(1 << PORTB5);
  }
}
