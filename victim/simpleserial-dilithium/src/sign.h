#ifndef SIGN_H
#define SIGN_H

#include <stddef.h>
#include <stdint.h>
#include "params.h"
#include "polyvec.h"
#include "poly.h"

int crypto_sign_keypair_derand(polyvecl *s1_out, uint8_t *pk, uint8_t *sk, uint8_t seed[SEEDBYTES]);

#endif
