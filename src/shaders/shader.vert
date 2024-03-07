#version 330 core

layout(location=0)in vec3 vertexPos;
layout(location=1)in vec2 vertexTexCoord;
layout(location=2)in vec3 vertexNormal;

out vec2 fragTexCoord;
out vec3 fragNormal;
out vec3 fragPos;
out vec4 fragLightSpacePos;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
uniform mat4 lightSpaceMatrix;

void main(){
    // Transform vertex position to clip space
    gl_Position=projection*view*model*vec4(vertexPos,1.);
    
    // Transform vertex position to light space for shadow mapping
    fragLightSpacePos=lightSpaceMatrix*vec4(vertexPos,1.);
    
    // Pass other vertex data to the fragment shader
    fragTexCoord=vertexTexCoord;
    fragNormal=normalize((model*vec4(vertexNormal,0.)).xyz);
    fragPos=(model*vec4(vertexPos,1.)).xyz;
}
