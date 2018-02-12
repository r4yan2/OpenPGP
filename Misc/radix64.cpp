#include "radix64.h"

namespace OpenPGP {/*
    std::string ascii2radix64(std::string str, const unsigned char char62, const unsigned char char63){
        std::string ret;
        char const* bytes_to_encode = str.c_str();
        unsigned long in_len = str.length();
        int i = 0;
        int j = 0;
        unsigned char char_array_3[3];
        unsigned char char_array_4[4];

        while (in_len--) {
            char_array_3[i++] = *(bytes_to_encode++);
            if (i == 3) {
                char_array_4[0] = (char_array_3[0] & 0xfc) >> 2;
                char_array_4[1] = ((char_array_3[0] & 0x03) << 4) + ((char_array_3[1] & 0xf0) >> 4);
                char_array_4[2] = ((char_array_3[1] & 0x0f) << 2) + ((char_array_3[2] & 0xc0) >> 6);
                char_array_4[3] = char_array_3[2] & 0x3f;

                for(i = 0; (i <4) ; i++)
                    ret += base64_chars[char_array_4[i]];
                i = 0;
            }
        }

        if (i)
        {
            for(j = i; j < 3; j++)
                char_array_3[j] = '\0';

            char_array_4[0] = ( char_array_3[0] & 0xfc) >> 2;
            char_array_4[1] = ((char_array_3[0] & 0x03) << 4) + ((char_array_3[1] & 0xf0) >> 4);
            char_array_4[2] = ((char_array_3[1] & 0x0f) << 2) + ((char_array_3[2] & 0xc0) >> 6);

            for (j = 0; (j < i + 1); j++)
                ret += base64_chars[char_array_4[j]];

            while((i++ < 3))
                ret += '=';

        }

        return ret;

    }

    std::string radix642ascii(std::string str, const unsigned char char62, const unsigned char char63){
        size_t in_len = str.length();
        size_t i = 0;
        size_t j = 0;
        int in_ = 0;
        unsigned char char_array_4[4], char_array_3[3];
        std::string ret;

        while (in_len-- && ( str[in_] != '=') && is_base64(str[in_])) {
            char_array_4[i++] = str[in_]; in_++;
            if (i ==4) {
                for (i = 0; i <4; i++)
                    char_array_4[i] = static_cast<unsigned char>(base64_chars.find(char_array_4[i]));

                char_array_3[0] = (char_array_4[0] << 2) + ((char_array_4[1] & 0x30) >> 4);
                char_array_3[1] = ((char_array_4[1] & 0xf) << 4) + ((char_array_4[2] & 0x3c) >> 2);
                char_array_3[2] = ((char_array_4[2] & 0x3) << 6) + char_array_4[3];

                for (i = 0; (i < 3); i++)
                    ret += char_array_3[i];
                i = 0;
            }
        }

        if (i) {
            for (j = i; j <4; j++)
                char_array_4[j] = 0;

            for (j = 0; j <4; j++)
                char_array_4[j] = static_cast<unsigned char>(base64_chars.find(char_array_4[j]));

            char_array_3[0] = (char_array_4[0] << 2) + ((char_array_4[1] & 0x30) >> 4);
            char_array_3[1] = ((char_array_4[1] & 0xf) << 4) + ((char_array_4[2] & 0x3c) >> 2);
            char_array_3[2] = ((char_array_4[2] & 0x3) << 6) + char_array_4[3];

            for (j = 0; (j < i - 1); j++) ret += char_array_3[j];
        }

        return ret;
    }

*/
std::string ascii2radix64(std::string str, const unsigned char char62, const unsigned char char63){
    std::string out = "", bin = "", pad = "";
    while (str.size() % 3){
        str += zero;
        pad += "=";
    }

    for(char const c : str){
        bin += makebin(c, 8);
    }

    std::string::size_type x = 0;
    while (x < bin.size()){
        out += ("ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789" + std::string(1, char62) + std::string(1, char63))[toint(bin.substr(x, 6), 2)];
        x += 6;
    }

    if (pad.size() == 2){                       // string length % 3 == 1
        out = out.substr(0, out.size() - 2);
    }

    if (pad.size() == 1){                       // string length % 3 == 2
        out = out.substr(0, out.size() - 1);
    }

    return out + pad;
}

std::string radix642ascii(std::string str, const unsigned char char62, const unsigned char char63){
    if (str.size() & 3){
        throw std::runtime_error("Error: Input string length is not a multiple of 4.");
    }

    std::string bin = "";

    // count padding
    uint8_t unpad = 0;
    while (str[str.size() - 1] == '='){
        unpad++;
        str = str.substr(0, str.size() - 1);
    }

    for(unsigned char c : str){
        if (('A' <= c) && (c <= 'Z')){
            bin += makebin(c - 'A', 6);
        }
        else if (('a' <= c) && (c <= 'z')){
            bin += makebin(c - 'G', 6);
        }
        else if (('0' <= c) && (c <= '9')){
            bin += makebin(c + 4, 6);
        }
        else if (c == char62){
            bin += "111110";
        }
        else if (c == char63){
            bin += "111111";
        }
        else{
            throw std::runtime_error("Error: Invalid Radix64 character found: " + std::string(1, c));
        }
    }

    bin += std::string(unpad * 6, '0');

    str = "";
    for(unsigned int x = 0; x < bin.size(); x += 8){
        str += std::string(1, static_cast <unsigned char> (toint(bin.substr(x, 8), 2)));
    }

    return str.substr(0, str.size() - unpad);   // remove padding when returning
}

}