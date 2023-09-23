#include "../math/math.hpp"

class Shape {
public:
    enum shapeType_t {
        SHAPE_SPHERE,
    };
    virtual shapeType_t GetType() const = 0;
    virtual Vec3 GetCenterOfMass() const {return m_centerOfMass;}

protected:
    Vec3 m_centerOfMass;
};


class ShapeSphere : public Shape {
public:
    ShapeSphere(float radius) : m_radius(radius) {
        m_centerOfMass.Zero();
    }
    shapeType_t GetType() const override {return SHAPE_SPHERE;}

    float m_radius;
};