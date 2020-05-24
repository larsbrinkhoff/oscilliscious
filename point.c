#include <stdint.h>
#include <SDL2/SDL.h>

#define CHANNELS 4

static SDL_AudioDeviceID dev;

void init (void)
{
  SDL_AudioSpec want, have;
  int i;

  for (i = 0; i < SDL_GetNumAudioDevices (0); i++)
    printf ("Device %d: %s\n", i, SDL_GetAudioDeviceName (i, 0));

  SDL_memset(&want, 0, sizeof want);
  want.freq = 44100;
  want.format = AUDIO_S16SYS;
  want.channels = CHANNELS;
  want.samples = 4096;
  want.callback = NULL;
  want.userdata = NULL;

  SDL_Init (SDL_INIT_AUDIO);

  dev = SDL_OpenAudioDevice(NULL, 0, &want, &have, SDL_AUDIO_ALLOW_FREQUENCY_CHANGE);
  if (dev == 0) {
    SDL_Log("Failed to open audio: %s", SDL_GetError());
    exit (1);
  } else {
    if (have.format != want.format)
      SDL_Log("We didn't get requested audio format.");
    if (have.freq != want.freq)
      SDL_Log("We didn't get requested audio frequency.");
    if (have.channels != want.channels)
      SDL_Log("We didn't get requested audio channels.");
    fprintf(stderr, "Format: %x\n", have.format);
    fprintf(stderr, "Frequency: %d\n", have.freq);
    fprintf(stderr, "Channels: %d\n", have.channels);
    fprintf(stderr, "Samples: %d\n", have.samples);
    fprintf(stderr, "Size: %d\n", have.size);
    SDL_PauseAudioDevice(dev, 0);
  }
}

void draw_xyz (int x, int y, int z)
{
  int16_t data[CHANNELS];

  if (x < 0 || x > 65535 || y < 0 || x > 65535)
    return;

  while (SDL_GetQueuedAudioSize (dev) > 44100)
    SDL_Delay (10);

  memset (data, 0, sizeof data);
  data[0] = x - 32768;
  data[1] = y - 32768;
  data[2] = z - 32768;

  SDL_QueueAudio (dev, data, sizeof data);
}
