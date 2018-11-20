#ifndef SL_GPIO_H_
#define SL_GPIO_H_

#ifdef __cplusplus
extern "C" {
#endif

#define GPIO_FILENAME_DEFINE(pin,field) char fileName[255] = {0}; \
        sprintf(fileName, "/sys/class/gpio/gpio%d/%s", pin, field);

#define	GPIO_OUT	(1)
#define GPIO_IN		(2)

#define GPIO_LOW    (0)
#define GPIO_HIGH   (1)

/* 
	把标准字符的io标注转换成gpio系统中的io标号
	解析gpio；gpio的端口都从0开始，像imx6ulgpio是从1开始
	要自动向前移一位，原理图上标注GPIO5_01, 实际在程序是要填写GPIO4_01
	这个结构还需要修改
*/
extern int convert_gpio_pin(const char *pin_str);
extern int export_gpio_pin(int pin);
extern int unexport_gpio_pin(int pin);
extern int set_gpio_value(int pin, unsigned char value);
extern int get_gpio_value(int pin);
extern int set_gpio_direction(int pin, int direction);
extern int get_gpio_direction(int pin);


#ifdef __cplusplus
}
#endif


#endif
