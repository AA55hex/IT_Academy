#pragma once
#include <memory>
#include <vector>
#include "wav_sound.h"
namespace sound
{
class sound_buffer
{
 public:
  using playback_ptr = std::shared_ptr<wav_sound::playback>;
  sound_buffer(int silence = 0);

  void use();
  void detach();

  void push_playback(playback_ptr playback);
  void clear();
  ~sound_buffer();

  static sound_buffer* current() { return current_buffer; }

 private:
  int silence{0};
  std::vector<playback_ptr> playback_list{};

  friend void audio_callback(void* userdata, Uint8* stream, int len);

  inline static sound_buffer* current_buffer{};
};
}  // namespace sound
