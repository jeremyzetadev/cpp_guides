#include <vector>
#include <string>
#include <iostream>
#include <random>
#include <iterator>
#include <algorithm>

int main()
{
  std::vector<int> v1;
  std::vector<int> v2;

  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_int_distribution<> dis(1, 100);

  std::generate_n(std::back_inserter(v1), 100, [&](){ return dis(gen); });
  std::generate_n(std::back_inserter(v2), 100, [&](){ return dis(gen); });

  std::vector<int> in_both;

  std::sort(std::begin(v1), std::end(v1));
  std::sort(std::begin(v2), std::end(v2));

  std::set_intersection(std::begin(v1), std::end(v1),
                        std::begin(v2), std::end(v2),
                        std::back_inserter(in_both));

  for (const auto i : in_both) {
    std::cout << i << ',';
  }
  std::cout << '\n';
}