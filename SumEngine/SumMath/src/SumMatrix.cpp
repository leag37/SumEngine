//*************************************************************************************************
// Title: SumMatrix.cpp
// Author: Gael Huber
// Description: Matrix math functions.
//*************************************************************************************************
#include "SumMatrix.h"

//*************************************************************************************************
// Determinant
//
//11 12 13 14
//21 22 23 24
//31 32 33 34
//41 42 43 44
//
//11 |22 23 24| - 12 |21 23 24| + 13 |21 22 24| - 14 |21 22 23|
//   |32 33 34|	   |31 33 34|	   |31 32 34|      |31 32 33|
//   |42 43 44|      |41 43 44|      |41 42 44|      |41 42 43|
//
//+11 ( 22 |33 34| - 23 |32 34| + 24 |32 33|)
//		 |43 44|	  |42 44|      |42 43|
//-12 ( 21 |33 34| - 23 |31 34| + 24 |31 33|)
//		 |43 44|      |41 44|      |41 43|
//+13 ( 21 |32 34| - 22 |31 34| + 24 |31 32|)
//	     |42 44|      |41 44|      |41 42|
//-14 ( 21 |32 33| - 22 |31 33| + 23 |31 32|)
//		 |42 43|      |41 43|      |41 42|
//
//+11 ( 22 (33.44 - 34.43) - 23 (32.44 - 34.42) + 24 (32.43 - 33.42))
//-12 ( 21 (33.44 - 34.43) - 23 (31.44 - 34.41) + 24 (31.43 - 33.41))
//+13 ( 21 (32.44 - 34.42) - 22 (31.44 - 34.41) + 24 (31.42 - 32.41))
//-14 ( 21 (32.43 - 33.42) - 22 (31.43 - 33.41) + 23 (31.42 - 32.41))
//
// Phase 1 - primary inner products
// v1 = zzyy -> 3
// v2 = wwwz -> 4
// v3 = yxxx -> 3
// v4 = wwwz -> 4
// v5 = yxxx -> 3
// v6 = zzyy -> 4
//
// p0 = v1.v2
// p1 = v3.v4
// p2 = v5.v6
//
// v1 = wwwz -> 3
// v2 = zzyy -> 4
// v3 = wwwz -> 3
// v4 = yxxx -> 4
// v5 = zzyy -> 3
// v6 = yxxx -> 4
//
// v1 = v1.v2
// v3 = v3.v4
// v5 = v5.v6
//
// Phase 2 - difference of inner products
// p0 = p0 - v1
// p1 = p1 - v3
// p2 = p2 - v5
//
// Phase 3 - secondary inner products
// v1 = yxxx -> 2
// v2 = zzyy -> 2
// v3 = wwwz -> 2
//
// p0 = p0.v1
// p1 = p1.v1
// p2 = p2.v2
//
// Phase 4 - aggregate sum
// p0 = p0 - p1
// p0 = p0 + p2
//
// Final product
// p1 = r1 * +-+-
// result = dot(p0, p1)
//*************************************************************************************************
Vector MatrixDeterminant(const Matrix& m)
{
	// Phase 1 - primary inner products
	// v1 = zzyy -> 3
	// v2 = wwwz -> 4
	// v3 = yxxx -> 3
	// v4 = wwwz -> 4
	// v5 = yxxx -> 3
	// v6 = zzyy -> 4
	//
	// p0 = v1.v2
	// p1 = v3.v4
	// p2 = v5.v6
	
	Vector v1 = _mm_shuffle_ps(m.r[2], m.r[2], _MM_SHUFFLE(1, 1, 2, 2));
	Vector v2 = _mm_shuffle_ps(m.r[3], m.r[3], _MM_SHUFFLE(2, 3, 3, 3));
	Vector v3 = _mm_shuffle_ps(m.r[2], m.r[2], _MM_SHUFFLE(0, 0, 0, 1));
	Vector v4 = _mm_shuffle_ps(m.r[3], m.r[3], _MM_SHUFFLE(2, 3, 3, 3));
	Vector v5 = _mm_shuffle_ps(m.r[2], m.r[2], _MM_SHUFFLE(0, 0, 0, 1));
	Vector v6 = _mm_shuffle_ps(m.r[3], m.r[3], _MM_SHUFFLE(1, 1, 2, 2));

	Vector p0 = _mm_mul_ps(v1, v2);
	Vector p1 = _mm_mul_ps(v3, v4);
	Vector p2 = _mm_mul_ps(v5, v6);
	
	// Phase 2 - difference of inner products
	// p0 = p0 - v1
	// p1 = p1 - v3
	// p2 = p2 - v5
	
	p0 = _mm_sub_ps(p0, v1);
	p1 = _mm_sub_ps(p1, v3);
	p2 = _mm_sub_ps(p2, v5);

	// Phase 3 - secondary inner products
	// v1 = yxxx -> 2
	// v2 = zzyy -> 2
	// v3 = wwwz -> 2
	//
	// p0 = p0.v1
	// p1 = p1.v2
	// p2 = p2.v3
	
	v1 = _mm_shuffle_ps(m.r[1], m.r[1], _MM_SHUFFLE(0, 0, 0, 1));
	v2 = _mm_shuffle_ps(m.r[1], m.r[1], _MM_SHUFFLE(1, 1, 2, 2));
	v3 = _mm_shuffle_ps(m.r[1], m.r[1], _MM_SHUFFLE(2, 3, 3, 3));

	p0 = _mm_mul_ps(p0, v1);
	p1 = _mm_mul_ps(p1, v2);
	p2 = _mm_mul_ps(p2, v3);

	// Phase 4 - aggregate sum
	// p0 = p0 - p1
	// p0 = p0 + p2
	
	p0 = _mm_sub_ps(p0, p1);
	p0 = _mm_add_ps(p0, p2);

	// Final product
	// p1 = r1 * +-+-
	// result = dot(p0, p1)
	p1 = _mm_mul_ps(m.r[0], gVDeterminantNegate);
	return Vec4Dot(p0, p1);
}

//*************************************************************************************************
// Decompose 
//*************************************************************************************************
//SBOOL MatrixDecompose(Vector* pOutScale, Vector* pOutRotation, Vector* pOutTranslation, const Matrix& m)
//{
//	// Create row vector u, v, and w
//	Vector u = _mm_load_ps(&m._11);
//	Vector v = _mm_load_ps(&m._21);
//	Vector w = _mm_load_ps(&m._31);
//
//	// Create orthonormal vectors 
//	Vector s1 = Vec3Length(u);
//	if(Vec3Equal(s1, gVZero))
//		return false;
//
//	Vector u0 = VectorReciprocal(s1);
//	u0 = _mm_mul_ps(u, u0);
//
//	Vector temp = Vec3Dot(v, u0);
//	temp = _mm_mul_ps(temp, u0);
//	temp = _mm_sub_ps(v, temp);
//	Vector s2 = Vec3Length(temp);
//	if(Vec3Equal(s2, gVZero))
//		return false;
//
//	Vector v0 = VectorReciprocal(s2);
//	v0 = _mm_mul_ps(v0, temp);
//	
//	temp = Vec3Dot(w, u0);
//	temp = _mm_mul_ps(temp, u0);
//	temp = _mm_sub_ps(w, temp);
//	Vector temp1 = Vec3Dot(w, v0);
//	temp1 = _mm_mul_ps(temp1, v0);
//	temp = _mm_sub_ps(temp, temp1);
//	Vector s3 = Vec3Length(temp);
//	if(Vec3Equal(s3, gVZero))
//		return false;
//
//	Vector w0 = VectorReciprocal(s3);
//	w0 = _mm_mul_ps(temp, w0);
//
//	// Populate reciprocal matrix
//	Matrix r = Matrix(u0, v0, w0, gVIdentityR3);
//	Vector det = MatrixDeterminant(r);
//	if(Vec4Equal(det, gVNegOne))
//	{
//		r.r[2] = _mm_mul_ps(r.r[2], gV3Negate);
//		s3 = _mm_mul_ps(s3, gVNegOne);
//	}
//
//	// Populate scale
//	temp = _mm_unpacklo_ps(s1, s2);
//	temp = _mm_shuffle_ps(temp, s3, _MM_SHUFFLE(0, 0, 1, 0));
//	*pOutScale = temp;
//
//	// Populate quaternion
//	*pOutRotation = QuaternionRotationMatrix(r);
//
//	// Populate translation
//	*pOutTranslation = _mm_load_ps(r.m[3]);
//
//	return true;
//}

//*************************************************************************************************
// Transpose
//
// [11 12 13 14]
// [21 22 23 24]
// [31 32 33 34]
// [41 42 43 44]
//
// [11 21 31 41]
// [12 22 32 42]
// [13 23 33 43]
// [14 24 34 44]
//
// v1 = _mm_unpacklo_ps(r1, r2)
// v1 = [11 21 12 22]
// v2 = _mm_unpacklo_ps(r3, r4)
// v2 = [31 41 32 42]
// m1 = _mm_shuffle_ps(v1, v2, _MM_SHUFFLE(1, 0, 1, 0))
// m2 = _mm_shuffle_ps(v1, v2, _MM_SHUFFLE(3, 2, 3, 2))
//
// v1 = _mm_unpackhi_ps(r1, r2)
// v1 = [13 23 14 24]
// v2 = _mm_unpackhi_ps(r3, r4)
// v2 = [33 43 34 44]
// m3 = _mm_shuffle_ps(v1, v2, _MM_SHUFFLE(1, 0, 1, 0))
// m4 = _mm_shuffle_ps(v1, v2, _MM_SHUFFLE(3, 2, 3, 2))
//*************************************************************************************************
Matrix MatrixTranspose(const Matrix& m)
{
	// Unpack lo and solve for first two rows
	Vector vTemp1 = _mm_unpacklo_ps(m.r[0], m.r[1]);
	Vector vTemp2 = _mm_unpacklo_ps(m.r[2], m.r[3]);

	Matrix result;
	result.r[0] = _mm_movelh_ps(vTemp1, vTemp2);
	result.r[1] = _mm_movehl_ps(vTemp2, vTemp1);

	// Unpack hi and solve for last two rows
	vTemp1 = _mm_unpackhi_ps(m.r[0], m.r[1]);
	vTemp2 = _mm_unpackhi_ps(m.r[2], m.r[3]);

	result.r[2] = _mm_movelh_ps(vTemp1, vTemp2);
	result.r[3] = _mm_movehl_ps(vTemp2, vTemp1);

	return result;
}

//*************************************************************************************************
// Multiply
//
//[a b c d]
//[e f g h]
//[i j k l]
//[m n o p]
//
//[q r s t] -> shuffle
//[u v w x]
//[y z 0 1]
//[2 3 4 5]
//
//A*B = 
//[aq+bu+cy+d2 ar+bv+cz+d3 as+bw+c0+d4 at+bx+c1+d5]
//[eq+fu+gy+h2 er+fv+gz+h3 es+fw+g0+h4 et+fx+g1+h5]
//...
//
// Process
//---------
//
//Desired matrix:
//[aq ar as at]
//[bu bv bw bx]
//[cy cz c0 c1]
//[d2 d3 d4 d5]
//
//to yield:
//[a a a a]  -> splat a, b, c, d
//[b b b b]
//[c c c c]
//[d d d d]
//
//[q r s t]
//[u v w x]
//[y z 0 1]
//[2 3 4 5]
//
//// For one row of matrix MResult
//1. Splat a, b, c, d into vTemp1-4
//2. Multiply vTemp1-4 . m2
//3. m.r[index] = vTemp1 + vTemp2 + vTemp3 + vTemp4
//*************************************************************************************************
Matrix MatrixMultiply(const Matrix& m1, const Matrix& m2)
{
	Matrix m;
	
	// Row 1
	Vector vTemp1 = _mm_load1_ps(&m1._11);
	Vector vTemp2 = _mm_load1_ps(&m1._12);
	Vector vTemp3 = _mm_load1_ps(&m1._13);
	Vector vTemp4 = _mm_load1_ps(&m1._14);

	vTemp1 = _mm_mul_ps(vTemp1, m2.r[0]);
	vTemp2 = _mm_mul_ps(vTemp2, m2.r[1]);
	vTemp3 = _mm_mul_ps(vTemp3, m2.r[2]);
	vTemp4 = _mm_mul_ps(vTemp4, m2.r[3]);

	vTemp1 = _mm_add_ps(vTemp1, vTemp2);
	vTemp3 = _mm_add_ps(vTemp3, vTemp4);
	m.r[0] = _mm_add_ps(vTemp1, vTemp3);

	// Row 2
	vTemp1 = _mm_load1_ps(&m1._21);
	vTemp2 = _mm_load1_ps(&m1._22);
	vTemp3 = _mm_load1_ps(&m1._23);
	vTemp4 = _mm_load1_ps(&m1._24);

	vTemp1 = _mm_mul_ps(vTemp1, m2.r[0]);
	vTemp2 = _mm_mul_ps(vTemp2, m2.r[1]);
	vTemp3 = _mm_mul_ps(vTemp3, m2.r[2]);
	vTemp4 = _mm_mul_ps(vTemp4, m2.r[3]);

	vTemp1 = _mm_add_ps(vTemp1, vTemp2);
	vTemp3 = _mm_add_ps(vTemp3, vTemp4);
	m.r[1] = _mm_add_ps(vTemp1, vTemp3);

	// Row 3
	vTemp1 = _mm_load1_ps(&m1._31);
	vTemp2 = _mm_load1_ps(&m1._32);
	vTemp3 = _mm_load1_ps(&m1._33);
	vTemp4 = _mm_load1_ps(&m1._34);

	vTemp1 = _mm_mul_ps(vTemp1, m2.r[0]);
	vTemp2 = _mm_mul_ps(vTemp2, m2.r[1]);
	vTemp3 = _mm_mul_ps(vTemp3, m2.r[2]);
	vTemp4 = _mm_mul_ps(vTemp4, m2.r[3]);

	vTemp1 = _mm_add_ps(vTemp1, vTemp2);
	vTemp3 = _mm_add_ps(vTemp3, vTemp4);
	m.r[2] = _mm_add_ps(vTemp1, vTemp3);

	// Row 4
	vTemp1 = _mm_load1_ps(&m1._41);
	vTemp2 = _mm_load1_ps(&m1._42);
	vTemp3 = _mm_load1_ps(&m1._43);
	vTemp4 = _mm_load1_ps(&m1._44);

	vTemp1 = _mm_mul_ps(vTemp1, m2.r[0]);
	vTemp2 = _mm_mul_ps(vTemp2, m2.r[1]);
	vTemp3 = _mm_mul_ps(vTemp3, m2.r[2]);
	vTemp4 = _mm_mul_ps(vTemp4, m2.r[3]);

	vTemp1 = _mm_add_ps(vTemp1, vTemp2);
	vTemp3 = _mm_add_ps(vTemp3, vTemp4);
	m.r[3] = _mm_add_ps(vTemp1, vTemp3);

	return m;
}

//*************************************************************************************************
// Multiply, followed by a transpose T(M1 * M2) 
//*************************************************************************************************
Matrix MatrixMultiplyTranspose(const Matrix& m1, const Matrix& m2)
{
	Matrix result = MatrixMultiply(m1, m2);
	return MatrixTranspose(result);
}

//*************************************************************************************************
// Inverse
//
// a b c d
// e f g h
// i j k l
// m n o p
//
// POSITIVES
// vTemp1 = aabb ghgh -> ag ah bg bh
// vTemp2 = aabb klkl -> ak al bk bl
// vTemp3 = aabb opop -> ao ap bo bp
//
// vTemp4 = aceg jljl -> aj cl ej gl
// vTemp5 = aceg npnp -> an cp en gp
// vTemp6 = acik fhnp -> af ch in kp
//
// vTemp7 = eeff klkl -> ek el fk fl
// vTemp8 = eeff opop -> eo ep fo fp
// vTemp9 = iijj opop -> io ip jo jp
//
// NEGATIVES
// vTemp10 = mmnn cdcd -> mc md nc nd
// vTemp11 = mmnn ghgh -> mg mh ng nh
// vTemp12 = mmnn klkl -> mk ml nk nl
//
// vTemp13 = ikik bdfh -> ib kd if kh
// vTemp14 = momo bdfh -> mb od mf oh
// vTemp15 = egmo bdjl -> eb gd mj ol
//
// vTemp16 = iijj cdcd -> ic id jc jd
// vTemp17 = iijj ghgh -> ig ih jg jh
// vTemp18 = eeff cdcd -> ec ed fc fd
//
// vTemp1-vTemp18 -> ag-ec ah-ed bg-fc bh-fd
// vTemp2-vTemp16 -> ak-ci al-di bk-cj bl-dj
// vTemp3-vTemp10 -> ao-cm ap-dm bo-cn bp-dn
// vTemp4-vTemp13 -> aj-bi cl-dk ej-fi gl-hk
// vTemp5-vTemp14 -> an-bm cp-do en-mf gp-ho
// vTemp6-vTemp15 -> af-eb ch-dg in-mj kp-lo
// vTemp7-vTemp17 -> ek-gi el-hi fk-gj fl-hj
// vTemp8-vTemp11 -> eo-gm ep-mh fo-gn fp-hn
// vTemp9-vTemp12 -> io-km ip-ml jo-kn jp-ln
//
//Calc row 0 det values
//00  01  02  03
//6.3 6.3 9.3 9.2
//9.3 9.1 9.1 9.0
//9.2 9.0 6.2 6.2
//5.3 5.3 8.3 8.2
//8.3 8.1 8.1 8.0
//8.2 8.0 5.2 5.2
//4.3 4.3 7.3 7.2
//7.3 7.1 7.1 7.0
//7.2 7.0 4.2 4.2
//
//feee
//ggff
//hhhg
//jiii
//kkjj
//lllk
//nmmm
//oonn
//pppo
//
//Calc row 1 det vectors
//10  11  12  13
//6.3 6.3 9.3 9.2
//9.3 9.1 9.1 9.0
//9.2 9.0 6.2 6.2
//5.1 5.1 3.3 3.2
//3.3 3.1 3.1 3.0
//3.2 3.0 5.0 5.0
//4.1 4.1 2.3 2.2
//2.3 2.1 2.1 2.0
//2.2 2.0 4.0 4.0
//
//baaa
//ccbb
//dddc
//jiii
//kkjj
//lllk
//nmmm
//oonn
//pppo
//
//Calc row 2 det vectors
//20  21  22  23
//5.3 5.3 8.3 8.2
//8.3 8.1 8.1 8.0
//8.2 8.0 5.2 5.2
//5.1 5.1 3.3 3.2
//3.3 3.1 3.1 3.0
//3.2 3.0 5.0 5.0
//6.1 6.1 1.3 1.2
//1.3 1.1 1.1 1.0
//1.2 1.0 6.0 6.0
//
//baaa
//ccbb
//dddc
//feee
//ggff
//hhhg
//nmmm
//oonn
//pppo
//
//Calc row 3 det vectors
//30  31  32  33
//4.3 4.3 7.3 7.2
//7.3 7.1 7.1 7.0
//7.2 7.0 4.2 4.2
//4.1 4.1 2.3 2.2
//2.3 2.1 2.1 2.0
//2.2 2.0 4.0 4.0
//6.1 6.1 1.3 1.2
//1.3 1.1 1.1 1.0
//1.2 1.0 6.0 6.0
//
//baaa
//ccbb
//dddc
//feee
//ggff
//hhhg
//jiii
//kkjj
//lllk
//*************************************************************************************************
Matrix MatrixInverse(Vector* pDeterminant, const Matrix& m)
{
	// Cache rows
	Vector r0 = m.r[0];
	Vector r1 = m.r[1];
	Vector r2 = m.r[2];
	Vector r3 = m.r[3];

	// Calculate possible 2x2 determinant values
	Vector vTemp00 = _mm_unpacklo_ps(r0, r0);							// aabb
	Vector vTemp01 = _mm_movehl_ps(r1, r1);								// ghgh
	Vector vTemp02 = _mm_movehl_ps(r2, r2);								// klkl
	Vector vTemp03 = _mm_movehl_ps(r3, r3);								// opop
	Vector vTemp04 = _mm_shuffle_ps(r0, r1, _MM_SHUFFLE(2, 0, 2, 0));	// aceg
	Vector vTemp05 = _mm_shuffle_ps(r2, r2, _MM_SHUFFLE(3, 1, 3, 1));	// jljl
	Vector vTemp06 = _mm_shuffle_ps(r3, r3, _MM_SHUFFLE(3, 1, 3, 1));	// npnp
	Vector vTemp07 = _mm_shuffle_ps(r0, r2, _MM_SHUFFLE(2, 0, 2, 0));	// acik
	Vector vTemp08 = _mm_shuffle_ps(r1, r3, _MM_SHUFFLE(3, 1, 3, 1));	// fhnp
	Vector vTemp09 = _mm_unpacklo_ps(r1, r1);							// eeff
	Vector vTemp10 = _mm_unpacklo_ps(r2, r2);							// iijj
	Vector vTemp11 = _mm_unpacklo_ps(r3, r3);							// mmnn
	Vector vTemp12 = _mm_movehl_ps(r0, r0);								// cdcd
	Vector vTemp13 = _mm_shuffle_ps(r2, r2, _MM_SHUFFLE(2, 0, 2, 0));	// ikik
	Vector vTemp14 = _mm_shuffle_ps(r0, r1, _MM_SHUFFLE(3, 1, 3, 1));	// bdfh
	Vector vTemp15 = _mm_shuffle_ps(r3, r3, _MM_SHUFFLE(2, 0, 2, 0));	// momo
	Vector vTemp16 = _mm_shuffle_ps(r1, r3, _MM_SHUFFLE(2, 0, 2, 0));	// egmo
	Vector vTemp17 = _mm_shuffle_ps(r0, r2, _MM_SHUFFLE(3, 1, 3, 1));	// bdjl

	// aceg jljl	ikik bdfh
	Vector vPos = VectorMul(vTemp04, vTemp05);
	Vector vNeg = VectorMul(vTemp13, vTemp14);
	Vector vTemp4 = VectorSub(vPos, vNeg);

	// aceg npnp	momo bdfh
	vPos = VectorMul(vTemp04, vTemp06);
	vNeg = VectorMul(vTemp15, vTemp14);
	Vector vTemp5 = VectorSub(vPos, vNeg);
	
	// acik fhnp	egmo bdjl
	vPos = VectorMul(vTemp07, vTemp08);
	vNeg = VectorMul(vTemp16, vTemp17);
	Vector vTemp6 = VectorSub(vPos, vNeg);
	
	// eeff klkl	iijj ghgh
	vPos = VectorMul(vTemp09, vTemp02);
	vNeg = VectorMul(vTemp10, vTemp01);
	Vector vTemp7 = VectorSub(vPos, vNeg);
	
	// eeff opop	mmnn ghgh	eo ep fo fp -> mg mh ng nh
	vPos = VectorMul(vTemp09, vTemp03);
	vNeg = VectorMul(vTemp11, vTemp01);
	Vector vTemp8 = VectorSub(vPos, vNeg);
	
	// iijj opop	mmnn klkl
	vPos = VectorMul(vTemp10, vTemp03);
	vNeg = VectorMul(vTemp11, vTemp02);
	Vector vTemp9 = VectorSub(vPos, vNeg);
	
	// Build matrix of minors
	//--------------------------
	// Create row constants
	vTemp00 = _mm_shuffle_ps(r0, r0, _MM_SHUFFLE(0, 0, 0, 1));	// baaa
	vTemp01 = _mm_shuffle_ps(r0, r0, _MM_SHUFFLE(1, 1, 2, 2));	// ccbb
	vTemp02 = _mm_shuffle_ps(r0, r0, _MM_SHUFFLE(2, 3, 3, 3));	// dddc
	vTemp03 = _mm_shuffle_ps(r1, r1, _MM_SHUFFLE(0, 0, 0, 1));	// feee
	vTemp04 = _mm_shuffle_ps(r1, r1, _MM_SHUFFLE(1, 1, 2, 2));	// ggff
	vTemp05 = _mm_shuffle_ps(r1, r1, _MM_SHUFFLE(2, 3, 3, 3));	// hhhg

	// Calculate row 0 determinant values
	Vector vTR0 = _mm_shuffle_ps(vTemp6, vTemp9, _MM_SHUFFLE(2, 3, 3, 3));
	vTR0 = VectorMul(vTR0, vTemp03);
	Vector vTR1 = _mm_shuffle_ps(vTemp9, vTemp9, _MM_SHUFFLE(0, 1, 1, 3));
	vTR1 = VectorMul(vTR1, vTemp04);
	vTR0 = VectorSub(vTR0, vTR1);

	vTR1 = _mm_shuffle_ps(vTemp9, vTemp6, _MM_SHUFFLE(2, 2, 0, 2));
	vTR1 = VectorMul(vTR1, vTemp05);
	Vector vRes0 = VectorAdd(vTR0, vTR1);
	
	// Calculate row 1 determinant values
	vTR0 = _mm_shuffle_ps(vTemp6, vTemp9, _MM_SHUFFLE(2, 3, 3, 3));
	vTR0 = VectorMul(vTR0, vTemp00);
	vTR1 = _mm_shuffle_ps(vTemp9, vTemp9, _MM_SHUFFLE(0, 1, 1, 3));
	vTR1 = VectorMul(vTR1, vTemp01);
	vTR0 = VectorSub(vTR0, vTR1);

	vTR1 = _mm_shuffle_ps(vTemp9, vTemp6, _MM_SHUFFLE(2, 2, 0, 2));
	vTR1 = VectorMul(vTR1, vTemp02);
	Vector vRes1 = VectorAdd(vTR0, vTR1);

	// Calculate row 2 determinant values
	vTR0 = _mm_shuffle_ps(vTemp5, vTemp8, _MM_SHUFFLE(2, 3, 3, 3));
	vTR0 = VectorMul(vTR0, vTemp00);
	vTR1 = _mm_shuffle_ps(vTemp8, vTemp8, _MM_SHUFFLE(0, 1, 1, 3));
	vTR1 = VectorMul(vTR1, vTemp01);
	vTR0 = VectorSub(vTR0, vTR1);

	vTR1 = _mm_shuffle_ps(vTemp8, vTemp5, _MM_SHUFFLE(2, 2, 0, 2));
	vTR1 = VectorMul(vTR1, vTemp02);
	Vector vRes2 = VectorAdd(vTR0, vTR1);

	// Calculate row 3 determinant values
	vTR0 = _mm_shuffle_ps(vTemp4, vTemp7, _MM_SHUFFLE(2, 3, 3, 3));
	vTR0 = VectorMul(vTR0, vTemp00);
	vTR1 = _mm_shuffle_ps(vTemp7, vTemp7, _MM_SHUFFLE(0, 1, 1, 3));
	vTR1 = VectorMul(vTR1, vTemp01);
	vTR0 = VectorSub(vTR0, vTR1);

	vTR1 = _mm_shuffle_ps(vTemp7, vTemp4, _MM_SHUFFLE(2, 2, 0, 2));
	vTR1 = VectorMul(vTR1, vTemp02);
	Vector vRes3 = VectorAdd(vTR0, vTR1);

	// Cache minors and create matrix of cofactors
	vRes0 = VectorMul(vRes0, gVNegateYW);
	vRes1 = VectorMul(vRes1, gVNegateXZ);
	vRes2 = VectorMul(vRes2, gVNegateYW);
	vRes3 = VectorMul(vRes3, gVNegateXZ);
	Matrix res = Matrix(vRes0, vRes1, vRes2, vRes3);

	// Adjugate of cofactor
	res = MatrixTranspose(res);

	// Find determinant of original matrix
	vTR0 = VectorMul(vRes0, r0);	// a b c d
	vTR1 = _mm_movehl_ps(vTR0, vTR0);	// c d c d
	vTR0 = VectorAdd(vTR0, vTR1);	// a+c b+d c+c d+d
	vTR1 = _mm_shuffle_ps(vTR0, vTR0, _MM_SHUFFLE(3, 3, 0, 1));
	vTR0 = VectorAdd(vTR0, vTR1);	// a+c+b+d b+c+a+c c+c+d+d d+d+d+d
	vTR0 = _mm_shuffle_ps(vTR0, vTR0, _MM_SHUFFLE(0, 0, 0, 0));
	*pDeterminant = vTR0;

	// Scale matrix by 1 over determinant
	vTR0 = VectorDiv(gVOne, vTR0);
	res.r[0] = VectorMul(res.r[0], vTR0);
	res.r[1] = VectorMul(res.r[1], vTR0);
	res.r[2] = VectorMul(res.r[2], vTR0);
	res.r[3] = VectorMul(res.r[3], vTR0);

	return res;
}

//*************************************************************************************************
// Matrix inverse transpose
//*************************************************************************************************
Matrix MatrixInverseTranspose(const Matrix& m)
{
	// Inverse transpose is only applied to normals, so ignore translation component
	Matrix tMat = Matrix(m.r[0], m.r[1], m.r[2], gVIdentityR3);

	// Calculate determinant
	Vector det = VectorZero();

	// Get matrix inverse
	tMat = MatrixInverse(&det, tMat);

	// Return transpose
	return MatrixTranspose(tMat);
}

//*************************************************************************************************
// Build a matrix which scales by (sx, sy, sz)
//*************************************************************************************************
Matrix MatrixScaling(float sx, float sy, float sz)
{
	Matrix m;
	m.r[0] = _mm_set_ps(0.0f, 0.0f, 0.0f, sx);
	m.r[1] = _mm_set_ps(0.0f, 0.0f, sy, 0.0f);
	m.r[2] = _mm_set_ps(0.0f, sz, 0.0f, 0.0f);
	m.r[3] = gVIdentityR3;
	return m;
}

//*************************************************************************************************
//  Build a matrix which scales by (sx, sy, sz)
//*************************************************************************************************
Matrix MatrixScaling(Vector s)
{
	Matrix m;
	m.r[0] = _mm_and_ps(gVXMask, s);
	m.r[1] = _mm_and_ps(gVYMask, s);
	m.r[2] = _mm_and_ps(gVZMask, s);
	m.r[3] = gVIdentityR3;
	return m;
}

//*************************************************************************************************
// Build a matrix which tranlates by (x, y, z) 
//*************************************************************************************************
Matrix MatrixTranslation(float x, float y, float z)
{
	Matrix m;
	m.r[0] = gVIdentityR0;
	m.r[1] = gVIdentityR1;
	m.r[2] = gVIdentityR2;
	m.r[3] = _mm_set_ps(1.0f, z, y, x);
	return m;
}

//*************************************************************************************************
//  Build a matrix which tranlates by (x, y, z)
//*************************************************************************************************
Matrix MatrixTranslation(Vector t)
{
	Matrix m;
	m.r[0] = gVIdentityR0;
	m.r[1] = gVIdentityR1;
	m.r[2] = gVIdentityR2;
	m.r[3] = t;
	return m;
}

//*************************************************************************************************
// Build a matrix which rotates around the X axis 
//*************************************************************************************************
Matrix MatrixRotationX(float angle)
{
	Vector vAngle = VectorReplicate(angle);
	return MatrixRotationX(vAngle);
	
}

//*************************************************************************************************
// Build a matrix which rotates around the X axis 
// 1  0  0  0
// 0  c  s  0
// 0 -s  c  0
// 0  0  0  1
//*************************************************************************************************
Matrix MatrixRotationX(Vector angle)
{
	// Load sin and cos values
	Vector sin, cos;
	VectorSinCos(&sin, &cos, angle);

	// Load second and third rows
	Vector vTemp1 = _mm_unpacklo_ps(sin, gVZero);	// s 0 s 0
	Vector vTemp2 = _mm_unpacklo_ps(gVZero, sin);	// 0 s 0 s
	Vector vTemp3 = VectorMul(gVNegateXZ, vTemp2);	// 0 -s 0 -s
	Vector vTemp4 = _mm_unpacklo_ps(cos, gVZero);	// c 0 c 0
	Vector vTemp5 = _mm_unpackhi_ps(gVZero, cos);	// 0 c 0 c

	// Populate the matrix
	Matrix m;
	m.r[0] = gVIdentityR0;
	m.r[1] = _mm_movelh_ps(vTemp5, vTemp2);
	m.r[2] = _mm_movelh_ps(vTemp3, vTemp4);
	m.r[3] = gVIdentityR3;

	return m;
}
//
//*************************************************************************************************
// Build a matrix which rotates around the Y axis 
//*************************************************************************************************
Matrix MatrixRotationY(float angle)
{
	Vector vAngle = VectorReplicate(angle);
	return MatrixRotationY(vAngle);
}

//*************************************************************************************************
// Build a matrix which rotates around the Y axis
// c  0 -s 0
// 0  1  0 0
// s  0  c 0
// 0  0  0 1
//*************************************************************************************************
Matrix MatrixRotationY(Vector angle)
{
	// Load sin and cos
	Vector sin, cos;
	VectorSinCos(&sin, &cos, angle);

	// Load first and third rows
	Vector vTemp1 = _mm_unpacklo_ps(sin, gVZero);	// s 0 s 0
	Vector vTemp2 = VectorMul(vTemp1, gVNegateXZ);	// -s 0 -s 0
	Vector vTemp3 = _mm_unpacklo_ps(cos, gVZero);	// c 0 c 0

	// Set all rows
	Matrix m;
	m.r[0] = _mm_movelh_ps(vTemp3, vTemp2);
	m.r[1] = gVIdentityR1;
	m.r[2] = _mm_movelh_ps(vTemp1, vTemp3);
	m.r[3] = gVIdentityR3;
	return m;
}

//*************************************************************************************************
// Build a matrix which rotates around the Z axis 
//*************************************************************************************************
Matrix MatrixRotationZ(float angle)
{
	Vector vAngle = VectorReplicate(angle);
	return MatrixRotationZ(vAngle);
}

//*************************************************************************************************
// Build a matrix which rotates around the Z axis
//pOut->_11 = c;		pOut->_12 = s;		pOut->_13 = 0.0f;	pOut->_14 = 0.0f;
//	pOut->_21 = -s;		pOut->_22 = c;		pOut->_23 = 0.0f;	pOut->_24 = 0.0f;
//	pOut->_31 = 0.0f;	pOut->_32 = 0.0f;	pOut->_33 = 0.0f;	pOut->_34 = 0.0f;
//	pOut->_41 = 0.0f;	pOut->_42 = 0.0f;	pOut->_43 = 0.0f;	pOut->_44 = 1.0f;
//************************************************************************************************* 
Matrix MatrixRotationZ(Vector angle)
{
	// Load sin and cos
	Vector sin, cos;
	VectorSinCos(&sin, &cos, angle);

	// Load first and second rows
	sin = _mm_unpacklo_ps(sin, cos);
	cos = _mm_shuffle_ps(sin, sin, _MM_SHUFFLE(3, 3, 0, 1));
	cos = _mm_mul_ps(cos, gVNegateX);

	// Construct matrix
	Matrix m;
	m.r[0] = sin;
	m.r[1] = cos;
	m.r[2] = gVIdentityR2;
	m.r[3] = gVIdentityR3;
	return m;
}

//*************************************************************************************************
// Build a matrix which rotates around an arbitrary axis
//*************************************************************************************************
Matrix MatrixRotationAxis(const Vector axis, float angle)
{
	Vector vAngle = VectorReplicate(angle);
	return MatrixRotationAxis(axis, vAngle);
}

//*************************************************************************************************
// Build a matrix which rotates around an arbitrary axis
//*************************************************************************************************
Matrix MatrixRotationAxis(const Vector axis, Vector angle)
{
	Vector normal = Vec3Normalize(axis);
	return MatrixRotationNormal(axis, angle);
	//// Sin and cos
	//Vector sin, cos;
	//VectorSinCos(&sin, &cos, angle);
	//Vector diffCos = Vec3Sub(gVOne, cos);
	//
	//// Construct the following vectors
	//// x * x * dc + c
	//// x * y * dc + (z * s)
	//// x * z * dc - (y * s)
	////
	//// x * y * dc - (z * s)
	//// y * y * dc + c
	//// y * z * dc + (x * s)
	////
	//// x * z * dc + (y * s)
	//// y * z * dc - (x * s)
	//// z * z * dc + c
	//Vector vTempX = _mm_shuffle_ps(axis, axis, _MM_SHUFFLE(0, 0, 0, 0));
	//Vector vTempZ = _mm_shuffle_ps(axis, axis, _MM_SHUFFLE(2, 2, 2, 2));
	//Vector vTempXY = _mm_shuffle_ps(axis, axis, _MM_SHUFFLE(1, 1, 0, 0));
	//Vector vTempYZ = _mm_shuffle_ps(axis, axis, _MM_SHUFFLE(2, 2, 1, 1));

	//Vector vTempSV = VectorMul(axis, sin);
	//Vector vTempCS = _mm_shuffle_ps(vTempSV, cos, _MM_SHUFFLE(2, 2, 0, 0));
	//vTempCS = _mm_shuffle_ps(vTempSV, vTempCS, _MM_SHUFFLE(2, 1, 1, 0));

	//Vector vTemp0 = _mm_shuffle_ps(vTempCS, vTempCS, _MM_SHUFFLE(3, 1, 2, 3));
	//vTemp0 = VectorMul(vTemp0, gVNegateZ);
	//Vector vTemp1 = _mm_shuffle_ps(vTempCS, vTempCS, _MM_SHUFFLE(3, 0, 3, 2));
	//vTemp1 = VectorMul(vTemp1, gVNegateX);
	//Vector vTemp2 = _mm_shuffle_ps(vTempCS, vTempCS, _MM_SHUFFLE(3, 3, 0, 1));
	//vTemp2 = VectorMul(vTemp2, gVNegateY);
	//
	//// Construct matrix
	//Vector vTemp = VectorMul(vTempX, axis);
	//vTemp = VectorMul(vTemp, diffCos);
	//vTemp0 = VectorAdd(vTemp, vTemp0);

	//vTemp = VectorMul(vTempXY, vTempYZ);
	//vTemp = VectorMul(vTemp, diffCos);
	//vTemp1 = VectorAdd(vTemp, vTemp1);

	//vTemp = VectorMul(v, vTempZ);
	//vTemp = VectorMul(vTemp, diffCos);
	//vTemp2 = VectorAdd(vTemp, vTemp2);

	//Matrix m;
	//m.r[0] = VectorAnd(vTemp0, gVMask3);
	//m.r[1] = VectorAnd(vTemp1, gVMask3);
	//m.r[2] = VectorAnd(vTemp2, gVMask3);
	//m.r[3] = gVIdentityR3;

	//return m;	
}

//*************************************************************************************************
// Build a matrix which rotates around an arbitrary normal axis
//*************************************************************************************************
Matrix MatrixRotationNormal(const Vector normal, float angle)
{
	Vector vAngle = VectorReplicate(angle);
	return MatrixRotationNormal(normal, vAngle);
}

//*************************************************************************************************
// Build a matrix which rotates around an arbitrary normal axis
//
// R = I*cos(theta) + sin(theta) * [u]x + (1 - cos(theta) u(x)u
// Where I is the identity matrix, [u]x is the cross product matrix of u, and u(x)u is the tensor
// product of u.
//*************************************************************************************************
Matrix MatrixRotationNormal(const Vector normal, Vector angle)
{
	// Get sin and cos values of angle
	Vector sin, cos;
	VectorSinCos(&sin, &cos, angle);

	// Load identity matrix
	Matrix m1 = MatrixIdentity();

	// Scale by cos
	m1 = MatrixScale(m1, cos);

	// Determine the cross product matrix
	Matrix m2 = MatrixCrossProduct(normal);
	
	// Scale by sin
	m2 = MatrixScale(m2, sin);

	// Get current return value
	m1 = MatrixAdd(m1, m2);

	// Get (1-cos)
	cos = VectorSub(gVOne, cos);

	// Get tensor product of u and u
	m2 = MatrixTensorProduct(normal, normal);

	// Scale by cos
	m2 = MatrixScale(m2, cos);

	// Add final product and return
	m1 = MatrixAdd(m1, m2);

	// Reset last row
	m1.r[3] = gVIdentityR3;

	return m1;
}

////*************************************************************************************************
//// 
////*************************************************************************************************
//// Build a matrix from a quaternion
//Matrix MatrixRotationQuaternion(const Vector q);

//*************************************************************************************************
// Yaw around the Y axis, a pitch around the X axis, and a roll around the Z axis 
//*************************************************************************************************
Matrix MatrixRotationYawPitchRoll(float yaw, float pitch, float roll)
{
	Vector vYaw = VectorReplicate(yaw);
	Vector vPitch = VectorReplicate(pitch);
	Vector vRoll = VectorReplicate(roll);
	return MatrixRotationYawPitchRoll(vYaw, vPitch, vRoll);
}

//*************************************************************************************************
// Yaw around the Y axis, a pitch around the X axis, and a roll around the Z axis 
//*************************************************************************************************
Matrix MatrixRotationYawPitchRoll(Vector yaw, Vector pitch, Vector roll)
{
	Matrix m1, m2;

	// Get the yaw and pitch rotation matrices
	m1 = MatrixRotationY(yaw);
	m2 = MatrixRotationX(pitch);

	// Get cumulative rotation matrix
	m1 = MatrixMultiply(m1, m2);

	// Get the roll matrix
	m2 = MatrixRotationZ(roll);

	// Find rotation matrix
	return MatrixMultiply(m1, m2);
}

////*************************************************************************************************
//// 
////*************************************************************************************************
//// Build transformation matrix with null arguments being treated as identity. 
//// Mout = Msc-1 * Msr-1 * Ms * Msr * Msc * Mrc-1 * Mr * Mrc * Mt
//Matrix MatrixTransformation(const Vector scalingCenter, const Vector scalingRotation, 
//	const Vector scaling, const Vector& rotationCenter, const Vector& rotation, const Vector& translation);
//
////*************************************************************************************************
//// 
////*************************************************************************************************
//// Build 2D transformation matrix in XY plane. Null arguments treated as identity. Mout = Msc-1 * Msr-1 * Ms * Msr * Msc * Mrc-1 * Mr * Mrc * Mt
//Matrix MatrixTransformation2D(const Vector scalingCenter, float scalingRotation, const Vector scaling,
//	const Vector rotationCenter, float rotation, const Vector& translation);
//
////*************************************************************************************************
//// 
////*************************************************************************************************
//// Build 2D transformation matrix in XY plane. Null arguments treated as identity. Mout = Msc-1 * Msr-1 * Ms * Msr * Msc * Mrc-1 * Mr * Mrc * Mt
//Matrix MatrixTransformation2D(const Vector scalingCenter, const Vector scalingRotation, const Vector scaling,
//	const Vector& rotationCenter, const Vector& rotation, const Vector& translation);
//
////*************************************************************************************************
//// 
////*************************************************************************************************
//// Build affine transformation matrix. Null arguments treated as identity. Mout = Ms * Mrc-1 * Mr * Mrc * Mt
//Matrix MatrixAffineTransformation(float scaling, const Vector rotationCenter, const Vector rotation, 
//	const Vector translation);
//
////*************************************************************************************************
//// 
////*************************************************************************************************
//// Build affine transformation matrix. Null arguments treated as identity. Mout = Ms * Mrc-1 * Mr * Mrc * Mt
//Matrix MatrixAffineTransformation(const Vector scaling, const Vector rotationCenter, const Vector rotation, 
//	const Vector& translation);
//
////*************************************************************************************************
//// 
////*************************************************************************************************
//// Build 2D affine transformation matrix in XY plane. Null arguments treated as identity. Mout = Ms * Mrc-1 * Mr * Mrc * Mt
//Matrix MatrixAffineTransformation2D(float scaling, const Vector rotationCenter, float rotation, const Vector translation);
//
////*************************************************************************************************
//// 
////*************************************************************************************************
//// Build 2D affine transformation matrix in XY plane. Null arguments treated as identity. Mout = Ms * Mrc-1 * Mr * Mrc * Mt
//Matrix MatrixAffineTransformation2D(const Vector scaling, const Vector rotationCenter, 
//	const Vector rotation, const Vector& translation);
//
////*************************************************************************************************
//// 
////*************************************************************************************************
//// Build a lookat matrix (right-handed)
//Matrix MatrixLookAtRH(const Vector eye, const Vector at, const Vector up);
//
//*************************************************************************************************
// Build a lookat matrix (left-handed)
//
// Construct z axis
// zAxis = Vec3Sub(at, eye)
// zAxis = Vec3Normalize(zAxis)
//
// Construct x axis
// xAxis = Vec3Cross(up, zAxis)
// xAxis = Vec3Normalize(xAxis)
//
// Construct y axis
// yAxis = Vec3Cross(zAxis, xAxis)
//
// Splat x and y axes
// vTemp1 = _mm_shuffle_ps(xAxis, yAxis, _MM_SHUFFLE(1, 0, 1, 0)) -> x.x x.y y.x y.y
// vTemp2 = _mm_shuffle_ps(xAxis, yAxis, _MM_SHUFFLE(3, 2, 3, 2)) -> x.z x.w y.z y.w
//
// Splat z axis
// vTemp3 = _mm_shuffle_ps(zAxis, gVZero, _MM_SHUFFLE(1, 0, 1, 0)) -> z.x z.y 0 0
// vTemp4 = _mm_shuffle_ps(zAxis, gVZero, _MM_SHUFFLE(3, 2, 3, 2)) -> z.z z.w 0 0
//
// Construct R0
// r1 = _mm_shuffle_ps(vTemp1, vTemp3, _MM_SHUFFLE(3, 0, 2, 0));
//
// Construct R1
// r2 = _mm_shuffle_ps(vTemp1, vTemp3, _MM_SHUFFLE(3, 1, 3, 1));
//
// Construct R2
// r3 = _mm_shuffle_ps(vTemp2, vTemp4, _MM_SHUFFLE(3, 0, 2, 0))
//
// Construct R3
// vTemp1 = Vec3Dot(xAxis, eye)
// vTemp1 = Vec3Mul(gVNegOne, vTemp1)
// vTemp2 = Vec3Dot(yAxis, eye)
// vTemp2 = Vec3Mul(gVNegOne, vTemp2)
// vTemp3 = Vec3Dot(zAxis, eye)
// vTemp3 = Vec3Mul(gVNegOne, vTemp3)
//
// vTemp1 = _mm_unpacklo_ps(vTemp1, vTemp2)
// vTemp2 = _mm_unpacklo_ps(vTemp3, gVOne)
// r4 = _mm_unpacklo_ps(vTemp1, vTemp2)
//*************************************************************************************************
Matrix MatrixLookAtLH(const Vector eye, const Vector at, const Vector up)
{
	// Construct z axis
	Vector zAxis = Vec3Sub(at, eye);
	zAxis = Vec3Normalize(zAxis);

	// Construct x axis
	Vector xAxis = Vec3Cross(up, zAxis);
	xAxis = Vec3Normalize(xAxis);

	// Construct y axis
	Vector yAxis = Vec3Cross(zAxis, xAxis);

	// Splat x and y axes
	Vector vTemp1 = _mm_shuffle_ps(xAxis, yAxis, _MM_SHUFFLE(1, 0, 1, 0));
	Vector vTemp2 = _mm_shuffle_ps(xAxis, yAxis, _MM_SHUFFLE(3, 2, 3, 2));

	// Splat z axis
	Vector vTemp3 = _mm_shuffle_ps(zAxis, gVZero, _MM_SHUFFLE(1, 0, 1, 0));
	Vector vTemp4 = _mm_shuffle_ps(zAxis, gVZero, _MM_SHUFFLE(3, 2, 3, 2));

	// Construct the matix
	Matrix m;

	// R0
	m.r[0] = _mm_shuffle_ps(vTemp1, vTemp3, _MM_SHUFFLE(3, 0, 2, 0));

	// R1
	m.r[1] = _mm_shuffle_ps(vTemp1, vTemp3, _MM_SHUFFLE(3, 1, 3, 1));

	// R2
	m.r[2] = _mm_shuffle_ps(vTemp2, vTemp4, _MM_SHUFFLE(3, 0, 2, 0));

	// R3
	vTemp1 = Vec3Dot(xAxis, eye);
	vTemp1 = Vec3Scale(vTemp1, gVNegOne);
	vTemp2 = Vec3Dot(yAxis, eye);
	vTemp2 = Vec3Scale(vTemp2, gVNegOne);
	vTemp3 = Vec3Dot(zAxis, eye);
	vTemp3 = Vec3Scale(vTemp3, gVNegOne);

	vTemp1 = _mm_unpacklo_ps(vTemp1, vTemp3);
	vTemp3 = _mm_unpacklo_ps(vTemp2, gVOne);
	m.r[3] = _mm_unpacklo_ps(vTemp1, vTemp3);

	return m;
}

////*************************************************************************************************
//// 
////*************************************************************************************************
//// Build a perspective projection matrix (right-handed)
//Matrix MatrixPerspectiveRH(float w, float h, float zn, float zf);
//
////*************************************************************************************************
//// 
////*************************************************************************************************
//// Build a perspective projection matrix (right-handed)
//Matrix MatrixPerspectiveRH(const Vector w, const Vector h, const Vector zn, const Vector& zf);
//
////*************************************************************************************************
//// 
////*************************************************************************************************
//// Build a perspective projection matrix (left-handed)
//Matrix MatrixPerspectiveLH(float w, float h, float zn, float zf);
//
////*************************************************************************************************
//// 
////*************************************************************************************************
//// Build a perspective projection matrix (left-handed)
//Matrix MatrixPerspectiveLH(const Vector w, const Vector h, const Vector zn, const Vector& zf);
//
////*************************************************************************************************
//// 
////*************************************************************************************************
//// Build a perspective projection matrix (right-handed)
//Matrix MatrixPerspectiveFovRH(float fovy, float aspect, float zn, float zf);
//
////*************************************************************************************************
//// 
////*************************************************************************************************
//// Build a perspective projection matrix (right-handed)
//Matrix MatrixPerspectiveFovRH(const Vector fovy, const Vector aspect, const Vector zn, const Vector& zf);
//
//*************************************************************************************************
// Build a perspective projection matrix (left-handed)
// 
// [cot(fovy/2)/aspect 0 0 0]
// [0 cot(fovy/2) 0 0]
// [0 0 (f)/(f-n) (nf)/(n-f)]
// [0 0 -1 0]
//*************************************************************************************************
Matrix MatrixPerspectiveFovLH(float fovy, float aspect, float zn, float zf)
{
	Vector vFovy = VectorReplicate(fovy);
	Vector vAspect = VectorReplicate(aspect);
	Vector vZn = VectorReplicate(zn);
	Vector vZf = VectorReplicate(zf);

	return MatrixPerspectiveFovLH(vFovy, vAspect, vZn, vZf);
}

//*************************************************************************************************
// Build a perspective projection matrix (left-handed) 
// 
// [cot(fovy/2)/aspect 0 0 0]
// [0 cot(fovy/2) 0 0]
// [0 0 (f)/(f-n) (nf)/(n-f)]
// [0 0 -1 0]
// 
// cot = cos/sin
//*************************************************************************************************
Matrix MatrixPerspectiveFovLH(const Vector fovy, const Vector aspect, const Vector zn, const Vector& zf)
{
	// Find fovy/2
	Vector fovy2 = VectorMul(fovy, gVOneHalf);

	// Find cot
	Vector sin, cos;
	VectorSinCos(&sin, &cos, fovy2);
	Vector cot = VectorDiv(cos, sin);
	fovy2 = VectorDiv(cot, aspect);

	// Matrix constructor
	Matrix m;

	// Construct the first row
	m.r[0] = _mm_move_ss(gVZero, fovy2);

	// Construct the second row
	m.r[1] = _mm_and_ps(gVYMask, cot);

	// Construct third row
	Vector range = VectorSub(zf, zn);
	range = VectorDiv(zf, range);
	Vector vTemp = _mm_and_ps(gVWMask, range);
	m.r[2] = _mm_unpackhi_ps(vTemp, gVIdentityR3);//, vTemp);

	/*vTemp1 = _mm_and_ps(gVYMask, vTemp1);
	range = VectorMul(gVNegOne, range);
	Vector vTemp2 = VectorMul(zn, zf);
	vTemp2 = VectorDiv(vTemp2, range);
	vTemp2 =  _mm_and_ps(gVYMask, vTemp2);
	m.r[2] = _mm_unpacklo_ps(vTemp1, vTemp2);*/

	// Construct fourth row	
	range = VectorMul(gVNegOne, range);
	range = VectorMul(range, zn);
	m.r[3] = _mm_and_ps(gVZMask, range);	

	return m;
}

////*************************************************************************************************
//// 
////*************************************************************************************************
//// Build a matrix which flattens geometry into a plane, as if casting a shadow from a light
//Matrix MatrixShadow(const Vector light, const Vector plane);
//
////*************************************************************************************************
//// 
////*************************************************************************************************
//// Build a matrix which reflects the coordinate system about a plane
//Matrix MatrixReflect(const Vector plane);
//
//*************************************************************************************************
// Creates a tensor product of given two 3D vectors
// uxvx uxvy uxvz
// uxvy uyvy uyvz
// uxvz uyvz uzvz
//*************************************************************************************************
Matrix MatrixTensorProduct(const Vector v1, const Vector v2)
{
	Matrix m;

	// Row 0
	Vector t = VectorSplatX(v1);
	m.r[0] = VectorMul(t, v2);

	// Row 1
	t = _mm_shuffle_ps(v1, v1, _MM_SHUFFLE(3, 1, 1, 0));
	Vector t2 = _mm_shuffle_ps(v2, v2, _MM_SHUFFLE(3, 2, 1, 1));
	m.r[1] = VectorMul(t, t2);

	// Row 2
	t = VectorSplatZ(v2);
	m.r[2] = VectorMul(t, v1);

	// Row 3
	m.r[3] = gVIdentityR3;

	return m;
}

//*************************************************************************************************
// Create the cross product matrix from a vector
// 0   -uz uy
// uz   0  -ux
// -uy  ux  0
//*************************************************************************************************
Matrix MatrixCrossProduct(const Vector v)
{
	// Negate the original vector
	Vector vNeg = VectorNegate(v);

	Vector v1 = _mm_unpacklo_ps(vNeg, gVZero);	// -ux 0 -uy 0
	Vector v2 = _mm_unpackhi_ps(gVZero, vNeg);	// 0 -uz 0 -uw
	Vector v3 = _mm_unpacklo_ps(v, gVZero);		// ux 0 uy 0
	Vector v4 = _mm_unpackhi_ps(v, gVZero);		// uz 0 uw 0
	Vector v5 = _mm_unpacklo_ps(v, vNeg);		// ux -ux uy -uy

	Matrix m;
	m.r[0] = _mm_shuffle_ps(v2, v3, _MM_SHUFFLE(3, 2, 1, 0));
	m.r[1] = _mm_movelh_ps(v4, v1);
	m.r[2] = _mm_shuffle_ps(v5, gVZero, _MM_SHUFFLE(0, 0, 0, 3));
	m.r[3] = gVIdentityR3;
	return m;
}
