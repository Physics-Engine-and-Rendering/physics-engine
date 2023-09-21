class Shape {
public:
    enum shapeType_t {
        SHAPE_SPHERE,
    };

    virtual shapeType_t GetType() const = 0;
};

class ShapeSphere : public Shape {
public:
    ShapeSphere(float radius) : m_radius(radius) {}
    shapeType_t GetType() const override { return SHAPE_SPHERE; }

    float m_radius;
};