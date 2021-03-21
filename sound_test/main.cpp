#include <cassert>
#include <chrono>
#include <cmath>
#include <cstdint>
#include <cstring>
#include <iomanip>
#include <iostream>

#include "sound.h"

wav_sound_meta loadWAV(const char* file_name);

int main(int /*argc*/, char* /*argv*/[])
{
  using namespace std;

  sound_manager::init();

  wav_sound_meta audio0{loadWAV("res/highlands.wav")};
  wav_sound_meta audio1{loadWAV("res/rain.wav")};

  sound_manager::play_sound(audio0, 25358000, true);
  sound_manager::play_sound(audio1);

  sound_manager::play();

  while (true)
    {
    };

  // stop audio device and stop thread call our callback function
  sound_manager::pause();

  return 0;
}

wav_sound_meta loadWAV(const char* file_name)
{
  using namespace std;
  SDL_AudioSpec audio_spec_from_file{};
  uint8_t* sample_buffer_from_file = nullptr;
  uint32_t sample_buffer_len_from_file = 0;

  clog << "loading sample buffer from file: " << file_name << endl;

  if (SDL_LoadWAV(file_name, &audio_spec_from_file, &sample_buffer_from_file,
                  &sample_buffer_len_from_file) == nullptr)
    {
      cerr << "error: can't parse and load audio samples from file\n";
      return wav_sound_meta{};
    }

  // clog << "loaded file audio spec:\n" << audio_spec_from_file << endl;

  wav_sound_meta result{sample_buffer_from_file, sample_buffer_len_from_file,
                        audio_spec_from_file};

  clog << "audio buffer from file size: " << sample_buffer_len_from_file
       << " B (" << sample_buffer_len_from_file / double(1024 * 1024) << ") Mb"
       << endl;
  return result;
}
