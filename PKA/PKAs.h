/*
PKAs.h
List of Public Key Algorithm headers

Copyright (c) 2013 - 2017 Jason Lee @ calccrypto at gmail.com

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
*/

#ifndef __PKAS__
#define __PKAS__

#include <map>
#include <stdexcept>

#include "PKA.h"

#include "DSA.h"
#include "ElGamal.h"
#include "RSA.h"

namespace OpenPGP {
    namespace PKA {
        // 9.1.  Public-Key Algorithms
        //
        //       ID           Algorithm
        //       --           ---------
        //       1          - RSA (Encrypt or Sign) [HAC]
        //       2          - RSA Encrypt-Only [HAC]
        //       3          - RSA Sign-Only [HAC]
        //       16         - ELGAMAL (Encrypt-Only) [ELGAMAL] [HAC]
        //       17         - DSA (Digital Signature Algorithm) [FIPS186] [HAC]
        //       18         - Reserved for Elliptic Curve
        //       19         - Reserved for ECDSA
        //       20         - Reserved (formerly ELGAMAL Encrypt or Sign)
        //       21         - Reserved for Diffie-Hellman (X9.42,
        //                    as defined for IETF-S/MIME)
        //       100 to 110 - Private/Experimental algorithm

        namespace ID {
            const uint8_t RSA_ENCRYPT_OR_SIGN           = 1;
            const uint8_t RSA_ENCRYPT_ONLY              = 2;
            const uint8_t RSA_SIGN_ONLY                 = 3;
            const uint8_t ELGAMAL                       = 16;
            const uint8_t DSA                           = 17;
            #ifdef GPG_COMPATIBLE
            const uint8_t ECDH                          = 18;
            const uint8_t ECDSA                         = 19;
            const uint8_t EdDSA                         = 22;
            #endif
        }

        const std::map <uint8_t, std::string> NAME = {
            std::make_pair(ID::RSA_ENCRYPT_OR_SIGN, "RSA (Encrypt or Sign)"),
            std::make_pair(ID::RSA_ENCRYPT_ONLY,    "RSA Encrypt-Only"),       // deprecated
            std::make_pair(ID::RSA_SIGN_ONLY,       "RSA Sign-Only"),          // deprecated
            std::make_pair(ID::ELGAMAL,             "ELGAMAL (Encrypt-Only)"),
            std::make_pair(ID::DSA,                 "DSA"),
            #ifdef GPG_COMPATIBLE
            std::make_pair(ID::ECDH,                 "ECDH"),
            std::make_pair(ID::ECDSA,                 "ECDSA"),
            std::make_pair(ID::EdDSA,                 "EdDSA"),
            #else
            std::make_pair(18,                      "Reserved for Elliptic Curve"),
            std::make_pair(19,                      "Reserved for ECDSA"),
            #endif
            std::make_pair(20,                      "Reserved (formerly ELGAMAL Encrypt or Sign)"),
            std::make_pair(21,                      "Reserved for Diffie-Hellman (X9.42), as defined for IETF-S / MIME)"),
            std::make_pair(100,                     "Private/Experimental algorithm"),
            std::make_pair(101,                     "Private/Experimental algorithm"),
            std::make_pair(102,                     "Private/Experimental algorithm"),
            std::make_pair(103,                     "Private/Experimental algorithm"),
            std::make_pair(104,                     "Private/Experimental algorithm"),
            std::make_pair(105,                     "Private/Experimental algorithm"),
            std::make_pair(106,                     "Private/Experimental algorithm"),
            std::make_pair(107,                     "Private/Experimental algorithm"),
            std::make_pair(108,                     "Private/Experimental algorithm"),
            std::make_pair(109,                     "Private/Experimental algorithm"),
            std::make_pair(110,                     "Private/Experimental algorithm"),
        };


        #ifdef GPG_COMPATIBLE
        namespace CURVE_OID {
            const std::string NIST_256          = "2A8648CE3D030107";
            const std::string NIST_384          = "2B81040022";
            const std::string NIST_521          = "2B81040023";
            const std::string BRAINPOOL_256     = "2B2403030208010107";
            const std::string BRAINPOOL_512     = "2B240303020801010D";
            const std::string ED_255            = "2B06010401DA470F01";
            const std::string CURVE_255         = "2B060104019755010501";
        }

        const std::map <std::string, std::string> CURVE_OID_STRING = {
            std::make_pair(CURVE_OID::NIST_256,         "1.2.840.10045.3.1.7"),
            std::make_pair(CURVE_OID::NIST_384,         "1.3.132.0.34"),
            std::make_pair(CURVE_OID::NIST_521,         "1.3.132.0.35"),
            std::make_pair(CURVE_OID::BRAINPOOL_256,    "1.3.36.3.3.2.8.1.1.7"),
            std::make_pair(CURVE_OID::BRAINPOOL_512,    "1.3.36.3.3.2.8.1.1.13"),
            std::make_pair(CURVE_OID::ED_255,           "1.3.6.1.4.1.11591.15.1"),
            std::make_pair(CURVE_OID::CURVE_255,        "1.3.6.1.4.1.3029.1.5.1")
        };

        const std::map <std::string, std::string> CURVE_NAME = {
                std::make_pair(CURVE_OID::NIST_256,      "NIST P-256"),
                std::make_pair(CURVE_OID::NIST_384,      "NIST P-384"),
                std::make_pair(CURVE_OID::NIST_521,      "NIST P-521"),
                std::make_pair(CURVE_OID::BRAINPOOL_256, "brainpoolP256r1"),
                std::make_pair(CURVE_OID::BRAINPOOL_512, "brainpoolP512r1"),
                std::make_pair(CURVE_OID::ED_255,        "Ed25519"),
                std::make_pair(CURVE_OID::CURVE_255,     "Curve25519")
        };

        const std::map <std::string, uint8_t> CURVE_OID_LENGTH = {
                std::make_pair(CURVE_OID::NIST_256,      8),
                std::make_pair(CURVE_OID::NIST_384,      5),
                std::make_pair(CURVE_OID::NIST_521,      5),
                std::make_pair(CURVE_OID::BRAINPOOL_256, 9),
                std::make_pair(CURVE_OID::BRAINPOOL_512, 9),
                std::make_pair(CURVE_OID::ED_255,        9),
                std::make_pair(CURVE_OID::CURVE_255,     10)
        };

        const std::map <std::string, MPI> CURVE_GENERATOR = {
                std::make_pair(CURVE_OID::NIST_256,      hextompi("036B17D1F2E12C4247F8BCE6E563A440F277037D812DEB33A0F4A13945D898C296")),
                std::make_pair(CURVE_OID::NIST_384,      hextompi("04AA87CA22BE8B05378EB1C71EF320AD746E1D3B628BA79B9859F741E082542A385502F25DBF55296C3A545E3872760AB73617DE4A96262C6F5D9E98BF9292DC29F8F41DBD289A147CE9DA3113B5F0B8C00A60B1CE1D7E819D7A431D7C90EA0E5F")),
                std::make_pair(CURVE_OID::NIST_521,      hextompi("0400C6858E06B70404E9CD9E3ECB662395B4429C648139053FB521F828AF606B4D3DBAA14B5E77EFE75928FE1DC127A2FFA8DE3348B3C1856A429BF97E7E31C2E5BD66011839296A789A3BC0045C8A5FB42C7D1BD998F54449579B446817AFBD17273E662C97EE72995EF42640C550B9013FAD0761353C7086A272C24088BE94769FD16650")),
                std::make_pair(CURVE_OID::BRAINPOOL_256, hextompi("048BD2AEB9CB7E57CB2C4B482FFC81B7AFB9DE27E1E3BD23C23A4453BD9ACE3262547EF835C3DAC4FD97F8461A14611DC9C27745132DED8E545C1D54C72F046997")),
                std::make_pair(CURVE_OID::BRAINPOOL_512, hextompi("0481AEE4BDD82ED9645A21322E9C4C6A9385ED9F70B5D916C1B43B62EEF4D0098EFF3B1F78E2D0D48D50D1687B93B97D5F7C6D5047406A5E688B352209BCB9F8227DDE385D566332ECC0EABFA9CF7822FDF209F70024A57B1AA000C55B881F8111B2DCDE494A5F485E5BCA4BD88A2763AED1CA2B2FA8F0540678CD1E0F3AD80892")),
                std::make_pair(CURVE_OID::ED_255,        9),
                std::make_pair(CURVE_OID::CURVE_255,     10)
        };

        const std::map <std::string, MPI> CURVE_ORDER = {
                std::make_pair(CURVE_OID::NIST_256,      hextompi("FFFFFFFF00000000FFFFFFFFFFFFFFFFBCE6FAADA7179E84F3B9CAC2FC632551")),
                std::make_pair(CURVE_OID::NIST_384,      hextompi("FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFC7634D81F4372DDF581A0DB248B0A77AECEC196ACCC52973")),
                std::make_pair(CURVE_OID::NIST_521,      hextompi("01FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFA51868783BF2F966B7FCC0148F709A5D03BB5C9B8899C47AEBB6FB71E91386409")),
                std::make_pair(CURVE_OID::BRAINPOOL_256, hextompi("A9FB57DBA1EEA9BC3E660A909D838D718C397AA3B561A6F7901E0E82974856A7")),
                std::make_pair(CURVE_OID::BRAINPOOL_512, hextompi("AADD9DB8DBE9C48B3FD4E6AE33C9FC07CB308DB3B3C9D20ED6639CCA70330870553E5C414CA92619418661197FAC10471DB1D381085DDADDB58796829CA90069")),
                std::make_pair(CURVE_OID::ED_255,        9),
                std::make_pair(CURVE_OID::CURVE_255,     10)
        };
        #endif

        const std::map <std::string, uint8_t> NUMBER = {
            std::make_pair("RSA_ENCRYPT_OR_SIGN",   ID::RSA_ENCRYPT_OR_SIGN),
            std::make_pair("RSA_ENCRYPT_ONLY",      ID::RSA_ENCRYPT_ONLY),
            std::make_pair("RSA_SIGN_ONLY",         ID::RSA_SIGN_ONLY),
            std::make_pair("ELGAMAL",               ID::ELGAMAL),
            std::make_pair("DSA",                   ID::DSA),
            #ifdef GPG_COMPATIBLE
            std::make_pair("ECDH",                  ID::ECDH),
            std::make_pair("ECDSA",                 ID::ECDSA),
            std::make_pair("EdDSA",                 ID::EdDSA),
            #endif
        };

        const std::map <uint8_t, char> SHORT = {
            std::make_pair(ID::RSA_ENCRYPT_OR_SIGN, 'R'),
            std::make_pair(ID::RSA_ENCRYPT_ONLY,    'R'),
            std::make_pair(ID::RSA_SIGN_ONLY,       'R'),
            std::make_pair(ID::ELGAMAL,             'g'),
            std::make_pair(ID::DSA,                 'D'),
            #ifdef GPG_COMPATIBLE
            std::make_pair(ID::ECDH,                 'e'),
            std::make_pair(ID::ECDSA,                'e'),
            std::make_pair(ID::EdDSA,                'e'),
            #endif
        };

        bool can_encrypt(const uint8_t alg);
        bool can_sign(const uint8_t alg);
        bool is_RSA(const uint8_t alg);

        /*
            params:
                DSA = {L, N}
                ELGAMAL = {bits}
                RSA = {bits}

            pub and pri are destination containers
        */
        Params generate_params(const uint8_t pka, const std::size_t bits);
        uint8_t generate_keypair(const uint8_t pka, const Params & params, Values & pri, Values & pub);
    }
}

#endif
