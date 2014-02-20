/* complex-to-complex fast Fourier tranform using FFTW
 * sudo apt-get install fftw3-dev
 * gcc 1dmin.c -lfftw3 */
#include <fftw3.h>
int main(void) {
  fftw_complex a[5] = {{0,0},{1,0},{2,0},{3,0},{4,0}};
  fftw_plan p = fftw_plan_dft_1d(5, a, a, FFTW_FORWARD, FFTW_ESTIMATE); int i;
  fftw_execute(p); fftw_execute(p);
  for (i = 0; i < 5; i++) printf("%d: %8.3f %8.3f\n", i, a[i][0], a[i][1]);
  fftw_destroy_plan(p); fftw_cleanup(); return 0;
}

