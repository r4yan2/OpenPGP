#include "errors.h"
#include "../Misc/sigtypes.h"

namespace { // anonymous namespace

    struct KeyErrCategory : std::error_category{
        const char* name() const noexcept override;
        std::string message(int ev) const override;
    };

    const char* KeyErrCategory::name() const noexcept{
        return "key";
    }

    std::string KeyErrCategory::message(int ev) const{
        switch (static_cast<KeyErrc>(ev))
        {
            case KeyErrc::BadKey:
                return "Error: packet is not a PGP Key.";

            case KeyErrc::NotEnoughPackets:
                return "Error: Not enough packets (minimum 2).";

            case KeyErrc::FirstPacketWrong:
                return "Error: First packet is not a Primary Key.";

            case KeyErrc::SignAfterPrimary:
                return "Error: Signature different from revocation found after the primary key.";

            case KeyErrc::NotUserID:
                return "Error: Packet is not a User ID or User Attribute Packet.";

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
        }

        return "Not recognized error";
    }

    const KeyErrCategory theKeyErrCategory{};

}

std::error_code make_error_code(KeyErrc e) {
    return {static_cast<int>(e), theKeyErrCategory};
}
