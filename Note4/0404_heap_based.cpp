#include <vector>
#include <memory>

struct Base {
  virtual int do_something() = 0;
  virtual ~Base() = default;
  Base() = default;
  Base(Base &&) = default;
  Base(const Base &) = default;
  Base& operator=(Base &&) = default;
  Base& operator=(const Base &) = default;
};

struct Derived : Base {
  virtual int do_something() override {
    return value++;
  }
  int value = 0;
};

struct Derived2 : Base {
  virtual int do_something() override {
    return value += 2;
  }
  int value = 5;
};

int main()
{
  std::vector<std::shared_ptr<Base>> objs;

  for (int i = 0; i < 1000; ++i) {
    objs.push_back(std::make_shared<Derived>());
    objs.push_back(std::make_shared<Derived2>());
  }

  for(const auto &o : objs) {
    o->do_something();
  }
}
