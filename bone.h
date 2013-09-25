#ifndef BONE_H
#define BONE_H

#include <vector>
#include <algorithm>
#include "glm/glm.hpp"

class Bone {
	public:
		Bone* parent;
		std::vector< Bone* > bones;

		float length;
		glm::mat4 M;

		Bone* add(Bone* b);
		void remove(Bone* b);
		void detach();

    void setRotate(float x, float y, float z);
    void rotate(float dx, float dy, float dz);

    glm::vec3 rotation;

		Bone() { Bone(0); };
		Bone(float l)  : length(l) { M = glm::mat4(1.0f); parent = NULL; rotation = glm::vec3(0.0f); };
		~Bone();
};

#endif
