#include <stdio.h>
#include <math.h>
#include <limits.h>

typedef unsigned long long Entero_grande;
#define ENTERO_MAS_GRANDE  ULLONG_MAX

int primo(Entero_grande n)
{
  volatile int p;
  int id, nthreads;
  Entero_grande i, s;

  p = (n % 2 != 0 || n == 2);

  if (p) {
    s = sqrt(n);
  #pragma omp parallel private(id, i)
  {
  	nthreads = omp_get_num_threads();
  	id = omp_get_thread_num();
    for (i =3+(id*2); p && i <= s; i += 2*nthreads)
      if (n % i == 0) p = 0;
  }
  }
  return p;
}

int main()
{
  Entero_grande n;

  for (n = ENTERO_MAS_GRANDE; !primo(n); n -= 2) {
    /* NADA */
  }

  printf("El mayor primo que cabe en %d bytes es %llu.\n",
         sizeof(Entero_grande), n);

  return 0;
}
