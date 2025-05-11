#include <iostream>
#include <array>

template<typename T>
void print_elements(const T &items)
{
  for (const auto &e : items) {
    std::cout << e << '\n';
  }
}


int main()
{
  std::array<int, 3> ints{3,2,1};
  print_elements(ints);
}
