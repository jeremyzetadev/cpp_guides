#include <iostream>
#include <vector>
#include <string>
#include <cstring>
#include <algorithm>

struct Vowel_Count {
  Vowel_Count(std::string t_word, const int t_num_vowels)
    : word(std::move(t_word)),
      num_vowels(t_num_vowels)
  {
  }

  int get_count() const {
    ++cache_calls;
    return num_vowels;
  }

  std::string word;

  private:
    int num_vowels;
    mutable int cache_calls = 0;
};

bool is_vowel(const char c)
{
  static std::vector<char> vowels = {'a','e','i','o','u'};

  return std::any_of(std::begin(vowels), std::end(vowels), [&](const char v){ return c == v; });
}

int count_vowels(const std::string &t_str)
{
  return std::count_if(std::begin(t_str), std::end(t_str), &is_vowel);
}

int main(int argc, const char *argv[])
{
  std::vector<std::string> args(argv, argv+argc);

  std::vector<Vowel_Count> vowel_counts;

  for (auto arg : args) {
    std::transform(std::begin(arg), std::end(arg), std::begin(arg), 
                   [](const char c){ return tolower(c); });

    const auto vowel_count = count_vowels(arg);

    vowel_counts.emplace_back(std::move(arg), vowel_count);
  }

  for (const auto &vc : vowel_counts) {
    std::cout << vc.word << ": " << vc.get_count() << '\n';
  }
}
