#include "Subpacket.h"

namespace OpenPGP {
namespace Subpacket {
namespace Tag17 {

std::string Sub::show_title() const{
    return Sub::show_title() + NAME.at(type) + " Subpacket (sub " + std::to_string(type) + ") (" + std::to_string(size) + " octets)";
}

Sub::~Sub(){}

Sub & Sub::operator=(const Sub & copy){
    Subpacket::Sub::operator=(copy);
    return *this;
}

std::string Sub::write() const{
    return std::string(1, type | (critical?0x80:0x00)) + raw();
}
}
}
}
