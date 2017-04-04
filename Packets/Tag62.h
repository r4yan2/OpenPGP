/*
Tag62.h
Private or Experimental Values

Copyright (c) 2013 - 2017 Jason Lee @ calccrypto at gmail.com

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
*/

#ifndef __TAG62__
#define __TAG62__

#include "packet.h"

class Tag62 : public Packet{
    private:
        std::string stream;

    public:
        typedef std::shared_ptr <Tag62> Ptr;

        Tag62();
        Tag62(const Tag62 & copy);
        Tag62(const std::string & data);
        void read(const std::string & data);
        std::string show(const std::size_t indents = 0, const std::size_t indent_size = 4) const;
        std::string raw() const;

        std::string get_stream() const;

        void set_stream(const std::string & data);

        Packet::Ptr clone() const;
};

#endif
