#include <vector>
#include <string>
#include <iostream>

int main(int argc, const char *argv[])
{
  const std::vector<std::string> args(argv, argv+argc);

  auto verbose_enabled = false;
  auto quiet_enabled = false;
  auto all_enabled = false;

  for (const auto &arg : args) {
    if (arg == "--verbose") { verbose_enabled = true; }
    else if (arg == "--quiet") { quiet_enabled = true; }
    else if (arg == "--all") { all_enabled = true; }
  }

  if (verbose_enabled) {
    std::cout << "\tVerbose mode enabled\n";
  }

  if (quiet_enabled) {
    std::cout << "\tQuiet mode enabled\n";
  }

  if (all_enabled) {
    std::cout << "\tProcess all enabled\n";
  }

  if (verbose_enabled && quiet_enabled) {
    std::cerr << "Conflicting settings, both `--quiet` and `--verbose` enabled\n";
    return EXIT_FAILURE;
  }

  return EXIT_SUCCESS;
}
