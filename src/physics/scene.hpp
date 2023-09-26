#pragma once

#include "body.hpp"
#include <vector>

class Scene {
public:
    void Initialize();
    void Update(const float dt_sec);
    std::vector<Body> m_bodies;
};