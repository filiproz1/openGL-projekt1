#pragma once
class Matrix4f
{
public:
	float m[4][4]{};	// {} inicjalizuj¹ zmienn¹, bez tego nie dzia³a 

	Matrix4f();
	Matrix4f(float a00, float a01, float a02, float a03,
		float a10, float a11, float a12, float a13,
		float a20, float a21, float a22, float a23,
		float a30, float a31, float a32, float a33);

	Matrix4f(Matrix4f m1, Matrix4f m2);
};