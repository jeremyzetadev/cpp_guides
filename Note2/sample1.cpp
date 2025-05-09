#include <vector>
#include <string>
#include <iostream>

int main(int argc, const char *argv[])
{
  std::vector<std::string> args;

  for (int i = 0; i < argc; ++i) {
    args.push_back(argv[i]);
  }

  auto verbose_enabled = false;
  auto quiet_enabled = false;
  auto all_enabled = false;

  for (int i = 0; i < static_cast<int>(args.size()); ++i) {
    if (args[(size_t)i] == "--verbose") verbose_enabled = true;
    if (args[(size_t)i] == "--quiet") quiet_enabled = true;
    if (args[(size_t)i] == "--all") all_enabled = true;
  }

  if (verbose_enabled) {
    std::cout << "\tVerbose mode enabled" << std::endl;
  }

  if (quiet_enabled) {
    std::cout << "\tQuiet mode enabled" << std::endl;
  }

  if (all_enabled) {
    std::cout << "\tProcess all enabled" << std::endl;
  }

  if (verbose_enabled && quiet_enabled) {
    std::cerr << "Conflicting settings, both `--quiet` and `--verbose` enabled" << std::endl;
    return 1;
  }

  return 0;
}