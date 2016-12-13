#define BOOST_TEST_MODULE My Test

#include <boost/test/included/unit_test.hpp>

#include <RawDataStreamImplementation.hpp>
#include <memory>
#include <sstream>
#include <string>
#include <array>

/*
BOOST_AUTO_TEST_CASE(Pseudo_Empty_Construction) {
    constexpr unsigned char pseudo_chars[] = {0x00, 0x00, 0x00, 0x00, 0x80};
    auto pseudo_empty_stream = std::make_unique<std::stringstream>
            (std::string((const char *) (pseudo_chars), sizeof(pseudo_chars) - 1), std::ios::binary | std::ios::in);
    RawDataStreamImplementation rawdata_stream{std::move(pseudo_empty_stream)};

    unsigned char buffer[32] = {};
    const auto read_bytes = rawdata_stream.readBytes(buffer, sizeof(buffer));
    BOOST_WARN_EQUAL(static_cast<int>(RawDataStreamImplementation::readBytes_return_code::no_data), -1);
    BOOST_CHECK_EQUAL(read_bytes, -1);
}
 */

BOOST_AUTO_TEST_CASE(Empty_Construction) {
    auto empty_stream = std::make_unique<std::stringstream>();
    RawDataStreamImplementation rawdata_stream{std::move(empty_stream)};

    unsigned char buffer[32] = {};
    const auto read_bytes = rawdata_stream.readBytes(buffer, sizeof(buffer));
    BOOST_WARN_EQUAL(static_cast<int>(RawDataStreamImplementation::readBytes_return_code::end_of_stream), -2);
    BOOST_CHECK_EQUAL(read_bytes, -2);
}

struct one_read_fixture {
    one_read_fixture(const char *data, size_t size) : one_read_fixture((const unsigned char *) (data), size) {}

    one_read_fixture(const unsigned char *data, size_t size) {
        auto stream = std::make_unique<std::stringstream>
                (std::string((const char *) (data), size), std::ios::binary | std::ios::in);
        RawDataStreamImplementation rawdata_stream{std::move(stream)};

        read_return_code = rawdata_stream.readBytes(buffer.data(), buffer.size());
    }

    static constexpr size_t buffer_size = 1024;

    int read_return_code;
    std::array<unsigned char, buffer_size> buffer;
};

BOOST_AUTO_TEST_CASE(Task_Example) {
    constexpr unsigned char pseudo_chars[] = {0x65, 0x50, 0x00, 0x00, 0x00, 0x00, 0x04, 0x00, 0x08, 0x10, 0x18};
    one_read_fixture fixture{pseudo_chars, sizeof(pseudo_chars)};

    std::array<unsigned char, 11> supposed{0x0C, 0xAA, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x01, 0x02, 0x03};
    BOOST_CHECK_GT(fixture.read_return_code, 0);
    BOOST_CHECK(memcmp(fixture.buffer.data(), supposed.data(), 11) == 0);
}

BOOST_AUTO_TEST_CASE(Mutli_Byte_Shift) {
    std::array<unsigned char, 11> in = {0x65, 0x50, 0x00, 0x00, 0x00, 0x00, 0x04, 0x00, 0x08, 0x10, 0x18};

    auto out = RawDataStreamImplementation::shift_multi_byte(in, 3);

    std::array<unsigned char, 11> supposed{0x0C, 0xAA, 0x00,0x00, 0x00, 0x00, 0x00, 0x80, 0x01, 0x02, 0x03};

    BOOST_CHECK(in == std::get<0>(RawDataStreamImplementation::shift_multi_byte(in, 0)));
    BOOST_CHECK(std::get<0>(out) == supposed);
}



