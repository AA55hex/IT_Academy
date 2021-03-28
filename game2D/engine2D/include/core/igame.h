#pragma once
namespace core
{
class igame
{
 public:
  virtual bool inicialize() = 0;

  virtual void read_input(double duration) = 0;
  virtual void update_data(double duration) = 0;
  virtual void render_output() = 0;

  bool is_playing() { return playing; }
  bool is_inicialized() { return inicialized; }

  virtual ~igame() {}

 protected:
  bool playing{true};
  bool inicialized{false};
};
}  // namespace core
