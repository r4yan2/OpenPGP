#include "Packet.h"

namespace OpenPGP {
namespace Packet {

bool is_key_packet(const uint8_t t){
    return (is_primary_key(t) || is_subkey(t));
}

bool is_primary_key(const uint8_t t){
    return ((t == SECRET_KEY) ||
            (t == PUBLIC_KEY));
}

bool is_subkey(const uint8_t t){
    return ((t == SECRET_SUBKEY) ||
            (t == PUBLIC_SUBKEY));
}

bool is_public(const uint8_t t){
    return ((t == PUBLIC_KEY) ||
            (t == PUBLIC_SUBKEY));
}

bool is_secret(const uint8_t t){
    return ((t == SECRET_KEY) ||
            (t == SECRET_SUBKEY));
}

bool is_user(const uint8_t t){
    return ((t == USER_ID) ||
            (t == USER_ATTRIBUTE));
}

bool is_session_key(const uint8_t t){
    return ((t == PUBLIC_KEY_ENCRYPTED_SESSION_KEY) ||
            (t == SYMMETRIC_KEY_ENCRYPTED_SESSION_KEY));
}

bool is_sym_protected_data(const uint8_t t){
    return ((t == SYMMETRICALLY_ENCRYPTED_DATA) ||
            (t == SYM_ENCRYPTED_INTEGRITY_PROTECTED_DATA));
}

std::string Tag::write_old_length(const std::string & data) const{
    std::string::size_type length = data.size();
    std::string out(1, 0b10000000 | (tag << 2));
    if (partial){
        out[0] |= 3;                                        // partial
    }
    else{
        if (length < 256){
            out[0] |= 0;                                    // 1 octet
            out += std::string(1, length);
        }
        else if ((256 <= length) && (length < 65536)){      // 2 octest
            out[0] |= 1;
            out += unhexlify(makehex(length, 4));
        }
        else if (65536 <= length){                          // 4 octets
            out[0] |= 2;
            out += unhexlify(makehex(length, 8));
        }
    }
    return out + data;
}

// returns formatted length string
std::string Tag::write_new_length(const std::string & data) const{
    std::string::size_type length = data.size();
    std::string out(1, 0b11000000 | tag);
    if (partial){                                           // partial
        uint8_t bits = 0;
        while (length > (1u << bits)){
            bits++;
        }
        length = 224 + bits;
        if (length > 254){
            throw std::runtime_error("Error: Data in partial Tag too large.");
        }

        out += std::string(1, length);
    }
    else{
        if (length < 192){                                  // 1 octet
            out += std::string(1, length);
        }
        else if ((192 <= length) && (length < 8383)){       // 2 octets
            length -= 0xc0;
            out += std::string(1, (length >> 8) + 0xc0 ) + std::string(1, length & 0xff);
        }
        else if (length > 8383){                            // 3 octets
            out += std::string(1, '\xff') + unhexlify(makehex(length, 8));
        }
    }
    return out + data;
}

std::string Tag::show_title() const{
    std::string out = (format?std::string("New"):std::string("Old")) + ": " + NAME.at(tag) + " (Tag " + std::to_string(tag) + ")";

    if (partial != NOT_PARTIAL) {
        out += " (partial ";

        switch (partial){
            case PARTIAL_START:
                out += "start";
                break;
            case PARTIAL_CONTINUE:
                out += "continue";
                break;
            case PARTIAL_END:
                out += "end";
                break;
            default:
                throw std::runtime_error("Error: Unknown partial type: " + std::to_string(partial));
                break;
        }

        out += ")";
    }

    return out;
}

Tag::Tag(const uint8_t t)
    : Tag(t, 0)
{}

Tag::Tag(const uint8_t t, uint8_t ver)
    : tag(t),
      version(ver),
      format(true),
      size(0),
      partial(NOT_PARTIAL)
{}

Tag::Tag(const Tag & copy)
    : tag(copy.tag),
      version(copy.version),
      format(copy.version),
      size(copy.size),
      partial(copy.partial)
{}

Tag::Tag()
    : Tag(UNKNOWN)
{}

Tag::~Tag(){}

std::string Tag::write(const Tag::Format header) const{
    const std::string data = raw();

    // make sure RFC 4880 sec 4.2.2.4 is followed
    if (partial == PARTIAL_START){
        if (data.size() < 512) {
            throw std::runtime_error("The first partial length MUST be at least 512 octets long.");
        }

        if ((tag != LITERAL_DATA)                           &&
            (tag != COMPRESSED_DATA)                        &&
            (tag != SYMMETRICALLY_ENCRYPTED_DATA)           &&
            (tag != SYM_ENCRYPTED_INTEGRITY_PROTECTED_DATA)) {
            throw std::runtime_error("An implementation MAY use Partial Body Lengths for data packets, be "
                                     "they literal, compressed, or encrypted. ... Partial Body Lengths MUST NOT be "
                                     "used for any other packet types.");
        }
    }

    if ((header == NEW) ||      // specified new header
        (tag > 15)){            // tag > 15, so new header is required
        return write_new_length(data);
    }
    return write_old_length(data);
}

uint8_t Tag::get_tag() const{
    return tag;
}

bool Tag::get_format() const{
    return format;
}

uint8_t Tag::get_version() const{
    return version;
}

std::size_t Tag::get_size() const{
    return size;
}

uint8_t Tag::get_partial() const{
    return partial;
}

void Tag::set_tag(const uint8_t t){
    tag = t;
}

void Tag::set_format(const bool f){
    format = f;
}

void Tag::set_version(const uint8_t v){
    version = v;
}

void Tag::set_size(const std::size_t s){
    size = s;
}

void Tag::set_partial(const uint8_t p){
    partial = p;
}

bool Tag::valid() const{
    return (partial == NOT_PARTIAL) || ((partial != NOT_PARTIAL)                        &&
                                        // should check for length >= 512 here, but length is not stored
                                        ((tag == LITERAL_DATA)                          ||
                                         (tag == COMPRESSED_DATA)                       ||
                                         (tag == SYMMETRICALLY_ENCRYPTED_DATA)          ||
                                         (tag == SYM_ENCRYPTED_INTEGRITY_PROTECTED_DATA)));
}

Tag & Tag::operator=(const Tag & copy)
{
    tag = copy.tag;
    version = copy.version;
    format = copy.format;
    size = copy.size;
    partial = copy.partial;
    return *this;
}

}
}
