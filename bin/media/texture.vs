precision mediump float;
precision lowp int;

uniform mat4 u_mvpMatrix;

attribute highp vec4 a_position;
attribute vec2 a_texCoord;

varying vec2 v_texCoord;

void main(void)
{
	v_texCoord = a_texCoord;
	gl_Position = u_mvpMatrix*a_position;
}