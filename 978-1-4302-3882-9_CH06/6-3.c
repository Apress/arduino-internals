void usart_putc(char c) {
  loop_until_bit_is_set(UCSR0A, UDRE0); // wait for transmit buffer to be empty
  UDR0 = c; // transmit character out the serial port
}
