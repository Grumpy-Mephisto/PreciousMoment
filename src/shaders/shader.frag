#version 330 core

in vec2 fragTexCoord;
in vec3 fragNormal;
in vec3 fragPos;
in vec4 fragLightSpacePos;

out vec4 screenColor;

uniform sampler2D material;
uniform sampler2DShadow shadowMap;

const vec3 sunDirection=normalize(vec3(-1.,1.,1.));
const vec3 viewPosition=vec3(0.,0.,0.);
const float shadowBias=.005;
const float ambientStrength=.1;

void main(){
    // Ambient + Diffuse Lighting
    float lightStrength=max(ambientStrength,dot(fragNormal,sunDirection));
    vec3 diffuseColor=lightStrength*texture(material,fragTexCoord).rgb;
    
    // Specular Lighting
    vec3 viewDirection=normalize(viewPosition-fragPos);
    vec3 reflectDirection=reflect(-sunDirection,fragNormal);
    float specularStrength=pow(max(0.,dot(viewDirection,reflectDirection)),32);
    vec3 specularColor=specularStrength*vec3(1.,1.,1.);
    
    // Shadow Calculation
    float shadow=textureProj(shadowMap,fragLightSpacePos+vec4(0.,0.,shadowBias,0.));
    float shadowFactor=mix(.5,1.,step(0.,shadow));// Smoothly interpolate based on shadow value
    
    // Combine diffuse, specular, and shadow components (with shadow factor)
    vec3 finalColor=shadowFactor*(diffuseColor+.5*specularColor);
    
    // Output final color
    screenColor=vec4(finalColor,1.);
}
