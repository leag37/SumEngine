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
		_view(MatrixIdentity()), _proj(MatrixIdentity())
{ }

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
	return _position;
}

//*************************************************************************************************
// Set the position
//*************************************************************************************************
void Camera::setPosition(const Vector position)
{
	_position = position;
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
	// Create rotation basis about X axis
	Matrix r = MatrixRotationX(x);

	// Transform the axis normals
	_right = Vec3TransformNormal(_right, r);
	_up = Vec3TransformNormal(_up, r);
	_forward = Vec3TransformNormal(_forward, r);
}

//*************************************************************************************************
// Rotate about the world Y axis
//*************************************************************************************************
void Camera::rotateY(SFLOAT y)
{
	// Create rotation basis about Y axis
	Matrix r = MatrixRotationY(y);

	// Transform the axis normals
	_right = Vec3TransformNormal(_right, r);
	_up = Vec3TransformNormal(_up, r);
	_forward = Vec3TransformNormal(_forward, r);
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

	_up = Vec3TransformNormal(_up, r);
	_forward = Vec3TransformNormal(_forward, r);
}

//*************************************************************************************************
// Rotate about the relative Y axis
//*************************************************************************************************
void Camera::yaw(SFLOAT y)
{
	// Rotate right and forward about the up vector
	Matrix r = MatrixRotationAxis(_up, y);

	_right = Vec3TransformNormal(_right, r);
	_forward = Vec3TransformNormal(_forward, r);
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
void Camera::lookAt(const Vector pos, const Vector target, const Vector up)
{
	// Get the rotation matrix
	Matrix r = MatrixLookAtLH(pos, target, up);

	// Rotate each basis vector by the rotation matrix
	_right = Vec3TransformNormal(gVIdentityR0, r);
	_up = Vec3TransformNormal(gVIdentityR1, r);
	_forward = Vec3TransformNormal(gVIdentityR2, r);

	// Set position
	_position = r.r[3];
}

//*************************************************************************************************
// Update the matrices based on current information and return the world-view matrix for this camera
//*************************************************************************************************
const Matrix Camera::viewProj()
{
	// Cache vectors for view update
	Vector u = _up;
	Vector r = _right;
	Vector f = _forward;
	Vector p = _position;

	// Normalize the forward vector
	f = Vec3Normalize(f);

	// Compute a corrected up vector
	u = Vec3Cross(f, r);
	u = Vec3Normalize(u);

	// Compute a corrected right vector
	r = Vec3Cross(u, f);

	// Get translation components
	Vector x = Vec3Dot(p, r);
	x = VectorNegate(x);
	Vector y = Vec3Dot(p, u);
	y = VectorNegate(y);
	Vector z = Vec3Dot(p, f);
	z = VectorNegate(z);

	// Construct the view matrix from the various component vectors
	// R, U, F, P
	//
	// rx ry rz 0
	// ux uy uz 0
	// fx fy fz 0
	// px py pz 1
	//
	// V0 = movelh(R, U) => rx ry ux uy
	// V1 = unpackhi(R, U) => rz uz rw uw
	// V1 = unpacklo(V1, gVIdentityR3) => rz 0 uz 0
	//
	// V2 = movelh(F, P) => fx fy px py
	// V3 = unpackhi(F, P) => fz pz fw pw
	// V3 = unpacklo(V3, gVIdentityR1) => fz 0 pz 1
	//
	// M0 = movelh(V0, V1) => rx ry rz 0
	// M1 = movehl(V1, V0) => ux uy uz 0
	// M2 = movelh(V2, V3) => fx fy fz 0
	// M3 = movehl(V3, V2) => px py pz 1
	Vector v0 = _mm_movelh_ps(r, u);
	Vector v1 = _mm_unpackhi_ps(r, u);
	v1 = _mm_unpacklo_ps(v1, p);

	Vector v2 = _mm_movelh_ps(f, p);
	Vector v3 = _mm_unpackhi_ps(f, p);
	v3 = _mm_unpacklo_ps(v3, gVIdentityR1);

	_view.r[0] = _mm_movelh_ps(v0, v1);
	_view.r[1] = _mm_movehl_ps(v1, v0);
	_view.r[2] = _mm_movelh_ps(v2, v3);
	_view.r[3] = _mm_movehl_ps(v3, v2);

	// View projection matrix
	return MatrixMultiply(_view, _proj);
}
