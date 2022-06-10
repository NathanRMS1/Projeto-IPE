byte TP = 0b10101010;
void setup() {
  DDRC = 0b11111111;
  
  // Initialize Timer1
  noInterrupts(); 
  
  TCCR1A = 0;
  TCCR1B = 0;
  TCNT1 = 0;
  OCR1A = 200; 
  
  TCCR1B |= (1 << WGM12); 
  TCCR1B |= (1 << CS10); 
  TIMSK1 |= (1 << OCIE1A); 
  
  interrupts(); // Enable interrupts
}
ISR(TIMER1_COMPA_vect) {
  PORTC = TP; 
  TP = ~TP; 
}
void loop() {
}
