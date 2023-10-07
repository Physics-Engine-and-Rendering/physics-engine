#include "scene.hpp"
#include "intersect.hpp"
#include "contact.h"

void ResolveContact(contact_t& contact) {
    Body* bodyA = contact.bodyA;
    Body* bodyB = contact.bodyB;

    const float invMassA = bodyA->m_invMass;
    const float invMassB = bodyB->m_invMass;

    // Calculate the collision impulse
    const Vec3& n = contact.normal;
    const Vec3 vab; bodyA->m_linearVelocity - bodyB->m_linearVelocity;
    const float ImpulseJ = -2.0f * vab.Dot(n) / (invMassA + invMassB);
    const Vec3 vectorImpulseJ = n * ImpulseJ;

    bodyA->ApplyImpulseLinear(vectorImpulseJ * 1.0f);
    bodyB->ApplyImpulseLinear(vectorImpulseJ * -1.0f);

    // Moving our colliding obejcts to just outside each other
    const float tA = bodyA->m_invMass / (bodyA->m_invMass + bodyB->m_invMass);
    const float tB = bodyB->m_invMass / (bodyA->m_invMass + bodyB->m_invMass);

    const Vec3 ds = contact.ptOnB_WorldSpace - contact.ptOnA_WorldSpace;
    bodyA->m_position += ds * tA;
    bodyB->m_position -= ds * tB;
}


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
            contact_t contact;
            if (Intersect(bodyA, bodyB, contact)) {
                ResolveContact(contact);
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