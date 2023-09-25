#include "intersect.hpp"

bool Intersect(const Body *bodyA, const Body *bodyB) {
    const Vec3 ab = bodyB->m_position - bodyA->m_position;

    const ShapeSphere *sphereA = (const ShapeSphere *)bodyA->m_shape;
    const ShapeSphere *sphereB = (const ShapeSphere *)bodyB->m_shape;

    const float radiusAB = sphereA->m_radius + sphereB->m_radius;
    const float lengthSquare = ab.GetLengthSqr();
    if (lengthSquare <= (radiusAB * radiusAB)) {
        return true;
    }
    return false;
}