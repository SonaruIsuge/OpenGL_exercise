#version 330 core

in vec4 vPosition;
in vec4 vColor;

out vec4 Color;

uniform mat4 ModelView;
uniform mat4 Projection;

void main()
{
    gl_Position = Projection * ModelView * vPosition;
    Color = vColor;
}