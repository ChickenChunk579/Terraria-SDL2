#pragma once
#include <SDL3_mixer/SDL_mixer.h>
#include <cassert>

static Mix_Music **currentlyPlaying = nullptr;

void initAudio() {
    SDL_AudioSpec spec;

    spec.freq = MIX_DEFAULT_FREQUENCY;
    spec.format = MIX_DEFAULT_FORMAT;
    spec.channels = MIX_DEFAULT_CHANNELS;

    assert(Mix_OpenAudio(0, &spec) != -1);

    Mix_QuerySpec(&spec.freq, &spec.format, &spec.channels);
}

void setCurrentlyPlaying(Mix_Music** music) {
    if (currentlyPlaying == music) {
        return;
    } else {
        Mix_PlayMusic(*music, 0);
        currentlyPlaying = music;
    }
}