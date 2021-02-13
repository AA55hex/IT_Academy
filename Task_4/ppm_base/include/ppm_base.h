#pragma once
#define __cplusplus 201703L
#include <render.h>
#include <array>
#include <cassert>
#include <string>
#include <vector>
namespace ppm
{
class image_manager
{
 public:
  static render::canvas& load_image(const std::string& path);
  static bool save_image(const render::canvas& img, const std::string& path);
};

}  // namespace ppm
