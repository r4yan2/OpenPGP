#include "TagNotValid.h"

namespace OpenPGP {
namespace Packet {

TagNotValid::TagNotValid()
    : Tag()
{}

TagNotValid::TagNotValid(const TagNotValid & copy)
    : Tag(copy)
{}

TagNotValid::TagNotValid(const std::string & data)
    : TagNotValid()
{
    read(data);
}

void TagNotValid::read(const std::string & data){
    TagNotValid::data = data;
}

std::string TagNotValid::show(const std::size_t indents, const std::size_t indent_size) const{
    const std::string indent(indents * indent_size, ' ');
    const std::string tab(indent_size, ' ');
    std::string out = indent + "NOT VALID PACKET\n";
    return out;
}

std::string TagNotValid::raw() const{
    return TagNotValid::data;
}

Tag::Ptr TagNotValid::clone() const{
    return std::make_shared <Packet::TagNotValid> (*this);
}

}
}