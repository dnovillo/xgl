#version 450

layout(binding = 0) uniform Uniforms
{
    double d1_1;
    double d1_2;

    dvec3 d3_1;
    dvec3 d3_2;
};

layout(location = 0) out vec4 fragColor;

void main()
{
    double d1_0 = reflect(d1_1, d1_2);

    dvec3 d3_0 = reflect(d3_1, d3_2);

    fragColor = (d3_0.x != d1_1) ? vec4(0.5) : vec4(1.0);
}