#include "cublas_v2.h"

void test(cublasHandle_t handle, cublasSideMode_t left_right,
          cublasFillMode_t upper_lower, cublasOperation_t transa,
          cublasDiagType_t unit_diag, int64_t m, int64_t n,
          const cuComplex *alpha, const cuComplex *a, int64_t lda, cuComplex *b,
          int64_t ldb) {
  // Start
  cublasCtrsm_64(handle /*cublasHandle_t*/, left_right /*cublasSideMode_t*/,
                 upper_lower /*cublasFillMode_t*/, transa /*cublasOperation_t*/,
                 unit_diag /*cublasDiagType_t*/, m /*int64_t*/, n /*int64_t*/,
                 alpha /*const cuComplex **/, a /*const cuComplex **/,
                 lda /*int64_t*/, b /*cuComplex **/, ldb /*int64_t*/);
  // End
}
