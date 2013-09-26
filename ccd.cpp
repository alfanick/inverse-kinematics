#include "ccd.h"
#include "helpers.h"
#include <cstdio>

void ccd::findNewAngles(Bone *endEffector, vec3 target, int iterations) {
  bool found = false;
  iterations = 1;
  while(!found && iterations--) {
    Bone * currentBone = endEffector;
    while(currentBone->parent != NULL) {
      vec4 endPosition = currentBone->getEndPosition();
      vec4 startPosition = currentBone->parent->getEndPosition();
      vec3 toTarget = normalize(vec3(target.x-startPosition.x, target.y-startPosition.y, target.z-startPosition.z));
      vec3 toEnd = normalize(vec3(endPosition.x-startPosition.x, endPosition.y-startPosition.y, endPosition.y));
      float cosine = dot(toEnd, toTarget);
      float angle = ANGLE(acos(cosine));
      if(currentBone == endEffector) {
        printf("target params: (%f, %f, %f)\n", target.x, target.y, target.z);
        printf("end params: (%f, %f, %f)\n", endPosition.x, endPosition.y, endPosition.z);
        printf("begin params: (%f, %f, %f)\n", startPosition.x, startPosition.y, startPosition.z);
        printf("angle: %f\n", angle);
      }
      if(cosine < 0.99) {
        // float delta_x = ANGLE(acos(toTarget.x)) - ANGLE(acos(toEnd.x));
        // float delta_y = ANGLE(acos(toTarget.y)) - ANGLE(acos(toEnd.y));
        // float delta_z = ANGLE(acos(toTarget.z)) - ANGLE(acos(toEnd.z));

        // currentBone->rotateMax(delta_x, delta_y, delta_z);

        vec3 crossResult = cross(toEnd, toTarget);
        crossResult = normalize(crossResult);
        quat rot = angleAxis(angle, crossResult);
        rot = normalize(rot);
        glm::vec3 euler = glm::eulerAngles(rot) ;
        currentBone->rotateMax(euler.x, euler.y, euler.z);
      }

      vec3 tmp = vec3(endEffector->getEndPosition());
      tmp.x -= target.x; tmp.y -= target.y; tmp.z -= target.z;
      if(dot(tmp, tmp) < 1.0) {
        found = true;
        printf("found\n");
      }
      currentBone = currentBone->parent;
    }
  }
}
