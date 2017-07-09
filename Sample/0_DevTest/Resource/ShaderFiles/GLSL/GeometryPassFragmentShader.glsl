#version 330 core
layout (location = 0) out vec4 gPosition;
layout (location = 1) out vec4 gNormal;
layout (location = 2) out vec4 gAlbedoSpec;


in vec2 TexCoords;
in vec3 FragPos;
in vec3 Normal;

uniform sampler2D TexDiffuse;
uniform sampler2D TexSpecular;

void main()
{    
    // Store the fragment position vector in the first gbuffer texture
    gPosition.rgb = FragPos;
    gPosition.a = 1.0f;
    // Also store the per-fragment normals into the gbuffer
    gNormal.rgb = normalize(Normal);
    gNormal.a = 1.0f;
    // And the diffuse per-fragment color
    gAlbedoSpec.rgb = texture(TexDiffuse, TexCoords).rgb;
    // Store specular intensity in gAlbedoSpec's alpha component
    gAlbedoSpec.a = texture(TexSpecular, TexCoords).r;
}