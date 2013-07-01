uniform mat4 mvMatrix;
uniform mat4 pMatrix;
uniform mat3 nMatrix;

uniform vec3 lightPosition;

attribute vec4 vVertex;
attribute vec2 vTexCoord0;
attribute vec3 vNormal;

varying vec2 vTex;

varying vec3 varyingNormal;
varying vec3 varyingLightDirection;

void main(void) {
	vTex = vTexCoord0;
    
    
    // Posição do vértice apenas com ModelView
    vec4 vPosition = mvMatrix * vVertex;

    varyingNormal = normalize(nMatrix * vNormal);
    
    varyingLightDirection = normalize(lightPosition - vPosition.xyz);

	gl_Position = pMatrix * vPosition;
}