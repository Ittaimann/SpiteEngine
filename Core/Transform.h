#ifndef TRANSFORM_H
#define TRANSFORM_H

//TODO: get this to be struct of arrays not array of structs
// foolish child don't you know that data oriented is the way
// of the future
//
// getters/setters to come later?
struct Transform
{
	float PosX,PosY,PosZ;
	float DegX,DegY,DegZ; // replace with quat at some point
	float ScaleX,ScaleY,ScaleZ;


	Transform()
	{
		PosX = 0;
		PosY = 0;
		PosZ = 0;
		DegX = 0;
		DegY = 0;
		DegZ = 0;
		ScaleX = 1;
		ScaleY = 1;
		ScaleZ = 1;
	}
};

#endif

