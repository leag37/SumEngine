//*************************************************************************************************
// Title: SumCamera.cpp
// Author: Gael Huber
// Description: A basic camera. A camera in SumEngine has two methods of storing information. The
//	first is the externally exposed data, the second is the internally exposed data. The world and
//	projection matrices are designed to be entirely used by the rendering engine can cannot be
//	directly manipulated. All externally exposed orientation and positioning data is accomplished
//	through manipulable postion and scale vectors and an orientation quaternion. The view matrix
//	will periodically synchronize itself with the most recent data. 
//*************************************************************************************************
#include "SumCamera.h"

//*************************************************************************************************
// Constructor
//*************************************************************************************************
Camera::Camera()
	:	_position(VectorZero()), _right(gVIdentityR0), _up(gVIdentityR1), _forward(gVIdentityR2),
		_nearZ(0.0f), _farZ(0.0f), _aspect(0.0f), _fovy(0.0f),
		_view(MatrixIdentity()), _proj(MatrixIdentity()),
		_yawAngle(0.0f), _pitchAngle(0.0f), _rollAngle(0.0f),
		_isYawFixed(true)
{ 
	_keyboardDirection= VectorZero();
	_mouseSensitivity = -0.25f;
	_rotateYAxis = true;

	for(int i = 0; i < MAX_KEYS; ++i)
	{
		_keys[i] = 0;
	}
}

//*************************************************************************************************
// Destructor
//*************************************************************************************************
Camera::~Camera()
{ }

//*************************************************************************************************
// Set the lens
//*************************************************************************************************
void Camera::setLens(SFLOAT fovy, SFLOAT aspect, SFLOAT nearZ, SFLOAT farZ)
{
	_fovy = fovy;
	_aspect = aspect;
	_nearZ = nearZ;
	_farZ = farZ;

	_proj = MatrixPerspectiveFovLH(_fovy, _aspect, _nearZ, _farZ);
}

//*************************************************************************************************
// Retrieve the position
//*************************************************************************************************
Vector Camera::position()
{
	return _eye;//_orientation.r[3];//_position;
}

//*************************************************************************************************
// Set the position
//*************************************************************************************************
void Camera::setPosition(const Vector position)
{
	_eye = position;
//	_position = position;
}

//*************************************************************************************************
// Move the camera relative to world axes
//*************************************************************************************************
void Camera::translate(const Vector v)
{
	_position = Vec3Add(_position, v);
}

//*************************************************************************************************
// Move the camera along the X axis
//*************************************************************************************************
void Camera::translateX(SFLOAT x)
{
	Vector vX = {x, 0.0f, 0.0f, 0.0f};
	_position = Vec3Add(_position, vX);
}

//*************************************************************************************************
// Move the camera along the Y axis
//*************************************************************************************************
void Camera::translateY(SFLOAT y)
{
	Vector vY = {0.0f, y, 0.0f, 0.0f};
	_position = Vec3Add(_position, vY);
}

//*************************************************************************************************
// Move the camera along the Z axis
//*************************************************************************************************
void Camera::translateZ(SFLOAT z)
{
	Vector vZ = {0.0f, 0.0f, z, 0.0f};
	_position = Vec3Add(_position, vZ);
}

//*************************************************************************************************
// Move the camera relative to local axes
//*************************************************************************************************
void Camera::translateRelative(const Vector v)
{
	// Get the normalized axis vector
	Vector axes = Vec3Add(_right, _up);
	axes = Vec3Add(axes, _forward);
	axes = Vec3Normalize(axes);

	// Scale axes by vector
	axes = VectorMul(axes, v);

	// Move the camera by new translation vector
	_position = Vec3Add(_position, axes);
}

//*************************************************************************************************
// Move the camera relative to local X axis
//*************************************************************************************************
void Camera::translateXRelative(SFLOAT x)
{
	// Create vector from data
	Vector vX = VectorReplicate(x);

	// Multiply by the right axis to get the scale of movement
	vX = VectorMul(_right, vX);

	// Translate the camera
	_position = Vec3Add(_position, vX);

	// Set keyboard direction
	vX = VectorSet(x, 0.0f, 0.0f, 0.0f);
	_keyboardDirection = VectorAdd(_keyboardDirection, vX);
}

//*************************************************************************************************
// Move the camera relative to the local Y axis
//*************************************************************************************************
void Camera::translateYRelative(SFLOAT y)
{
	// Create vector from data
	Vector vY = VectorReplicate(y);

	// Multiply by up axis to get scale of movement
	vY = VectorMul(_up, vY);

	// Translate
	_position = Vec3Add(_position, vY);
}

//*************************************************************************************************
// Move the camera relative to the local Z axis
//*************************************************************************************************
void Camera::translateZRelative(SFLOAT z)
{
	// Create vector from data
	Vector vZ = VectorReplicate(z);

	// Multiply by forward axis to get scale of movement
	vZ = VectorMul(_forward, vZ);

	// Translate
	_position = Vec3Add(_position, vZ);
}

//*************************************************************************************************
// Rotate about the world X axis
//*************************************************************************************************
void Camera::rotateX(SFLOAT x)
{
	_pitchAngle += x;

	// Create rotation basis about X axis
	Matrix r = MatrixRotationX(x);
	Vector rotate = QuaternionRotationAxis(gVIdentityR0, x);

	// Transform the axis normals
	_right = QuaternionTransformVector(_right, rotate);
	_up = QuaternionTransformVector(_up, rotate);
	_forward = QuaternionTransformVector(_forward, rotate);
}

//*************************************************************************************************
// Rotate about the world Y axis
//*************************************************************************************************
void Camera::rotateY(SFLOAT y)
{
	_yawAngle += y;

	// Create rotation basis about Y axis
	Matrix r = MatrixRotationY(y);
	Vector rotate = QuaternionRotationAxis(gVIdentityR1, y);

	// Transform the axis normals
	_right = QuaternionTransformVector(_right, rotate);
	_up = QuaternionTransformVector(_up, rotate);
	_forward = QuaternionTransformVector(_forward, rotate);
}

//*************************************************************************************************
// Rotate about the world Z axis
//*************************************************************************************************
void Camera::rotateZ(SFLOAT z)
{
	// Create rotation basis about Y axis
	Matrix r = MatrixRotationZ(z);

	// Transform the axis normals
	_right = Vec3TransformNormal(_right, r);
	_up = Vec3TransformNormal(_up, r);
	_forward = Vec3TransformNormal(_forward, r);
}

//*************************************************************************************************
// Rotate about the relative X axis
//*************************************************************************************************
void Camera::pitch(SFLOAT p)
{
	// Rotate look and up about the right vector
	Matrix r = MatrixRotationAxis(_right, p);
	Vector rotation = QuaternionRotationAxis(_right, p);

	_up = QuaternionTransformVector(_up, rotation);
	_forward = QuaternionTransformVector(_forward, rotation);

	_pitchAngle += p;
}

//*************************************************************************************************
// Rotate about the relative Y axis
//*************************************************************************************************
void Camera::yaw(SFLOAT y)
{
	// Rotate right and forward about the up vector
	Matrix r = MatrixRotationAxis(_up, y);
	Vector rotation = QuaternionRotationAxis(_up, y);

	_right = QuaternionTransformVector(_right, rotation);
	_forward = QuaternionTransformVector(_forward, rotation);

	_yawAngle += y;

//	_right = Vec3TransformNormal(_right, r);
//	_forward = Vec3TransformNormal(_forward, r);
}

//*************************************************************************************************
// Rotate about the relative Z axis
//*************************************************************************************************
void Camera::roll(SFLOAT r)
{
	// Rotate right and up about the forward vector
	Matrix rot = MatrixRotationAxis(_forward, r);

	_right = Vec3TransformNormal(_right, rot);
	_up = Vec3TransformNormal(_up, rot);
}

//*************************************************************************************************
// Rotate by a yaw, a pitch, and a roll all at once
//*************************************************************************************************
void Camera::rotateYawPitchRoll(SFLOAT yaw, SFLOAT pitch, SFLOAT roll)
{
	Vector rotation = QuaternionRotationYawPitchRoll(yaw, pitch, roll);

	//_right = QuaternionTransformVector(_right, rotation);
	_up = QuaternionTransformVector(_up, rotation);
	_forward = QuaternionTransformVector(_forward, rotation);
}

//*************************************************************************************************
// Set the camera rotation
//*************************************************************************************************
void Camera::setRotation(SFLOAT yaw, SFLOAT pitch, SFLOAT roll)
{
	// Get the general rotation matrix
	Matrix r = MatrixRotationYawPitchRoll(yaw, pitch, roll);

	// Rotate each basis vector by the rotation matrix
	_right = Vec3TransformNormal(gVIdentityR0, r);
	_up = Vec3TransformNormal(gVIdentityR1, r);
	_forward = Vec3TransformNormal(gVIdentityR2, r);
}

//*************************************************************************************************
// Look at a point in space
//*************************************************************************************************
void Camera::lookAt(const Vector eye, const Vector lookAt, const Vector up)
{
	// Set eye and lookat parameters
	_eye = eye;
	_forward = Vec3Sub(lookAt, _eye);
	_forward = Vec3Normalize(_forward);
	_up = up;
}

//*************************************************************************************************
// Update the matrices based on current information and return the world-view matrix for this camera
//*************************************************************************************************
const Matrix Camera::viewProj()
{
	// Move eye by the velocity
	_eye = Vec3Add(_eye, _velocity);

	// Eye is position of camera
	Vector eye = _eye;

	// LookAt is the eye + forward
	Vector lookAt = Vec3Add(_eye, _forward);

	// Up is the up axis
	Vector up = _up;

	// Calculate view and world matrices
	_view = MatrixLookAtLH(eye, lookAt, up);
	_world = MatrixInverse(0, _view);

	// View projection matrix
	return MatrixMultiply(_view, _proj);
}

// Map a given keycode to a camera binding
void Camera::mapKey(SUINT keyCode, SUINT binding)
{
	_keys[binding] = keyCode;
}

// Update based on new input parameters
void Camera::updateInput(SFLOAT deltaTime)
{
	// Set deltaTime
	_deltaTime = deltaTime;

	// Check for keyboard input
	//**********************************************
	// Grab keyboard
	const InputDeviceKeyboard* keyboard = InputManager::getSingletonPtr()->keyboard();
	
	// Update velocity based on input, etc.
	_keyboardDirection = VectorZero();
	
	// Forward
	if(_keys[FORWARD] && keyboard->getKey(_keys[FORWARD]))
	{
		_keyboardDirection = VectorAdd(_keyboardDirection, VectorSet(0.0f, 0.0f, 1.0f, 0.0f));
	}
	// Back
	if(_keys[BACKWARD] && keyboard->getKey(_keys[BACKWARD]))
	{
		_keyboardDirection = VectorAdd(_keyboardDirection, VectorSet(0.0f, 0.0f, -1.0f, 0.0f));
	}

	// Left
	if(_keys[LEFT] && keyboard->getKey(_keys[LEFT]))
	{
		_keyboardDirection = VectorAdd(_keyboardDirection, VectorSet(-1.0f, 0.0f, 0.0f, 0.0f));
	}
	
	// Right
	if(_keys[RIGHT] && keyboard->getKey(_keys[RIGHT]))
	{
		_keyboardDirection = VectorAdd(_keyboardDirection, VectorSet(1.0f, 0.0f, 0.0f, 0.0f));
	}

	// Toggle axis
	if(_keys[TOGGLE_AXIS] && keyboard->getKeyPressed(_keys[TOGGLE_AXIS]))
	{
		_rotateYAxis = !_rotateYAxis;
	}

	// Check for mouse input
	//**********************************************
	// Grab mouse
	const InputDeviceMouse* mouse = InputManager::getSingletonPtr()->mouse();
	
	// Get rotation angles
	SFLOAT yawAngle = Math::ToRadian(mouse->relXf() * _mouseSensitivity);
	if(yawAngle != 0.0f)
	{
		rotateY(yawAngle);
	}
	
	SFLOAT pitchAngle = Math::ToRadian(mouse->relYf() * _mouseSensitivity);
	if(pitchAngle != 0.0f)
	{
		pitch(pitchAngle);
	}

	// Update the camera velocity
	updateVelocity();
}

void Camera::updateVelocity()
{
	// Check for velocity being equal to 0
	Vector acceleration = _keyboardDirection;
	if(VectorCompareNotEqual(acceleration, gVZero))
	{
		// Perform velocity update with euler integration
		acceleration = Vec3Normalize(_keyboardDirection);

		_velocity = VectorMul(acceleration, VectorReplicate(5.0f * _deltaTime));//VectorAdd(_velocity, acceleration);

		// If we have a fixed yaw, we must extract velocity into separate components
		if(_isYawFixed)
		{
			// Get the local forward velocity and the horizontal velocity
			Vector lForwardVelocity = VectorAnd(_velocity, gVZMask);
			Vector lSideVelocity = VectorAnd(_velocity, gVXMask);

			// Find the global forward velocity
			Vector forwardRotation = QuaternionCalculateRotation(_forward, gVIdentityR2);
			Vector gForwardVelocity = QuaternionTransformVector(lForwardVelocity, forwardRotation);

			// Find the global horizontal velocity
			Vector rightRotation = QuaternionCalculateRotation(_right, gVIdentityR0);
			Vector gSideVelocity = QuaternionTransformVector(lSideVelocity, rightRotation);

			// The velocity is the sum of these two velocities
			_velocity = VectorAdd(gForwardVelocity, gSideVelocity);
		}
	}
	else
	{
		_velocity = VectorZero();
	}

}
