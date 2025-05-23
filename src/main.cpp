#include <CL/cl2.hpp>
#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>

#define CHECK(err, msg) \
    if (err != CL_SUCCESS) { \
        std::cerr << msg << " Error Code: " << err << std::endl; \
        exit(1); \
    }

std::string loadKernel(const char* path) {
    std::ifstream file(path);
    std::stringstream ss;
    ss << file.rdbuf();
    return ss.str();
}

int main() {
    cl_int err;

    // Platform & device
    cl_platform_id platform;
    cl_device_id device;
    err = clGetPlatformIDs(1, &platform, nullptr);
    CHECK(err, "Failed to get platform");

    err = clGetDeviceIDs(platform, CL_DEVICE_TYPE_CPU, 1, &device, nullptr);
    CHECK(err, "Failed to get device");

    // Context & queue
    cl_context context = clCreateContext(nullptr, 1, &device, nullptr, nullptr, &err);
    CHECK(err, "Failed to create context");

    cl_command_queue queue = clCreateCommandQueueWithProperties(context, device, nullptr, &err);
    CHECK(err, "Failed to create queue");

    // Kernel source
    std::string src = loadKernel("kernel.cl");
    const char* src_cstr = src.c_str();
    cl_program program = clCreateProgramWithSource(context, 1, &src_cstr, nullptr, &err);
    CHECK(err, "Failed to create program");

    err = clBuildProgram(program, 1, &device, nullptr, nullptr, nullptr);
    if (err != CL_SUCCESS) {
        size_t log_size;
        clGetProgramBuildInfo(program, device, CL_PROGRAM_BUILD_LOG, 0, nullptr, &log_size);
        std::vector<char> log(log_size);
        clGetProgramBuildInfo(program, device, CL_PROGRAM_BUILD_LOG, log_size, log.data(), nullptr);
        std::cerr << "Build log:\n" << log.data() << std::endl;
        exit(1);
    }

    cl_kernel kernel = clCreateKernel(program, "stress_cpu", &err);
    CHECK(err, "Failed to create kernel");

    // Data buffer
    const size_t count = 1024;
    std::vector<float> data(count, 1.0f);
    cl_mem buffer = clCreateBuffer(context, CL_MEM_READ_WRITE | CL_MEM_COPY_HOST_PTR,
                                   sizeof(float) * count, data.data(), &err);
    CHECK(err, "Failed to create buffer");

    err = clSetKernelArg(kernel, 0, sizeof(cl_mem), &buffer);
    CHECK(err, "Failed to set kernel arg");

    size_t global_size = count;
    err = clEnqueueNDRangeKernel(queue, kernel, 1, nullptr, &global_size, nullptr, 0, nullptr, nullptr);
    CHECK(err, "Failed to enqueue kernel");

    err = clEnqueueReadBuffer(queue, buffer, CL_TRUE, 0, sizeof(float) * count, data.data(), 0, nullptr, nullptr);
    CHECK(err, "Failed to read buffer");

    std::cout << "Finished. Sample output: " << data[0] << std::endl;

    clReleaseMemObject(buffer);
    clReleaseKernel(kernel);
    clReleaseProgram(program);
    clReleaseCommandQueue(queue);
    clReleaseContext(context);
}

