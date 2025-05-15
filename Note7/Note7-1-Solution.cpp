// NOTES:
// This version compiles to 45% smaller size the the original
//                   run in 1/2 the time of the original
#include <memory>
#include <vector>
#include <iostream>
#include <algorithm>

enum class Types {
  Double,
  Int
};

struct Value_Holder
{
  Value_Holder(int t_i)
    : m_int(t_i),
      m_type(Types::Int)

  {
  }

  Value_Holder(double t_d)
    : m_double(t_d),
      m_type(Types::Double)
  {
  }

  Types type() const {
    return m_type;
  }

  double as_double() const {
    if (m_type == Types::Double) {
      return m_double;
    } else {
      return m_int;
    }
  }

  int as_int() const {
    if (m_type == Types::Int) {
      return m_int;
    } else {
      return m_double;
    }
  }

  void print() const {
    if (m_type == Types::Int) {
      std::cout << m_int;
    } else {
      std::cout << m_double;
    }
  }

  int m_int = 0;
  double m_double = 0;
  Types m_type;

};

struct Operation {
  virtual ~Operation() = default;
  Operation(const Operation &) = default;
  Operation(Operation &&) = default;
  Operation&operator=(const Operation &) = default;
  Operation&operator=(Operation &&) = default;

  Operation(std::vector<Types> t_types)
    : m_types(t_types)
  {
  }

  virtual Value_Holder do_call(const std::vector<Value_Holder> &t_values) = 0;

  const std::vector<Types> &get_types() {
    return m_types;
  }

  private:
    std::vector<Types> m_types;
};

struct Operation_Double_Sum : Operation {
  Operation_Double_Sum()
    : Operation({Types::Double, Types::Double})
  {
  }

  Value_Holder do_call(const std::vector<Value_Holder> &t_values) {
    std::cout << "double sum called\n";
    return t_values[0].as_double() + t_values[1].as_double();
  }
};

struct Operation_Int_Sum : Operation {
  Operation_Int_Sum()
    : Operation({Types::Int, Types::Int})
  {
  }

  Value_Holder do_call(const std::vector<Value_Holder> &t_values) {
    std::cout << "int sum called\n";
    return t_values[0].as_int() + t_values[1].as_int();
  }
};

struct Operation_Int_3_Sum : Operation {
  Operation_Int_3_Sum()
    : Operation({Types::Int, Types::Int, Types::Int})
  {
  }

  Value_Holder do_call(const std::vector<Value_Holder> &t_values) {
    std::cout << "int 3 sum called\n";
    return t_values[0].as_int() + t_values[1].as_int() + t_values[2].as_int();
  }
};

struct Op_Caller {
  std::vector<std::unique_ptr<Operation>> operations;

  void add_operation(std::unique_ptr<Operation> t_op) {
    operations.emplace_back(std::move(t_op));
  }

  Value_Holder do_call(const std::vector<Value_Holder> &t_values) {
    // we want to execute the function that matches with the fewest number
    // of differences possible in the order it was registered by
    // the user

    // loop over possible number of differences
    for (size_t i = 0; i < t_values.size() + 1; ++i)
    {
      for (const auto &oper : operations)
      {
        if (t_values.size() == oper->get_types().size()) {
          const auto num_diffs =
            std::inner_product(
                std::begin(oper->get_types()), std::end(oper->get_types()),
                std::begin(t_values), 0,
                std::plus<>(),
                [](const Types &type, const Value_Holder &value) {
                  return type == value.type()?0:1;
                }
              );

          if (i == num_diffs) {
            // this loop matches the num difference iteration we are on
            // and we've already verified the number of parameters
            return oper->do_call(t_values);
          }
        }

      }
    }

    throw std::runtime_error("No matching function call");
  }
};


int main()
{

  Op_Caller oc;
  oc.add_operation(std::make_unique<Operation_Double_Sum>());
  oc.add_operation(std::make_unique<Operation_Int_Sum>());
  oc.add_operation(std::make_unique<Operation_Int_3_Sum>());

  std::cout << oc.do_call({3,4,5}).as_int() << '\n';
  std::cout << oc.do_call({3.4, 4}).as_double() << '\n';
  std::cout << oc.do_call({3, 4}).as_int() << '\n';
  std::cout << oc.do_call({3, 4.9}).as_double() << '\n';
  std::cout << oc.do_call({3.4, 4.9}).as_double() << '\n';
}