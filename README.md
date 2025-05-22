# 🧠 HyperCompute — A Modular System Stress Benchmark

Welcome to **HyperCompute**, a high-performance C++-based system stress-testing utility. This tool is designed to benchmark various subsystems of your PC in **modular layers**, from **CPU and system I/O** to (eventually) **GPU acceleration** and **text-based CLI rendering**.

## 💡 What It Does

HyperCompute is built to simulate **extreme system stress** using:
- 🧮 **OpenCL** (CPU backend for now)
- 📏 **GMP / MPFR** for high-precision floating-point operations
- 🚀 **AVX / SSE** intrinsics for raw SIMD math throughput
- 📦 **System I/O benchmarking** for stress testing disk or virtual memory

> ⚠️ GPU benchmarks **coming soon**. Currently CPU and I/O focused.

---

## 📦 Features

- ✅ Modular OpenCL kernel launching
- ✅ GMP/MPFR integration for **bigfloat math benchmarks**
- ✅ AVX/SSE-accelerated synthetic loops
- ✅ Raw I/O read/write and memory paging stress tests
- ⚙️ CMake-based build system
- 🧵 Multithreaded, with adjustable load tuning
- 📊 CLI live stats (planned)
- 🎨 TUI or ASCII-based visual rendering benchmarks (planned)

---

## 🔧 Build Instructions

**Dependencies**:
- CMake (>=3.15)
- OpenCL SDK (tested with POCL & Intel OpenCL CPU runtimes)
- GMP + MPFR (`sudo pacman -S gmp mpfr` on Arch)
- A compiler with AVX/SSE support (`g++`, `clang++`, etc.)

```bash
git clone https://github.com/yourname/HyperCompute.git
cd HyperCompute
mkdir build && cd build
cmake ..
make -j$(nproc)
./HyperCompute
