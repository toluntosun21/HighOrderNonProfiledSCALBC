/*
    This file is part of the ChipWhisperer Example Targets
    Copyright (C) 2012-2017 NewAE Technology Inc.

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/
#ifdef STM32F3XX
#include "stm32f3xx.h"
#endif
#include "hal.h"
#include <stdint.h>
#include <stdlib.h>
#include "simpleserial.h"
#include "params.h"
#include "polyvec.h"
#include "masking_interface.h"
#include "fips202.h"

#define KYBER_POLYCOMPRESSEDBYTES_DU (320)

uint8_t sk[N*sizeof(int32_t)]; // 1024
polyvecl s1;
masked_polyvecl ms1;


uint8_t dummy[1];

int prng_off = 0;

void system_init()
{
#ifdef STM32F3XX
    SCB->CPACR |= ((3UL << 10*2) | ((3UL << 11*2)));
#endif
}

uint8_t gen_key(uint8_t* k, uint8_t len)
{
    crypto_sign_keypair_derand(&s1, NULL, sk, k); // only returns s1[0] in NTT domain
    //because of 128-bytes read and write buffer, dividing the output to chunks
    simpleserial_put('r', 128, sk);
    simpleserial_put('r', 128, sk + 128);
    simpleserial_put('r', 128, sk + 256);
    simpleserial_put('r', 128, sk + 384);
    simpleserial_put('r', 128, sk + 512);
    simpleserial_put('r', 128, sk + 640);
    simpleserial_put('r', 128, sk + 768);
    simpleserial_put('r', 128, sk + 896);
    return 0x00;
}

uint8_t sign(uint8_t* c, uint8_t len)
{
    mask_polyvecl(&ms1, &s1);
    masked_crypto_sign_signature(c, &ms1);
    simpleserial_put('r', 0, dummy);
    return 0x00;
}

uint8_t set_prng_off(uint8_t* x, uint8_t len)
{
    prng_off = 1;
    return 0x00;
}


uint8_t set_prng_on(uint8_t* x, uint8_t len)
{
    prng_off = 0;
    return 0x00;
}


int main(void)
{
    platform_init();
    init_uart();
    trigger_setup();
    system_init();

    simpleserial_init();
    simpleserial_addcmd('p', 32, sign);
    simpleserial_addcmd('k', 32, gen_key);
    simpleserial_addcmd('x', 0, set_prng_off);
    simpleserial_addcmd('q', 0, set_prng_on);

    while(1)
        simpleserial_get();
}
