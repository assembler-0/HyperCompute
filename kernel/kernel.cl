// kernel.cl
__kernel void stress_cpu(__global float* data) {
    int id = get_global_id(0);
    float x = data[id];
    for (int i = 0; i < 100000; ++i)
        x = sin(x) * cos(x) + tan(x);
    data[id] = x;
}
