#include <stdint.h>
#include "params.h"
#include "sign.h"
#include "polyvec.h"
#include "poly.h"
#include "symmetric.h"
#include "fips202.h"

/*************************************************
* Name:        crypto_sign_keypair
*
* Description: Generates public and private key.
*
* Arguments:   - uint8_t *pk: pointer to output public key (allocated
*                             array of CRYPTO_PUBLICKEYBYTES bytes)
*              - uint8_t *sk: pointer to output private key (allocated
*                             array of CRYPTO_SECRETKEYBYTES bytes)
*
* Returns 0 (success)
**************************************************/
int crypto_sign_keypair_derand(polyvecl *s1_out, uint8_t *pk, uint8_t *sk, uint8_t seed[SEEDBYTES]) {
  uint8_t seedbuf[3*SEEDBYTES];
  uint8_t tr[CRHBYTES];
  const uint8_t *rho, *rhoprime, *key;
  polyvecl mat[K];
  polyvecl s1, s1hat;
  polyveck s2, t1, t0;

  /* Get randomness for rho, rhoprime and key */
  shake256(seedbuf, 3*SEEDBYTES, seed, SEEDBYTES);
  rho = seedbuf;
  rhoprime = seedbuf + SEEDBYTES;
  key = seedbuf + 2*SEEDBYTES;

  /* Sample short vectors s1 and s2 */
  polyvecl_uniform_eta(&s1, rhoprime, 0);

  for (int i = 0; i < N; ++i) {
    s1_out->vec[0].coeffs[i] = s1.vec[0].coeffs[i];
  }

  /* Matrix-vector multiplication */
  s1hat = s1;
  polyvecl_ntt(&s1hat);

  for (int i = 0; i < N; ++i) {
    sk[4*i    ] =  s1hat.vec[0].coeffs[i]        & 0xFF;
    sk[4*i + 1] = (s1hat.vec[0].coeffs[i] >> 8 ) & 0xFF;
    sk[4*i + 2] = (s1hat.vec[0].coeffs[i] >> 16) & 0xFF;
    sk[4*i + 3] = (s1hat.vec[0].coeffs[i] >> 24) & 0xFF;
  }

  return 0;
}