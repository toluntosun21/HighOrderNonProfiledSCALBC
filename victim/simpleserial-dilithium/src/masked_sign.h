
#ifndef MASKED_SIGN_H
#define MASKED_SIGN_H

#include <stddef.h>
#include <stdint.h>
#include "params.h"
#include "polyvec.h"
#include "poly.h"
#include "masking_interface.h"

int masked_crypto_sign_signature_from_challenge(uint8_t *sig, 
                                                masked_polyvecl* ms1);



#endif