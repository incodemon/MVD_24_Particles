#include "ParticleEmitter.h"
#include "extern.h"
#include "Parsers.h"

//HOW DOES TRANSFORM FEEDBACK WORK?
//A transform feedback is basically a mechanism by which OpenGL can tell the 
//output from a shader to be written back to a vertex buffer, (which is 
//probably part of a VAO.
//The transformfeedback object itself is just handle which points the shader attribute
//to the buffer id
//Procedure
//---------
//Create two VAOs 'A' and 'B'
//Create two empty transform feedbacks 'A' and 'B'
//For each VAO:
//create vertex array buffer with initial geometry
//use glbindbufferbase to bind the transform feedback id to the
// - buffer of bound VAO
// - out attribute id in shader
//e.g Transform Feedback A is bound to vertex buffer in VAO A
//
//Now when we draw:
//Bind VAO 'A' but bind Transform feedback *B*
//That way when we draw buffer of A, the out variable in vertex shader will save data to B
//then next frame bind VAO 'B' and transform feedback A 
//etc.


void ParticleEmitter::init() {




}

void ParticleEmitter::update() {
	//glUseProgram(particle_shader_->program);

	

}
