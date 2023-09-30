#include <iostream>
#include "body.hpp"
#include "../math/math.hpp"

struct contact_t {
    Vec3 ptOnA_WorldSpace;
    Vec3 ptOnB_WorldSpace;
    Vec3 ptOnA_LocalSpace;
    Vec3 ptOnB_LocalSpace;

    Vec3 normal;
    float separationDistance;
    float timeOfImpact;

    Body* bodyA;
    Body* bodyB;
};