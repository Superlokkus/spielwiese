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
#include <iterator>

class RawDataStreamImplementation : public RawDataStream {
public:
    enum struct readBytes_return_code : int {
        end_of_stream = -2,
        no_data = -1,
    };

    static constexpr unsigned bit_align_mark_length = 5;
    static constexpr char bit_align_mark[bit_align_mark_length] = {0x00, 0x00, 0x00, 0x00, (char) (0x80)};
    static constexpr unsigned read_block_size = 7; //Prime so the probability is low to always read in the middle of bit align marks

    /*! @param shift_by 8 < value < 8, value > 0 means right shift, value < 0 is left shift
       *
       */
    template<size_t N, typename CHAR_T = unsigned char>
    static std::array<CHAR_T, N> shift_multi_byte(const std::array<CHAR_T, N> &to_shift, const int shift_by) {
        std::array<unsigned char, N + 2> check_buffer = {};
        memcpy(check_buffer.data() + 1, to_shift.data(), to_shift.size());
        if (shift_by > 0) {
            unsigned char *current = check_buffer.data() + N; //So we got to the last valid value
            for (int i = 0; i < N; ++i) {
                *current >>= shift_by;//current shifted
                unsigned char buffer = 0;//gotta get the carry from left
                unsigned char mask = 1 << shift_by;
                mask -= 1; //mask the n bits
                buffer = *(current - 1) & mask;
                buffer <<= CHAR_BIT - shift_by;
                *current |= buffer;
                current -= 1;
            }
        } else if (shift_by < 0) {
            const int n = std::abs(shift_by);
            unsigned char *current = check_buffer.data();
            for (int i = 0; i < N; ++i) {
                *current <<= n;
                unsigned char buffer = 0;
                unsigned char mask = 1 << n;
                mask -= 1;
                mask <<= CHAR_BIT - n;
                buffer = *(current + 1) & mask;
                buffer >>= CHAR_BIT - n;
                *current |= buffer;
                current += 1;
            }
        }
        std::array<CHAR_T, N> final_values = {};
        memcpy(final_values.data(), check_buffer.data() + 1, N * sizeof(CHAR_T));
        return final_values;
    }


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

        constexpr char bit_align_mark[bit_align_mark_length] = {0x00, 0x00, 0x00, 0x00, (char) (0x80)};

        auto remove_mark = [] () {

        };

        for (int shift = 0; shift < CHAR_BIT; ++shift) {
            auto shifted = shift_multi_byte(read_buffer,shift);
            auto order_mark = search_for_align_mark(shifted.cbegin(), shifted.cend());

            if (order_mark != shifted.cend()) {
                remove_mark();
                read_buffer = shifted;
                break;
            }

            shifted = shift_multi_byte(read_buffer,-shift);
            order_mark = search_for_align_mark(shifted.cbegin(), shifted.cend());

            if (order_mark != shifted.cend()) {
                remove_mark();
                read_buffer = shifted;
                break;
            }
        }
        memcpy(buffer,read_buffer.data(),read_count);

        return read_count;
    }

    RawDataStreamImplementation(std::unique_ptr<std::istream> &&stream)
            : RawDataStream(), byte_stream_(std::move(stream)) {}

    template<typename Iterator_t>
    static auto search_for_align_mark(Iterator_t first, Iterator_t last) -> Iterator_t {
        constexpr char bit_align_mark[bit_align_mark_length] = {0x00, 0x00, 0x00, 0x00, (char) (0x80)};
        if (std::distance(first, last) < bit_align_mark_length)
            return last;
        for (auto window_end = first + bit_align_mark_length - 1; window_end != last; ++first, ++window_end) {
            if (*first == bit_align_mark[0]
                && *(first + 1) == bit_align_mark[1]
                && *(first + 2) == bit_align_mark[2]
                && *(first + 3) == bit_align_mark[3]
                && *(first + 4) == bit_align_mark[4]) {
                return first;
            }
        }
        return last;
    }

private:
    std::unique_ptr<std::istream> byte_stream_;
    std::deque<char> cached_;
};


#endif //CPP_SPIELWIESE_RAWDATASTREAMIMPLEMENTATION_HPP
