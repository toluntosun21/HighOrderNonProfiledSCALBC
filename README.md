# HighOrderNonProfiledSCALBC
Efficient first and higher order side-channel attacks against Lattice-Based Post-Quantum Cryptography 

# Non-Profiled Higher-Order Side-Channel Attacks against Lattice-Based Post-Quantum Cryptography

Source code for the [research paper](https://cic.iacr.org/p/2/3/31/pdf).

This repository provides a set of tools to perform non-profiled side-channel analysis attacks against (masked) implementations of Lattice-Based Cryptography (LBC):
* `victim`: ChipWhisperer-based Kyber768 and Dilithium3 victim projects.
* `attack`: CPA, HOCPA against Kyber768 and Dilithium3 polynomial multiplication and a lattice attack on top of the side-channel analysis attacks.

## Practical Experiments
### Victim

* An arbitrary order masked Kyber768 victim project and an arbitrary order masked Dilithium3.
* Both victims are developed for the [ChipWhisperer Framework](https://github.com/newaetech/chipwhisperer).
* The victims only contain the polynomial multiplication part to practise non-profiled attacks against NTT-based polynomial multiplication.
* Masked Kyber768 implementation is from [uclcrypto/pqm4_masked/](https://github.com/uclcrypto/pqm4_masked/) `5fe90ba`. Masked Dilithium3 implementation is from [fragerar/tches24_masked_Dilithium](https://github.com/fragerar/tches24_masked_Dilithium/tree/master) `5b5fd32`.

### Attack
* HOCPA against first-order masked Kyber768 (using absolute value prediction function).
* Attack codes are built using [scaredcu](https://github.com/toluntosun21/scaredcu) which is GPU porting of [scared](https://gitlab.com/eshard/scared).
* Running the lattice attack requires [fpylll](https://github.com/fplll/fpylll) and implements the [paper](https://eprint.iacr.org/2023/1781.pdf).


When referring to this work in academic literature, please consider using the following bibTeX excerpt:
```
@article{10.62056/a0txl8n4e,
         author={Tolun Tosun and Elisabeth Oswald and Erkay Savaş},
         title={Non-Profiled Higher-Order Side-Channel Attacks against Lattice-Based Post-Quantum Cryptography},
         volume={2},
         number={3},
         year={2025},
         date={2025-10-06},
         issn={3006-5496},
         doi={10.62056/a0txl8n4e},
         journal={{IACR} Communications in Cryptology},
         publisher={International Association for Cryptologic Research}
}
```
