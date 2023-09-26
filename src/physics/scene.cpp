#include "scene.hpp"
#include "intersect.hpp"

void Scene::Update(const float dt_sec) {
    for (int i = 0; i < m_bodies.size(); i++) {
        Body *body = &m_bodies[i];
        float mass = 1.0f / body->m_invMass;
        Vec3 impulseGravity = Vec3(0, -10, 0) * mass * dt_sec;
        body->ApplyImpulseLinear(impulseGravity);
    }

    for (int i = 0; i < m_bodies.size(); i++) {
        for (int j = i + 1; j < m_bodies.size(); j++) {
            Body *bodyA = &m_bodies[i];
            Body *bodyB = &m_bodies[j];
            if (0.0f == bodyA->m_invMass && 0.0f == bodyB->m_invMass) {
                continue;
            }
            if (Intersect(bodyA, bodyB)) {
                bodyA->m_linearVelocity.Zero();
                bodyB->m_linearVelocity.Zero();
            }
        }
    }

    for (int i = 0; i < m_bodies.size(); i++) {
        m_bodies[i].m_position += m_bodies[i].m_linearVelocity * dt_sec;
    }
}


void Scene::Initialize() {
    Body body;
    body.m_position = Vec3(0, 100, 0);
    body.m_orientation = Quat(0, 0, 0, 1);
    body.m_invMass = 1.0f;
    body.m_shape = new ShapeSphere(1.0f);
    body.m_color = Vec3(1.0);
    m_bodies.push_back(body);

    body.m_position = Vec3(0, -1000, 0);
    body.m_orientation = Quat(0, 0, 0, 1);
    body.m_invMass = 0.0f;
    body.m_shape = new ShapeSphere(1000.0f);
    body.m_color = Vec3(1.0, 0.0, 0.0);
    m_bodies.push_back(body);
}