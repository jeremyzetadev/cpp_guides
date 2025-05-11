#include <iostream>

template<typename T>
struct Scope_Exit
{
  Scope_Exit(T t_fun) : fun(std::move(t_fun))
  {
  }

  ~Scope_Exit() { fun(); }
  Scope_Exit(const Scope_Exit &) = delete;
  Scope_Exit(Scope_Exit &&) = default;
  Scope_Exit&operator=(const Scope_Exit &) = delete;
  Scope_Exit&operator=(Scope_Exit &&) = delete;

  T fun;
};

template<typename T>
auto make_scope_exit(T &&t) {
  return Scope_Exit<T>(std::forward<T>(t));
}

int main(int argc, char *argv[])
{
  const auto scope = make_scope_exit([](){ std::cout << "Main exited\n"; });

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