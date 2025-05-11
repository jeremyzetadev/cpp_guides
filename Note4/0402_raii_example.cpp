#include <string>
#include <sys/stat.h>
#include <stdexcept>
#include <fcntl.h>
#include <unistd.h>
#include <vector>
#include <iostream>

class Fifo
{
  static int openfifo(const std::string &t_fname, int flags, mode_t t_mode) {
    if (::mkfifo(t_fname.c_str(), t_mode) != 0) {
      throw std::runtime_error("Unable to mkfifo: " + t_fname);
    }
    const auto fid = ::open(t_fname.c_str(), flags, t_mode);
    if (fid == -1) {
      throw std::runtime_error("Unable to open fifo: " + t_fname);
    } else {
      return fid;
    }
  }

  public:
  Fifo(const std::string &t_fname, int t_flags, mode_t t_mode)
    : m_fileid(openfifo(t_fname, t_flags, t_mode)) {
      // fileid successfully initialized
    }

  ~Fifo() {
    ::close(m_fileid);
  }

  int fileid() const {
    return m_fileid;
  }

  private:
  int m_fileid;
};

int read_from_fifo(const std::string &t_fifo_name)
{
  Fifo f(t_fifo_name, O_RDONLY, S_IRUSR | S_IWUSR);

  size_t bytes_read = 0;

  while (bytes_read < 1024) {
    std::vector<uint8_t> buff(256, 0);
    const auto bytes = read(f.fileid(), &buff.front(), buff.size());
    if (bytes < 0) {
      throw std::runtime_error("Error reading from fifo!");
    }
    bytes_read += bytes;
  }

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

