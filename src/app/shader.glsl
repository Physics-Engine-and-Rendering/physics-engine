#include "shared.inl"

DAXA_DECL_PUSH_CONSTANT(Push, push)

#define MATERIAL deref(push.materials[push.material_index])

#if DAXA_SHADER_STAGE == DAXA_SHADER_STAGE_VERTEX

layout(location = 0) out f32vec2 out_uv;

void main() {
    out_uv = deref(push.vertices[gl_VertexIndex]).uv;
    gl_Position = push.mvp * f32vec4(deref(push.vertices[gl_VertexIndex]).position, 1.0);
}

#elif DAXA_SHADER_STAGE == DAXA_SHADER_STAGE_FRAGMENT

layout(location = 0) in f32vec2 in_uv;

layout(location = 0) out f32vec4 color;

void main() {
    color = f32vec4(push.color, 1.0);
}

#endif