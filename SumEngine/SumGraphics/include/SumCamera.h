//*************************************************************************************************
// Title: SumCamera.h
// Author: Gael Huber
// Description: A basic camera. A camera in SumEngine has two methods of storing information. The
//	first is the externally exposed data, the second is the internally exposed data. The world and
//	projection matrices are designed to be entirely used by the rendering engine can cannot be
//	directly manipulated. All externally exposed orientation and positioning data is accomplished
//	through manipulable postion and scale vectors and an orientation quaternion. The view matrix
//	will periodically synchronize itself with the most recent data. 
//*************************************************************************************************
#ifndef __SUMCAMERA_H__
#define __SUMCAMERA_H__

#include "SumRenderCore.h"

class Camera
{
public:
	// Constructor
	Camera();

	// Destructor
	virtual ~Camera();

	// Set the lens
	void setLens();

	// Retrieve the position
	void position();

	// Set the position
	void setPosition();

	// Move the camera relative to world axes
	void translate();

	// Move the camera along the X axis
	void translateX();

	// Move the camera along the Y axis
	void translateY();

	// Move the camera along the Z axis
	void translateZ();

	// Move the camera relative to local axes
	void translateRelative();

	// Move the camera relative to local X axis
	void translateXRelative();

	// Move the camera relative to the local Y axis
	void translateYRelative();

	// Move the camera relative to the local Z axis
	void translateZRelative();

	// Rotate the camera
	void rotate();

	// Rotate about the world X axis
	void rotateX();

	// Rotate about the world Y axis
	void rotateY();

	// Rotate about the world Z axis
	void rotateZ();

	// Rotate about the relative X axis
	void pitch();

	// Rotate about the relative Y axis
	void yaw();

	// Rotate about the relative Z axis
	void roll();

	// Set the camera rotation
	void setRotation();

	// Look at a point in space
	void lookAt();

	// Update the matrices based on current information and return the world-view matrix for this camera
	const Matrix viewProj();

private:
	// Directional properties
	//**********************************************
	
	// Position vector

	// Right vector
	
	// Up vector

	// Look/forward vector

	// Frustrum properties
	//**********************************************

	// Near z

	// Far z

	// Aspect ratio

	// Field of view

	// Near window height

	// Far window height

	// Matrices
	//**********************************************
	
	// View matrix

	// Projection matrix
};

#endif