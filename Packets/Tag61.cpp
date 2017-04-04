#include "Tag61.h"

Tag61::Tag61()
    : Tag61(std::string())
{}

Tag61::Tag61(const Tag61 & copy)
    : Packet(copy),
      stream(copy.stream)
{}

Tag61::Tag61(const std::string & data)
    : Packet(61),
      stream(data)
{}

void Tag61::read(const std::string & data){
    stream = data;
}

std::string Tag61::show(const std::size_t indents, const std::size_t indent_size) const{
    const std::string indent(indents * indent_size, ' ');
    const std::string tab(indent_size, ' ');
    return indent + show_title() + "\n" + 
           indent + tab + hexlify(stream);
}

std::string Tag61::raw() const{
    return stream;
}

std::string Tag61::get_stream() const{
    return stream;
}

void Tag61::set_stream(const std::string & data){
    stream = data;
}

Packet::Ptr Tag61::clone() const{
    return std::make_shared <Tag61> (*this);
}
