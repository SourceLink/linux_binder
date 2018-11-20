#ifndef SL_UART_H_
#define SL_UART_H_

#ifdef __cplusplus
extern "C" {
#endif
extern int uart_setup_port(
		int dev_fd, 
		int baud_rate, 
		int data_bits, 
		int parity,
		int stop_bits
		);

extern int uart_reset_port(int dev_fd);
extern int uart_send_buf(int dev_fd, unsigned char *_buf, int len);
extern int uart_send_char(int dev_fd, unsigned char value);
extern int uart_get_buf(int dev_fd, unsigned char *buf, int len);
extern int uart_get_char(int dev_fd, unsigned char *byte_data);



#define CON2	"/dev/ttySAC1"		//485
#define CON3	"/dev/ttySAC2"		//232
#define CON4	"/dev/ttySAC3"		//232
#define CON5	"/dev/ttySAC4"		//232
#define CON6	"/dev/ttySAC5"		//ttl
#define CON7	"/dev/ttySAC6"		//ttl
#define CON8	"/dev/ttySAC7"		//ttl

#ifdef __cplusplus
}
#endif

#endif
