#pragma once

#include <daxa/daxa.hpp>
using namespace daxa::types;

#include <GLFW/glfw3.h>

struct WindowState {
    bool close_requested = {};
    bool resize_requested = {};
    bool focused = true;
    std::array<bool, 5> mouse_button_down_old = {};
    std::array<bool, 5> mouse_button_down = {};
    std::array<bool, 512> key_down = {};
    std::array<bool, 512> key_down_old = {};
    i32 old_cursor_pos_x = {};
    i32 old_cursor_pos_y = {};
    i32 cursor_change_x = {};
    i32 cursor_change_y = {};
};

using Key = i32;
using Button = i32;

struct AppWindow {
    AppWindow(i32 width, i32 height, std::string_view _name);
    ~AppWindow();

    auto create_swapchain(daxa::Device& device) const -> daxa::Swapchain;

    auto update() -> bool;

    [[nodiscard]] auto key_pressed(Key key) const -> bool;
    [[nodiscard]] auto key_just_pressed(Key key) const -> bool;
    [[nodiscard]] auto key_just_released(Key key) const -> bool;

    [[nodiscard]] auto button_pressed(Button button) const -> bool;
    [[nodiscard]] auto button_just_pressed(Button button) const -> bool;
    [[nodiscard]] auto button_just_released(Button button) const -> bool;

    [[nodiscard]] auto scroll_x() const -> f32;
    [[nodiscard]] auto scroll_y() const -> f32;

    [[nodiscard]] auto cursor_x() const -> i32;
    [[nodiscard]] auto get_cursor_x() const -> i32;
    [[nodiscard]] auto get_cursor_y() const -> i32;
    [[nodiscard]] auto get_cursor_change_x() const -> i32;
    [[nodiscard]] auto get_cursor_change_y() const -> i32;
    [[nodiscard]] auto is_cursor_over_window() const -> bool;
    void capture_cursor();
    void release_cursor();
    [[nodiscard]] auto is_cursor_captured() const -> bool;

    [[nodiscard]] auto is_focused() const -> bool;

    void set_width(u32 width) const;
    void set_height(u32 height) const;
    [[nodiscard]] auto get_width() const -> u32;
    [[nodiscard]] auto get_height() const -> u32;

    void set_name(std::string name);
    [[nodiscard]] auto get_name() const -> std::string const &;

    std::unique_ptr<WindowState> window_state = {};
    u32 glfw_window_id = {};
    bool cursor_captured = {};
    std::string name = {};
    GLFWwindow *glfw_handle = {};
    i32 cursor_pos_change_x = {};
    i32 cursor_pos_change_y = {};
};