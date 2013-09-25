#ifndef BONE_H
#define BONE_H

#include <vector>
#include <algorithm>
#include "glm/glm.hpp"

#include <exception>

/**
 * Exception thrown when rotation angle
 * exceeds constraints for given angle.
 */
class ConstraintException : std::exception { };

/**
 * Simple Bone (and joint) representation using
 * length and angles in respect to parent Bone.
 */
class Bone {
	public:
    //! Parent Bone (NULL if root)
		Bone* parent;
    //! Set of Bones (joint definition)
		std::vector< Bone* > bones;

    //! Length of the Bone
		float length;

    //! Transfomation matrix
		glm::mat4 M;

    //! Current rotation angles
    glm::vec3 rotation;

    //! Angles contraint (index 0 is minimum, index 1 is maximum)
    glm::vec3 constraint[2];


    /**
     * Add child Bone - add new Bone to the joint
     *
     * @param b Bone to add, memory is retained
     * @return Just added Bone
     */
		Bone* add(Bone* b);

    /**
     * Remove child Bone
     *
     * @param b Bone Bone to remove, memory is released
     */
		void remove(Bone* b);

    /**
     * Detach itself from parent joint. Memory is not released.
     */
    void detach();

    /**
     * Set constraint for angles.
     *
     * @param nx Minimum X angle
     * @param mx Maximum X angle
     * @param ny Minimum Y angle
     * @param my Maximum Y angle
     * @param nz Minimum Z angle
     * @param mz Maximum Z angle
     * @return this
     */
    Bone* constraints(float nx, float mx, float ny, float my, float nz, float mz);

    /**
     * Check if given angles are inside the contraints.
     *
     * @param x X angle
     * @param y Y angle
     * @param z Z angle
     * @throw ConstraintException if any angle is outside its constraint
     */
    void checkConstraints(float x, float y, float z);

    /**
     * Set absolute angle, constaints are check, overflow over -360/360 degrees
     * are handled.
     *
     * @throw ConstraintException if any angle is outside its constriant
     * @see Bone::checkConstraints()
     * @param x X angle
     * @param y Y angle
     * @param z Z angle
     * @return this
     */
    Bone* setRotate(float x, float y, float z);

    /**
     * Set angle relative to current angle values.
     *
     * @see Bone::setRotate()
     * @throw ConstraintException if any angle (after addition) is outside its constriant
     * @param dx X change (+-)
     * @param dy Y change (+-)
     * @param dz Z change (+-)
     * @return this
     */
    Bone* rotate(float dx, float dy, float dz);

    /**
     * Find Bone using its unique identifier. On every joint there
     * may be maximum 8 bones identified using this method.
     *
     * The rightmost digit represents the current joint index
     * (i.e. 1 will return first bone, 4 will return 4th bone - vector index 3).
     * If id is longer then one digit, it is read recusively
     * from right to left (i.e. 31 will return 3rd bone on 1st bone joint,
     * 231 will return 2nd bone on previously mentioned bone joint).
     *
     * @param id Bone identifier (every digit must be [1;9])
     * @return Bone
     */
    Bone* bone(unsigned long long id);

    /**
     * Create bone of given length, angles are not constrained.
     *
     * @param l Length
     */
		Bone(float l)  : length(l) {
      M = glm::mat4(1.0f);
      parent = NULL;
      rotation = glm::vec3(0.0f);
      constraint[0] = glm::vec3(-360.0f);
      constraint[1] = glm::vec3(360.0f);
    };

    /**
     * Destroy Bone and its children attached to joint
     */
		~Bone();
};

#endif
