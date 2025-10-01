#include "masking_interface.h"
#include "params.h"
#include "polyvec.h"
#include "fips202.h"
#include "randombytes.h"

extern inline uint32_t rand32();


int32_t center(int32_t x){
  /* Maps elements of Z_q in [-Q, ..., Q] to representatives in [-Q/2, ..., Q/2[ */
  x += Q;
  x %= Q;
  if (x > Q/2) x -= Q;
  return x;
}



void mask_polyvecl(masked_polyvecl* mpv, polyvecl* pv){
 /* Takes an unmasked polyvecl and mask it (arith mod q), should not be used outside of testing*/
  int32_t temp;
  for(int i=0; i < L; ++i){
    for(int j=0; j < N; ++j){
      ((mpv->shares[0]).vec[i]).coeffs[j] = (pv->vec[i]).coeffs[j];
    }
  }

  for(int k=1; k < N_SHARES; ++k){
    for(int i=0; i < L; ++i){
      for(int j=0; j < N; ++j){
        temp = ((int32_t)rand32())%Q;
        ((mpv->shares[k]).vec[i]).coeffs[j] = center(temp);
        ((mpv->shares[0]).vec[i]).coeffs[j] = center((((mpv->shares[0]).vec[i]).coeffs[j] - temp)%Q);
      }
    }
  }
}
