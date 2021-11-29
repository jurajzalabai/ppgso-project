#version 330
// A texture is expected as program attribute
uniform sampler2D Texture;

// (optional) Transparency
uniform float Transparency;

// (optional) Texture offset
uniform vec2 TextureOffset;
uniform float diffuse_strength;
uniform float specular_strength;
uniform float ambient_strength;
uniform vec3 viewPos;

// The vertex shader will feed this input
in vec2 texCoord;
in vec3 fragPos;

// Wordspace normal passed from vertex shader
in vec4 normal;

// The final color
out vec4 FragmentColor;

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

vec3 CalcPointLight(PointLight light, vec3 viewDir)
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
        return (ambient + diffuse + specular);
    }
    return vec3(0.0f);
}

void main() {

    vec3 viewDir = normalize(viewPos - fragPos);
    vec3 result = vec3(0.0f);
    for(int i = 0; i < NR_POINT_LIGHTS; i++)
    result += CalcPointLight(pointLights[i], viewDir);
  FragmentColor = texture(Texture, vec2(texCoord.x, 1.0 - texCoord.y) + TextureOffset) * vec4(result, 1.0f);
  FragmentColor.a = Transparency;
}
