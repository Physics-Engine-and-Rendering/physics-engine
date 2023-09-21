#include <iostream>
#include "Math/math.hpp"

using namespace Math;

int main() {
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
    std::cout << result << '\n';

    auto a = cross(f32vec3{1, 2, 2}, f32vec3{2, 1, 1});
    //auto a = cross(f32vec2{1, 2}, f32vec2{2, 1});

    return 0;
}
