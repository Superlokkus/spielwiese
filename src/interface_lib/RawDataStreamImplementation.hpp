/*! @file RawDataStreamImplementation.hpp
 *
 */

#ifndef CPP_SPIELWIESE_RAWDATASTREAMIMPLEMENTATION_HPP
#define CPP_SPIELWIESE_RAWDATASTREAMIMPLEMENTATION_HPP

#include "RawDataStream.h"

#include <memory>
#include <istream>
#include <array>
#include <cstdint>
#include <algorithm>
#include <deque>
#include <bitset>

class RawDataStreamImplementation : public RawDataStream {
public:
    enum struct readBytes_return_code : int {
        end_of_stream = -2,
        no_data = -1,
    };

    static constexpr unsigned bit_align_mark_length = 5;
    static constexpr char bit_align_mark[bit_align_mark_length] = {0x00, 0x00, 0x00, 0x00, (char) (0x80)};
    static constexpr unsigned read_block_size = 7; //Prime so the probability is low to always read in the middle of bit align marks

    virtual int readBytes(unsigned char *buffer, int num_bytes) override {
        if (num_bytes <= 0) {
            return 0;
        }

        if (num_bytes <= cached_.size()) {
            for (size_t i = 0; i < num_bytes; ++i) {
                buffer[i] = cached_.front();
            }
            return num_bytes;
        }

        std::array<char, read_block_size> read_buffer = {};
        byte_stream_->read(read_buffer.data(), read_block_size);
        const auto read_count = byte_stream_->gcount();

        if (read_count == 0 && byte_stream_->eof()) {
            return static_cast<int> (readBytes_return_code::end_of_stream);
        }

        auto check_for_misalign = [](const std::array<char, read_block_size> &read_buffer) -> unsigned {
            //bit shift range from 0 in both -/+infty
            //Check for mark
            std::array<char, read_block_size + 2> check_buffer = {};
            memcpy(check_buffer.data() + 1, read_buffer.data(), read_buffer.size());

            /*! @param shift_by 8 < Value < 8
             *
             */
            auto shift_multi_byte = [&](int shift_by) {
                char *first = check_buffer.data() + 1;
                if (shift_by > 0) {

                }
            };
        };


        return static_cast<int> (readBytes_return_code::no_data);
    }

    RawDataStreamImplementation(std::unique_ptr<std::istream> &&stream)
            : RawDataStream(), byte_stream_(std::move(stream)) {}

private:
    std::unique_ptr<std::istream> byte_stream_;
    std::deque<char> cached_;
};


#endif //CPP_SPIELWIESE_RAWDATASTREAMIMPLEMENTATION_HPP
