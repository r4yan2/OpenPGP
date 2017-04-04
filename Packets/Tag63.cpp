#include "Tag63.h"

Tag63::Tag63()
    : Tag63(std::string())
{}

Tag63::Tag63(const Tag63 & copy)
    : Packet(copy),
      stream(copy.stream)
{}

Tag63::Tag63(const std::string & data)
    : Packet(63),
      stream(data)
{}

void Tag63::read(const std::string & data){
    stream = data;
}

std::string Tag63::show(const std::size_t indents, const std::size_t indent_size) const{
    const std::string indent(indents * indent_size, ' ');
    const std::string tab(indent_size, ' ');
    return indent + show_title() + "\n" + 
           indent + tab + hexlify(stream);
}

std::string Tag63::raw() const{
    return stream;
}

std::string Tag63::get_stream() const{
    return stream;
}

void Tag63::set_stream(const std::string & data){
    stream = data;
}

Packet::Ptr Tag63::clone() const{
    return std::make_shared <Tag63> (*this);
}
