#include <iostream>
#include "math/math.hpp"
#include "physics/scene.hpp"
#include "app/app.hpp"

int main() {
    Scene scene;
    scene.Initialize();

    // for(int i = 0; i < 100; i++) {
    //     for(const auto body : scene.m_bodies) {
    //         std::cout << body.m_position.x << " " << body.m_position.y << " " << body.m_position.z << std::endl;
    //     }
    //     scene.Update(1.0 / 60);
    // }

    // std::cout << "Hello World!" << '\n';
    App app;
    app.run();

    return 0;
}