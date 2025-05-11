#include <vector>
#include <string>
#include <iostream>
#include <random>

int main()
{
  std::vector<int> v1;
  std::vector<int> v2;

  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_int_distribution<> dis(1, 100);

  for (int i = 0; i < 100; ++i) {
    v1.push_back(dis(gen));
    v2.push_back(dis(gen));
  }

  std::vector<int> in_both;

  for (const auto i : v1) {
    for (const auto j : v2) {
      if (i == j) {
        in_both.push_back(j);
        break;
      }
    }
  }

  for (const auto i : in_both) {
    std::cout << i << ',';
  }
  std::cout << '\n';
}
