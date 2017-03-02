//
// Created by Drien BRETON on 2/21/17.
//

#include "opencl.h"
#include "libft.h"
#include "get_next_line.h"

//TODO get proper kernel numbers
#define	NUM_KERNEL 256

static void		store_kernels(t_hashtable *kernel, cl_kernel *tmp_kers,cl_uint kern_num)
{
	char 		ker_name[256];
	cl_uint		i;

	i = 0;
	while (i < kern_num)
	{
		clGetKernelInfo(tmp_kers[i], CL_KERNEL_FUNCTION_NAME, 256, (void *)ker_name, NULL);
		ht_set(kernel, ker_name, (void *)tmp_kers[i]);
		++i;
	}
}

static char 	*read_file_contents(int fd, size_t *src_len)
{
	char 		*line;
	char 		*tmp;
	char 		*src_str;

	src_str = (char *)malloc(sizeof(char));
	src_str[0] = 0;
	while (get_next_line(fd, &line) > 0)
	{

		tmp = src_str;
		src_str = ft_strjoin(src_str, line);
		free(tmp);
		free(line);
	}
	close(fd);
	//TODO handle errors
	*src_len = ft_strlen(src_str);
	return (src_str);
}

int 			read_kernel(t_hashtable *kernel, const char *fileName, t_cl_env *env)
{
	int 		fd;
	char 		*src_str;
	cl_program 	program = NULL;
	cl_int 		ret;
	cl_kernel 	*tmp_kers;
	cl_uint 	kern_num;
	size_t 		src_len;


	fd = open(fileName, O_RDWR);
	if (fd < 0)
		return (-1);
	tmp_kers = (cl_kernel *)malloc(sizeof(cl_kernel) * NUM_KERNEL);
	src_str = read_file_contents(fd, &src_len);
	program = clCreateProgramWithSource(env->ctx, 1, (const char **)&src_str, (const size_t *)&src_len, &ret);
	ret = clBuildProgram(program, 1, &env->device_id, NULL, NULL, NULL);
	ret = clCreateKernelsInProgram(program, NUM_KERNEL, tmp_kers,&kern_num);
	store_kernels(kernel, tmp_kers, kern_num);
	return (1);
}
//use absolute or relative path to directory
t_cl			*cl_init(const char *manifest_dir)
{
	t_cl		*res;
	cl_int		ret;
	int 		fd;
	char 		*tmp;
	char 		*line;
	char 		*file_name;

	res = (t_cl *)malloc(sizeof(t_cl));
	res->env = (t_cl_env*)malloc(sizeof(t_cl_env));
	res->kernels = create_hash_table(1021);
	file_name = ft_strjoin(manifest_dir, "/manifest");
	fd = open(file_name, O_RDWR);
	free(file_name);
	clGetPlatformIDs(1, &res->env->platform_id, &res->env->ret_num_platforms);
	clGetDeviceIDs(res->env->platform_id, CL_DEVICE_TYPE_DEFAULT, 1, &res->env->device_id, &res->env->ret_num_devices);
	res->env->ctx = clCreateContext(NULL, 1, &res->env->device_id, NULL, NULL, &ret);
	res->queue = clCreateCommandQueue(res->env->ctx, res->env->device_id, 0, &ret);
	while (get_next_line(fd, &line)> 0)
	{
		if (ft_strlen(line) > 0)
		{
			tmp = ft_strjoin("/", line);
			file_name = ft_strjoin(manifest_dir, tmp);
			read_kernel(res->kernels, file_name, res->env);
			free(tmp);
			free(file_name);
		}
	}
	return (res);
}
