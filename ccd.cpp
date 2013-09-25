#include "ccd.h"
#define PI 3.14159265
#define ANGLE(rad) rad*PI/180.0

void ccd::findNewAngles(Bone *endEffector, vec3 target, int iterations = 10) {
  bool found = false;
  while(!found && iterations--) {
    Bone * currentBone = endEffector;
    while(currentBone->parent != NULL) {
      vec3 endPosition = currentBone->getEndPosition();
      vec3 startPosition = currentBone->parent->getEndPosition();
      vec3 toTarget = normalize(vec3(target.x-startPosition.x, target.y-startPosition.y, target.z-startPosition.z));
      vec3 toEnd = normalize(vec3(endPosition.x-startPosition.x, endPosition.y-startPosition.y, endPosition.y));
      float cosine = dot(toTarget, toEnd);
      if(cosine < 0.99) {
        delta_x = ANGLE(acos(toTarget.x)) - ANGLE(acos(toEnd.x));
        delta_y = ANGLE(acos(toTarget.y)) - ANGLE(acos(toEnd.y));
        delta_z = ANGLE(acos(toTarget.z)) - ANGLE(acos(toEnd.z));

        currentBone->rotate(delta_x, delta_y, delta_z);

        // vec3 crossResult = cross(toTarget, toEnd);
        // clockwise rotation
        // float angle = ANGLE(acos(cosine));
        // if(crossResult.z > 0.0f) { 
        //    
        // }
      }
      if(dot(endEffector->getEndPosition(), target) >= 0.99) {
        found = true;
      }
      currentBone = currentBone->parent;
    }
  }
}
