//
// Created by Drien BRETON on 2/21/17.
//

#include "opencl.h"
#include "libft.h"

#define	NUM_KERNEL 256 //TODO get proper kernel numbers

int 			read_kernel(t_kernel **kernel, const char *fileName, t_cl_env *env)
{
	int 		fd;
	char 		*line;
	char 		*src_str;
	char 		*tmp;
	cl_program 	program = NULL;
	cl_int 		ret;
	cl_kernel 	*tmp_kers;
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
		tmp = src_str;
		src_str = ft_strjoin(src_str, line);
		free(tmp);
		free(line);
	}
	close(fd);
	fd = ft_strlen(src_str);
	program = clCreateProgramWithSource(env->ctx, 1, (const char **)&src_str, (const size_t *)&fd, &ret);
	ret = clBuildProgram(program, 1, &env->device_id, NULL, NULL, NULL);
	ret = clCreateKernelsInProgram(program, NUM_KERNEL, tmp_kers,NULL);
	//-------------------------------------------------------------------

	char 		ker_name[256];
	i = 0;
	j = 0;
	while (kernel[j]->name)
		++j;
	while (tmp_kers[i])
	{
		clGetKernelInfo(tmp_kers[i], CL_KERNEL_FUNCTION_NAME, 256, (void *)ker_name, NULL);
		kernel[j]->name = ft_strdup(ker_name);
		kernel[j]->kernel = tmp_kers[i];
		++j;
		++i;
	}
}
