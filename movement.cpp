#include "movement.h"

#include <algorithm>

Movement::Movement() {
  position = 0;
  sequence.resize(1);
}

Movement* Movement::move(Bone* bone, glm::vec3 delta_angles) {
  return set(bone, sequence[position][bone] + delta_angles);
}

Movement* Movement::set(Bone* bone, glm::vec3 angles) {
  sequence[position][bone] = angles;

  return this;
}

Movement* Movement::keyframe() {
  position++;
  sequence.resize(position+1);

  sequence[position] = sequence[position-1];

  return this;
}

Movement* Movement::set(Bone* root) {
  set(root, root->rotation);

  for (std::vector<Bone*>::iterator it = root->bones.begin(); it != root->bones.end(); ++it) {
    set(*it);
  }

  return this;
}

Movement* Movement::start() {
  position = 0;

  return this;
}

bool Movement::frame() {
  if (position >= framesCount())
    return false;

  for (std::map<Bone*,glm::vec3>::iterator kv = sequence[position].begin(); kv != sequence[position].end(); ++kv) {
    kv->first->setRotate(kv->second.x, kv->second.y, kv->second.z);
  }

  position++;

  return true;
}

int Movement::framesCount() {
  return sequence.size();
}


