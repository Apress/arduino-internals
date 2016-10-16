void usart_puti(long i) {

  char s[25]; // character buffer to build string in

  itoa(i, s, 10); // convert integer to ASCII string, base 10
  usart_puts(s); // now print the string on the serial port
}
