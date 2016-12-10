
/*
 * A data stream contains a binary stream of data in little endian byte format.
 *
 * The binary data can be mis-aligned to byte boundaries.
 * In order to indicate alignment to the consumer, a periodic alignment 
 * synchronisation sequence is output.
 * The alignment sequence is defined as 4 bytes of 0x00 followed by a byte of 0x80.
 *
 * For example, the following stream is mis-aligned by 3 bits and has an alignment sequence followed by 
 * the byte values 0x01,0x02,0x03
 *
 * 0x65, 0x50, 0x00, 0x00, 0x00, 0x00, 0x04, 0x00, 0x08, 0x10, 0x18
 *
 * The sequence ends when there's not enough bits left to fill a byte
 *
 */

/* 
 * Programming Challenge:
 * 
 * 1. Write an implementation of the abstract base class RawDataStream below 
 *    that can readBytes from a data stream as described above.
 *
 * 2. Demonstrate how you would test your implementation
 *
 */


class RawDataStream {
public:
    RawDataStream() {};

    virtual ~RawDataStream();

    /*
     * Reads raw data from a stream
     *
     * @param buffer to store read bytes in
     * @param num_bytes number of bytes to read from the stream into the buffer
     *
     * @return number of bytes read from stream into buffer
     *        -1 no data in stream
     *        -2 End of stream
     */
    virtual int readBytes(unsigned char *buffer, int num_bytes) = 0;
};

