void usart_init(unsigned long rate) {
  UCSR0A = 0<<TXC0 | 0<<U2X0 | 0<<MPCM0;
  UCSR0B = 1<<RXCIE0 | 0<<TXCIE0 | 0<<UDRIE0 | 1<<RXEN0 | 0<<TXEN0 | 0<<UCSZ02 | 0<<TXB80;
  UCSR0C = 0<<UMSEL01 | 0<<UMSEL00 | 0<<UPM01 | 0<<UPM00 | 0<<USBS0 | 1<<UCSZ01 | 1<<UCSZ00 | 0<<UCPOL0;
  UBRR0 = (F_CPU / 16 / rate - 1);
}

void setup() {
  bitSet(DDRB, 5); // D13 (PB5) is connected to an LED
  usart_init(9600); // configure USART
}

void loop() {
  // nothing happens here
}

ISR(USART_RX_vect) {
  bitSet(PINB, 5); // toggle LED
  unsigned char c = UDR0; // read incoming byte to clear interrupt flag
}
