/*! @file RawDataStreamImplementation.hpp
 *
 */

#ifndef CPP_SPIELWIESE_RAWDATASTREAMIMPLEMENTATION_HPP
#define CPP_SPIELWIESE_RAWDATASTREAMIMPLEMENTATION_HPP

#include "RawDataStream.h"

#include <memory>
#include <istream>

class RawDataStreamImplementation : public RawDataStream {
public:
    enum struct readBytes_return_code : int {
        end_of_stream = -2,
        no_data = -1,
    };

    virtual int readBytes(unsigned char *buffer, int num_bytes) override {
        std::char_traits<char>::int_type byte = this->byte_stream_->get();
        if (byte == std::char_traits<char>::eof()) {
            return static_cast<int> (readBytes_return_code::end_of_stream);
        }


        return static_cast<int> (readBytes_return_code::no_data);
    }

    RawDataStreamImplementation(std::unique_ptr<std::istream> &&stream)
            : RawDataStream(), byte_stream_(std::move(stream)) {}

protected:
    std::unique_ptr<std::istream> byte_stream_;
};


#endif //CPP_SPIELWIESE_RAWDATASTREAMIMPLEMENTATION_HPP
