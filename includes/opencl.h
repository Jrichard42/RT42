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
# include "hashtable.h"

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
	cl_kernel 	*kernel;
}				t_kernel;
typedef struct 	s_cl
{
	t_cl_env	*env;
	t_hashtable	*kernels;
	cl_command_queue queue;
}				t_cl;

int 			read_kernel(t_hashtable *kernel, const char *fileName, t_cl_env *env);
t_cl			cl_init(const char *manifest_dir);

#endif
