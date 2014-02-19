/* complex-to-complex fast Fourier tranform using FFTW
 * sudo apt-get install fftw3-dev
 * gcc 3d.c -lfftw3 */
#include <stdlib.h>
#include <math.h>
#include <fftw3.h>


void mul3(double *w, double *x, double *y, double *z)
{
  double t[2];
  t[0] = x[0] * y[0] - x[1] * y[1];
  t[1] = x[0] * y[1] + x[1] * y[0];
  w[0] = t[0] * z[0] - t[1] * z[1];
  w[1] = t[0] * z[1] + t[1] * z[0];
}

/* brute-force calculation
 * http://www.fftw.org/doc/The-1d-Discrete-Fourier-Transform-_0028DFT_0029.html */
void ft3d(int n0, int n1, int n2, fftw_complex *in, fftw_complex *out)
{
  int j0, j1, j2, j, k0, k1, k2, k;
  double (*cs0)[2], (*cs1)[2], (*cs2)[2], cs[2];

  cs0 = calloc(n0, sizeof(*cs0));
  cs1 = calloc(n1, sizeof(*cs1));
  cs2 = calloc(n2, sizeof(*cs2));
  for (j = 0; j < n0; j++) {
    cs0[j][0] = cos(2*M_PI*j/n0);
    cs0[j][1] = sin(2*M_PI*j/n0);
  }
  for (j = 0; j < n1; j++) {
    cs1[j][0] = cos(2*M_PI*j/n1);
    cs1[j][1] = sin(2*M_PI*j/n1);
  }
  for (j = 0; j < n2; j++) {
    cs2[j][0] = cos(2*M_PI*j/n2);
    cs2[j][1] = sin(2*M_PI*j/n2);
  }
  for (k0 = 0; k0 < n0; k0++)
  for (k1 = 0; k1 < n1; k1++)
  for (k2 = 0; k2 < n2; k2++) {
    k = k0 * n1 * n2 + k1 * n2 + k2;
    out[k][0] = out[k][1] = 0;
    for (j0 = 0; j0 < n0; j0++)
    for (j1 = 0; j1 < n1; j1++)
    for (j2 = 0; j2 < n2; j2++) {
      j = j0 * n1 * n2 + j1 * n2 + j2;
      mul3(cs, cs0[j0 * k0 % n0], cs1[j1 * k1 % n1], cs2[j2 * k2 % n2]);
      out[k][0] += in[j][0]*cs[0] + in[j][1]*cs[1];
      out[k][1] += in[j][1]*cs[0] - in[j][0]*cs[1];
    }
  }
  free(cs0);
  free(cs1);
  free(cs2);
}


#define N0 5
#define N1 7
#define N2 8

int main(void)
{
  fftw_complex in[N0][N1][N2], out[N0][N1][N2], out2[N0][N1][N2]; /* double [2] */
  fftw_plan p;
  int i0, i1, i2;

  p = fftw_plan_dft_3d(N0, N1, N2, &in[0][0][0], &out[0][0][0], FFTW_FORWARD, FFTW_ESTIMATE);

  for (i0 = 0; i0 < N0; i0++)
  for (i1 = 0; i1 < N1; i1++)
  for (i2 = 0; i2 < N2; i2++) {
    in[i0][i1][i2][0] = sin(2*M_PI*i0/N0) + 3*cos(6*M_PI*i1/N1);
    in[i0][i1][i2][1] = 5*cos(4*M_PI*i2/N2);
  }

  fftw_execute(p);
  ft3d(N0, N1, N2, &in[0][0][0], &out2[0][0][0]);

  for (i0 = 0; i0 < N0; i0++)
  for (i1 = 0; i1 < N1; i1++)
  for (i2 = 0; i2 < N2; i2++)
    if ( fabs(out[i0][i1][i2][0]) > 1e-3  || fabs(out[i0][i1][i2][1]) > 1e-3
      || fabs(out2[i0][i1][i2][0]) > 1e-3 || fabs(out2[i0][i1][i2][1]) > 1e-3 )
      printf("%6d %6d %6d: %20.10f %20.10f |  %20.10f %20.10f\n",
        i0, i1, i2, out[i0][i1][i2][0], out[i0][i1][i2][1],
        out2[i0][i1][i2][0], out2[i0][i1][i2][1]);

  fftw_destroy_plan(p);
  fftw_cleanup();
  return 0;
}

