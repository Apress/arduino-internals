void usart_puts(char *s) {
  while(*s) {
    usart_putc(*s);
    s++;
  }
}
