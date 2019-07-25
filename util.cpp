#include <cmath>

// Para comparar valores floating point
bool comp(double x, double y)
{
	float epsilon = 0.0005f;
	return std::fabs(x - y) < epsilon;
}