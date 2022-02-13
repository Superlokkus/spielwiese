#include <SDL.h>
#include <SDL_audio.h>


int main() {
    SDL_Init(SDL_INIT_AUDIO);

    SDL_AudioSpec spec{};
    Uint8 *audio_buf{};
    Uint32 audio_len{};

    SDL_LoadWAV("/Users/markus/Downloads/CantinaBand60.wav", &spec, &audio_buf, &audio_len);

    SDL_AudioSpec ob_spec{};
    auto device = SDL_OpenAudioDevice(NULL, 0, &spec, &ob_spec, SDL_AUDIO_ALLOW_ANY_CHANGE);

    SDL_QueueAudio(device, audio_buf, audio_len);
    SDL_PauseAudioDevice(device, 0);

    SDL_Delay(5000);

    SDL_CloseAudioDevice(device);
    SDL_FreeWAV(audio_buf);

    SDL_QuitSubSystem(SDL_INIT_AUDIO);
}
