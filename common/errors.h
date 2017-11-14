#include <system_error>


enum class KeyErrc{
    NotExistingVersion      = 1,    // "Error: Version should be 2, 3 or 4"
    BadKey                  = 2,    // "Error: Bad key type: " + std::to_string(pgp.get_type()) + "\n"
    NotEnoughPackets        = 3,    // "Error: Not enough packets (minimum 2).\n"
    FirstPacketWrong        = 4,    // "Error: First packet is not a " + Packet::NAME.at(key) + ".\n"
    SignAfterPrimary        = 5,    // "Error: Packet " + std::to_string(i) + " following " + Packet::NAME.at(key) + " is not a key revocation signature.\n"
    AtLeastOneUID           = 6,    // "Error: Needed at least one UserID"
    NotUserID               = 7,    // "Error: Packet is not a User ID or User Attribute Packet.\n"
    WrongSignature          = 8,    // "Error: Signature is not a certification or revocation."
    NoSubkeyFound           = 9,    // "Error: Bad subkey packet.\n"
    Ver3Subkey              = 10,   // "Error: Version 3 keys MUST NOT have subkeys.\n";
    NoSubkeyBinding         = 11,   // "Error: No " + Signature_Type::NAME.at(Signature_Type::SUBKEY_BINDING_SIGNATURE) + " packet found following subkey.\n"
    NotAllPacketsAnalyzed   = 12,   // "Error: the index should be at the end of the packets"
    NotAPublicKey           = 13,   // "Error: ASCII Armor type is not PUBLIC_KEY_BLOCK.\n"
    NotASecretKey           = 14    // "Error: ASCII Armor type is not SECRET_KEY_BLOCK.\n"
};
namespace std{
    template <>
    struct is_error_code_enum<KeyErrc> : true_type {};
}

std::error_code make_error_code(KeyErrc);
