#include <memory>
#include <vector>
#include <iostream>

enum Types {
  Double,
  Int
};

struct Value_Holder
{
  Value_Holder(int t_i)
    : m_int(std::make_shared<int>(t_i))
  {
  }

  Value_Holder(double t_d)
    : m_double(std::make_shared<double>(t_d))
  {
  }

  Types type() const {
    if (m_int) {
      return Int;
    } else {
      return Double;
    }
  }

  double as_double() const {
    if (m_double) {
      return *m_double;
    } else {
      return *m_int;
    }
  }

  int as_int() const {
    if (m_int) {
      return *m_int;
    } else {
      return *m_double;
    }
  }

  void print() const {
    if (m_int) {
      std::cout << *m_int;
    } else {
      std::cout << *m_double;
    }
  }

  std::shared_ptr<int> m_int;
  std::shared_ptr<double> m_double;
};

struct Operation {
  virtual ~Operation() {}
  virtual Value_Holder do_call(const std::vector<Value_Holder> &t_values) = 0;
  virtual std::vector<Types> get_types() = 0;
};

struct Operation_Double_Sum : Operation {
  virtual ~Operation_Double_Sum() {}
  Value_Holder do_call(const std::vector<Value_Holder> &t_values) {
    std::cout << "double sum called\n";
    return t_values[0].as_double() + t_values[1].as_double();
  }
  virtual std::vector<Types> get_types() {
    return { Double, Double };
  }
};

struct Operation_Int_Sum : Operation {
  virtual ~Operation_Int_Sum() {}
  Value_Holder do_call(const std::vector<Value_Holder> &t_values) {
    std::cout << "int sum called\n";
    return t_values[0].as_int() + t_values[1].as_int();
  }
  virtual std::vector<Types> get_types() {
    return { Int, Int };
  }
};

struct Operation_Int_3_Sum : Operation {
  virtual ~Operation_Int_3_Sum() {}
  Value_Holder do_call(const std::vector<Value_Holder> &t_values) {
    std::cout << "int 3 sum called\n";
    return t_values[0].as_int() + t_values[1].as_int() + t_values[2].as_int();
  }
  virtual std::vector<Types> get_types() {
    return { Int, Int, Int };
  }
};

struct Op_Caller {
  std::vector<std::shared_ptr<Operation>> operations;

  void add_operation(std::shared_ptr<Operation> t_op) {
    operations.push_back(t_op);
  }

  Value_Holder do_call(const std::vector<Value_Holder> &t_values) {
    std::vector<Types> types;

    for (std::vector<Value_Holder>::const_iterator itr = t_values.begin();
         itr != t_values.end();
         ++ itr) {
      types.push_back(itr->type());
    }

    // we want to execute the function that matches with the fewest number
    // of differences possible in the order it was registered by
    // the user

    // loop over possible number of differences 
    for (int i = 0; i < static_cast<int>(types.size() + 1); ++i) {
      // loop over possible operations
      for (std::vector<std::shared_ptr<Operation>>::const_iterator itr = operations.begin();
           itr != operations.end();
           ++itr)
      {
        if (types.size() == (*itr)->get_types().size()) {
          // don't try unless we have a param size match
          int num_diffs = 0;
          for (int j = 0; j < static_cast<int>((*itr)->get_types().size()); ++j) {
            if ((*itr)->get_types()[j] != types[j]) {
              ++num_diffs;
            }
          }

          if (i == num_diffs) {
            // this loop matches the num difference iteration we are on
            // and we've already verified the number of parameters
            return (*itr)->do_call(t_values);
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
  oc.add_operation(std::shared_ptr<Operation>(new Operation_Double_Sum()));
  oc.add_operation(std::shared_ptr<Operation>(new Operation_Int_Sum()));
  oc.add_operation(std::shared_ptr<Operation>(new Operation_Int_3_Sum()));

  std::cout << oc.do_call({3,4,5}).as_int() << '\n';
  std::cout << oc.do_call({3.4, 4}).as_double() << '\n';
  std::cout << oc.do_call({3, 4}).as_int() << '\n';
  std::cout << oc.do_call({3, 4.9}).as_double() << '\n';
  std::cout << oc.do_call({3.4, 4.9}).as_double() << '\n';
}
