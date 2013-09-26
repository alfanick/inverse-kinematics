#include "ccd.h"
#include "helpers.h"

void ccd::findNewAngles(Bone *endEffector, vec3 target, int iterations) {
  bool found = false;
  while(!found && iterations--) {
    Bone * currentBone = endEffector;
    while(currentBone->parent != NULL) {
      vec4 endPosition = currentBone->getEndPosition();
      vec4 startPosition = currentBone->parent->getEndPosition();
      vec3 toTarget = normalize(vec3(target.x-startPosition.x, target.y-startPosition.y, target.z-startPosition.z));
      vec3 toEnd = normalize(vec3(endPosition.x-startPosition.x, endPosition.y-startPosition.y, endPosition.y));
      float cosine = dot(toTarget, toEnd);
      if(cosine < 0.99) {
        float delta_x = ANGLE(acos(toTarget.x)) - ANGLE(acos(toEnd.x));
        float delta_y = ANGLE(acos(toTarget.y)) - ANGLE(acos(toEnd.y));
        float delta_z = ANGLE(acos(toTarget.z)) - ANGLE(acos(toEnd.z));

        currentBone->rotate(delta_x, delta_y, delta_z);

        // vec3 crossResult = cross(toTarget, toEnd);
        // clockwise rotation
        // float angle = ANGLE(acos(cosine));
        // if(crossResult.z > 0.0f) { 
        //    
        // }
      }
      if(dot(glm::vec3(endEffector->getEndPosition()), target) >= 0.99) {
        found = true;
      }
      currentBone = currentBone->parent;
    }
  }
}
