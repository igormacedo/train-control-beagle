#include <stdio.h>  // prinf()
#include <unistd.h> // fork()
#include <stdlib.h> // exit()
#include <sys/resource.h> // setpriority(), getpriority()
#include <time.h> // usleep()
#include <fcntl.h> // O_RDONLY
#include <gpio.h> // gpio functions

#define ADC4 "/sys/bus/iio/devices/iio:device0/in_voltage4_raw"
#define ADC6 "/sys/bus/iio/devices/iio:device0/in_voltage6_raw"
#define MAX_BUFF 64

#define GPIO_LED_SON1 68
#define GPIO_LED_SON2 67

int main(int argc, char **argv)
{

}
