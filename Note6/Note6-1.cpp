#include <memory>
#include <iostream>

struct Object {
  virtual ~Object() = default;
  virtual int value() { return 1; }
};

struct Derived : Object {
  virtual int value() { return 2; }
};

void use_object(const std::shared_ptr<Object> &o) {
  std::cout << o->value() << '\n';
}

int main()
{
  use_object(std::make_shared<Derived>()); 
}
