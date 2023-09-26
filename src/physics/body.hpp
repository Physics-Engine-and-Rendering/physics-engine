#pragma once

#include "shape.hpp"

class Body {
public:
    Body() :
        m_position( 0.0f ),
        m_orientation( 0.0f, 0.0f, 0.0f, 1.0f ),
        m_shape( NULL ) {
            m_linearVelocity.Zero();
    }

    Vec3 m_position;
    Quat m_orientation;
    Vec3 m_linearVelocity;
    float m_invMass;
    Shape *m_shape;
    Vec3 m_color;

    Vec3 GetCenterOfMassWorldSpace() const;
    Vec3 GetCenterOfMassModelSpace() const;

    Vec3 WorldSpaceToBodySpace(const Vec3 &pt) const;
    Vec3 BodySpaceToWorldSpace(const Vec3 &pt) const;

    void ApplyImpulseLinear(const Vec3 &impulse);
};