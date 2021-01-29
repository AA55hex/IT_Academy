#include <iostream>
#include <SDL_version.h>
std::ostream& operator<<(std::ostream& ost, const SDL_version& version)
{
    ost << static_cast<int>(version.major)
        << '.' << static_cast<int>(version.minor)
        << '.' << static_cast<int>(version.patch)
        << std::endl;
    return ost;
}

int main()
{
    SDL_version version_linked{};
    SDL_version version_compiled{};

    SDL_VERSION(&version_compiled);
    SDL_GetVersion(&version_linked);

    std::cout << "Compiled:\t" << version_compiled
              << "Linked:\t" << version_linked;

    return !std::cout.good();
}
