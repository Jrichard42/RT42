//
// Created by Drien BRETON on 2/21/17.
//

#include "opencl.h"
#include "libft.h"
#include "get_next_line.h"

//TODO get proper kernel numbers
#define	NUM_KERNEL 256

int 			read_kernel(t_hashtable *kernel, const char *fileName, t_cl_env *env)
{
	int 		fd;
	char 		*line;
	char 		*src_str;
	char 		*tmp;
	cl_program 	program = NULL;
	cl_int 		ret;
	cl_kernel 	*tmp_kers;
	cl_uint 	kern_num;
	size_t 		src_len;
	cl_uint		i;


	fd = open(fileName, O_RDWR);
	if (fd < 0)
		return (-1);
	src_str = malloc(sizeof(char));
	tmp_kers = (cl_kernel *)malloc(sizeof(cl_kernel) * NUM_KERNEL);
	ft_bzero(tmp_kers, sizeof(cl_kernel) * NUM_KERNEL);
	src_str[0] = 0;
	while (get_next_line(fd, &line) > 0)
	{
		//TODO use realloc
		tmp = src_str;
		src_str = ft_strjoin(src_str, line);
		free(tmp);
		free(line);
	}
	close(fd);
	//TODO handle errors
	src_len= ft_strlen(src_str);
	program = clCreateProgramWithSource(env->ctx, 1, (const char **)&src_str, (const size_t *)&src_len, &ret);
	ret = clBuildProgram(program, 1, &env->device_id, NULL, NULL, NULL);
	ret = clCreateKernelsInProgram(program, NUM_KERNEL, tmp_kers,&kern_num);
	//-------------------------------------------------------------------

	char 		ker_name[256];
	i = 0;
	while (i < kern_num)
	{
		clGetKernelInfo(tmp_kers[i], CL_KERNEL_FUNCTION_NAME, 256, (void *)ker_name, NULL);
		ht_set(kernel, ker_name, (void *)tmp_kers[i]);
		++i;
	}
	return (1);
}
//use absolute or relative path to directory
t_cl			cl_init(const char *manifest_dir)
{
	t_cl		res;
	cl_int		ret;
	int 		fd;
	char 		*tmp;
	char 		*line;
	char 		*file_name;
	int 		i;

	res.env = (t_cl_env*)malloc(sizeof(t_cl_env));
	res.kernels = create_hash_table(1021);
	file_name = ft_strjoin(manifest_dir, "/manifest");
	fd = open(file_name, O_RDWR);
	free(file_name);
//if (fd < 0)
//	return ((t_cl)NULL);
	ret = clGetPlatformIDs(1, &res.env->platform_id, &res.env->ret_num_platforms);
	ret = clGetDeviceIDs(res.env->platform_id, CL_DEVICE_TYPE_DEFAULT, 1, &res.env->device_id, &res.env->ret_num_devices);
	res.env->ctx = clCreateContext(NULL, 1, &res.env->device_id, NULL, NULL, &ret);
	res.queue = clCreateCommandQueue(res.env->ctx, res.env->device_id, 0, &ret);
	while ((i = get_next_line(fd, &line))> 0)
	{
		if (ft_strlen(line) > 0)
		{
			tmp = ft_strjoin("/", line);
			file_name = ft_strjoin(manifest_dir, tmp);
			read_kernel(res.kernels, file_name, res.env);
			free(tmp);
			free(file_name);
		}
	}

	return (res);
}
