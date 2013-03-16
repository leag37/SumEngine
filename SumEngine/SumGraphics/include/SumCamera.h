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

class SUM_DECLSPEC_ALIGN_16 Camera
{
public:
	_SUM_ALIGN(Camera);

public:
	// Constructor
	Camera();

	// Destructor
	virtual ~Camera();

	// Set the lens
	void setLens(SFLOAT fovy, SFLOAT aspect, SFLOAT nearZ, SFLOAT farZ);

	// Retrieve the position
	Vector position();

	// Set the position
	void setPosition(const Vector position);

	// Move the camera relative to world axes
	void translate(const Vector v);

	// Move the camera along the X axis
	void translateX(SFLOAT x);

	// Move the camera along the Y axis
	void translateY(SFLOAT y);

	// Move the camera along the Z axis
	void translateZ(SFLOAT z);

	// Move the camera relative to local axes
	void translateRelative(const Vector v);

	// Move the camera relative to local X axis
	void translateXRelative(SFLOAT x);

	// Move the camera relative to the local Y axis
	void translateYRelative(SFLOAT y);

	// Move the camera relative to the local Z axis
	void translateZRelative(SFLOAT z);

	// Rotate about the world X axis
	void rotateX(SFLOAT x);

	// Rotate about the world Y axis
	void rotateY(SFLOAT y);

	// Rotate about the world Z axis
	void rotateZ(SFLOAT z);

	// Rotate about the relative X axis
	void pitch(SFLOAT p);

	// Rotate about the relative Y axis
	void yaw(SFLOAT y);

	// Rotate about the relative Z axis
	void roll(SFLOAT r);

	// Set the camera rotation
	void setRotation(SFLOAT yaw, SFLOAT pitch, SFLOAT roll);

	// Look at a point in space
	void lookAt(const Vector pos, const Vector target, const Vector up);

	// Update the matrices based on current information and return the world-view matrix for this camera
	const Matrix viewProj();

private:
	// Directional properties
	//**********************************************
	
	// Position vector
	Vector _position;

	// Right vector
	Vector _right;
	
	// Up vector
	Vector _up;

	// Look/forward vector
	Vector _forward;

	Matrix _orientation;

	// Frustrum properties
	//**********************************************

	// Field of view
	SFLOAT _fovy;

	// Aspect ratio
	SFLOAT _aspect;

	// Near z
	SFLOAT _nearZ;

	// Far z
	SFLOAT _farZ;

	// Near window height

	// Far window height

	// Matrices
	//**********************************************
	
	// View matrix
	Matrix _view;

	// Projection matrix
	Matrix _proj;
};

#endif