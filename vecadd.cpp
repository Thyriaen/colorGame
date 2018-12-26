/*
 * Copyright (c) 2015 Tobias Rautenkranz <mail@tobias.rautenkranz.ch>
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */

/*
 * ROCm 2.0 introduces full support for kernels written in the OpenCL 2.0 C language on certain devices
 * and systems.  Applications can detect this support by calling the “clGetDeviceInfo” query function
 * with “parame_name” argument set to “CL_DEVICE_OPENCL_C_VERSION”.  In order to make use of OpenCL 2.0
 * C language features, the application must include the option “-cl-std=CL2.0” in options passed to
 * the runtime API calls responsible for compiling or building device programs.  The complete
 * specification for the OpenCL 2.0 C language can be obtained using the following link:
 * https://www.khronos.org/registry/OpenCL/specs/opencl-2.0-openclc.pdf
 */


#define CL_HPP_ENABLE_EXCEPTIONS
#define CL_HPP_TARGET_OPENCL_VERSION 200

#include <CL/cl2.hpp> // OpenCL 2 C++ Bindings
#include <iostream>
#include <vector>
#include <algorithm>

/*
 * Returns a Platfrom supporting OpenCL 2 or an empty one
 */
cl::Platform findCL2Platform()
{
    std::vector<cl::Platform> platforms;
    cl::Platform::get(&platforms);

    for (auto &p : platforms) {
        std::string version = p.getInfo<CL_PLATFORM_VERSION>();
        if (version.find("OpenCL 2.") != std::string::npos) {
            return p;
        }
    }
    return cl::Platform();
}

/*
 * OpenCL Program Source
 */
const std::string rot13Kernel = R"====(
kernel void rot13(global char* in, global char* out)
{
  int num = get_global_id(0);
  char c = in[num];
  if ('a' <= c && c <= 'z') {
    out[num] = ((c - 'a') + 13) % 26 + 'a';
  } else if ('A' <= c && c <= 'Z') {
    out[num] = ((c - 'A') + 13) % 26 + 'A';
  } else {
    out[num] = c;
  }
}
)====";

int main(int argc, const char* argv[])
{
    if (argc != 1) {
        std::cerr << "Usage: " << argv[0] << "\n";
        std::cerr << "Reads a line from standard input and "
                     "prints the rot13'ed text to the standard output.\n";
        return EXIT_FAILURE;
    }

    cl::Platform platform = findCL2Platform();

    if (0 == platform()) {
        std::cerr << "No OpenCL 2 platform found.\n";
        return EXIT_FAILURE;
    }


    cl::Platform defaultPlatform = cl::Platform::setDefault(platform);
    if (defaultPlatform != platform) {
        std::cerr << "Error setting default platform\n";
        return EXIT_FAILURE;
    }

    // Make OpenCL Program
    cl::Program program(rot13Kernel);

    try {
        // Compile
        program.build("-cl-std=CL2.0");
    }
    catch (cl::BuildError e) {
        // Catch Compile failture and print diagnostics
        std::cerr << "Erro building program helloworld.cl: " << e.what() << "\n";
        for (auto &pair : e.getBuildLog()) {
            std::cerr << pair.second << std::endl;
        }

        return EXIT_FAILURE;
    }


    //
    // Get Input
    //
    std::string input;
    std::getline(std::cin, input); // only reads on line (not till EOF)
    if (std::cin.fail()) {
        std::cerr << "\nInput error\n";
        return EXIT_FAILURE;
    }

    size_t strlength = input.length();

    //
    // Setup Buffers
    //
    cl::Buffer inputBuffer(std::begin(input), std::end(input), true/*read only*/);

    cl::Buffer outputBuffer = cl::Buffer(
            CL_MEM_WRITE_ONLY | CL_MEM_HOST_READ_ONLY,
            input.length() * sizeof(char));

    //
    // Make and run Kernel
    //
    auto kernel = cl::KernelFunctor<cl::Buffer, cl::Buffer>(program, "rot13");

    kernel(cl::EnqueueArgs(cl::NDRange(input.length())),
           inputBuffer, outputBuffer);


    //
    // Readback result
    //
    std::string output(input); // output is the same size as input
    cl::copy(outputBuffer, std::begin(output), std::end(output));

    std::cout << output << std::endl;

    return EXIT_SUCCESS;
}
