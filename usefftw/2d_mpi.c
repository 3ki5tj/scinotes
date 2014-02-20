/* 2D FFT with MPI
 * suppose libfftw3_mpi.a and libfftw3.a exist in $HOME/app/lib
 * mpicc 2d_mpi.c -lfftw3_mpi -lfftw3 -L$HOME/app/lib -I$HOME/app/include
 * mpirun -np 2 ./a.out
 * */
#include <fftw3-mpi.h>

int main(int argc, char **argv)
{
  const ptrdiff_t N0 = 5, N1 = 6;
  fftw_plan p;
  fftw_complex *a;
  ptrdiff_t size_l = N0 * N1, n0_l = N0, i0_l = 0, i, j;
  int rank = 0, size = 1;

  MPI_Init(&argc, &argv);
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  MPI_Comm_size(MPI_COMM_WORLD, &size);
  fftw_mpi_init();
  size_l = fftw_mpi_local_size_2d(N0, N1, MPI_COMM_WORLD, &n0_l, &i0_l);
  a = fftw_alloc_complex(size_l);

  for (i = 0; i < n0_l; i++)
    for (j = 0; j < N1; j++) {
      a[i*N1 + j][0] = i0_l + 1;
      a[i*N1 + j][1] = j + 1;
    }

  p = fftw_mpi_plan_dft_2d(N0, N1, a, a, MPI_COMM_WORLD,
                           FFTW_FORWARD, FFTW_ESTIMATE);
  fftw_execute(p);
  fftw_destroy_plan(p);

  p = fftw_mpi_plan_dft_2d(N0, N1, a, a, MPI_COMM_WORLD,
                           FFTW_BACKWARD, FFTW_ESTIMATE);
  fftw_execute(p);
  fftw_destroy_plan(p);

  printf("%d/%d: %g (%d) %g, %d\n",
      rank, size, a[0][0]/(N0*N1), i0_l + 1, a[0][1]/(N0*N1), size_l);
  MPI_Finalize();
  return 0;
}
