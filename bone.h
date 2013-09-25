#ifndef BONE_H
#define BONE_H

#include <vector>
#include <algorithm>
#include "glm/glm.hpp"

#include <exception>

class ConstraintException : std::exception { };

class Bone {
	public:
		Bone* parent;
		std::vector< Bone* > bones;

		float length;
		glm::mat4 M;

		Bone* add(Bone* b);
		void remove(Bone* b);
		void detach();

    Bone* constraints(float nx, float mx, float ny, float my, float nz, float mz);
    void checkConstraints(float x, float y, float z);

    Bone* setRotate(float x, float y, float z);
    Bone* rotate(float dx, float dy, float dz);

    Bone* bone(unsigned long long id);

    glm::vec3 rotation;
    glm::vec3 constraint[2];

		Bone() { Bone(0); };
		Bone(float l)  : length(l) {
      M = glm::mat4(1.0f);
      parent = NULL;
      rotation = glm::vec3(0.0f);
      constraint[0] = glm::vec3(-360.0f);
      constraint[1] = glm::vec3(360.0f);
    };
		~Bone();
};

#endif
