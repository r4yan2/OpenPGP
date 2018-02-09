#include <system_error>


namespace {
    struct ParsingErrCategory : std::error_category{
        const char* name() const noexcept override;
        std::string message(int ev) const override;
        const uint16_t info;

        ParsingErrCategory(uint16_t i): info(i) {};
    };
}

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
    NotASecretKey           = 14,   // "Error: ASCII Armor type is not SECRET_KEY_BLOCK.\n"
    DifferentKeys           = 15,   // "Error: Merge not possible between two different keys\n"
};

enum class ParsingErrc{
    ParsingError            = 31,   // "Error: error during parsing data\n"
    PubkeyAlgorithmNotFound = 32,   // "Error: Public key Algorithm not found\n"
    PubkeyVersionNotFound   = 33,   // "Error: Public key version not found\n"
    LengthLEQZero           = 34,   // "Error: Length of packet <= 0\n"
    SignaturePKANotFound    = 35,   // "Error: Signature PKA not found\n"
    SignatureHashNotFound   = 36,   // "Error: Signature HASH not found\n"
    SignatureVersionNotFound = 37,   // "Error: Signature version not found\n"
    SignatureLengthWrong    = 38,   // "Error: Length of hashed material must be 5.\n"
};

namespace std{
    template <>
    struct is_error_code_enum<KeyErrc> : true_type {};
    template <>
    struct is_error_code_enum<ParsingErrc> : true_type {};
}

std::error_code make_error_code(KeyErrc);
std::error_code make_error_code(ParsingErrc, uint16_t);