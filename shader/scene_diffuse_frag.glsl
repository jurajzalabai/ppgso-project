#version 330
layout (location = 0) out vec4 FragmentColor;
layout (location = 1) out vec4 BrightColor;
// A texture is expected as program attribute
uniform sampler2D Texture;
uniform sampler2D shadowMap;

// (optional) Transparency
uniform float Transparency;

// (optional) Texture offset
uniform vec2 TextureOffset;
uniform float diffuse_strength;
uniform float specular_strength;
uniform float ambient_strength;
uniform vec3 viewPos;
uniform vec3 lightPos;

// The vertex shader will feed this input
in vec2 texCoord;
in vec3 fragPos;

in vec4 FragPosLightSpace;
// Wordspace normal passed from vertex shader
in vec4 normal;

// The final color

struct PointLight {
    vec3 position;

    float constant;
    float linear;
    float quadratic;

    vec3  direction;
    float cutOff;
    float outerCutOff;

    vec3 color;
};
#define NR_POINT_LIGHTS 4
uniform PointLight pointLights[NR_POINT_LIGHTS];

float ShadowCalculation(vec4 fragPosLightSpace)
{
    // perform perspective divide
    vec3 projCoords = fragPosLightSpace.xyz / fragPosLightSpace.w;
    // transform to [0,1] range
    projCoords = projCoords * 0.5 + 0.5;
    // get closest depth value from light's perspective (using [0,1] range fragPosLight as coords)
    float closestDepth = texture(shadowMap, projCoords.xy).r;
    // get depth of current fragment from light's perspective
    float currentDepth = projCoords.z;
    // calculate bias (based on depth map resolution and slope)
    vec3 normal_diff = normalize(normal.xyz);
    vec3 lightDir = normalize(lightPos - fragPos);
    float bias = max(0.05 * (1.0 - dot(normal_diff, lightDir)), 0.005);
    // check whether current frag pos is in shadow
    // float shadow = currentDepth - bias > closestDepth  ? 1.0 : 0.0;
    // PCF
    float shadow = 0.0;
    vec2 texelSize = 1.0 / textureSize(shadowMap, 0);
    for(int x = -1; x <= 1; ++x)
    {
        for(int y = -1; y <= 1; ++y)
        {
            float pcfDepth = texture(shadowMap, projCoords.xy + vec2(x, y) * texelSize).r;
            shadow += currentDepth - bias > pcfDepth  ? 1.0 : 0.0;
        }
    }
    shadow /= 9.0;

    // keep the shadow at 0.0 when outside the far_plane region of the light's frustum.
    if(projCoords.z > 1.0)
    shadow = 0.0;

    return shadow;
}



vec3 CalcPointLight(PointLight light, vec3 viewDir, int lightNumb)
{

    vec3 lightDir = normalize(light.position - fragPos);
    float theta = dot(lightDir, normalize(-light.direction));
    float epsilon   = light.cutOff - light.outerCutOff;
    float intensity = clamp((theta - light.outerCutOff) / epsilon, 0.0, 1.0);
    if(theta > light.outerCutOff)
    {
        // diffuse shading
        float diff = max(dot(normal, vec4(lightDir, 1.0f)), 0.0);
        // specular shading
        vec3 reflectDir = reflect(-lightDir, vec3(normal));
        float spec = pow(max(dot(viewDir, reflectDir), 0.0), 50);
        // attenuation
        float distance    = length(light.position - fragPos);
        float attenuation = (light.constant + light.linear * distance + light.quadratic * (distance * distance));
        // combine results
        vec3 ambient  = light.color * ambient_strength;
        vec3 diffuse  = light.color  * diff * diffuse_strength;
        vec3 specular = light.color * spec * specular_strength;
        ambient  *= attenuation;
        diffuse  *= attenuation;
        specular *= attenuation;
        diffuse  *= intensity;
        specular *= intensity;
        ambient *= intensity;
        if (lightNumb == 0){
            float shadow = ShadowCalculation(FragPosLightSpace);
            return (ambient + (1.0 - shadow) * (diffuse + specular));
        }
        return (ambient + diffuse + specular);
    }
    return vec3(0.0f);
}

void main() {

    vec3 viewDir = normalize(viewPos - fragPos);
    vec3 result = vec3(0.0f);
    for(int i = 0; i < NR_POINT_LIGHTS; i++)
    result += CalcPointLight(pointLights[i], viewDir, i);

    float brightness = dot(result, vec3(0.2126, 0.7152, 0.0722));
    if(brightness > 2.0)
    BrightColor = vec4(result, 1.0);
    else
    BrightColor = vec4(0.0, 0.0, 0.0, 1.0);
  FragmentColor = texture(Texture, vec2(texCoord.x, 1.0 - texCoord.y) + TextureOffset) * vec4(result, 1.0f);
  FragmentColor.a = Transparency;
}
