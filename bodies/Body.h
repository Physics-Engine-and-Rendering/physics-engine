#include <Eigen/Eigen>
#include "Shape.h"

class Body {
public:
    Eigen::Vector3f m_position;
    Eigen::Quaternionf m_orientation;
    Shape *m_shape;
};