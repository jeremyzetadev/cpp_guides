#include <iostream>
#include <string>

struct Print_On_Exit
{
  Print_On_Exit(std::string t_msg)
    : msg(std::move(t_msg))
  {
  }

  ~Print_On_Exit() {
    std::cout << msg << '\n';
  }
  Print_On_Exit(const Print_On_Exit &) = delete;
  Print_On_Exit(Print_On_Exit &&) = default;
  Print_On_Exit&operator=(const Print_On_Exit &) = delete;
  Print_On_Exit&operator=(Print_On_Exit &&) = default;
  

  std::string msg;
};

int main(int argc, char *argv[])
{
  Print_On_Exit me("Main Exited");

  if (argc < 5) {
    std::cout << "Not enough params\n";
    return EXIT_FAILURE;
  } else if (argc > 10) {
    std::cout << "Too many params\n";
    return EXIT_FAILURE;
  } else {
    if (argv[0] == std::string("program1")) {
      std::cout << "Program1 called\n";
      return EXIT_SUCCESS;
    } else {
      std::cout << "argv[1]:" << argv[1] << '\n';
      return EXIT_SUCCESS;
    }
  }
}