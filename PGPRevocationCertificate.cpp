#include "PGPRevocationCertificate.h"

PGPRevocationCertificate::PGPRevocationCertificate()
    : PGP()
{
    type = PUBLIC_KEY_BLOCK;
}

PGPRevocationCertificate::PGPRevocationCertificate(const PGP & copy)
    : PGP(copy)
{}

PGPRevocationCertificate::PGPRevocationCertificate(const PGPRevocationCertificate & copy)
    : PGP(copy)
{}

PGPRevocationCertificate::PGPRevocationCertificate(const std::string & data)
    : PGP(data)
{
    type = PUBLIC_KEY_BLOCK;

    // warn if packet sequence is not meaningful
    if (!meaningful()){
        throw std::runtime_error("Error: Data does not form a meaningful PGP Revocation Certificate");
    }
}

PGPRevocationCertificate::PGPRevocationCertificate(std::istream & stream)
    : PGP(stream)
{
    type = PUBLIC_KEY_BLOCK;

    // warn if packet sequence is not meaningful
    if (!meaningful()){
        throw std::runtime_error("Error: Data does not form a meaningful PGP Revocation Certificate");
    }
}

PGPRevocationCertificate::~PGPRevocationCertificate(){}

uint8_t PGPRevocationCertificate::get_revoke_type() const{
    if (!meaningful()){
        throw std::runtime_error("Error: Bad Revocation Certificate.");
    }

    return std::static_pointer_cast <Tag2> (packets[0]) -> get_type();
}

bool PGPRevocationCertificate::meaningful(const PGP & pgp){
    if (pgp.get_type() != PUBLIC_KEY_BLOCK){
        // "Error: ASCII Armor type is not PUBLIC_KEY_BLOCK.\n";
        return false;
    }

    if (pgp.get_packets().size() != 1){
        // "Error: Wrong number of packets.\n";
        return false;
    }

    if (pgp.get_packets()[0] -> get_tag() != Packet::SIGNATURE){
        // "Error: Packet is not a signature packet.\n";
        return false;
    }

    if (!Signature_Type::is_revocation(std::static_pointer_cast <Tag2> (pgp.get_packets()[0]) -> get_type())){
        // "Error: Signature packet does not contain a revocation certificate.\n";
        return false;
    }

    return true;
}

bool PGPRevocationCertificate::meaningful() const{
    return meaningful(*this);
}

PGP::Ptr PGPRevocationCertificate::clone() const{
    return std::make_shared <PGPRevocationCertificate> (*this);
}