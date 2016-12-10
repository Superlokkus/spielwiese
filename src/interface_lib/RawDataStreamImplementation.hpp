/*! @file RawDataStreamImplementation.hpp
 *
 */

#ifndef CPP_SPIELWIESE_RAWDATASTREAMIMPLEMENTATION_HPP
#define CPP_SPIELWIESE_RAWDATASTREAMIMPLEMENTATION_HPP

#include "RawDataStream.h"

class RawDataStreamImplementation : public RawDataStream {
public:
    virtual int readBytes(unsigned char *buffer, int num_bytes) override {

    }
};


#endif //CPP_SPIELWIESE_RAWDATASTREAMIMPLEMENTATION_HPP
