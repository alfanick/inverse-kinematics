#include "movement.h"

#include <algorithm>

float sgn(float s) {
  return s <= 0 ? -1 : 1;
}

Movement::Movement() {
  position = 0;
  n = 0;
  sequence.resize(1);
}

Movement* Movement::move(Bone* bone, glm::vec3 delta_angles) {
  return set(bone, sequence[position][bone]+delta_angles);
}

Movement* Movement::set(Bone* bone, glm::vec3 angles) {
  sequence[position][bone] = angles;

  printf("(%d) %f: \t%f\t\t%f\t\t%f\n", position, bone->length, angles.x, angles.y, angles.z);

  return this;
}

Movement* Movement::keyframe() {
  position++;
  sequence.resize(position+1);

  sequence[position] = sequence[position-1];

  for (std::map<Bone*,glm::vec3>::iterator kv = sequence[position].begin(); kv != sequence[position].end(); ++kv) {
      printf("[%d] %f: \t%f\t\t%f\t\t%f\n", position, kv->first->length, kv->second.x, kv->second.y, kv->second.z);

  }

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
  n =0 ;

  return this;
}

bool Movement::frame(float fill) {
  if (fill * n >= 1.0f || position >= framesCount()) {
    n = 0;
    return false;
  }

  for (std::map<Bone*,glm::vec3>::iterator kv = sequence[position].begin(); kv != sequence[position].end(); ++kv) {
    kv->first->rotate(
        (sequence[position-1][kv->first].x - kv->second.x) * fill * sgn(kv->second.x),
        (sequence[position-1][kv->first].y - kv->second.y) * fill * sgn(kv->second.y),
        (sequence[position-1][kv->first].z - kv->second.z) * fill * sgn(kv->second.z)
    );
  }
  n++;

  return true;
}

bool Movement::next() {
  if (position >= framesCount())
    return false;

  n = 0;
  position++;

  return true;
}

int Movement::framesCount() {
  return sequence.size();
}


