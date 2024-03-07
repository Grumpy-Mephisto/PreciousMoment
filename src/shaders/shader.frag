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

void main(){
    // Diffuse Lighting
    float lightStrength=max(.2,dot(fragNormal,sunDirection));
    vec3 diffuseColor=lightStrength*texture(material,fragTexCoord).rgb;
    
    // Specular Lighting
    vec3 viewDirection=normalize(viewPosition-fragPos);
    vec3 reflectDirection=reflect(-sunDirection,fragNormal);
    float specularStrength=pow(max(0.,dot(viewDirection,reflectDirection)),32);
    vec3 specularColor=specularStrength*vec3(1.,1.,1.);
    
    // Shadow Calculation
    float shadow=textureProj(shadowMap,fragLightSpacePos+vec4(0.,0.,shadowBias,0.));
    float shadowFactor=shadow>0.?1.:.5;// If shadow is 0, then the fragment is in shadow
    
    // Combine diffuse, specular, and shadow components
    vec3 finalColor=shadowFactor*(diffuseColor+.5*specularColor);
    
    // Output final color
    screenColor=vec4(finalColor,1.);
}
