#include "Task.hpp"

Task::Task(void) {
    this->_buildOptions.push_back("-cl-mad-enable");
    this->_buildOptions.push_back("-cl-fast-relaxed-math");
    this->_buildOptions.push_back("-Werror");
    this->_defineOptions.insert(t_DefineOption("RANGE", "1.5f"));
    this->_defineOptions.insert(t_DefineOption("REST_DENSITY", "7000.0f"));
    this->_defineOptions.insert(t_DefineOption("MY_PI", "3.1415926f"));
    this->_defineOptions.insert(t_DefineOption("MAX", "15.0f"));
    this->_defineOptions.insert(t_DefineOption("MIN", "-15.0f"));
    this->_defineOptions.insert(t_DefineOption("EPSILON", "0.0001f"));
    this->_defineOptions.insert(t_DefineOption("COLL_EPSILON", "0.001f"));
    this->_defineOptions.insert(t_DefineOption("DEBUG", DEBUG_OPENCL));
    this->_defineOptions.insert(t_DefineOption("PRESSURE_K", "0.1"));
    this->_defineOptions.insert(t_DefineOption("PRESSURE_N", "1"));
    this->_defineOptions.insert(t_DefineOption("COEFF_DISPLAY", "10"));
    this->_defineOptions.insert(t_DefineOption("POS_OFFSET", "1.0f"));
}

void            Task::setMaxGid(std::string maxGid) {
    this->_defineOptions.insert(t_DefineOption("MAX_GID", maxGid));
}

void            Task::setSizeGrid(std::string sizeX, std::string sizeY, std::string sizeZ) {
    this->_defineOptions.insert(t_DefineOption("SIZE_GRID_X", sizeX));
    this->_defineOptions.insert(t_DefineOption("SIZE_GRID_Y", sizeY));
    this->_defineOptions.insert(t_DefineOption("SIZE_GRID_Z", sizeZ));
}

void            Task::setCoefSizeCell(std::string size) {
    this->_defineOptions.insert(t_DefineOption("COEF_SIZE_CELL", size));
}

void            Task::setCellSize(std::string size) {
    this->_defineOptions.insert(t_DefineOption("CELL_SIZE", size));
}
std::string     Task::getOptions() {
    std::string res = "";

    for (auto &it : this->_buildOptions) {
        res += it + " ";
    }
    for (auto &it : this->_defineOptions) {
        res += "-D " + it.first + "="  + it.second + " ";
    }
    return res;
}

cl_kernel       Task::getKernel() {
    return this->_kernel;
}

std::string     *Task::getSrc(std::string filename) const {
    std::ifstream ifs(filename);

    
    return new std::string( (std::istreambuf_iterator<char>(ifs) ),
                            (std::istreambuf_iterator<char>()) );
}

void            Task::setBoxSize(cl_float sizeBox) {
    this->_sizeBox = sizeBox;
    this->_defineOptions["BOX_SIZE"] = std::to_string(static_cast<int>(std::trunc(sizeBox)));
}

void            Task::setOffset(std::string offset) {
    this->_defineOptions["OFFSET"] = offset;
}

void            Task::releaseKernel() {
    clReleaseKernel(this->_kernel);
    clReleaseProgram(this->_program);
}

void            Task::enqueueKernel(cl_command_queue queue) {
    int     err;

    err = clEnqueueNDRangeKernel(
            queue,
            this->_kernel,
            1,
            NULL,
            &this->_globalWorkSize,
            &this->_localWorkSize,
            0,
            NULL,
            NULL);
    checkCLSuccess(err, "clEnqueueNDRangeKernel");
}

void        Task::_createKernel(std::string filename, std::string kernelName)
{
    std::string     *source;
    const char      *char_source;
    int             err;
    std::string options = this->getOptions();

    source = this->getSrc(filename);
    char_source = source->c_str();
    this->_program = clCreateProgramWithSource(this->_context, 1, &char_source, NULL, NULL);
    if (this->_program == NULL) {
        std::cerr << "Program creation fail" << std::endl;
        throw new OpenCLException;
    }
    delete source;


    err = clBuildProgram(this->_program, 0, NULL, options.c_str(), NULL, NULL);
    if (err != CL_SUCCESS) {
        char    buildlog[16384];
        clGetProgramBuildInfo(this->_program, this->_device, CL_PROGRAM_BUILD_LOG, sizeof(buildlog), buildlog, NULL);
        std::cerr << "Error on compilation(" << filename << ") options: '" << options << "'" << std::endl;
        std::cerr << "error " << err << std::endl;
        std::cerr << "buildlog: " << buildlog << std::endl;
        throw new OpenCLException();
    }

    if (DEBUG_HOST) {
        std::cout << "Compilation of " << filename << " with options: '" << options << "'" << std::endl;
    }

    this->_kernel = clCreateKernel(this->_program, kernelName.c_str(), &err);
    checkCLSuccess(err, "clCreateKernel");

    err = clGetKernelWorkGroupInfo(
        this->_kernel,
        this->_device,
        CL_KERNEL_WORK_GROUP_SIZE,
        sizeof(this->_localWorkSize),
        &(this->_localWorkSize),
        NULL);
    checkCLSuccess(err, "clGetKernelWorkGroupInfo");

    this->_nbWorkGroup = this->_nbParticle / this->_localWorkSize + 1;
    this->_globalWorkSize = this->_nbWorkGroup * this->_localWorkSize;
    this->_maxGid = this->_nbParticle - 1;
    if (DEBUG_HOST) {
        std::cout << "max gid: " << this->_maxGid << std::endl;
        std::cout << "Local work size: " << this->_localWorkSize << std::endl;
        std::cout << "global work size: " << this->_globalWorkSize << std::endl;
        std::cout << "nb work group: " << this->_nbWorkGroup << std::endl;
    }
}
