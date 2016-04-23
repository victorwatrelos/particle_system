#ifndef __OPENCL_INC__HPP__
# define __OPENCL_INC__HPP__

# include <OpenCL/cl.h>
# include <OpenCL/cl_gl.h>
# include <OpenCL/cl_gl_ext.h>
# define QUOTE(str) #str
# define EXPAND_AND_QUOTE(str) QUOTE(str)
# define DEBUG_HOST 0
# define DEBUG_OPENCL_VALUE 0
# define DEBUG_OPENCL "1"
# define DEBUG_TIME 1

#endif
