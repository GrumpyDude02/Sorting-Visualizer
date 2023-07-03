#include <SDL2/SDL.h>
#ifndef BEEPER_H
#define BEEPER_H

#define AMPLITUDE 32000
#define CHANNELS 1
#define SAMPLE_RATE 44100
#define BUFFER_SIZE 4096
#define DEFAULT_TONE 440.0f

typedef struct Beeper
{
    int buffer;
    int amplitude;
    int sample_rate;
    int channels;
    float tone;
    Uint64 sample_played;
    SDL_AudioDeviceID device;
} Beeper;

Beeper *InitializeBepper(int buffer, int amplitude, int sample_rate, int channel, float tone);
int RequestDevice(Beeper *beeper);
void AddTone(Beeper *beeper, float freq);
void PlaySounds(Beeper *beeper, int duration);
void DetroyBeeper(Beeper *beeper);
void AudioCallBack(void *beeper, Uint8 *stream, int len);

#endif