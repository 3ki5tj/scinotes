/* http://stackoverflow.com/questions/3114448 */
#include <stdio.h>
#include <math.h>
#include <fftw3.h>
int main(void)
{
  fftw_complex *in, *out;
  fftw_plan p;
  int i, j, w = 16, h = 16;
  double a = 2;
  in = (fftw_complex *) fftw_malloc(sizeof(fftw_complex) * w * h);
  out = (fftw_complex *) fftw_malloc(sizeof(fftw_complex) * w * h);
  for (i = 0; i < w; i++)
    for (j = 0; j < h; j++) {
      in[i * h + j][0] = exp(-1. * ((i - w / 2) * (i - w / 2) + (j - h / 2) * (j - h / 2)) / (a * a));
      in[i * h + j][1] = 0;
    }
  p = fftw_plan_dft_2d(w, h, in, out, FFTW_FORWARD, FFTW_ESTIMATE);
  fftw_execute(p);
  for (i = 0; i < w; i++)
    for (j = 0; j < h; j++)
      printf("%4d %4d: %+9.4f %+9.4f i\n", i, j, out[i * h + j][0], out[i * h + j][1]);
  fftw_destroy_plan(p); fftw_cleanup();
  fftw_free(in); fftw_free(out);
  return 0;
}



