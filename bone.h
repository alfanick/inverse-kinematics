#ifndef BONE_H
#define BONE_H

#include <vector>
#include "glm/glm.hpp"

class Bone {
	public:
		Bone* parent;
		std::vector< Bone* > bones;

		float length;
		glm::mat4 M;

		void add(Bone* b);
		void remove(Bone* b);
		void detach();

		Bone() { Bone(0); };
		Bone(float l)  : length(l) { };
		~Bone();
};

#endif
