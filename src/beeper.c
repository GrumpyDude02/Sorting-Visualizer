#include <SDL2/SDL.h>
#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include "beeper.h"

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
    beeper->sample_played = 0;
    beeper->SoundOn = 0;
    beeper->ocs_type = 1;
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
    beeper->tone = freq;
}

double osc(int type, double x)
{
    switch (type)
    {
    case 0:
        return sin(x);
        break;
    case 1:
        return sin(x) < 0.0 ? -1.0 : 1.0;
    default:
        break;
    }
}
double Fade(Beeper *beeper, double *amp)
{
    if (*amp < AMPLITUDE && beeper->SoundOn)
        *amp = *amp + 10;
    else if (*amp > 0.0 && !beeper->SoundOn)
        *amp = *amp - 10;
    return beeper->amplitude;
}

static void AddSamples(Beeper *beeper, Sint16 *stream, int len)
{
    memset(stream, 0, len / sizeof(Sint16));
    int samples = len / sizeof(Sint16);
    double amp = 0;
    for (int i = 0; i < samples; i++)
    {
        double x = (2.0 * M_PI * (beeper->sample_played + i) / beeper->sample_rate) * beeper->tone;
        stream[i] = (Sint16)(beeper->amplitude / 2 * osc(1, x));
    }
    beeper->sample_played += samples;
}

void AudioCallBack(void *user_data, Uint8 *stream, int len)
{
    AddSamples((Beeper *)user_data, (Sint16 *)stream, len);
}

void Beep(Beeper *beeper, int duration)
{
    beeper->SoundOn = 1;
    SDL_PauseAudioDevice(beeper->device, 0);
    SDL_Delay(duration);
    SDL_PauseAudioDevice(beeper->device, 1);
    beeper->SoundOn = 0;
}

void DetroyBeeper(Beeper *beeper)
{
    SDL_CloseAudio();
    free(beeper);
}