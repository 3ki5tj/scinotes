/* real-to-complex fast Fourier tranform using FFTW
 * sudo apt-get install fftw3-dev
 * gcc 1dr2c.c -lfftw3 */
#include <stdlib.h>
#include <math.h>
#include <fftw3.h>


/* brute-force calculation
 * www.fftw.org/doc/The-1d-Real_002ddata-DFT.html */
void ft(int n, double *in, fftw_complex *out)
{
  int j, k;
  double *c, *s;

  c = calloc(n, sizeof(*c));
  s = calloc(n, sizeof(*s));
  for (j = 0; j < n; j++) {
    c[j] = cos(2*M_PI*j/n);
    s[j] = sin(2*M_PI*j/n);
  }
  for (k = 0; k < n; k++) {
    out[k][0] = out[k][1] = 0;
    /* out[k] = sum_{j from 0 to n - 1} in[j] * exp(-2*pi*j*k*I/N) */
    for (j = 0; j < n; j++) {
      out[k][0] += in[j] * c[j * k % n];
      out[k][1] -= in[j] * s[j * k % n];
    }
  }
  free(c);
  free(s);
}


int main(void)
{
  double *in, *in2;
  fftw_complex *out, *out2; /* double [2] */
  fftw_plan p, q;
  int i, N = 16;

  in = (double *) fftw_malloc(sizeof(*in) * N);
  in2 = (double *) fftw_malloc(sizeof(*in2) * N);
  out = (fftw_complex *) fftw_malloc(sizeof(*out) * N);
  out2 = (fftw_complex *) fftw_malloc(sizeof(*out2) * N);
  /* http://www.fftw.org/fftw3_doc/Real_002ddata-DFTs.html */
  p = fftw_plan_dft_r2c_1d(N, in, out, FFTW_ESTIMATE);

  for (i = 0; i < N; i++)
    in[i] = sin(2*M_PI*i/N) + 3.*cos(6*M_PI*i/N);

  fftw_execute(p);
  ft(N, in, out2);

  for (i = 0; i <= N/2; i++)
    printf("%6d %20.10f %20.10f |  %20.10f %20.10f\n",
        i, out[i][0], out[i][1], out2[i][0], out2[i][1]);

  printf("\nApplying the inverse transform...\n");
  q = fftw_plan_dft_c2r_1d(N, out, in2, FFTW_ESTIMATE);
  fftw_execute(q);
  for (i = 0; i < N; i ++)
    printf("%6d %20.10f %20.10f\n", i, in[i], in2[i]/N);

  fftw_destroy_plan(p); fftw_cleanup();
  fftw_free(in); fftw_free(in2); fftw_free(out); fftw_free(out2);
  return 0;
}

