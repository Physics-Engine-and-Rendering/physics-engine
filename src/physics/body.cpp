#include "body.hpp"

Vec3 Body::GetCenterOfMassWorldSpace() const {
    Vec3 centerOfMass = m_shape->GetCenterOfMass();
    Vec3 pos = m_position + m_orientation.RotatePoint(centerOfMass);
    return pos;
}


Vec3 Body::GetCenterOfMassModelSpace() const {
    const Vec3 centerOfMass = m_shape->GetCenterOfMass();
    return centerOfMass;
}


Vec3 Body::WorldSpaceToBodySpace(const Vec3 &worldPt) const {
    Vec3 tmp = worldPt - GetCenterOfMassWorldSpace();
    Quat inverseOrient = m_orientation.Inverse();
    Vec3 bodySpace = inverseOrient.RotatePoint(tmp);
    return bodySpace;
}


Vec3 Body::BodySpaceToWorldSpace(const Vec3 &worldPt) const {
    Vec3 worldSpace = GetCenterOfMassWorldSpace() + m_orientation.RotatePoint(worldPt);
    return worldSpace;
}


void Body::ApplyImpulseLinear(const Vec3 &impulse) {
    if (0.0f == m_invMass) {
        return;
    }
    m_linearVelocity += impulse * m_invMass;
}