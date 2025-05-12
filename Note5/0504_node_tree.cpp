#include <memory>
#include <vector>

struct Node : std::enable_shared_from_this<Node> {
  std::shared_ptr<Node> parent;
  std::vector<std::shared_ptr<Node>> children;
  void addChild(const std::shared_ptr<Node> &c) {
    children.push_back(c);
    c->parent = this->shared_from_this();
  }
};

int main() {
  auto node = std::make_shared<Node>();
  node->addChild(std::make_shared<Node>());
}

