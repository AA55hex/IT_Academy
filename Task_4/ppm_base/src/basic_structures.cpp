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

render::canvas image_manager::load_image(const std::string& path)
{
  using namespace std;
  ifstream input{path, ios_base::binary};

  string ppm_format{};
  input >> ppm_format;
  if (ppm_format != "P6") throw "incorrect ppm format";

  char buff{};
  string comment{};
  bool is_comments{true};
  while (is_comments)
    {
      input >> buff;
      is_comments = buff == '#';
      if (is_comments)
        {
          std::getline(input, comment, '\n');
        }
    }

  input.putback(buff);
  size_t width{}, height{};
  int color_limit;
  input >> width >> height >> color_limit;
  if (color_limit != 255) throw "bad color limit";

  render::canvas result{width, height};
  std::streamsize buf_size =
      static_cast<std::streamsize>(sizeof(render::rgb_color) * result.size());
  input.read(reinterpret_cast<char*>(result.data()), buf_size);
  return result;
}
}  // namespace ppm
