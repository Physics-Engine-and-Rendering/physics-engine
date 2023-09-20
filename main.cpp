#include "Math/math.hpp"
#include <iostream>

using namespace Math;

int main() {
    std::cout << "Hello, Physics Engine!" << std::endl;
    f32vec2 vec1 = {1, 2};
    f32vec2 vec2 = {3, 4};
    f32vec2 add = vec1 + vec2;
    f32vec2 sub = vec1 - vec2;
    f32vec2 mul = vec1 * vec2;
    f32vec2 div = vec1 / vec2;
    f32 result = dot(vec1, vec2);

    std::cout << add.x << " " << add.y << '\n';
    std::cout << sub.x << " " << sub.y << '\n';
    std::cout << mul.x << " " << mul.y << '\n';
    std::cout << div.x << " " << div.y << '\n';
    std::cout <<

    return 0;
}
