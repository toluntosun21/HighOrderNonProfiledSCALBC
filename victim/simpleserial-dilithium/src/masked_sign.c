#include <stdint.h>
#include "params.h"
#include "sign.h"
#include "polyvec.h"
#include "poly.h"
#include "fips202.h"

#include "masked_sign.h"
#include "masking_interface.h"
#include "masked_polyvec_operations.h"



/***************************************************
  The functon is minimized for SCA
***************************************************/
int masked_crypto_sign_signature(uint8_t *sig, 
                                 masked_polyvecl* ms1)
{
  unsigned int n;
  uint16_t nonce = 0;
  masked_polyvecl mz;
  poly cp;

  poly_challenge(&cp, sig);

  poly_ntt(&cp);

  masked_polyvecl_ntt(ms1);

  trigger_high();

  masked_polyvecl_pointwise_poly_montgomery(&mz, &cp, ms1);  

  trigger_low();

  return 0;
}
