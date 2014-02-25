    /* complex-to-complex fast Fourier tranform using FFTW
     * gcc 1dex1.c -lfftw3 */
    #include <stdlib.h>
    #include <math.h>
    #include <fftw3.h>
    #define N 16
    int main(void)
    {
      fftw_complex in[N], out[N], in2[N]; /* double [2] */
      fftw_plan p, q;
      int i;

      /* prepare a cosine wave of frequency 3 */
      for (i = 0; i < N; i++) {
        in[i][0] = cos(2*M_PI*3*i/N);
        in[i][1] = 0;
      }

      /* forward Fourier transform, save the result in 'out' */
      p = fftw_plan_dft_1d(N, in, out, FFTW_FORWARD, FFTW_ESTIMATE);
      fftw_execute(p);
      for (i = 0; i < N; i++)
        printf("freq: %3d %+9.5f %+9.5f I\n", i, out[i][0], out[i][1]);
      fftw_destroy_plan(p);

      /* backward Fourier transform, save the result in 'in2' */
      printf("\nInverse transform:\n");
      q = fftw_plan_dft_1d(N, out, in2, FFTW_BACKWARD, FFTW_ESTIMATE);
      fftw_execute(q);
      /* normalize */
      for (i = 0; i < N; i++) {
        in2[i][0] *= 1./N;
        in2[i][1] *= 1./N;
      }
      for (i = 0; i < N; i++)
        printf("recover: %3d %+9.5f %+9.5f I vs. %+9.5f %+9.5f I\n",
            i, in[i][0], in[i][1], in2[i][0], in2[i][1]);
      fftw_destroy_plan(q);

      fftw_cleanup();
      return 0;
    }

