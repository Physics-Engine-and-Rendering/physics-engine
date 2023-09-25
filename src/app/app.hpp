#pragma once
#include <daxa/daxa.hpp>
#include <daxa/utils/pipeline_manager.hpp>
using namespace daxa::types;

#include "window.hpp"
#include "camera.hpp"
#include "model.hpp"

struct App {
    App();
    ~App();

    auto run() -> i32;
    void update();

    AppWindow window;
    daxa::Instance instance = {};
    daxa::Device device = {};
    daxa::Swapchain swapchain = {};
    daxa::PipelineManager pipeline_manager = {};

    ControlledCamera3D controlled_camera = {};

    std::shared_ptr<daxa::RasterPipeline> pipeline = {};

    std::unique_ptr<Model> sphere = {};

    daxa::ImageId depth_image = {};

    f32 delta_time = 0.016f;
    std::chrono::time_point<std::chrono::steady_clock> last_time_point = {};
};