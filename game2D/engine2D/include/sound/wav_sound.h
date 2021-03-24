#pragma once
#include <SDL.h>
#include <memory>
namespace sound
{
enum struct playback_state
{
  on_play,
  on_pause,
  on_delete
};

class wav_sound
{
 public:
  struct playback
  {
    playback(wav_sound& sound_, uint32_t pos = 0, bool loop = false,
             playback_state state = playback_state ::on_play);
    void replay();
    wav_sound& sound;
    uint32_t position{0};
    playback_state state{playback_state ::on_play};
    bool is_looped{false};
  };

  wav_sound(uint8_t* data, uint32_t duration);

  std::shared_ptr<playback> play(
      uint32_t pos = 0, bool loop = false,
      playback_state state = playback_state ::on_play);

  uint8_t* get_data() const { return data; }
  uint32_t get_duration() const { return duration; }

  ~wav_sound();

  wav_sound(wav_sound&&);
  wav_sound& operator=(wav_sound&&);

  wav_sound() = delete;
  wav_sound(wav_sound&) = delete;
  wav_sound& operator=(wav_sound&) = delete;

 private:
  uint8_t* data{nullptr};
  uint32_t duration{0};
};
}  // namespace sound
