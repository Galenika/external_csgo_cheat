#pragma once

class vector_3 {
public:
	vector_3(void) { x = y = z = 0.0f; }
	vector_3(float X, float Y, float Z) { x = X; y = Y; z = Z; }
	vector_3(float* v) { x = v[0]; y = v[1]; z = v[2]; }
	vector_3(const float* v) { x = v[0]; y = v[1]; z = v[2]; }
	vector_3(const vector_3& v) { x = v.x; y = v.y; z = v.z; }

	float& operator[](int i) { return ((float *)this)[i]; }
	float operator[](int i) const { return ((float *)this)[i]; }
	vector_3 operator + (const vector_3& v) const { return vector_3(x + v.x, y + v.y, z + v.z); }
	vector_3 operator - (const vector_3& v) const { return vector_3(x - v.x, y - v.y, z - v.z); }

	float length_sqr(void) const {
		return (x* x + y * y + z * z);
	}
public:
	float x, y, z;
};
