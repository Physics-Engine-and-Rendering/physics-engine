#include "Shape.hpp"

class Body {
public:
    Body();

    Eigen::Vector3f m_position;
    Eigen::Quaternionf m_orientation;
    Eigen::Vector3f m_linearVelocity;
    float m_invMass;
    Shape *m_shape;

    Eigen::Vector3f GetCenterOfMassWorldSpace() const;
    Eigen::Vector3f GetCenterOfMassModelSpace() const;

    Eigen::Vector3f WorldSpaceToBodySpace(const Eigen::Vector3f &pt) const;
    Eigen::Vector3f BodySpaceToWorldSpace(const Eigen::Vector3f &pt) const;

    void ApplyImpulseLinear(const Eigen::Vector3f &impulse);
};


Eigen::Vector3f Body::GetCenterOfMassWorldSpace() const {
    const Eigen::Vector3f centerOfMass = m_shape->GetCenterOfMass();
    const Eigen::Vector3f pos = m_position + m_orientation.RotatePoint(centerOfMass);
    return pos;
}


Eigen::Vector3f Body::GetCenterOfMassModelSpace() const {
    const Eigen::Vector3f centerOfMass = m_shape->GetCenterOfMass();
    return centerOfMass;
}


Eigen::Vector3f Body::WorldSpaceToBodySpace(const Eigen::Vector3f &worldPt) const {
    Eigen::Vector3f tmp = worldPt - GetCenterOfMassWorldSpace();
    Eigen::Quaternionf inverseOrient = m_orientation.inverse();
    Eigen::Vector3f bodySpace = inverseOrient.RotatePoint(tmp);
    return bodySpace;
}


Eigen::Vector3f Body::BodySpaceToWorldSpace(const Eigen::Vector3f &worldPt) const {
    Eigen::Vector3f worldSpace = GetCenterOfMassWorldSpace() + m_orientation.RotatePoint(worldPt);
    return worldSpace;
}


void Body::ApplyImpulseLinear(const Eigen::Vector3f &impulse) {
    if (0.0f == m_invMass) {
        return;
    }
    m_linearVelocity += impulse * m_invMass;
}