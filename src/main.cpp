#include <pthread.h>
#include <unistd.h>

#include "DisplayFactory.h"

#define ADC4 "/sys/bus/iio/devices/iio:device0/in_voltage4_raw"
#define ADC6 "/sys/bus/iio/devices/iio:device0/in_voltage6_raw"
#define MAX_BUFF 64

Display* display = 0;
pthread_mutex_t trail3_mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t show_mutex = PTHREAD_MUTEX_INITIALIZER;

static int train1_sleep_time_ms = 1000;
static int train2_sleep_time_ms = 2000;

void* train1_thread(void*)
{
    while (1) {
        if (!display)
            break;

        display->clear(4);
        display->fill(1, 'o');
        pthread_mutex_lock(&show_mutex);
        display->show();
        pthread_mutex_unlock(&show_mutex);

        usleep(train1_sleep_time_ms * 1000);

        display->clear(1);
        display->fill(2, 'o');
        pthread_mutex_lock(&show_mutex);
        display->show();
        pthread_mutex_unlock(&show_mutex);

        usleep(train1_sleep_time_ms * 1000);

        pthread_mutex_lock(&trail3_mutex);
        display->clear(2);
        display->fill(3, 'o');
        pthread_mutex_lock(&show_mutex);
        display->show();
        pthread_mutex_unlock(&show_mutex);

        usleep(train1_sleep_time_ms * 1000);

        display->clear(3);
        pthread_mutex_unlock(&trail3_mutex);
        display->fill(4, 'o');
        pthread_mutex_lock(&show_mutex);
        display->show();
        pthread_mutex_unlock(&show_mutex);

        usleep(train1_sleep_time_ms * 1000);
    }
}

void* train2_thread(void*)
{
    display->fill(5, 'x');
    pthread_mutex_lock(&show_mutex);
    display->show();
    pthread_mutex_unlock(&show_mutex);

    usleep(train2_sleep_time_ms * 1000);

    while (1) {
        if (!display)
            break;

        display->clear(5);
        display->fill(6, 'x');
        pthread_mutex_lock(&show_mutex);
        display->show();
        pthread_mutex_unlock(&show_mutex);

        usleep(train2_sleep_time_ms * 1000);

        display->clear(6);
        display->fill(7, 'x');
        pthread_mutex_lock(&show_mutex);
        display->show();
        pthread_mutex_unlock(&show_mutex);

        usleep(train2_sleep_time_ms * 1000);

        pthread_mutex_lock(&trail3_mutex);
        display->clear(7);
        display->fill(3, 'x');
        pthread_mutex_lock(&show_mutex);
        display->show();
        pthread_mutex_unlock(&show_mutex);

        usleep(train2_sleep_time_ms * 1000);

        display->clear(3);
        pthread_mutex_unlock(&trail3_mutex);
        display->fill(5, 'x');
        pthread_mutex_lock(&show_mutex);
        display->show();
        pthread_mutex_unlock(&show_mutex);

        usleep(train2_sleep_time_ms * 1000);
    }
}

void* speed_thread(void*)
{
    int fd = 0;
    char buf_ADC4[MAX_BUFF] = {0};
    snprintf(buf_ADC4, sizeof(buf_ADC4), ADC4);
    char adc4[5] = {0,0,0,0,0}; // four digits and null terminator \0

    char buf_ADC6[MAX_BUFF] = {0};
    snprintf(buf_ADC6, sizeof(buf_ADC6), ADC6);
    char adc6[5] = {0,0,0,0,0}; // four digits and null terminator \0

    while (1) {
        fd = open(buf_ADC4, O_RDONLY | O_NONBLOCK);
        read(fd, adc4, 4); // reads 4 bytes from file FD to adc4
        close(fd);

        fd = open(buf_ADC6, O_RDONLY | O_NONBLOCK);
        read(fd, adc6, 4); // reads 4 bytes from file FD to adc6
        close(fd);

        printf("ADC4: %d\tADC6: %d\n", atoi(adc4), atoi(adc6));

        train1_sleep_time_ms = atoi(adc4);
        train2_sleep_time_ms = atoi(adc6);
        usleep(100);
    }
}

int main(int argc, char* argv[])
{
    display = DisplayFactory::getDisplay(Display::LCD);

    pthread_t train1, train2;
    pthread_t speed;


    pthread_create(&train1, NULL, train1_thread, NULL);
    pthread_create(&train2, NULL, train2_thread, NULL);
    pthread_create(&speed, NULL, speed_thread, NULL);

    pthread_join(train1, NULL);
    pthread_join(train2, NULL);
    pthread_join(speed, NULL);

    return 0;
}
