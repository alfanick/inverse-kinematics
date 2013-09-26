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
      vec3 toEnd = normalize(vec3(endPosition.x-startPosition.x, endPosition.y-startPosition.y, endPosition.z-startPosition.z));
      float cosine = dot(toEnd, toTarget);
      float angle = ANGLE(acos(cosine));
      if(currentBone == endEffector) {
        printf("target params: (%f, %f, %f)\n", target.x, target.y, target.z);
        printf("end params: (%f, %f, %f)\n", endPosition.x, endPosition.y, endPosition.z);
        printf("begin params: (%f, %f, %f)\n", startPosition.x, startPosition.y, startPosition.z);
        printf("angle: %f\n", angle);
      }
      if(cosine < 0.99) {
        quat rot = ccd::rotationBetweenVectors(toTarget, toEnd);
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

quat ccd::rotationBetweenVectors(vec3 start, vec3 dest){
    start = normalize(start);
    dest = normalize(dest);
 
    float cosTheta = dot(start, dest);
    vec3 rotationAxis;
 
    if (cosTheta < -1 + 0.001f){
        // special case when vectors in opposite directions:
        // there is no "ideal" rotation axis
        // So guess one; any will do as long as it's perpendicular to start
        rotationAxis = cross(vec3(0.0f, 0.0f, 1.0f), start);
        if (length2(rotationAxis) < 0.01 ) // bad luck, they were parallel, try again!
            rotationAxis = cross(vec3(1.0f, 0.0f, 0.0f), start);
 
        rotationAxis = normalize(rotationAxis);
        return angleAxis(180.0f, rotationAxis);
    }
 
    rotationAxis = cross(start, dest);
 
    float s = sqrt( (1+cosTheta)*2 );
    float invs = 1 / s;
 
    return quat(
        s * 0.5f, 
        rotationAxis.x * invs,
        rotationAxis.y * invs,
        rotationAxis.z * invs
    );
 
}
