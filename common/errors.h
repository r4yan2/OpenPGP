#include <string>

enum class KeyErrc{
    BadKey                  = 1,    // "Error: Bad key type: " + std::to_string(pgp.get_type()) + "\n"
    NotEnoughPackets        = 2,    // "Error: Not enough packets (minimum 2).\n"
    FirstPacketWrong        = 3,    // "Error: First packet is not a " + Packet::NAME.at(key) + ".\n"
    SignAfterPrimary        = 4,    // "Error: Packet " + std::to_string(i) + " following " + Packet::NAME.at(key) + " is not a key revocation signature.\n"
    AtLeastOneUID           = 5,    // "Error: Needed at least one UserID"
    NotUserID               = 6,    // "Error: Packet is not a User ID or User Attribute Packet.\n"
    WrongSignature          = 7,    // "Error: Signature is not a certification or revocation."
    NoSubkeyFound           = 8,    // "Error: Bad subkey packet.\n"
    Ver3Subkey              = 9,    // "Error: Version 3 keys MUST NOT have subkeys.\n";
    NoSubkeyBinding         = 10,   // "Error: No " + Signature_Type::NAME.at(Signature_Type::SUBKEY_BINDING_SIGNATURE) + " packet found following subkey.\n"
    NotAllPacketsAnalyzed   = 11    // the index should be at the end of the packets
};
namespace std{
    template <>
    struct is_error_code_enum<KeyErrc> : true_type {};
}

std::error_code make_error_code(KeyErrc);

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
        }
    }

    const KeyErrCategory theKeyErrCategory{};

}


std::error_code make_error_code(KeyErrc e){
    return {static_cast<int>(e), theKeyErrCategory};
}