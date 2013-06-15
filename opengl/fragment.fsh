varying vec2 vTex;
uniform sampler2D textureUnit0;
uniform sampler2D textureUnit1;

varying float yPos;

void main(void){
	if(yPos > -0.5){
		gl_FragColor = texture2D(textureUnit1, vTex);
	}else if(yPos > -1.5){
		float dist = abs(1.0/yPos);
		gl_FragColor = texture2D(textureUnit1, vTex) * dist;
	}else{
		gl_FragColor = texture2D(textureUnit0, vTex);
	}
	
}
