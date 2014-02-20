/* complex-to-complex fast Fourier tranform using FFTW
 * sudo apt-get install fftw3-dev
 *
 * suppose libfftw3_omp.a exists in $HOME/app/lib
 * export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:$HOME/app/lib
 * gcc -fopenmp 2d_t.c -lfftw3_omp -L$HOME/app/lib
 *
 * or for the Pthread version
 * gcc 2d_t.c -lfftw3_threads -lpthread -L$HOME/app/lib
 *
 * To run the program with two threads
 * ./a.out 2
 * */
#include <time.h>
#include <stdlib.h>
#include <math.h>
#ifdef _OPENMP
#include <omp.h>
#endif
#include <fftw3.h>

int main(int argc, char **argv)
{
  fftw_complex *in; /* double [2] */
  fftw_plan p;
  int i0, i1, i, N = 4096, nthreads = -1;

  if (argc > 1) nthreads = atoi(argv[1]);
#ifdef _OPENMP
  nthreads = (nthreads < 0) ? omp_get_max_threads() : 2;
#else
  if (nthreads < 0) nthreads = 2;
#endif
  if (argc > 2) N = atoi(argv[2]);

  fftw_init_threads();
  in = (fftw_complex *) fftw_malloc(sizeof(*in) * N * N);

  for (i0 = 0; i0 < N; i0++) {
    for (i1 = 0; i1 < N; i1++) {
      i = i0 * N + i1;
      in[i][0] = i0 + 1;
      in[i][1] = i1 + 1;
    }
  }

  fftw_plan_with_nthreads(nthreads);
  p = fftw_plan_dft_2d(N, N, in, in, FFTW_FORWARD, FFTW_ESTIMATE);
  fftw_execute(p);
  p = fftw_plan_dft_2d(N, N, in, in, FFTW_BACKWARD, FFTW_ESTIMATE);
  fftw_execute(p);
  printf("%d threads, %g %g\n", nthreads, in[0][0]/(N*N), in[0][1]/(N*N));

  fftw_destroy_plan(p); fftw_cleanup_threads(); fftw_free(in);
  return 0;
}

