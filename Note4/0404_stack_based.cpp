#include <vector>
#include <memory>


struct Derived {
  int do_something() {
    return value++;
  }
  int value = 0;
};

struct Derived2 {
  int do_something() {
    return value += 2;
  }
  int value = 5;
};

int main()
{
  std::vector<Derived> objs1;
  std::vector<Derived2> objs2;

  for (int i = 0; i < 1000; ++i) {
    objs1.emplace_back();
    objs2.emplace_back();
  }

  const auto do_something = [](auto &vec){
    for(auto &o : vec) {
      o.do_something();
    }    
  };

  do_something(objs1);
  do_something(objs2);
}