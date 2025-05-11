#include <string>
#include <sys/stat.h>
#include <stdexcept>
#include <fcntl.h>
#include <unistd.h>
#include <vector>
#include <iostream>

int read_from_fifo(const std::string &t_fifo_name)
{
  const auto flags = O_RDONLY;
  const auto mode = S_IRUSR | S_IWUSR;

  const auto fid = [&](){
    if (::mkfifo(t_fifo_name.c_str(), mode) != 0) {
      throw std::runtime_error("Unable to mkfifo: " + t_fifo_name);
    }
    const auto fid = ::open(t_fifo_name.c_str(), flags, mode);
    if (fid == -1) {
      throw std::runtime_error("Unable to open fifo: " + t_fifo_name);
    } else {
      return fid;
    }
  }();

  size_t bytes_read = 0;
  while (bytes_read < 1024) {
    std::vector<uint8_t> buff(256, 0);
    const auto bytes = read(fid, &buff.front(), buff.size());
    if (bytes < 0) {
      close(fid); // good thing we remembered to close this
      throw std::runtime_error("Error reading from fifo!");
    }
    bytes_read += bytes;
  }

  close(fid); // and here
  return bytes_read;
}

int main()
{
  try {
    std::cout << "total bytes read: " << read_from_fifo("/home/jason/fifo") << '\n';
  } catch (const std::exception &e) {
    std::cout << "exception while reading from fifo: " << e.what() << '\n';
  }
}
