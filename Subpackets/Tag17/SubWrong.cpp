#include "SubWrong.h"

namespace OpenPGP {
    namespace Subpacket {
        namespace Tag17 {
            SubWrong::SubWrong()
                    : Sub(),
                    data()
            {}

            SubWrong::SubWrong(const uint8_t &t)
                    : SubWrong()
            {
                this->set_type(t);
            }

            SubWrong::SubWrong(const std::string & data)
                    : SubWrong()
            {
                read(data);
            }

            void SubWrong::read(const std::string & d){
                data = d;
            }

            std::string SubWrong::show(const std::size_t indents, const std::size_t indent_size) const{
                const std::string indent(indents * indent_size, ' ');
                const std::string tab(indent_size, ' ');
                return indent + "Subpacket private/reserved\n" + indent + "TAG: " + std::to_string(type);
            }
            std::string SubWrong::raw() const{
                return data;
            }

            Sub::Ptr SubWrong::clone() const{
                return std::make_shared <SubWrong> (*this);
            }

        }
    }
}