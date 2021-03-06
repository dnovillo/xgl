#version 450

layout(binding = 0) uniform Uniforms
{
    ivec3 i3;
};

layout(location = 0) out vec4 fragColor;

void main()
{
    uvec3 u3 = i3;

    fragColor = (u3.x != u3.y) ? vec4(0.0) : vec4(1.0);
}