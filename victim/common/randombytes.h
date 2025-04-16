#ifndef PQCLEAN_RANDOMBYTES_H
#define PQCLEAN_RANDOMBYTES_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

#ifdef _WIN32
/* Load size_t on windows */
#include <crtdefs.h>
#else
#include <unistd.h>
#endif /* _WIN32 */

/*
 * Write `n` bytes of high quality random bytes to `buf`
 */
#define randombytes     PQCLEAN_randombytes
int randombytes(uint8_t *output, size_t n);

extern int prng_off;

inline uint32_t rand32() {
  uint32_t rand;
  if (prng_off){
    return 0;
  }
  else
  {
    randombytes((uint8_t*) &rand, sizeof(rand));
    return rand;
  }
}

#ifdef __cplusplus
}
#endif

#endif /* PQCLEAN_RANDOMBYTES_H */
