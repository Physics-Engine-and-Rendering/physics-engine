#include <vector>
#include "Body.h"

class Scene {
public:
    void initialize();
    void update(const float dt_sec);
    std::vector<Body> m_bodies;
};