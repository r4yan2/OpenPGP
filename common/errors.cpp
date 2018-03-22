#include "errors.h"
#include "../Misc/sigtypes.h"

namespace { // anonymous namespace

    struct ParsingErrCategory : std::error_category{
        const char* name() const noexcept override;
        std::string message(int ev) const override;
    };

    struct KeyErrCategory : std::error_category{
        const char* name() const noexcept override;
        std::string message(int ev) const override;
    };



    const char* KeyErrCategory::name() const noexcept{
        return "key";
    }

    const char* ParsingErrCategory::name() const noexcept{
        return "Parsing";
    }

    std::string KeyErrCategory::message(int ev) const{
        switch (static_cast<KeyErrc>(ev)){
            case KeyErrc::BadKey:
                return "Error: packet is not a PGP Key.";

            case KeyErrc::NotEnoughPackets:
                return "Error: Not enough packets (minimum 2).";

            case KeyErrc::FirstPacketWrong:
                return "Error: First packet is not a Primary Key.";

            case KeyErrc::SignAfterPrimary:
                return "Error: Signature different from revocation found after the primary key.";

            case KeyErrc::WrongSignature:
                return "Error: Signature is not a certification or revocation.";

            case KeyErrc::AtLeastOneUID:
                return "Error: Needed at least one UserID.";

            case KeyErrc::NoSubkeyFound:
                return "Error: No subkey found.";

            case KeyErrc::Ver3Subkey:
                return "Error: Version 3 keys MUST NOT have subkeys.";

            case KeyErrc::NoSubkeyBinding:
                return "Error: No " + OpenPGP::Signature_Type::NAME.at(OpenPGP::Signature_Type::SUBKEY_BINDING_SIGNATURE) + " packet found following subkey.";

            case KeyErrc::NotAllPacketsAnalyzed:
                return "Error: Not all packets have been analyzed";

            case KeyErrc::NotExistingVersion:
                return "Error: Version should be 2, 3 or 4";

            case KeyErrc::NotAPublicKey:
                return "Error: ASCII Armor type is not PUBLIC_KEY_BLOCK.";

            case KeyErrc::NotASecretKey:
                return "Error: ASCII Armor type is not PRIVATE_KEY_BLOCK.";

            case KeyErrc::DifferentKeys:
                return "Error: Merge not possible between two different keys";

            default:
                return "Not recognized error";
        }
        //return "Not recognized error";
    }

    std::string ParsingErrCategory::message(int ev) const{
        switch (static_cast<ParsingErrc>(ev)){
            case ParsingErrc::ParsingError:
                return "Error: Could not parse data";

            case ParsingErrc::PubkeyAlgorithmNotFound:
                return "Error: Public key Algorithm not found";

            case ParsingErrc::PubkeyVersionNotFound:
                return "Error: Public key Version not found";

            case ParsingErrc::LengthLEQZero:
                return "Error: Length of packet";

            case ParsingErrc::SignaturePKANotFound:
                return "Error: Signature PKA not found";

            case ParsingErrc::SignatureHashNotFound:
                return "Error: Signature HASH not found";

            case ParsingErrc::SignatureVersionNotFound:
                return "Error: Signature Version not found";

            case ParsingErrc::SignatureLengthWrong:
                return "Error: Length of hashed material must be 5";

            default:
                return "Not recognized error";
        }
    }

    const KeyErrCategory theKeyErrCategory{};
    const ParsingErrCategory theParsingErrCategory{};

}

std::error_code make_error_code(KeyErrc e) {
    return {static_cast<int>(e), theKeyErrCategory};
}

std::error_code make_error_code(ParsingErrc e) {
    return {static_cast<int>(e), theParsingErrCategory};
}
