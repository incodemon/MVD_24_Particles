#version 330

layout(location = 0) in vec3 a_vertex;
layout(location = 1) in vec3 a_velocity;
layout(location = 2) in float a_age;
layout(location = 3) in float a_life;

out vec3 v_vertex;
out vec3 v_velocity;
out float v_age;
out float v_life;

uniform mat4 u_mvp;
uniform mat4 u_model;
uniform mat4 u_vp;
uniform float u_time;

uniform float u_height_near_plane;

float random(vec2 co){
	highp float a = 12.9898;
	highp float b = 78.233;
	highp float c = 43758.5453;
	highp float dt = dot(co.xy ,vec2(a,b));
	highp float sn = mod(dt,3.14);
	return fract(sin(sn) * c);
}

void main()
{
    
    //move particle
    v_velocity = a_velocity;
    v_vertex = a_vertex + vec3(0,0.001,0);
    v_age = a_age;
    v_life = a_life;
    
    gl_Position = u_vp * u_model * vec4(a_vertex, 1.0);
    
    gl_PointSize = 5.0;
    
}
