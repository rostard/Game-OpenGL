#version 330 core

layout (location = 0) in vec4 vertex;

uniform mat4 model;
uniform mat4 projection;
out vec2 TexCoords;

void main() {
    TexCoords = vertex.zw;
    gl_Position = projection * model * vec4(vertex.xy, 1.0, 1.0);
}
