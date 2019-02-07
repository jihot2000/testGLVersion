#version 300 es
layout(location = 0) in vec4 vPosition;
void main()
{
    gl_Position.x = vPosition.x;
    gl_Position.y = vPosition.y;
    gl_Position.z = vPosition.z;
}
