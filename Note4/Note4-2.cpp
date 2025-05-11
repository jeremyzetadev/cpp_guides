#include <iostream>

int main(int argc, char *argv[])
{
  if (argc < 5) {
    std::cout << "Not enough params\n";
    std::cout << "Main exited\n";
    return EXIT_FAILURE;
  } else if (argc > 10) {
    std::cout << "Too many params\n";
    std::cout << "Main exited\n";
    return EXIT_FAILURE;
  } else {
    if (argv[0] == std::string("program1")) {
      std::cout << "Program1 called\n";
      std::cout << "Main exited\n";
      return EXIT_SUCCESS;
    } else {
      std::cout << "argv[1]:" << argv[1] << '\n';
      std::cout << "Main exited\n";
      return EXIT_SUCCESS;
    }
  }
}
