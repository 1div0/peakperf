#include "512_12.h"

void compute(int index) {
  for(long i=0; i<MAXFLOPS_ITERS; i++) {
      farr[index][0]  = _mm512_fmadd_ps(mult, farr[index][0], farr[index][1]);
      farr[index][2]  = _mm512_fmadd_ps(mult, farr[index][2], farr[index][3]);
      farr[index][4]  = _mm512_fmadd_ps(mult, farr[index][4], farr[index][5]);
      farr[index][6]  = _mm512_fmadd_ps(mult, farr[index][6], farr[index][7]);
      farr[index][8]  = _mm512_fmadd_ps(mult, farr[index][8], farr[index][9]);
      farr[index][10] = _mm512_fmadd_ps(mult, farr[index][10], farr[index][11]);
      farr[index][12] = _mm512_fmadd_ps(mult, farr[index][12], farr[index][13]);
      farr[index][14] = _mm512_fmadd_ps(mult, farr[index][14], farr[index][15]);
      farr[index][16] = _mm512_fmadd_ps(mult, farr[index][16], farr[index][17]);
      farr[index][18] = _mm512_fmadd_ps(mult, farr[index][18], farr[index][19]);
      farr[index][20] = _mm512_fmadd_ps(mult, farr[index][20], farr[index][21]);
      farr[index][22] = _mm512_fmadd_ps(mult, farr[index][22], farr[index][23]);
    }
}
