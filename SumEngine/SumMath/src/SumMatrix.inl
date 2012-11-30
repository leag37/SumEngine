//*************************************************************************************************
// Title: SumMatrix.inl
// Author: Gael Huber
// Description: Matrix mathematics functions.
//*************************************************************************************************

//*************************************************************************************************
// Base constructor
//*************************************************************************************************
SUMINLINE Matrix::Matrix()
{ }

//*************************************************************************************************
// Constructor
//*************************************************************************************************
SUMINLINE Matrix::Matrix(const Vector r0, const Vector r1, const Vector r2, const Vector r3)
{
	r[0] = r0;
	r[1] = r1;
	r[2] = r2;
	r[3] = r3;
}

//*************************************************************************************************
// Constructor
//*************************************************************************************************
SUMINLINE Matrix::Matrix(SFLOAT m11, SFLOAT m12, SFLOAT m13, SFLOAT m14,
		SFLOAT m21, SFLOAT m22, SFLOAT m23, SFLOAT m24,
		SFLOAT m31, SFLOAT m32, SFLOAT m33, SFLOAT m34,
		SFLOAT m41, SFLOAT m42, SFLOAT m43, SFLOAT m44)
{
	r[0] = VectorSet(m11, m12, m13, m14);
	r[1] = VectorSet(m21, m22, m23, m24);
	r[2] = VectorSet(m31, m32, m33, m34);
	r[3] = VectorSet(m41, m42, m43, m44);
}

//*************************************************************************************************
// Constructor
//*************************************************************************************************
SUMINLINE Matrix::Matrix(const SFLOAT* m)
{
	r[0] = _mm_loadu_ps(m);
	r[1] = _mm_loadu_ps(m + 4);
	r[2] = _mm_loadu_ps(m + 8);
	r[3] = _mm_loadu_ps(m + 12);
}

//*************************************************************************************************
// Accessor
//*************************************************************************************************
SUMINLINE SFLOAT Matrix::operator() (SUINT row, SUINT column) const
{
	return m[row][column];
}

//*************************************************************************************************
// Array-accessor
//*************************************************************************************************
SUMINLINE SFLOAT& Matrix::operator() (SUINT row, SUINT column)
{
	return m[row][column];
}

//*************************************************************************************************
// Assignment operator
//*************************************************************************************************
SUMINLINE Matrix& Matrix::operator=(const Matrix& m)
{
	r[0] = m.r[0];
	r[1] = m.r[1];
	r[2] = m.r[2];
	r[3] = m.r[3];
	return *this;
}

//*************************************************************************************************
// Matrix multiplication
//*************************************************************************************************
SUMINLINE Matrix& Matrix::operator*=(const Matrix& m)
{
	*this = MatrixMultiply(*this, m);
	return *this;
}

//*************************************************************************************************
// Matrix multiplication
//*************************************************************************************************
SUMINLINE Matrix Matrix::operator*(const Matrix& m) const
{
	return MatrixMultiply(*this, m);
}


//*************************************************************************************************
// Identity matrix
//*************************************************************************************************
SUMINLINE Matrix MatrixIdentity()
{
	Matrix m;
	m.r[0] = gVIdentityR0;
	m.r[1] = gVIdentityR1;
	m.r[2] = gVIdentityR2;
	m.r[3] = gVIdentityR3;
	return m;
}

//*************************************************************************************************
// Is identity
//*************************************************************************************************
SUMINLINE bool MatrixIsIdentity(const Matrix& m)
{
	// Get equalities for all the rows
	Vector vTemp1 = _mm_cmpeq_ps(m.r[0], gVIdentityR0);
	Vector vTemp2 = _mm_cmpeq_ps(m.r[1], gVIdentityR1);
	Vector vTemp3 = _mm_cmpeq_ps(m.r[2], gVIdentityR2);
	Vector vTemp4 = _mm_cmpeq_ps(m.r[3], gVIdentityR3);

	// Find aggregate equalities
	vTemp1 = _mm_and_ps(vTemp1, vTemp2);
	vTemp3 = _mm_and_ps(vTemp3, vTemp4);
	vTemp1 = _mm_and_ps(vTemp1, vTemp3);

	// Find bit mask
	return _mm_movemask_ps(vTemp1) == 0x0F;
}

//*************************************************************************************************
// Sum of two matrices
//*************************************************************************************************
SUMINLINE Matrix MatrixAdd(const Matrix& m1, const Matrix& m2)
{
	Matrix m;
	m.r[0] = _mm_add_ps(m1.r[0], m2.r[0]);
	m.r[1] = _mm_add_ps(m1.r[1], m2.r[1]);
	m.r[2] = _mm_add_ps(m1.r[2], m2.r[2]);
	m.r[3] = _mm_add_ps(m1.r[3], m2.r[3]);
	return m;
}

//*************************************************************************************************
// Difference between two matrices
//*************************************************************************************************
SUMINLINE Matrix MatrixSub(const Matrix& m1, const Matrix& m2)
{
	Matrix m;
	m.r[0] = _mm_sub_ps(m1.r[0], m2.r[0]);
	m.r[1] = _mm_sub_ps(m1.r[1], m2.r[1]);
	m.r[2] = _mm_sub_ps(m1.r[2], m2.r[2]);
	m.r[3] = _mm_sub_ps(m1.r[3], m2.r[3]);
	return m;
}

//*************************************************************************************************
// Scale a matrix
//*************************************************************************************************
SUMINLINE Matrix MatrixScale(const Matrix& m, SFLOAT s)
{
	Vector vS = _mm_set1_ps(s);
	return MatrixScale(m, vS);
}

//*************************************************************************************************
// Scale a matrix
//*************************************************************************************************
SUMINLINE Matrix MatrixScale(const Matrix& m, const Vector s)
{
	Matrix scale;
	scale.r[0] = _mm_mul_ps(m.r[0], s);
	scale.r[1] = _mm_mul_ps(m.r[1], s);
	scale.r[2] = _mm_mul_ps(m.r[2], s);
	scale.r[3] = _mm_mul_ps(m.r[3], s);
	return scale;
}