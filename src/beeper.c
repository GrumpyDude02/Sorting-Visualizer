#include <SDL2/SDL.h>
#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include "beeper.h"

int sample_nr = 0;
Beeper *InitializeBepper(int buffer, int amplitude, int sample_rate, int channel, float tone)
{
    Beeper *beeper = (Beeper *)malloc(sizeof(Beeper));
    if (beeper == NULL)
    {
        return NULL;
    }
    beeper->amplitude = amplitude;
    beeper->buffer = buffer;
    beeper->sample_rate = sample_rate;
    beeper->channels = channel;
    beeper->tone = tone;
    if (RequestDevice(beeper) == -1)
        return NULL;
    return beeper;
}

int RequestDevice(Beeper *beeper)
{
    SDL_AudioSpec desired;
    SDL_zero(desired);
    desired.freq = beeper->sample_rate;
    desired.channels = beeper->channels;
    desired.format = AUDIO_S16SYS;
    desired.samples = beeper->buffer;
    desired.userdata = beeper;
    desired.callback = AudioCallBack;
    beeper->device = SDL_OpenAudioDevice(NULL, 0, &desired, NULL, 0);
    if (beeper->device == 0)
    {
        printf("Failde to request audio device.\n%s.\n", SDL_GetError());
        SDL_CloseAudio();
        return -1;
    }
    return 0;
    SDL_PauseAudioDevice(beeper->device, 1);
}

void AddTone(Beeper *beeper, float freq)
{
    beeper->time = 0;
    beeper->tone = freq;
}

#define FADE_DURATION 0.01 // 10 milliseconds

static void AddSamples(Beeper *beeper, Sint16 *stream, int len)
{
    double period = 2 * M_PI * beeper->tone / beeper->sample_rate;
    double x = 0;
    int samples = len / sizeof(Sint16);

    // Apply linear fade-in and fade-out
    double fadeLength = beeper->sample_rate * FADE_DURATION;
    double fadeStep = 1.0 / fadeLength;
    double fadeValue = 0.0;

    for (int i = 0; i < samples; i++)
    {
        double sampleValue = beeper->amplitude * sin(x);

        // Apply fade-in and fade-out
        if (i < fadeLength)
        {
            sampleValue *= fadeValue;
            fadeValue += fadeStep;
        }
        else if (i > samples - fadeLength)
        {
            sampleValue *= fadeValue;
            fadeValue -= fadeStep;
        }

        stream[i] = (Sint16)sampleValue;
        x += period;
    }
}

// static void AddSamples(Beeper *beeper, Sint16 *stream, int len)
// {
//     double period = 2 * M_PI * beeper->tone / beeper->sample_rate;
//     double x = 0;
//     for (int i = 0; i < len; i++)
//     {
//         stream[i] = (Sint16)(beeper->amplitude * sin(x));
//         x += period;
//     }
// }

void AudioCallBack(void *user_data, Uint8 *stream, int len)
{
    AddSamples((Beeper *)user_data, (Sint16 *)stream, len);
}

void DetroyBeeper(Beeper *beeper)
{
    SDL_CloseAudio();
    free(beeper);
}