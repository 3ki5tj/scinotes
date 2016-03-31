#include <stdio.h>

/* Tausworthe random number generator uniform random number between 0 and 1 */
double rand01(void)
{
  static unsigned long s1 = 5318008, s2 = 11547776, s3 = 1040032;
#define TAUS(s,a,b,c,d) (((s & c) << d) & 0xffffffffUL) ^ ((((s << a) & 0xffffffffUL)^s) >>b)
  s1 = TAUS(s1, 13, 19, 4294967294UL, 12);
  s2 = TAUS(s2,  2, 25, 4294967288UL, 4);
  s3 = TAUS(s3,  3, 11, 4294967280UL, 17);
#undef TAUS
  return (s1 ^ s2 ^ s3) / 4294967296.0;
}

/* single trial of length-n trajectory */
static double getvar(int n, double r)
{
  int i;
  double x, s = 0;

  x = ( rand01() > 0.5 ? 1 : -1 );
  for ( i = 0; i < n; i++ ) {
    if ( rand01() < r ) {
      x = ( rand01() > 0.5 ? 1 : -1 );
    }
    s += x;
  }

  return s * s;
}

/* multiple trials */
static double getvar_m(int n, double r, int m)
{
  int j;
  double s, ss = 0;

  for ( j = 0; j < m; j++ ) {
    s = getvar(n, r);
    ss += s;
  }

  return ss / m;
}

int main(void)
{
  double alice, bob;

  alice = getvar_m(10000, 1, 1000);
  bob = getvar_m(10000, 0.5, 1000);

  printf("alice %g, bob %g, ratio %g\n", alice, bob, bob/alice);

  return 0;
}
