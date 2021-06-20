#include "Packets/Tag2/SubWrong.h"

namespace OpenPGP {
    namespace Subpacket {
        namespace Tag2 {
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

            void SubWrong::actual_read(const std::string & d){
                data = d;
            }

            void SubWrong::show_contents(HumanReadable & hr) const{
                hr << "Subpacket private/reserved\n" << "TAG: " + std::to_string(type);
            }

            Status SubWrong::actual_valid(const bool check_mpi) const{
                return Status::SUCCESS;
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
