__kernel void matvec_mul(__global float4 *mat, __global float4 *vec,
                         __global float *result) {
  int i = get_global_id(0);
  result[i] = dot(mat[i], vec[0]);
}
