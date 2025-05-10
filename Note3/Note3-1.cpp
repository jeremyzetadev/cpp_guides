#include <vector>
#include <string>
#include <sstream>
#include <iostream>

class Particle {
  public:
    Particle() {
      m_description = "";
      m_id = 0;
      m_x_velocity = 0;
      m_y_velocity = 0;
    }

    Particle(int id, std::string description) {
      m_description = std::move(description);
      m_id = id;

      m_x_velocity = 0;
      m_y_velocity = 0;
    }

    std::string description() const {
      return m_description;
    }

  private:
    int m_id;
    std::string m_description;
    int m_x_velocity;
    int m_y_velocity;

};

int main()
{
  std::string description;
  Particle p;
  std::vector<Particle> particles;

  for (int i = 0; i < 10; ++i) {
    std::stringstream ss;
    ss << "ID: " << i;
    description = ss.str();
    p = Particle(i, description);
    particles.push_back(std::move(p));
  }

  for (const auto &p : particles) {
    std::cout << "Particle: " << p.description() << '\n';
  }
}