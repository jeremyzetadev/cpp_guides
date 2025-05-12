#include <memory>
#include <vector>

struct Node : std::enable_shared_from_this<Node> {
  std::vector<std::shared_ptr<Node>> children;
  void addChild(const std::shared_ptr<Node> &c) {
    children.push_back(c);
    c->m_parent = this->shared_from_this();
  }

  std::shared_ptr<Node> parent()
  {
    auto p = m_parent.lock();

    if (p) {
      return p;
    } else {
      m_parent.reset();
//      throw std::runtime_error("no parent");
    }
  }

  private:
    std::weak_ptr<Node> m_parent;
};

int main() {
  auto node = std::make_shared<Node>();
  node->addChild(std::make_shared<Node>());
}
