/* complex-to-complex fast Fourier tranform using FFTW
 * sudo apt-get install fftw3-dev
 * gcc 1d.c -lfftw3 */
#include <stdlib.h>
#include <math.h>
#include <fftw3.h>


/* brute-force calculation
 * http://www.fftw.org/doc/The-1d-Discrete-Fourier-Transform-_0028DFT_0029.html */
void ft(int n, fftw_complex *in, fftw_complex *out)
{
  int j, k, t;
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
      t = j * k % n;
      out[k][0] += in[j][0]*c[t] + in[j][1]*s[t];
      out[k][1] += in[j][1]*c[t] - in[j][0]*s[t];
    }
  }
  free(c);
  free(s);
}


int main(void)
{
  fftw_complex *in, *out, *out2; /* double [2] */
  fftw_plan p;
  int i, N = 16;

  in = (fftw_complex *) fftw_malloc(sizeof(*in) * N);
  out = (fftw_complex *) fftw_malloc(sizeof(*out) * N);
  out2 = (fftw_complex *) fftw_malloc(sizeof(*out2) * N);
  p = fftw_plan_dft_1d(N, in, out, FFTW_FORWARD, FFTW_ESTIMATE);

  for (i = 0; i < N; i++) {
    in[i][0] = sin(2*M_PI*i/N) + 3.*cos(6*M_PI*i/N);
    in[i][1] = 4*sin(8*M_PI*i/N);
  }

  fftw_execute(p);
  ft(N, in, out2);

  for (i = 0; i < N; i++)
    printf("%6d %20.10f %20.10f |  %20.10f %20.10f\n",
        i, out[i][0], out[i][1], out2[i][0], out2[i][1]);

  fftw_destroy_plan(p); fftw_cleanup();
  fftw_free(in); fftw_free(out); fftw_free(out2);
  return 0;
}

