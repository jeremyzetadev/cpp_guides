#include <memory>
#include <iostream>

void use_loggers(const std::shared_ptr<FILE> &out, const std::shared_ptr<FILE> &err)
{
  std::string s = "hello world";

  fwrite(s.c_str(), 1, s.size(), out.get());
  fwrite(s.c_str(), 1, s.size(), err.get());
}


int main()
{
  const auto FILE_maker = [](const std::string &t_fname){
    FILE *f = fopen(t_fname.c_str(), "a");
    if (f == nullptr) {
      throw std::runtime_error("Unable to open file for appending: " + t_fname);
    } else {
      return f;
    }
  };

  const auto FILE_deleter = [](FILE *f) {
    fclose(f);
  };

  try {
    auto out = std::shared_ptr<FILE>(FILE_maker("/home/jason/logout"), FILE_deleter);
    auto err = std::shared_ptr<FILE>(FILE_maker("/home/jason/logerr"), FILE_deleter);
    use_loggers(out, err);
  } catch (const std::exception &e) {
    std::cout << "Exception: " << e.what() << '\n';
  }
}