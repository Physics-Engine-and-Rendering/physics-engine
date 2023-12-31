#include "camera.hpp"
#include <numbers>
#include <glm/gtx/rotate_vector.hpp>
#include <iostream>

void Camera3D::resize(i32 size_x, i32 size_y) {
    aspect = static_cast<f32>(size_x) / static_cast<f32>(size_y);
    proj_mat = glm::perspective(glm::radians(fov), aspect, near_clip, far_clip);
    proj_mat[1][1] *= -1.0f;
}

auto Camera3D::get_vp() -> glm::mat4 {
    return proj_mat * view_mat;
}

auto Camera3D::get_view() -> glm::mat4 {
    return view_mat;
}

void ControlledCamera3D::update(AppWindow& window, f32 dt) {
    if (window.is_focused()) {
        if (window.key_just_pressed(GLFW_KEY_ESCAPE)) {
            if (window.is_cursor_captured()) {
                window.release_cursor();
            }
            else {
                window.capture_cursor();
            }
        }
    } else if (window.is_cursor_captured()) {
        window.release_cursor();
    }

    if(window.is_cursor_captured()) {
        rotation.x += static_cast<f32>(window.get_cursor_change_x()) * mouse_sens * 0.0001f * camera.fov;
        rotation.y += static_cast<f32>(window.get_cursor_change_y()) * mouse_sens * 0.0001f * camera.fov;
    }

    constexpr auto MAX_ROT = 1.56825555556f;
    if (rotation.y > MAX_ROT) { rotation.y = MAX_ROT; }
    if (rotation.y < -MAX_ROT) { rotation.y = -MAX_ROT; }

    glm::vec3 forward_direction = glm::normalize(glm::vec3{ cos(rotation.x) * cos(rotation.y), -sin(rotation.y), sin(rotation.x) * cos(rotation.y) });
    glm::vec3 up_direction = glm::vec3{ 0.0f, 1.0f, 0.0f };
    glm::vec3 right_direction = glm::normalize(glm::cross(forward_direction, up_direction));

    glm::vec3 move_direction = glm::vec3{ 0.0f };
    if (window.key_pressed(keybinds.move_pz)) { move_direction += forward_direction; }
    if (window.key_pressed(keybinds.move_nz)) { move_direction -= forward_direction; }
    if (window.key_pressed(keybinds.move_nx)) { move_direction += right_direction; }
    if (window.key_pressed(keybinds.move_px)) { move_direction -= right_direction; }
    if (window.key_pressed(keybinds.move_py)) { move_direction += up_direction; }
    if (window.key_pressed(keybinds.move_ny)) { move_direction -= up_direction; }

    position += move_direction * dt * (window.key_pressed(keybinds.toggle_sprint) ? sprint_speed : 2.0f) * 7.5f;
    camera.view_mat = glm::lookAt(position, position + forward_direction, glm::vec3{0.0f, 1.0f, 0.0f});
}