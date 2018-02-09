#ifndef __TAGNOTVALID__
#define __TAGNOTVALID__

#include "Packet.h"

namespace OpenPGP {
    namespace Packet {
        class TagNotValid : public Tag {
            private:
                std::string data;

            public:
                typedef std::shared_ptr <Packet::TagNotValid> Ptr;

                TagNotValid();
                TagNotValid(const TagNotValid & copy);
                TagNotValid(const std::string & data);

                void read(const std::string & data);
                std::string show(const std::size_t indents = 0, const std::size_t indent_size = 4) const;
                std::string raw() const;

                Tag::Ptr clone() const;
        };
    }
}

#endif
