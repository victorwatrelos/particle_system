#ifndef TASK_HPP
# define TASK_HPP

# include "OpenCLInc.hpp"
# include <string>
# include <fstream>
# include <vector>
# include <map>
# include <cmath>
# include "clUtil.hpp"

typedef std::pair<std::string, std::string> t_DefineOption;

class Task {
    public:
        Task(void);
        cl_kernel           getKernel();
        std::string         *getSrc(std::string filename) const;
        void                enqueueKernel(cl_command_queue queue);
        void                releaseKernel();
        void                setMaxGid(std::string maxGid);
        cl_int				getMaxGid(void);
        std::string         getOptions();
    protected:
        void                                _createKernel(std::string filename, std::string kernelName);
        cl_kernel                           _kernel;
        cl_program                          _program;
        cl_context                          _context;
        cl_device_id                        _device;
        size_t                              _localWorkSize;
        size_t                              _globalWorkSize;
        size_t                              _nbWorkGroup;
        size_t                              *_maxWorkItemSize;
        cl_int                              _nbParticle;
        cl_int                              _maxGid;
        std::vector<std::string>            _buildOptions;
        std::map<std::string, std::string>  _defineOptions;
};

#endif
