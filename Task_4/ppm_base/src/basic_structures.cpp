#include <fstream>
#include "ppm_base.h"
#include "render.h"
namespace ppm
{
bool image_manager::save_image(const render::canvas& img,
                               const std::string& path)
{
  using namespace std;
  ofstream out{path, ios_base::binary};
  if (!out.is_open()) return false;
  const char end{'\n'};
  const char space{'\n'};
  const int color_limit{255};
  out << "P6" << end;
  out << img.get_width() << space << img.get_height() << end << color_limit
      << end;
  streamsize buffer{static_cast<streamsize>(
      sizeof(render::rgb_color) * img.get_width() * img.get_height())};
  out.write(reinterpret_cast<const char*>(img.data()), buffer);
  return out.good();
}
}  // namespace ppm
