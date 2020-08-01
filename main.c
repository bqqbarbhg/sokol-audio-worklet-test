#include "sokol_audio.h"
#include <math.h>
#include <stdio.h>
#include <emscripten.h>

#define PUSH_FRAMES 512

static void render_audio(float* buffer, int num_frames, int num_channels) {
    static float t = 0.0f;
    const float dt = 1.0f / (float)saudio_sample_rate();
    for (int i = 0; i < num_frames; i++) {
        float wave = sinf(t * 262.0f * 2.0f * 3.14159f);
        float fade = sinf(t);
        float volume = 0.05f;
        buffer[i*2 + 0] = wave * (fade + 1.0f) * volume;
        buffer[i*2 + 1] = wave * (1.0f - fade) * volume;
        t += dt;
    }
}

void push_audio()
{
    static float buffer[PUSH_FRAMES * 2];
    int num_frames = saudio_expect();
    if (num_frames > PUSH_FRAMES) num_frames = PUSH_FRAMES;
    if (num_frames > 0) {
        printf("%d\n", num_frames);
        render_audio(buffer, num_frames, 2);
        saudio_push(buffer, num_frames);
    }
}

int main() {
    // init sokol-audio with default params
    saudio_setup(&(saudio_desc){
        #ifndef PUSH
            .stream_cb = render_audio,
        #endif
        .num_channels = 2,
    });

    printf("Make sure to click to start the sound!\n");

    #ifdef PUSH
        emscripten_set_main_loop(push_audio, 100, 0);
    #endif

    return 0;
}

#define SOKOL_IMPL
#include "sokol_audio.h"

