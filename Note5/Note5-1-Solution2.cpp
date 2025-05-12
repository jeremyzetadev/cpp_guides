#include <memory>
#include <iostream>
#include <fstream>

void use_loggers(std::ostream &out, std::ostream &err)
{
  std::string s = "hello world";

  out << s;
  err << s;
}


int main()
{
  std::ofstream out("/home/jason/logout");
  std::ofstream err("/home/jason/logerr");

  try {
    use_loggers(out, err);
  } catch (const std::exception &e) {
    std::cout << "Exception: " << e.what() << '\n';
  }
}
