#ifndef CCD_H
#define CCD_H

#include "bone.h"
#include "glm/glm.hpp"
using namespace glm;

namespace ccd {
  void findNewAngles(Bone *endEffector, vec3 target, int iterations);
}

#endif
