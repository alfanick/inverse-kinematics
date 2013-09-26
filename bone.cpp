#include "bone.h"
#include "helpers.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "glm/gtc/quaternion.hpp"
#include "glm/gtx/quaternion.hpp"
#include <cstdio>

Bone::Bone(float l) {
  length = l;
  M = glm::mat4(1.0f);
  parent = NULL;
  rotation = glm::vec3(0.0f);
  coordinates = glm::vec3(0.0f);
  constraint[0] = glm::vec3(-360.0f);
  constraint[1] = glm::vec3(360.0f);
};

Bone* Bone::add(Bone *b) {
	b->parent = this;
	bones.push_back(b);

  return b;
}

void Bone::remove(Bone *b) {
	b->parent = NULL;
	bones.erase(std::remove(bones.begin(), bones.end(), b), bones.end());

	delete b;
}

glm::vec4 Bone::getEndPosition() {
  glm::vec4 endPosition;
  if(parent == NULL) {
    endPosition = glm::vec4(0.0f, 0.0f, 0.0f, 1.0f);
  }
  else {
    endPosition = parent->getEndPosition();
  }

  glm::mat4 A(1.0f);
  glm::quat rot(glm::vec3(RAD(rotation.x), RAD(rotation.y), RAD(rotation.z)));
  A = glm::translate(A, glm::vec3(0.0f, 0.0f, length));

  endPosition = A*(rot*endPosition);

  return endPosition;
}

Bone* Bone::constraints(float nx, float mx, float ny, float my, float nz, float mz) {
  constraint[0] = glm::vec3(nx, ny, nz);
  constraint[1] = glm::vec3(mx, my, mz);

  return this;
}

void Bone::checkConstraints(float x, float y, float z) {
  if (x < constraint[0].x || x > constraint[1].x ||
      y < constraint[0].y || y > constraint[1].y ||
      z < constraint[0].z || z > constraint[1].z) {
    throw new ConstraintException();
  }
}

Bone* Bone::setRotate(float x, float y, float z) {
  float lx, ly, lz;

  checkConstraints(lx = fmod(x, 360.0f), ly = fmod(y, 360.f), lz = fmod(z, 360.0f));

  rotation.x = lx;
  rotation.y = ly;
  rotation.z = lz;

  return this;
}

Bone* Bone::rotate(float dx, float dy, float dz) {
  return setRotate(rotation.x+dx, rotation.y+dy, rotation.z+dz);

  return this;
}

void Bone::detach() {
	parent->bones.erase(std::remove(bones.begin(), bones.end(), this), bones.end());
	parent = NULL;
}

Bone* Bone::bone(unsigned long long id) {
  if (id < 10) {
    return bones[id-1];
  } else {
    return bones[id % 10 - 1]->bone(id/10);
  }
}

Bone::~Bone() {
	for (std::vector<Bone*>::iterator it = bones.begin(); it != bones.end(); it++) {
		delete *it;
	}
}

