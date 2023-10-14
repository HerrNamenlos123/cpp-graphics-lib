
#ifndef CPPGFX_BASE64_HPP
#define CPPGFX_BASE64_HPP

#include <string>
#include <vector>

namespace cppgfx {

    std::string encode_base64(const std::vector<uint8_t>& data);

    std::vector<uint8_t> decode_base64(const std::string& str);

}

#endif //CPPGFX_BASE64_HPP
