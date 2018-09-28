#version 130
in vec3 aPos;
in vec3 aColor;
uniform float xOffset;
out vec3 ourPosition;
void main()
{
    gl_Position = vec4(aPos.x + xOffset, -aPos.y, aPos.z, 1.0);
    ourPosition = aPos;
}
