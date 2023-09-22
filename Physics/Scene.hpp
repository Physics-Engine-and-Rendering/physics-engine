#include <Eigen/Eigen>
#include "Body.hpp"

class Scene {
public:
    void Initialize();
    void Update(const float dt_sec);
    std::vector<Body> m_bodies;
};


void Scene::Update(const float dt_sec) {
    for (int i = 0; i < m_bodies.size(); i++) {
        Body *body = &m_bodies[i];
        float mass = 1.0f / body->m_invMass;
        Eigen::Vector3f impulseGravity = Eigen::Vector3f(0, 0, -10) * mass * dt_sec;
        body->ApplyImpulseLinear(impulseGravity);
    }

    for (int i = 0; i < m_bodies.size(); i++) {
        m_bodies[i].m_position += m_bodies[i].m_linearVelocity * dt_sec;
    }
}

void Scene::Initialize() {
    Body body;
    body.m_position = Eigen::Vector3f(0, 0, 10);
    body.m_orientation = Eigen::Quaternionf(0, 0, 0, 1);
    body.m_invMass = 1.0f;
    body.m_shape = new ShapeSphere(1.0f);
    m_bodies.push_back(body);

    body.m_position = Eigen::Vector3f(0, 0, -1000);
    body.m_orientation = Eigen::Quaternionf(0, 0, 0, 1);
    body.m_invMass = 0.0f;
    body.m_shape = new ShapeSphere(1000.0f);
    m_bodies.push_back(body);
}