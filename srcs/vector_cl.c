//
// Created by Drien BRETON on 3/2/17.
//
#include "vector_cl.h"

float 				*do_cl_vector_calc3f(t_cl *cl, char *ker_name, float *v1,
										  float *v2)
{
	cl_mem 			memobj[3];
	float 			*res;
	cl_kernel 		kernel;

	kernel = ht_get(cl->kernels, ker_name);
	res = (float *)malloc(sizeof(float) * 3);
	memobj[0] = clCreateBuffer(cl->env->ctx, CL_MEM_READ_WRITE, 3 * sizeof(float), NULL, NULL);
	memobj[1] = clCreateBuffer(cl->env->ctx, CL_MEM_READ_WRITE, 3 * sizeof(float), NULL, NULL);
	memobj[2] = clCreateBuffer(cl->env->ctx, CL_MEM_READ_WRITE, 3 * sizeof(float), NULL, NULL);
	clEnqueueWriteBuffer(cl->queue, memobj[0], CL_TRUE, 0, 3*sizeof(float), v1, 0, NULL, NULL);
	clEnqueueWriteBuffer(cl->queue, memobj[1], CL_TRUE, 0, 3*sizeof(float), v2, 0, NULL, NULL);
	clSetKernelArg(kernel, 0, 3 * sizeof(float), (void *)&memobj[0]);
	clSetKernelArg(kernel, 1, 3 * sizeof(float), (void *)&memobj[1]);
	clSetKernelArg(kernel, 2, sizeof(cl_mem), (void *)&memobj[2]);
	clEnqueueTask(cl->queue, kernel, 0, NULL, NULL);
	clEnqueueReadBuffer(cl->queue, memobj[2], CL_TRUE, 0, 3 * sizeof(float), res, 0, NULL, NULL);
	clReleaseMemObject(memobj[0]);
	clReleaseMemObject(memobj[1]);
	clReleaseMemObject(memobj[2]);
	return (res);
}

t_vector3f			add_vector3f_cl(t_cl *cl, t_vector3f v1, t_vector3f v2)
{
	float 			*va;
	float 			*vb;
	float 			*vc = NULL;
	t_vector3f		res;

	va = (float *)malloc(sizeof(float) * 3);
	vb = (float *)malloc(sizeof(float) * 3);
	va[0] = v1.x;
	va[1] = v1.y;
	va[2] = v1.z;
	vb[0] = v2.x;
	vb[1] = v2.y;
	vb[2] = v2.z;
	vc = do_cl_vector_calc3f(cl, "add_vector3f", va, vb);
	res.x = vc[0];
	res.y = vc[1];
	res.z = vc[2];
	free(va);
	free(vb);
	free(vc);
	return (res);
}
float				dot_vector3f_cl(t_cl *cl, t_vector3f v1, t_vector3f v2)
{
	float 			*va;
	float 			*vb;
	float 			*vc = NULL;
	float			res;

	va = (float *)malloc(sizeof(float) * 3);
	vb = (float *)malloc(sizeof(float) * 3);
	va[0] = v1.x;
	va[1] = v1.y;
	va[2] = v1.z;
	vb[0] = v2.x;
	vb[1] = v2.y;
	vb[2] = v2.z;
	vc = do_cl_vector_calc3f(cl, "dot_vector3f", va, vb);
	res = vc[0];
	free(va);
	free(vb);
	free(vc);
	return (res);
}
