precision mediump float;
precision lowp int;

uniform mat4 u_mvpMatrix;
uniform vec4 u_color;

attribute highp vec4 a_position;

varying vec4 v_color;

void main(void)
{
	v_color = u_color;
	gl_Position = u_mvpMatrix*a_position;
}
