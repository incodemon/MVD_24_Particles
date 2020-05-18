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

    //these are the names of the transform feedbacks in shader
    const GLchar* feedback_varyings[] = {
        "v_vertex",
        "v_velocity",
        "v_age",
        "v_life"
    };

    particle_shader_ = new Shader(
        "data/shaders/particles.vert",
        "data/shaders/particles.frag",
        4,
        feedback_varyings
        );

    //tell opengl to set particle size in shader
    glEnable(GL_PROGRAM_POINT_SIZE);

    int num_points = 1000;

    //creating arrays for particles attributes
    std::vector<GLfloat> vertices;
    vertices.resize(num_points * 3);

    std::vector<GLfloat> velocities;
    velocities.resize(num_points * 3);

    std::vector<GLfloat> ages;
    ages.resize(num_points);

    std::vector<GLfloat> lives;
    lives.resize(num_points);

    //initialise arrays with data

    for (int i = 0; i < num_points; i++) {
        vertices[i] = 0;
        velocities[i] = 0;
        ages[i] = -9.0f;
        lives[i] = float(rand() % 9000) / 9000.0f;
    }

    //create vertex array objects
    glGenVertexArrays(1, &vaoA_);
    glGenVertexArrays(1, &vaoB_);

    //create transform feedback ids
    glGenTransformFeedbacks(1, &tfA_);
    glGenTransformFeedbacks(1, &tfB_);


    //create vbos
    //fil array A
    glBindVertexArray(vaoA_);
    GLuint vb_A_pos, vb_A_vel, vb_A_age, vb_A_lif;

    //vertices buffer
    glGenBuffers(1, &vb_A_pos);
    glBindBuffer(GL_ARRAY_BUFFER, vb_A_pos);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), &(vertices[0]), GL_STREAM_COPY);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

    //velocity buffer
    glGenBuffers(1, &vb_A_vel);
    glBindBuffer(GL_ARRAY_BUFFER, vb_A_vel);
    glBufferData(GL_ARRAY_BUFFER, velocities.size() * sizeof(float), &(velocities[0]), GL_STREAM_COPY);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);

    //age buffer
    glGenBuffers(1, &vb_A_age);
    glBindBuffer(GL_ARRAY_BUFFER, vb_A_age);
    glBufferData(GL_ARRAY_BUFFER, ages.size() * sizeof(float), &(ages[0]), GL_STREAM_COPY);
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 1, GL_FLOAT, GL_FALSE, 0, 0);

    //life buffer
    glGenBuffers(1, &vb_A_lif);
    glBindBuffer(GL_ARRAY_BUFFER, vb_A_lif);
    glBufferData(GL_ARRAY_BUFFER, lives.size() * sizeof(float), &(lives[0]), GL_STREAM_COPY);
    glEnableVertexAttribArray(3);
    glVertexAttribPointer(3, 1, GL_FLOAT, GL_FALSE, 0, 0);

    glBindTransformFeedback(GL_TRANSFORM_FEEDBACK, tfA_);
    //bind the vbos above to tfA_
    glBindBufferBase(GL_TRANSFORM_FEEDBACK_BUFFER, 0, vb_A_pos);
    glBindBufferBase(GL_TRANSFORM_FEEDBACK_BUFFER, 1, vb_A_vel);
    glBindBufferBase(GL_TRANSFORM_FEEDBACK_BUFFER, 2, vb_A_age);
    glBindBufferBase(GL_TRANSFORM_FEEDBACK_BUFFER, 3, vb_A_lif);


    //buffer B

    //now fill array B, same as A
    glBindVertexArray(vaoB_);
    GLuint vb_B_pos, vb_B_vel, vb_B_age, vb_B_lif;

    glGenBuffers(1, &vb_B_pos);
    glBindBuffer(GL_ARRAY_BUFFER, vb_B_pos);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), &(vertices[0]), GL_STREAM_COPY);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

    //velocity buffer
    glGenBuffers(1, &vb_B_vel);
    glBindBuffer(GL_ARRAY_BUFFER, vb_B_vel);
    glBufferData(GL_ARRAY_BUFFER, velocities.size() * sizeof(float), &(velocities[0]), GL_STREAM_COPY);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);

    //age buffer
    glGenBuffers(1, &vb_B_age);
    glBindBuffer(GL_ARRAY_BUFFER, vb_B_age);
    glBufferData(GL_ARRAY_BUFFER, ages.size() * sizeof(float), &(ages[0]), GL_STREAM_COPY);
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 1, GL_FLOAT, GL_FALSE, 0, 0);

    //life buffer
    glGenBuffers(1, &vb_B_lif);
    glBindBuffer(GL_ARRAY_BUFFER, vb_B_lif);
    glBufferData(GL_ARRAY_BUFFER, lives.size() * sizeof(float), &(lives[0]), GL_STREAM_COPY);
    glEnableVertexAttribArray(3);
    glVertexAttribPointer(3, 1, GL_FLOAT, GL_FALSE, 0, 0);


    glBindTransformFeedback(GL_TRANSFORM_FEEDBACK, tfB_);
    glBindBufferBase(GL_TRANSFORM_FEEDBACK_BUFFER, 0, vb_B_pos);
    glBindBufferBase(GL_TRANSFORM_FEEDBACK_BUFFER, 1, vb_B_vel);
    glBindBufferBase(GL_TRANSFORM_FEEDBACK_BUFFER, 2, vb_B_age);
    glBindBufferBase(GL_TRANSFORM_FEEDBACK_BUFFER, 3, vb_B_lif);
    glBindVertexArray(0);

}

void ParticleEmitter::update() {
    glUseProgram(particle_shader_->program);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glDepthMask(GL_FALSE);

    Camera& cam = ECS.getComponentInArray<Camera>(ECS.main_camera);
    lm::mat4 model_matrix;
    lm::mat4 mvp_matrix = cam.view_projection * model_matrix;

    particle_shader_->setUniform(U_MODEL, model_matrix);
    particle_shader_->setUniform(U_VP, cam.view_projection);
    particle_shader_->setUniform(U_TIME, (float)glfwGetTime());
    //set texture later

    if (vaoSource == 0) {
        //render vaoA
        glBindVertexArray(vaoA_);
        //bind tfB
        glBindTransformFeedback(GL_TRANSFORM_FEEDBACK, tfB_);
        //switch vao source
        vaoSource = 1;
    }
    else {
        glBindVertexArray(vaoB_);
        glBindTransformFeedback(GL_TRANSFORM_FEEDBACK, tfA_);
        vaoSource = 0;
    }

    glBeginTransformFeedback(GL_POINTS);

    glDrawArrays(GL_POINTS, 0, 1000);

    glEndTransformFeedback();


    glDisable(GL_BLEND);
    glDepthMask(GL_TRUE);
}