#include "cusparse.h"

void test(cusparseHandle_t handle, cusparseOperation_t op_a,
          cusparseOperation_t op_b, const void *alpha,
          cusparseSpMatDescr_t mat_a, cusparseSpMatDescr_t mat_b,
          const void *beta, cusparseSpMatDescr_t mat_c,
          cudaDataType compute_type, cusparseSpGEMMAlg_t alg,
          cusparseSpGEMMDescr_t desc, size_t *buffer_size, void *buffer) {
  // Start
  cusparseSpGEMM_compute(
      handle /*cusparseHandle_t*/, op_a /*cusparseOperation_t*/,
      op_b /*cusparseOperation_t*/, alpha /*const void **/,
      mat_a /*cusparseSpMatDescr_t*/, mat_b /*cusparseSpMatDescr_t*/,
      beta /*const void **/, mat_c /*cusparseSpMatDescr_t*/,
      compute_type /*cudaDataType*/, alg /*cusparseSpGEMMAlg_t*/,
      desc /*cusparseSpGEMMDescr_t*/, buffer_size /*size_t **/,
      buffer /*void **/);
  // End
}
