#include "sound.h"
#include <algorithm>
#include <cstring>
#include <iostream>
bool sound_manager::init()
{
  playback_list = std::vector<playback>{};

  if (SDL_Init(SDL_INIT_AUDIO) < 0)
    {
      std::cerr << "error: can't init audio: " << SDL_GetError();
      return false;
    }

  const char* device_name = nullptr;    // device name or nullptr
  const int32_t is_capture_device = 0;  // 0 - play device, 1 - microphone
  SDL_AudioSpec disired{.freq = 48000,
                        .format = AUDIO_S16LSB,
                        .channels = 2,  // stereo
                        .silence = 0,
                        .samples = 4096,  // must be power of 2
                        .padding = 0,
                        .size = 0,
                        .callback = audio_callback,
                        .userdata = &playback_list};

  SDL_AudioSpec returned{};

  const int32_t allow_changes = 0;

  audio_device = SDL_OpenAudioDevice(device_name, is_capture_device, &disired,
                                     &returned, allow_changes);
  if (audio_device == 0)
    {
      std::cerr << "error: failed to open audio device: " << SDL_GetError()
                << std::endl;
      return EXIT_FAILURE;
    }

  if (disired.format != returned.format ||
      disired.channels != returned.channels || disired.freq != returned.freq)
    {
      std::cerr << "error: disired != returned audio device settings!";
      return EXIT_FAILURE;
    }

  return true;
}

void sound_manager::dispose()
{
  pause();
  SDL_CloseAudioDevice(audio_device);

  playback_list.clear();
}

void sound_manager::play_sound(const wav_sound_meta& sound,
                               uint32_t current_pos, bool is_looped)
{
  playback_list.push_back(playback{&sound, current_pos, is_looped, true});
}
void sound_manager::clear_stream() { playback_list.clear(); }

void sound_manager::audio_callback(void* userdata, Uint8* stream, int len)
{
  std::remove_if(playback_list.begin(), playback_list.end(),
                 [](playback& p) { return !p.is_playing; });
  std::memset(stream, 0, static_cast<size_t>(len));
  for (playback& snd : playback_list)
    {
      uint32_t delta = snd.sound_data->duration - snd.current_pos;
      const uint8_t* current_buff = &snd.sound_data->begin[snd.current_pos];
      uint32_t stream_length{static_cast<uint32_t>(len)};
      if (delta > 0)
        {
          if (delta <= stream_length)
            {
              // copy rest to buffer
              SDL_MixAudioFormat(stream, current_buff,
                                 snd.sound_data->specification.format, delta,
                                 SDL_MIX_MAXVOLUME);
              snd.current_pos += delta;
            }
          else
            {
              SDL_MixAudioFormat(stream, current_buff,
                                 snd.sound_data->specification.format,
                                 stream_length, SDL_MIX_MAXVOLUME);
              snd.current_pos += stream_length;
            }
        }
      else
        {
          if (snd.is_looped)
            {
              // start from begining
              snd.current_pos = 0;
            }
          else
            {
              snd.is_playing = false;
            }
        }
    }
}

void sound_manager::play() { SDL_PauseAudioDevice(audio_device, SDL_FALSE); }
void sound_manager::pause() { SDL_PauseAudioDevice(audio_device, SDL_TRUE); }

wav_sound_meta::~wav_sound_meta() { SDL_FreeWAV(begin); }

wav_sound_meta::wav_sound_meta(wav_sound_meta&& sound)
{
  begin = sound.begin;
  duration = sound.duration;
  specification = sound.specification;

  sound.begin = nullptr;
}
wav_sound_meta& wav_sound_meta::operator=(wav_sound_meta&& sound)
{
  SDL_FreeWAV(begin);

  begin = sound.begin;
  duration = sound.duration;
  specification = sound.specification;

  sound.begin = nullptr;
  return *this;
}

wav_sound_meta::wav_sound_meta(uint8_t* begin_, uint32_t duration_,
                               SDL_AudioSpec spec_)
    : begin{begin_}, duration{duration_}, specification{spec_}
{
}
