precision mediump float;
precision lowp int;

uniform sampler2D u_map;

varying vec2 v_texCoord;

void main(void)
{
	gl_FragColor = texture2D(u_map, v_texCoord);
}
