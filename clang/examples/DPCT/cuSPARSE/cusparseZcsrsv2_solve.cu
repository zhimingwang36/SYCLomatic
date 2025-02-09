#include "cusparse.h"

void test(cusparseHandle_t handle, cusparseOperation_t trans, int m, int nnz,
          const cuDoubleComplex *alpha, cusparseMatDescr_t desc,
          const cuDoubleComplex *value, const int *row_ptr, const int *col_idx,
          csrsv2Info_t info, const cuDoubleComplex *f, cuDoubleComplex *x,
          cusparseSolvePolicy_t policy, void *buffer) {
  // Start
  cusparseZcsrsv2_solve(
      handle /*cusparseHandle_t*/, trans /*cusparseOperation_t*/, m /*int*/,
      nnz /*int*/, alpha /*const cuDoubleComplex **/,
      desc /*cusparseMatDescr_t*/, value /*const cuDoubleComplex **/,
      row_ptr /*const int **/, col_idx /*const int **/, info /*csrsv2Info_t*/,
      f /*const cuDoubleComplex **/, x /*cuDoubleComplex **/,
      policy /*cusparseSolvePolicy_t*/, buffer /*void **/);
  // End
}
