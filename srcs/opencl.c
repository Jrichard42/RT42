//
// Created by Drien BRETON on 2/21/17.
//

#include "opencl.h"
#include "libft.h"
#include "get_next_line.h"

//TODO get proper kernel numbers
#define	NUM_KERNEL 256

int 			read_kernel(t_kernel **kernel, const char *fileName, t_cl_env *env)
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
	int 		i;
	int 		j;


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
	printf("%s\n", fileName);
	close(fd);
	src_len= ft_strlen(src_str);
	program = clCreateProgramWithSource(env->ctx, 1, (const char **)&src_str, (const size_t *)&src_len, &ret);
	ret = clBuildProgram(program, 1, &env->device_id, NULL, NULL, NULL);
	ret = clCreateKernelsInProgram(program, NUM_KERNEL, tmp_kers,&kern_num);
	//-------------------------------------------------------------------

	char 		ker_name[256];
	i = 0;
	j = 0;
	while (kernel[j])
		++j;
	*kernel = (t_kernel *)ft_realloc((void *)*kernel, sizeof(t_kernel) * (i + kern_num) + 1);
	while (tmp_kers[i])
	{
		clGetKernelInfo(tmp_kers[i], CL_KERNEL_FUNCTION_NAME, 256, (void *)ker_name, NULL);
		kernel[j]->name = ft_strdup(ker_name);
		kernel[j]->kernel = tmp_kers[i];
		++j;
		++i;
		//kernel[j] = NULL;
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

	res.env.platform_id = NULL;
	file_name = ft_strjoin(manifest_dir, "/manifest");
	fd = open(file_name, O_RDWR);
	printf("%d : %s\n", fd, file_name);
	free(file_name);
	//if (fd < 0)
	//	return ((t_cl)NULL);
	ret = clGetPlatformIDs(1, &res.env.platform_id, &res.env.ret_num_platforms);
	ret = clGetDeviceIDs(res.env.platform_id, CL_DEVICE_TYPE_DEFAULT, 1, &res.env.device_id, &res.env.ret_num_devices);
	res.env.ctx = clCreateContext(NULL, 1, &res.env.device_id, NULL, NULL, &ret);
	res.queue = clCreateCommandQueue(res.env.ctx, res.env.device_id, 0, &ret);
	res.kernels = NULL;
	//res.kernels = (t_kernel *)malloc(sizeof(t_kernel));
	//res.kernels[0] = 0;
	while (get_next_line(fd, &line) > 0)
	{
		printf("%s\n", line);
		if (ft_strlen(line) > 0)
		{
			tmp = ft_strjoin("/", line);
			file_name = ft_strjoin(manifest_dir, tmp);
			printf("%s\n", file_name);
			read_kernel(&res.kernels, file_name, &res.env);
			//-----------------------------------------------------------------

			//-----------------------------------------------------------------
			free(file_name);
		}
	}

	return (res);
}
