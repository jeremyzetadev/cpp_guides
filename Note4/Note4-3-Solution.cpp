#include <iostream>
#include <memory>

class Data_Holder
{
  public:
    Data_Holder(std::string t_str)
      : str_ptr(std::make_unique<std::string>(std::move(t_str)))
    {
    }

    Data_Holder(int t_i)
      : int_ptr(std::make_unique<int>(t_i))
    {
    }

    Data_Holder() = default;
    Data_Holder(Data_Holder &&t_other) = default;
    Data_Holder(const Data_Holder &) = delete;
    Data_Holder&operator=(Data_Holder &&t_other) = default;
    Data_Holder&operator=(const Data_Holder &) = delete;


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
    std::unique_ptr<std::string> str_ptr;
    std::unique_ptr<int> int_ptr;
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
