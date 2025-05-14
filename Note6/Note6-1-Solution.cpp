#include <memory>
#include <iostream>

struct Object {
  virtual ~Object() = default;
  virtual int value() { return 1; }
};

struct Derived : Object {
  virtual int value() { return 2; }
};

void use_object(Object &o) {
  std::cout << o->value() << '\n';
}

int main()
{
  Derived o;
  use_object(o); 
}
