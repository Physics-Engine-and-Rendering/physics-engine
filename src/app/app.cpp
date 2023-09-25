#include "app.hpp"
#include "../physics/scene.hpp"

App::App() : window{800, 600, "physics-engine"},
             instance{daxa::create_instance({})},
             device{instance.create_device(daxa::DeviceInfo{
                 .enable_buffer_device_address_capture_replay = true,
                 .name = "my device"})},
             swapchain{window.create_swapchain(this->device)},
             pipeline_manager{daxa::PipelineManagerInfo{
                 .device = device,
                 .shader_compile_options = {
                     .root_paths = {
                         DAXA_SHADER_INCLUDE_DIR,
                         "./",
                     },
                     .language = daxa::ShaderLanguage::GLSL,
                     .enable_debug_info = true,
                 },
                 .name = "pipeline_manager",
             }} {
    last_time_point = std::chrono::steady_clock::now();
    controlled_camera.camera.resize(static_cast<i32>(window.get_width()), static_cast<i32>(window.get_height()));
    sphere = std::make_unique<Model>(device, "src/app/assets/sphere.gltf");

    pipeline = pipeline_manager.add_raster_pipeline(daxa::RasterPipelineCompileInfo {
            .vertex_shader_info = daxa::ShaderCompileInfo {
                .source = daxa::ShaderSource { daxa::ShaderFile { .path = "src/app/shader.glsl" }, },
            },
            .fragment_shader_info = daxa::ShaderCompileInfo {
                .source = daxa::ShaderSource { daxa::ShaderFile { .path = "src/app/shader.glsl" }, },
            },
            .color_attachments = {{ .format = swapchain.get_format() }},
            .depth_test = {
                .depth_attachment_format = daxa::Format::D32_SFLOAT,
                .enable_depth_test = true,
                .enable_depth_write = true,
            },
            .raster = {
                .face_culling = daxa::FaceCullFlagBits::FRONT_BIT
            },
            .push_constant_size = sizeof(Push),
        }).value();
}

App::~App() {
}

auto App::run() -> i32 {

    Scene scene;
    scene.Initialize();

    while (!window.window_state->close_requested) {
        auto new_time_point = std::chrono::steady_clock::now();
        this->delta_time = std::chrono::duration_cast<std::chrono::duration<float, std::chrono::milliseconds::period>>(new_time_point - this->last_time_point).count() * 0.001f;
        this->last_time_point = new_time_point;
        window.update();

        if (window.window_state->resize_requested) {
            controlled_camera.camera.resize(static_cast<i32>(window.get_width()), static_cast<i32>(window.get_height()));
            window.window_state->resize_requested = false;
        }

        update();
        scene.Update(delta_time);

        daxa::CommandList cmd_list = device.create_command_list({.name = "my command list"});
        daxa::ImageId swapchain_image = swapchain.acquire_next_image();
        if (swapchain_image.is_empty()) {
            continue;
        }
        daxa::ImageMipArraySlice swapchain_image_full_slice = device.info_image_view(swapchain_image.default_view()).slice;

        cmd_list.pipeline_barrier_image_transition({
            .src_access = daxa::AccessConsts::TRANSFER_WRITE,
            .src_layout = daxa::ImageLayout::UNDEFINED,
            .dst_layout = daxa::ImageLayout::TRANSFER_DST_OPTIMAL,
            .image_slice = swapchain_image_full_slice,
            .image_id = swapchain_image,
        });

        cmd_list.begin_renderpass( daxa::RenderPassBeginInfo {
            .color_attachments = { daxa::RenderAttachmentInfo {
                .image_view = swapchain_image.default_view(),
                .load_op = daxa::AttachmentLoadOp::CLEAR,
                .clear_value = std::array<f32, 4>{0.2f, 0.4f, 1.0f, 1.0f},
            }},
            // .depth_attachment = {{
            //     .image_view = uses.depth_target.view(),
            //     .load_op = daxa::AttachmentLoadOp::CLEAR,
            //     .clear_value = daxa::DepthValue{1.0f, 0},
            // }},
            .render_area = {.x = 0, .y = 0, .width = window.get_width(), .height = window.get_height()},
        });
        cmd_list.set_pipeline(*pipeline);

        for(auto& body : scene.m_bodies) {
            ShapeSphere* shape = reinterpret_cast<ShapeSphere*>(&body.m_shape);
            glm::mat4 model_mat = glm::translate(glm::mat4{1.0f}, *reinterpret_cast<glm::vec3*>(&body.m_position)) * glm::scale(glm::mat4{1.0f}, glm::vec3{shape->m_radius});

            glm::mat4 mvp = controlled_camera.camera.get_vp() * model_mat;

            for(auto& primitive : sphere->primitives) {
                cmd_list.push_constant(Push {
                    .mvp = *reinterpret_cast<f32mat4x4*>(&mvp),
                    .vertices = device.get_device_address(sphere->vertex_buffer),
                });

                if(primitive.index_count > 0) {
                    cmd_list.set_index_buffer(sphere->index_buffer, 0);
                    cmd_list.draw_indexed({
                        .index_count = primitive.index_count,
                        .instance_count = 1,
                        .first_index = primitive.first_index,
                        .vertex_offset = static_cast<i32>(primitive.first_vertex),
                        .first_instance = 0,
                    });
                } else {
                    cmd_list.draw({
                        .vertex_count = primitive.vertex_count,
                        .instance_count = 1,
                        .first_vertex = primitive.first_vertex,
                        .first_instance = 0
                    });
                }
            }
        }


        cmd_list.end_renderpass();

        cmd_list.pipeline_barrier_image_transition({
            .dst_access = daxa::AccessConsts::TRANSFER_WRITE,
            .src_layout = daxa::ImageLayout::TRANSFER_DST_OPTIMAL,
            .dst_layout = daxa::ImageLayout::PRESENT_SRC,
            .image_slice = swapchain_image_full_slice,
            .image_id = swapchain_image,
        });

        cmd_list.complete();

        const auto &acquire_semaphore = swapchain.get_acquire_semaphore();
        const auto &present_semaphore = swapchain.get_present_semaphore();
        const auto &gpu_timeline = swapchain.get_gpu_timeline_semaphore();
        const auto cpu_timeline = swapchain.get_cpu_timeline_value();

        device.submit_commands({
            .command_lists = {cmd_list},
            .wait_binary_semaphores = {acquire_semaphore},
            .signal_binary_semaphores = {present_semaphore},
            .signal_timeline_semaphores = {{gpu_timeline, cpu_timeline}},
        });
        device.present_frame({
            .wait_binary_semaphores = {present_semaphore},
            .swapchain = swapchain,
        });
    }

    return 0;
}

void App::update() {
    controlled_camera.update(window, delta_time);

    std::cout << "camera position: " << controlled_camera.position.x << " " << controlled_camera.position.y << " " << controlled_camera.position.z << std::endl;

    // glm::mat4 inverse_projection_matrix = glm::inverse(controlled_camera.camera.proj_mat);
    // glm::mat4 inverse_view_matrix = glm::inverse(controlled_camera.camera.view_mat);

    // this->context.shader_global_block.globals.camera_projection_matrix = *reinterpret_cast<f32mat4x4*>(&controlled_camera.camera.proj_mat);
    // this->context.shader_global_block.globals.camera_inverse_projection_matrix = *reinterpret_cast<f32mat4x4*>(&inverse_projection_matrix);
    // this->context.shader_global_block.globals.camera_view_matrix = *reinterpret_cast<f32mat4x4*>(&controlled_camera.camera.view_mat);
    // this->context.shader_global_block.globals.camera_inverse_view_matrix = *reinterpret_cast<f32mat4x4*>(&inverse_view_matrix);
    // this->context.shader_global_block.globals.resolution = { static_cast<i32>(window.get_width()), static_cast<i32>(window.get_height()) };
}