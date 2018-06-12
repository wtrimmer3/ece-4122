#version 410 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;
layout (location = 2) in vec2 aTexture;

out vec3 ourColor;
out vec2 TextureCoordinate;

void main()
{
    gl_Position = vec4(aPos.x - 0.6f, aPos.y + 0.6f, aPos.z, 1.0);
    ourColor = aColor;
    TextureCoordinate = vec2(aTexture.x, aTexture.y);
}