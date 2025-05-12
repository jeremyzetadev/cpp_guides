#include <string>
#include <iostream>
#include <cstdlib>

struct MyClass {
  std::string s = "Hello World";
  MyClass() { std::cout << "constructor\n"; }
  ~MyClass() { std::cout << "destructor\n"; }
  MyClass(const MyClass &) = default;
  MyClass(MyClass &&) = default;
  MyClass&operator=(const MyClass &) = default;
  MyClass&operator=(MyClass &&) = default;
};
int main() {
  void *p = malloc(sizeof(MyClass));


  free(p);
}
