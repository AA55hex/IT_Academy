#pragma once
#include <render/frame_structures.h>
#include <memory>
#include <vector>
namespace render
{
class sprite2D;

/*!
 * \brief Аниматор спрайта
 * \note Аниматор спрайта работает только с текстурными атласами, но не с
 * массивами текстур
 */
class sprite_animator
{
 public:
  /*!
   * \brief Фрейм анимации
   * Воспомогательная структура, согласно которой отрисовывается спрайт
   */
  struct frame
  {
    const frame_descriptor discriptor;  ///< описатель области кадра
    double duration{0};  ///< длительность кадра в миллисекундах
  };

  /*!
   * \brief Инициализация аниматора
   * \param sprite  спрайт, используемый для анимации
   */
  sprite_animator(std::shared_ptr<sprite2D> sprite);

  /*!
   * \brief Обновление  состояния анимации
   * \param duration    прошедшее время в миллисекундах
   */
  void update(double duration);
  void render(const render_settings& settings);

  void add_frame(const frame_descriptor& discriptor, double duration);
  void clear_frames();

  const frame* current_frame();

  unsigned int get_frames_count() { return frames.size(); }
  double get_duration() { return summary_duration; }

 private:
  std::shared_ptr<sprite2D> sprite;
  std::vector<frame> frames{};
  size_t current_frame_index{0};
  double current_duration{0};
  double summary_duration{0};
};
}  // namespace render
