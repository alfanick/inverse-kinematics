#include "bone.h"

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

Bone* Bone::constraints(float nx, float mx, float ny, float my, float nz, float mz) {
  constraint[0] = glm::vec3(nx, ny, nz);
  constraint[1] = glm::vec3(mx, my, mz);
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

Bone::~Bone() {
	for (std::vector<Bone*>::iterator it = bones.begin(); it != bones.end(); it++) {
		delete *it;
	}
}

