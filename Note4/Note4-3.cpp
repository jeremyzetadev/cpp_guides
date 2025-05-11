#include <iostream>

class Data_Holder
{
  public:
    Data_Holder(std::string t_str)
      : str_ptr(new std::string(std::move(t_str)))
    {
    }

    Data_Holder(int t_i)
      : int_ptr(new int(t_i))
    {
    }

    Data_Holder() = default;

    Data_Holder(Data_Holder &&t_other)
      : str_ptr(t_other.str_ptr), int_ptr(t_other.int_ptr) 
    {
      t_other.str_ptr = nullptr;
      t_other.int_ptr = nullptr;
    }

    Data_Holder(const Data_Holder &) = delete;

    Data_Holder&operator=(Data_Holder &&t_other)
    {
      cleanup();
      std::swap(str_ptr, t_other.str_ptr);
      std::swap(int_ptr, t_other.int_ptr);
      return *this;
    }

    Data_Holder&operator=(const Data_Holder &) = delete;

    ~Data_Holder()
    {
      cleanup();
    }


    void print() {
      if (str_ptr) {
        std::cout << *str_ptr << '\n';
      } else if (int_ptr) {
        std::cout << *int_ptr << '\n';
      } else {
        std::cout << "empty\n";
      }
    }

  private:
    void cleanup()
    {
      if (str_ptr) {
        delete str_ptr;
        str_ptr = nullptr;
      }

      if (int_ptr) {
        delete int_ptr;
        int_ptr = nullptr;
      }
    }

    std::string *str_ptr = nullptr;
    int *int_ptr = nullptr;
};

int main()
{
  Data_Holder dh(1);
  Data_Holder dh2("string");
  Data_Holder dh3;

  dh.print();
  dh2.print();
  dh3.print();
}