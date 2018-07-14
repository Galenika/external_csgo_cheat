#pragma once
#define DEG2RAD( x ) ( ( float )( x ) * ( float )( ( float )( M_PI ) / 180.0f ) )
#define RAD2DEG( x ) ( ( float )( x ) * ( float )( 180.0f / ( float )( M_PI ) ) )
#define M_RADPI 57.295779513082f
#define M_PI 3.14159265358979323846f
#define METERS_PER_INCH	(0.0254f)

class c_math : c_singleton<c_math>
{
public:
	float get_fov(vector_3 angle, vector_3 src, vector_3 dst)
	{
		auto make_vector = [](vector_3 angle, vector_3& vector) -> void
		{
			float pitch = float(angle[0] * M_PI / 180);
			float yaw = float(angle[1] * M_PI / 180);
			float tmp = float(cos(pitch));
			vector[0] = float(-tmp * -cos(yaw));
			vector[1] = float(sin(yaw)*tmp);
			vector[2] = float(-sin(pitch));
		};

		auto calc_angle = [](vector_3 src, vector_3 dst) -> vector_3
		{
			vector_3 vec_aimang;
			vector_3 delta = src - dst;
			float hyp = sqrt((delta.x * delta.x) + (delta.y * delta.y));
			vec_aimang.x = atanf(delta.z / hyp) * M_RADPI;
			vec_aimang.y = atanf(delta.y / delta.x) * M_RADPI;
			vec_aimang.z = 0.0f;
			if (delta.x >= 0.0)
				vec_aimang.y += 180.0f;

			return vec_aimang;
		};

		auto dot = [](const vector_3 &v1, vector_3 &v2) -> float
		{
			return v1[0] * v2[0] + v1[1] * v2[1] + v1[2] * v2[2];
		};

		vector_3 aim = vector_3();
		vector_3 ang = calc_angle(src, dst);
		make_vector(angle, aim);
		make_vector(ang, ang);

		float mag = sqrt(pow(aim.x, 2) + pow(aim.y, 2) + pow(aim.z, 2));
		float u_dot_v = dot(aim, ang);

		return RAD2DEG(acos(u_dot_v / (pow(mag, 2))));
	}

};