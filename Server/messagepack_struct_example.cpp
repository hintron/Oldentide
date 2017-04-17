// https://github.com/msgpack/msgpack-c.git

/* To Compile:
    g++ -std=c++11 -I /home/michael/Documents/msgpack-c/include/ messagepack_struct_example.cpp
*/

// Simply clone the code and set the include path

#include <msgpack.hpp>
#include <string>
#include <iostream>
#include <sstream>

#include "Packets.h"

// Test struct
typedef struct {
    PTYPE packetType;
    int32_t packetId;
    int32_t sessionId;
    std::string my_str;
    // Need to designate the values for messagepack
    MSGPACK_DEFINE(packetType, packetId, sessionId, my_str);
    // MSGPACK_DEFINE(packetType, packetId);
} foo_struct_t;
// Need to specify enums as a type
MSGPACK_ADD_ENUM(PTYPE);


// Copied from the message pack c++ example
int main(int argc, char const *argv[]) {
    // Can also try using tuples
    // std::tuple<uint8_t, uint8_t, uint8_t> src1(
    //     15,
    //     31,
    //     255
    // );

    // Cannot do this unless you take away the default values for struct type
    foo_struct_t src2 = {
        .packetType = SENDPLAYERACTION,
        .packetId = 17,
        .sessionId = 1337,
        .my_str = std::string("Hello!")
    };



    // serialize the object into the buffer.
    // any classes that implements write(const char*,size_t) can be a buffer.
    std::stringstream buffer;
    // msgpack::pack(buffer, src1);
    msgpack::pack(buffer, src2);

    // send the buffer ...
    buffer.seekg(0);

    // deserialize the buffer into msgpack::object instance.
    std::string str(buffer.str());
    std::cout << std::hex << str << std::dec << std::endl;
    std::cout << str.size() << std::endl;

    for (int i = 0; i < str.size(); ++i) {
        printf("%02X", str.c_str()[i]);
    }
    printf("\n");

    // TODO: Understand messagepack better
    // FFFFFF940F11FFFFFFCD0539FFFFFFA648656C6C6F21
    // FFFFFF94 | 15 -> 0F | 17 -> 11 | FFFFFFCD0539FFFFFF | Hello! -> A6 48656C6C6F21

    msgpack::object_handle oh = msgpack::unpack(str.data(), str.size());

    // deserialized object is valid during the msgpack::object_handle instance is alive.
    msgpack::object deserialized = oh.get();

    // msgpack::object supports ostream.
    std::cout << deserialized << std::endl;

    // convert msgpack::object instance into the original type.
    // if the type is mismatched, it throws msgpack::type_error exception.
    // msgpack::type::tuple<uint8_t, uint8_t, uint8_t> dst1;
    foo_struct_t dst2;
    // deserialized.convert(dst1);
    deserialized.convert(dst2);

    // Prove that I can access the struct like normal
    std::cout << dst2.packetType << "|" << dst2.packetId << "|" << dst2.sessionId << "|" << dst2.my_str << std::endl;
    return 0;
}