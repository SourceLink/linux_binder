#ifndef SL_SPI_H_
#define SL_SPI_H_

#ifdef __cplusplus
extern "C" {
#endif
// SPIMode
#define SPI_MODE0  (0)  // CPOL  0, CPHA  0
#define SPI_MODE1  (1)  // CPOL  0, CPHA  1
#define SPI_MODE2  (2)  // CPOL  1, CPHA  0
#define SPI_MODE3  (3)  // CPOL  1, CPHA  1

extern int set_spi_writeBits_PerWord(int spi_fd, int bits);
extern int set_spi_max_speed(int spi_fd, unsigned int spi_speed);
extern int set_spi_data_mode(int spi_fd, int mode);

extern int write_bytes_to_spi(
		int spi_fd
		, unsigned char * writeData
		, int writeLen
		, int spi_delay
		, int spi_speed
		, int spi_bits
		);
extern int read_bytes_from_spi(
	 int spi_fd
	 , unsigned char * readBuffer
	 , int readLen
	 , int spi_delay
	 , int spi_speed
	 , int spi_bits
	 );


#define SPI1_PATH "/dev/spidev0.0"
#define SPI2_PATH "/dev/spidev1.0"
#ifdef __cplusplus
}
#endif

#endif
