#include <CL/cl.h>
#include <iostream>

int main() {
    cl_uint platformCount;
    clGetPlatformIDs(0, nullptr, &platformCount);
    std::cout << "Found " << platformCount << " OpenCL platforms.\n";
    return 0;
}

