#ifndef MOVEMENT_H
#define MOVEMENT_H

#include <map>
#include <vector>
#include <cstdio>

#include "bone.h"

class Movement {
  private:
    /**
     * Vector represents sequence of maps, each map represents
     * angles of given bone in the given frame.
     */
    std::vector< std::map<Bone*, glm::vec3> > sequence;

    float n;
    int position;

  public:
    Movement();

    Movement* move(Bone* bone, glm::vec3 delta_angles);
    Movement* set(Bone* bone, glm::vec3 angles);
    Movement* keyframe();
    Movement* set(Bone* root);

    Movement* start();
    bool next();

    bool frame(float fill);

    int framesCount();
};

#endif
