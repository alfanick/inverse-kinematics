#include "movement.h"

#include <algorithm>

glm::vec3 sgn(glm::vec3 a, glm::vec3 b) {
  return glm::vec3(
    a.x*b.x < 0.0f ? 1 : -1,
    a.y*b.y < 0.0f ? 1 : -1,
    a.z*b.z < 0.0f ? 1 : -1
  );
}

Movement::Movement() {
  position = 0;
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
  moved.clear();
  moved.resize(sequence.size());

  for (int i = 0; i < sequence.size(); i++) {
    for (std::map<Bone*,glm::vec3>::iterator kv = sequence[i].begin(); kv != sequence[i].end(); ++kv) {
      moved[i][kv->first] = glm::vec3(0.0f);
    }
  }

  return this;
}

bool Movement::frame(float fill) {
  if (position >= framesCount()) {
    return false;
  }

  int c = 0;

  for (std::map<Bone*,glm::vec3>::iterator kv = sequence[position].begin(); kv != sequence[position].end(); ++kv) {
    glm::vec3 dv = (sequence[position-1][kv->first] - kv->second) * sgn(sequence[position-1][kv->first], kv->second) * fill;

    moved[position][kv->first] += glm::abs(dv);

    if (glm::abs(moved[position][kv->first]).x >= glm::abs(sequence[position-1][kv->first] - kv->second).x) {
      c++;
    } else {
      kv->first->rotate(dv.x, 0, 0);
    }

    if (glm::abs(moved[position][kv->first]).y >= glm::abs(sequence[position-1][kv->first] - kv->second).y) {
      c++;
    } else {
      kv->first->rotate(0, dv.y, 0);
    }

    if (glm::abs(moved[position][kv->first]).z >= glm::abs(sequence[position-1][kv->first] - kv->second).z) {
      c++;
    } else {
      kv->first->rotate(0, 0, dv.z);
    }
  }

  return c < sequence[position].size() * 3;
}

bool Movement::next() {
  if (position >= framesCount())
    return false;

  position++;

  return true;
}

int Movement::framesCount() {
  return sequence.size();
}


