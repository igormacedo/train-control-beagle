#include <pthread.h>
#include <unistd.h>
#include <lcd.h>

#include "DisplayFactory.h"

Display* display = 0;
pthread_mutex_t trail3_mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t show_mutex = PTHREAD_MUTEX_INITIALIZER;

#define TRAIN1_SLEEP 1
#define TRAIN2_SLEEP 2

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

        sleep(TRAIN1_SLEEP);

        display->clear(1);
        display->fill(2, 'o');
        pthread_mutex_lock(&show_mutex);
        display->show();
        pthread_mutex_unlock(&show_mutex);

        sleep(TRAIN1_SLEEP);

        pthread_mutex_lock(&trail3_mutex);
        display->clear(2);
        display->fill(3, 'o');
        pthread_mutex_lock(&show_mutex);
        display->show();
        pthread_mutex_unlock(&show_mutex);

        sleep(TRAIN1_SLEEP);

        display->clear(3);
        pthread_mutex_unlock(&trail3_mutex);
        display->fill(4, 'o');
        pthread_mutex_lock(&show_mutex);
        display->show();
        pthread_mutex_unlock(&show_mutex);

        sleep(TRAIN1_SLEEP);
    }
}

void* train2_thread(void*)
{
    display->fill(5, 'x');
    pthread_mutex_lock(&show_mutex);
    display->show();
    pthread_mutex_unlock(&show_mutex);

    sleep(TRAIN2_SLEEP);

    while (1) {
        if (!display)
            break;

        display->clear(5);
        display->fill(6, 'x');
        pthread_mutex_lock(&show_mutex);
        display->show();
        pthread_mutex_unlock(&show_mutex);

        sleep(TRAIN2_SLEEP);

        display->clear(6);
        display->fill(7, 'x');
        pthread_mutex_lock(&show_mutex);
        display->show();
        pthread_mutex_unlock(&show_mutex);

        sleep(TRAIN2_SLEEP);

        pthread_mutex_lock(&trail3_mutex);
        display->clear(7);
        display->fill(3, 'x');
        pthread_mutex_lock(&show_mutex);
        display->show();
        pthread_mutex_unlock(&show_mutex);

        sleep(TRAIN2_SLEEP);

        display->clear(3);
        pthread_mutex_unlock(&trail3_mutex);
        display->fill(5, 'x');
        pthread_mutex_lock(&show_mutex);
        display->show();
        pthread_mutex_unlock(&show_mutex);

        sleep(TRAIN2_SLEEP);
    }
}

int main(int argc, char* argv[])
{
    display = DisplayFactory::getDisplay(Display::CONSOLE);
    if (display == DisplayFactory::getDisplay(Display::LCD)){
        display.lcd_fd = lcd_open("/dev/lcd0");
    }

    pthread_t t1, t2;

    pthread_create(&t1, NULL, train1_thread, NULL);
    pthread_create(&t2, NULL, train2_thread, NULL);

    pthread_join(t1, NULL);
    pthread_join(t2, NULL);

    return 0;
}
