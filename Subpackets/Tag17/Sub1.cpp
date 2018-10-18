#include "Sub1.h"

namespace OpenPGP {
namespace Subpacket {
namespace Tag17 {

unsigned int Sub1::count = 0;

Sub1::Sub1()
    : Sub(IMAGE_ATTRIBUTE),
      version(),
      encoding(),
      reserved_12(),
      image(),
      current(++count)
{}

Sub1::Sub1(const std::string & data)
    : Sub1()
{
    read(data);
}

void Sub1::read(const std::string & data){
    if (data.size()){
        version = data[2];
        encoding = data[3];
        reserved_12 = data.substr(4, 12);
        header_length = data.substr(0, 2);
        try{
        image = data.substr(16, data.size() - 16); // remove image header - 12 '\x00's
        }catch(...){image = "";}
        size = data.size();
    }
}

std::string Sub1::show(const std::size_t indents, const std::size_t indent_size) const{
    const std::string indent(indents * indent_size, ' ');
    const std::string tab(indent_size, ' ');
    const decltype(Image_Attributes::NAME)::const_iterator ia_it = Image_Attributes::NAME.find(encoding);
    std::string out = indent + show_title() + "\n" +
                      indent + tab;

    const std::string filename = "image" + std::to_string(current) + "." + ((ia_it == Image_Attributes::NAME.end())?"Unknown":(ia_it -> second));
    std::ofstream f(filename, std::ios::binary);
    if (f){
        f << image;
        f.close();
        out += "Check working directory for";
    }
    else{
        out += "Error writing to";
    }

    return out + " '" + filename + "'.";
}

std::string Sub1::raw() const{
    std::string header = std::string(1, version) + std::string(1, encoding) + reserved_12;
    return header_length + header + image;
    //return unhexlify(little_end(makehex(header.size() + 2, 4), 16)) + header + image;
    //return "\x10" + zero + std::string(1, version) + std::string(1, encoding) + reserved_12 + image;
}

uint8_t Sub1::get_encoding() const{
    return encoding;
}

std::string Sub1::get_image() const{
    return image;
}

void Sub1::set_encoding(const uint8_t & enc){
    encoding = enc;
}

void Sub1::set_image(const std::string & i){
    image = i;
}

Sub::Ptr Sub1::clone() const{
    return std::make_shared <Sub1> (*this);
}

}
}
}
