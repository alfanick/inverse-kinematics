#include "bone.h"

void Bone::add(Bone *b) {
	b->parent = this;
	bones.push_back(b);
}

void Bone::remove(Bone *b) {
	b->parent = NULL;
	bones.erase(std::remove(bones.begin(), bones.end(), b), bones.end());

	delete b;
}

void Bone::setRotate(float x, float y, float z) {
  rotation.x = x;
  rotation.y = y;
  rotation.z = z;
}

void Bone::rotate(float dx, float dy, float dz) {
  rotation.x += dx;
  rotation.y += dy;
  rotation.z += dz;
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

