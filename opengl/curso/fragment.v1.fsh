varying vec2 vTex;
uniform sampler2D textureUnit0;
uniform sampler2D textureUnit1;

uniform vec4 ambientColor;
uniform vec4 diffuseColor;
uniform vec4 specularColor;

varying vec3 varyingNormal;
varying vec3 varyingLightDirection;

void main(void) {
    float diffIntensity = max(0.0,
        dot(normalize(varyingNormal),
        normalize(varyingLightDirection)));
    
    float specIntensity = 0.0;
    
    if(diffIntensity != 0.0){
        vec3 vReflection = normalize(reflect(-normalize(varyingLightDirection), normalize(varyingNormal)));
        
        specIntensity = pow(max(0.0, dot(normalize(varyingNormal), vReflection)), 30.0);
    }
    
    vec4 vFragColor = ambientColor +
    (diffuseColor * diffIntensity) +
    (specularColor * specIntensity);

    gl_FragColor = texture2D(textureUnit0, vTex) * vFragColor;
}