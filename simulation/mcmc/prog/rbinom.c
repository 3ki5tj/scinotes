/* generate a binomial distribution */
#include <stdio.h>

double N = 20; /* no need to be an integer */
int nsteps = 1000000; /* number of simulation steps */

#define NMAX 100
double hist[NMAX+1] = {0}; /* histogram */

/* uniform random number between 0 and 1 */
static double rand01(void)
{
  static unsigned long s1 = 5318008, s2 = 11547776, s3 = 1040032;
#define TAUS(s,a,b,c,d) (((s & c) << d) & 0xffffffffUL) ^ ((((s << a) & 0xffffffffUL)^s) >>b)
  s1 = TAUS(s1, 13, 19, 4294967294UL, 12);
  s2 = TAUS(s2,  2, 25, 4294967288UL, 4);
  s3 = TAUS(s3,  3, 11, 4294967280UL, 17);
#undef TAUS
  return (s1^s2^s3)/4294967296.0;
}

int main(void)
{
  int i = N/2, j, t;
  double r;

  for ( t = 1; t <= nsteps; t++ ) {
    if ( rand01() > 0.5 ) { /* jump to the right */
      j = i + 1;
      /* compute the acceptance probability */
      if ( j > N ) {
        r = 0; /* reject out-of-boundary moves */
      } else {
        r = (N - i) / (i + 1.0);
      }
    } else { /* jump to the left */
      j = i - 1;
      if ( j < 0 ) {
        r = 0; /* reject out-of-boundary moves */
      } else {
        r = i / (N - i + 1.0);
      }
    }

    if ( r > 1 || rand01() < r ) {
      i = j;
    }

    hist[i] += 1;
  }

  for ( i = 0; i <= N; i++ ) {
    hist[i] /= nsteps; /* normalized the histogram */
    printf("%4d %8.6f ", i, hist[i]);
    for ( j = 0; j < hist[i]*200; j++) printf("*");
    printf("\n");
  }
  return 0;
}

