#include <vector>
#include <string>
#include <iostream>

class Particle {
  public:
    Particle(int id, std::string description)
      : m_id(id),
        m_description(std::move(description))
    {
    }

    std::string description() const {
      return m_description;
    }

  private:
    int m_id = 0;
    std::string m_description;
    int m_x_velocity = 0;
    int m_y_velocity = 0;

};

int main()
{
  std::vector<Particle> particles;

  for (int i = 0; i < 10; ++i) {
    particles.emplace_back(i, "ID: " + std::to_string(i));
  }

  for (const auto &p : particles) {
    std::cout << "Particle: " << p.description() << '\n';
  }
}