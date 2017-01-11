void setup() {
  DDRB |= (1 << DDB5);        // Set Pin 13 as an output.
  DDRD |= ~(1 << DDB2);       // Set Pin 2 as an input.
}

void loop() {
  if(((PIND >> 2) & 1) == 1){ // If Pin 2 reads HIGH
    PORTB |= (1 << PORTB5);   // Write HIGH to Pin 13
  } else {
    PORTB &= ~(1 << PORTB5);  // Write LOW to Pin 13
  }
}
