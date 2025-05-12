#include <memory>
#include <map>
#include <vector>


class Factory;

class Object {
  public:
    Object(int t_id, std::shared_ptr<Factory> t_factory) 
      : id(t_id), m_factory(std::move(t_factory)) {}
    void add_child();
    std::vector<std::shared_ptr<Object>> children;
    int id;

  private:
    int m_sub_id = 0;
    std::shared_ptr<Factory> m_factory;
};

class Factory : public std::enable_shared_from_this<Factory>
{
  public:
    std::shared_ptr<Object> make_object(int t_id) {
      const auto itr = m_cache.find(t_id);
      if (itr != m_cache.end()) {
        return itr->second;
      } else {
        return m_cache.insert(std::make_pair(t_id, std::make_shared<Object>(t_id, shared_from_this()))).first->second;
      }
    }

  private:
    std::map<int, std::shared_ptr<Object>> m_cache;
};

void Object::add_child(){
  children.emplace_back(m_factory->make_object(id * 10 + (++m_sub_id)));
}

int main()
{
  auto factory = std::make_shared<Factory>();

  auto obj = factory->make_object(1);
  obj->add_child();
}