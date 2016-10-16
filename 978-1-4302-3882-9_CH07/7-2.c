ISR(USART_RX_vect) {
  unsigned char c = UDR0; // read incoming byte to clear interrupt flag
  if(c =='1') {
    bitSet(PORTB, 5); // turn on LED
  } else if(c == '0') {
    bitClear(PORTB, 5); // turn off LED
  }
}
