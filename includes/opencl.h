//
// Created by Drien BRETON on 2/21/17.
//

#ifndef RT42_OPENCL_H
#define RT42_OPENCL_H

# ifdef __APPLE__
#  include <OpenCL/opencl.h>
# else
#  include <CL/cl.h>
# endif

typedef struct	s_cl_env
{
	cl_context ctx;
	cl_device_id device_id;
	cl_platform_id platform_id;
	cl_uint ret_num_devices;
	cl_uint ret_num_platforms;

}				t_cl_env;

typedef struct 	s_kernel
{
	char 		*name;
	cl_kernel 	kernel;
}				t_kernel;

int 			read_kernel(cl_program *program, const char *fileName, t_cl_env *env);

#endif
