#include <stdio.h>
#include <SDL2/SDL.h>
#include <math.h>
#include "my_func.h"
#include "bar.h"
#include "beeper.h"

int main(int argc, char *argv[])
{
    SDL_Init(SDL_INIT_AUDIO | SDL_INIT_EVENTS | SDL_INIT_VIDEO);
    WindowProp dimensions = {1280, 600, 0.0, 0.0};
    SortingParams sp;
    SDL_zero(sp);
    Beeper *beep = InitializeBepper(BUFFER_SIZE, AMPLITUDE, SAMPLE_RATE, CHANNELS, 440.0f);
    SDL_PauseAudioDevice(beep->device, 0);
    float f = 400;
    while (1)
    {
        f += 10;
        AddTone(beep, f);
        SDL_Delay(500);
    }

    if (beep == NULL)
        return -1;
    SortingAlgorithm sort[] = {
        {bubble_sort},
        {quick_sort},
        {selection_sort},
        {merge_sort},
        {insertion_sort},
        {cocktail_sort}};
    int choice;
    while ((choice = get_choice()) != 0)
    {
        do
        {
            sp.bar_number = get_int("Enter the number of bars (max = 600) : ");
        } while (sp.bar_number < 0 || sp.bar_number > 600);

        dimensions.cell_h = dimensions.HEIGHT / (float)sp.bar_number;
        dimensions.cell_w = dimensions.WIDTH / (float)sp.bar_number;
        sp.start_index = 0;
        sp.end_index = sp.bar_number - 1;
        if (render_window(dimensions, choice, sp, sort) == -1)
        {
            SDL_Quit();
            return -1;
        }
    }
    DetroyBeeper(beep);
    SDL_Quit();
    return 0;
}

// int main(int argc, char **argv)
// {
//     SDL_Init(SDL_INIT_AUDIO);

//     the representation of our audio device in SDL:
//     SDL_AudioDeviceID audio_device;

//     opening an audio device:
//     SDL_AudioSpec audio_spec;
//     SDL_zero(audio_spec);
//     audio_spec.freq = 44100;
//     audio_spec.format = AUDIO_S16SYS;
//     audio_spec.channels = 1;
//     audio_spec.samples = 1024;
//     audio_spec.callback = NULL;

//     audio_device = SDL_OpenAudioDevice(
//         NULL, 0, &audio_spec, NULL, 0);

//     pushing 3 seconds of samples to the audio buffer:
//     float x = 0;
//     for (int i = 0; i < audio_spec.freq * 3; i++)
//     {
//         x += .010f;

//         SDL_QueueAudio expects a signed 16-bit value
//         note: "5000" here is just gain so that we will hear something
//         int16_t sample = sin(x * 4) * 5000;

//         const int sample_size = sizeof(int16_t) * 1;
//         SDL_QueueAudio(audio_device, &sample, sample_size);
//     }

//     unpausing the audio device (starts playing):
//     SDL_PauseAudioDevice(audio_device, 0);

//     SDL_Delay(3000);

//     SDL_CloseAudioDevice(audio_device);
//     SDL_Quit();

//     return 0;
// }