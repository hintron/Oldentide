// https://github.com/msgpack/msgpack-c.git

// To compile:
// g++ -I /home/michael/Documents/msgpack-c/include/ messge_pack_example.cpp

// Simply clone the code somewhere and set the include path

#include <msgpack.hpp>
#include <string>
#include <iostream>
#include <iomanip>
#include <sstream>

#include "Packets.h"

// Test struct
typedef struct {
    PTYPE packetType;
    int32_t packetId;
    int32_t sessionId;
    // Need to designate the values for messagepack
    MSGPACK_DEFINE(packetType, packetId, sessionId);
} foo_struct_t;
// Need to specify enums as a type
MSGPACK_ADD_ENUM(PTYPE);


// Copied from the message pack c++ example
int main(int argc, char const *argv[]) {
    // msgpack::type::tuple<int, bool, std::string> src(1, true, "example");
    // std::tuple<int, bool, std::string> src(1, true, "example");
    std::tuple<uint8_t, uint8_t, uint8_t> src1(
        15,
        31,
        255
    );

    // Cannot do this unless you take away the default values for struct type
    foo_struct_t src2 = {
        .packetType = SENDPLAYERACTION,
        .packetId = 17,
        .sessionId = 1337,
    };


    // serialize the object into the buffer.
    // any classes that implements write(const char*,size_t) can be a buffer.
    std::stringstream buffer;
    // msgpack::pack(buffer, src);
    // msgpack::pack(buffer, src1);
    msgpack::pack(buffer, src2);
    // msgpack::pack(buffer, 17);
    // msgpack::pack(buffer, NULL);


    // send the buffer ...
    buffer.seekg(0);

    // deserialize the buffer into msgpack::object instance.
    std::string str(buffer.str());
    std::cout << std::hex << str << std::endl;

    msgpack::object_handle oh = msgpack::unpack(str.data(), str.size());

    // deserialized object is valid during the msgpack::object_handle instance is alive.
    msgpack::object deserialized = oh.get();

    // msgpack::object supports ostream.
    std::cout << deserialized << std::endl;

    // convert msgpack::object instance into the original type.
    // if the type is mismatched, it throws msgpack::type_error exception.
    // msgpack::type::tuple<int, bool, std::string> dst;
    msgpack::type::tuple<uint8_t, uint8_t, uint8_t> dst1;
    foo_struct_t dst2;
    // deserialized.convert(dst);
    // deserialized.convert(dst1);
    deserialized.convert(dst2);


    std::cout << dst2.packetType << "|" << dst2.packetId << "|" << dst2.sessionId << "|" << std::endl;


    return 0;
}