#include "mbed.h"

#include "uLCD_4DGL.h"

using namespace std::chrono;

#define DEBOUNCE_TIME 200
#define INPUT 0
#define START 1

#define RESOLUTION 10

uLCD_4DGL uLCD(D1, D0, D2);
DigitalOut led_blue(LED3);
DigitalOut led_test(LED1);

Timer debounce_button;
InterruptIn button_up(D11);
InterruptIn button_down(D9);
InterruptIn button_select(D8);
InterruptIn button_fft(USER_BUTTON);

Thread fft_thread;

EventQueue queue(32 * EVENTS_EVENT_SIZE);

Timer wave_generate;
AnalogOut Wave(PA_4);
AnalogIn Measure(A0);

Timer fft;

Thread uLCD_thread;
Thread analogout_thread;

void freq_up();
void freq_down();
void freq_select();
void uLCD_display();
void analogout();
void fft_data();

int freq = 20;
int state = INPUT;
float ADCdata[100];
int sample = 100;

int main()

{
    uLCD_thread.start(uLCD_display);
    analogout_thread.start(analogout);
    fft_thread.start(callback(&queue, &EventQueue::dispatch_forever));

    debounce_button.start();
    button_down.rise(&freq_down);
    button_up.rise(&freq_up);
    button_select.rise(&freq_select);
    button_fft.rise(queue.event(fft_data));

    wave_generate.start();

    fft.start();
    
    while(true) {
        led_blue = !led_blue;
        ThisThread::sleep_for(1s);
    }

}

void fft_data() {
    for (int i = 0; i < sample; i++){
        ADCdata[i] = Measure;

        while(duration_cast<milliseconds>(fft.elapsed_time()).count() < 10);
        fft.reset();
    }

    for (int i = 0; i < sample; i++){
        printf("%f\r\n", ADCdata[i]);
        ThisThread::sleep_for(100ms);
    }
}

void analogout() {
    while(true) {
        int t = 1000000 / freq;
        int dt = round(float(t) / RESOLUTION);

        float v = 0.91;
        float dv = 0.91 / RESOLUTION;

        while(state == START) {
            v -= dv;
            if (v < 0) {
                v = 0.91;
            }
            Wave = v;
            //while(duration_cast<milliseconds>(wave_generate.elapsed_time()).count() < dt);
            while(wave_generate.elapsed_time().count() < dt);
            wave_generate.reset();
        }
        Wave = 0;
    }
}

void freq_down() {
    if (duration_cast<milliseconds>(debounce_button.elapsed_time()).count() > DEBOUNCE_TIME) {
        freq -= 5;
        debounce_button.reset();
        state = INPUT;
    }
}

void freq_up() {
    if (duration_cast<milliseconds>(debounce_button.elapsed_time()).count() > DEBOUNCE_TIME) {
        freq += 5;
        debounce_button.reset();
        state = INPUT;
    }
}

void freq_select() {
    if (duration_cast<milliseconds>(debounce_button.elapsed_time()).count() > DEBOUNCE_TIME) {
        debounce_button.reset();
        state = START;
    }
}

void uLCD_display() {
    uLCD.locate(1, 1);
    uLCD.printf("Freq Selector");
    uLCD.locate(1, 3);
    uLCD.printf("State: ");
    while(true) {
        if (state == INPUT) {
            uLCD.locate(1, 2);
            uLCD.printf("%4dHz", freq);
            uLCD.locate(8, 3);
            uLCD.printf("INPUT");
        } else if (state == START) {
            uLCD.locate(7, 3);
            uLCD.printf("START");
        }
    }
}