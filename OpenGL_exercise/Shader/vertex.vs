#version 330 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec3 color;
layout (location = 2) in vec2 texCoord;

out vec3 OurColor;
out vec2 TexCoord;

uniform mat4 modelView;
uniform mat4 projection;

void main()
{
    gl_Position = projection * modelView * vec4(position, 1.0f);
    OurColor = color;
    TexCoord = vec2(texCoord.x, 1.0 - texCoord.y);
}