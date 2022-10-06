#include <CL/cl.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

int main() {
  cl_platform_id platform;
  clGetPlatformIDs(1, &platform, NULL);
  cl_device_id device;
  clGetDeviceIDs(platform, CL_DEVICE_TYPE_GPU, 1, &device, NULL);
  cl_int err;
  cl_context context = clCreateContext(NULL, 1, &device, NULL, NULL, &err);

  FILE *prog_handle = fopen("matvec.cl", "r");
  fseek(prog_handle, 0, SEEK_END);
  size_t prog_size = ftell(prog_handle);
  rewind(prog_handle);
  char *prog_buf = (char *)malloc(prog_size + 1);
  prog_buf[prog_size] = 0;
  fread(prog_buf, sizeof(char), prog_size, prog_handle);
  fclose(prog_handle);

  cl_program prog = clCreateProgramWithSource(
      context, 1, (const char **)&prog_buf, &prog_size, &err);
  free(prog_buf);
  clBuildProgram(prog, 0, NULL, NULL, NULL, NULL);

  cl_kernel kernel = clCreateKernel(prog, "matvec_mul", &err);
  cl_command_queue queue =
      clCreateCommandQueueWithProperties(context, device, NULL, &err);

  float mat[16] = {0.,  2.,  4.,  6.,  8.,  10., 12., 14.,
                   16., 18., 20., 22., 24., 26., 28., 30.},
        vec[4] = {0., 3., 6., 9.}, result[4];
  cl_mem mat_buf =
             clCreateBuffer(context, CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR,
                            sizeof(float) * 16, mat, &err),
         vec_buf =
             clCreateBuffer(context, CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR,
                            sizeof(float) * 4, vec, &err),
         result_buf = clCreateBuffer(context, CL_MEM_WRITE_ONLY,
                                     sizeof(float) * 4, NULL, &err);
  clSetKernelArg(kernel, 0, sizeof(cl_mem), &mat_buf);
  clSetKernelArg(kernel, 1, sizeof(cl_mem), &vec_buf);
  clSetKernelArg(kernel, 2, sizeof(cl_mem), &result_buf);

  size_t wu_per_kernel = 4;
  clEnqueueNDRangeKernel(queue, kernel, 1, NULL, &wu_per_kernel, NULL, 0, NULL,
                         NULL);
  clEnqueueReadBuffer(queue, result_buf, CL_TRUE, 0, sizeof(float) * 4, result,
                      0, NULL, NULL);
  printf("Result vector: [%g, %g, %g, %g]\n", result[0], result[1], result[2],
         result[3]);
  clReleaseMemObject(mat_buf);
  clReleaseMemObject(vec_buf);
  clReleaseMemObject(result_buf);
  clReleaseKernel(kernel);
  clReleaseCommandQueue(queue);
  clReleaseProgram(prog);
  clReleaseContext(context);
}
