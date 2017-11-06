#include "lcd.h"
#include <pthread.h>
#include <unistd.h>

#include "DisplayFactory.h"

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
    while (1) {
        train1_sleep_time_ms = 1000;
        train2_sleep_time_ms = 2000;
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
