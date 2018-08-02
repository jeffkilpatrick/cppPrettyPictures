#pragma once

#include "pp/utility/Exports.h"

#include <string>

namespace pp {
    class Image;

    /**
        Export the given image to BMP.
    **/
    PP_EXPORT void WriteBmp(const std::string& path, const pp::Image& img);

    /**
        Export the given image to PNG.
    **/
    PP_EXPORT void WritePng(const std::string& path, const pp::Image& img, const std::string& description);
    PP_EXPORT std::vector<uint8_t> WritePng(const pp::Image& img, const std::string& description);
}
