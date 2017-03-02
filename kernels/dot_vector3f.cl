__kernel void dot_vector3f(__global float *v1, __global float *v2, __global float *ret)
{
	float3 va;
	float3 vb;
	float res;

	va.x = v1[0];
	va.y = v1[1];
	va.z = v1[2];
	vb.x = v2[0];
	vb.y = v2[1];
	vb.z = v2[2];
	res = dot(va, vb);
	*ret = res;
}