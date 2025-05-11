#include <iostream>

void print_elements(const int *items, const int num)
{
  for (int i = 0; i < num; ++i) {
    std::cout << items[i] << '\n';
  }
}


int main()
{
  int *ints = new int[3];
  ints[0] = 3;
  ints[1] = 2;
  ints[2] = 1;

  print_elements(ints, 3);
  delete[] ints;
}
