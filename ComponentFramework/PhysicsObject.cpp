#include "PhysicsObject.h"

PhysicsObject::PhysicsObject(){
	/// Another way to initialize within the constructor
	angle = angularVel = angularAccel = 0.0f;
	rotationalI = 1.0f;

}


PhysicsObject::~PhysicsObject(){

}

