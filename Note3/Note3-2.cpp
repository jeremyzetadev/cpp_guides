#include <iostream>
#include <vector>
#include <string>
#include <cstring>

struct Vowel_Count {
  Vowel_Count(std::string t_word, const int t_num_vowels) {
    word = std::move(t_word);
    num_vowels = t_num_vowels;
    cache_calls = 0;
  }

  int get_count() const {
    ++const_cast<int&>(cache_calls);
    return num_vowels;
  }

  std::string word;

  private:
    int num_vowels;
    int cache_calls;
};

int count_vowels(const std::string &t_str)
{
  int count = 0;

  std::vector<char> vowels = {'a','e','i','o','u'};

  for (const auto l : t_str) {
    for (const auto v : vowels) {
      if (l == v) {
        // this is a vowel
        ++count;
        break; //break out of current vowel loop
      }
    }
  }

  return count;
}

int main(int argc, const char *argv[])
{
  std::vector<std::string> args;
  for (int i = 0; i < argc; ++i) {
    args.push_back(argv[i]);
  }

  std::vector<Vowel_Count> vowel_counts;

  std::string lcase;
  for (int i = 0; i < static_cast<int>(args.size()); ++i) {
    lcase = "";
    for (std::string::const_iterator itr = args[static_cast<size_t>(i)].begin();
         itr != args[static_cast<size_t>(i)].end();
         ++itr) {
      lcase.push_back((char)tolower(*itr));
    }

    Vowel_Count vc(std::move(lcase), count_vowels(lcase));
    vowel_counts.push_back(vc);
  }

  for (int i = 0; i < static_cast<int>(vowel_counts.size()); ++i) {
    std::cout << vowel_counts[static_cast<size_t>(i)].word << ": " << vowel_counts[static_cast<size_t>(i)].get_count() << '\n';
  }
}

