#include "bone.h"

Bone::add(Bone *b) {
	b->parent = b;
	bones.push_back(b);
}

Bone::remove(Bone *b) {
	b->parent = NULL;
	bones.erase(std::remove(bones.begin(), bones.end(), b), bones.end());

	delete b;
}

Bone::detach() {
	parent->bones.erase(std::remove(bones.begin(), bones.end(), b), bones.end());
	parent = NULL;
}

Bone::~Bone() {
	for (std::vector<Bone*>::iterator it = bones.begin(); it != bones.end(); it++) {
		delete *it;
	}
}

