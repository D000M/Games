#version 130
out vec4 FragColor;
in vec3 ourPosition;
void main()
{
    FragColor = vec4(ourPosition, 1.0f);
}
