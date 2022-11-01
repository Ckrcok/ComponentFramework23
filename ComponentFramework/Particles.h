#ifndef PARTICLES_H
#include <Vector>
#include <glew.h>
#include "Vector.h"
using namespace MATH;



class Particles {
public:
    Particles(int numberOfParticles);
    ~Particles();
    void Render() const;
private:

    std::vector<Vec3> pos;
    std::vector<Vec3> vel;
    std::vector<Vec4> color;
    GLuint vao, vbo;
    void setupParticles();
};
#endif

