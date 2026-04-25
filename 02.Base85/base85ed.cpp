#include <vector>
#include <cstdint>
#include <stdexcept>

#include "base85ed.h"

namespace
{

constexpr uint32_t BASE = 85;

const char ALPHABET[] =
    "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ"
    "abcdefghijklmnopqrstuvwxyz"
    "!#$%&()*+-;<=>?@^_`{|}~";

int digit_of(uint8_t ch)
{
    for (int i = 0; i < 85; ++i)
    {
        if (static_cast<uint8_t>(ALPHABET[i]) == ch)
        {
            return i;
        }
    }

    throw std::runtime_error("Invalid base85 character");
}

} // namespace


std::vector<uint8_t> base85::encode(std::vector<uint8_t> const &bytes)
{
    std::vector<uint8_t> result;

    for (size_t i = 0; i < bytes.size(); i += 4)
    {
        size_t chunk_size = bytes.size() - i;
        if (chunk_size > 4)
        {
            chunk_size = 4;
        }

        uint32_t value = 0;

        for (size_t j = 0; j < 4; ++j)
        {
            value <<= 8;

            if (j < chunk_size)
            {
                value |= bytes[i + j];
            }
        }

        uint8_t encoded[5];

        for (int j = 4; j >= 0; --j)
        {
            encoded[j] = static_cast<uint8_t>(ALPHABET[value % BASE]);
            value /= BASE;
        }

        for (size_t j = 0; j < chunk_size + 1; ++j)
        {
            result.push_back(encoded[j]);
        }
    }

    return result;
}


std::vector<uint8_t> base85::decode(std::vector<uint8_t> const &b85str)
{
    std::vector<uint8_t> result;

    for (size_t i = 0; i < b85str.size(); i += 5)
    {
        size_t chunk_size = b85str.size() - i;
        if (chunk_size > 5)
        {
            chunk_size = 5;
        }

        if (chunk_size == 1)
        {
            throw std::runtime_error("Invalid base85 length");
        }

        uint8_t block[5];

        for (size_t j = 0; j < chunk_size; ++j)
        {
            block[j] = b85str[i + j];
        }

        for (size_t j = chunk_size; j < 5; ++j)
        {
            block[j] = '~';
        }

        uint64_t value = 0;

        for (size_t j = 0; j < 5; ++j)
        {
            value = value * BASE + static_cast<uint64_t>(digit_of(block[j]));
        }

        if (value > UINT32_MAX)
        {
            throw std::runtime_error("Invalid base85 block");
        }

        uint32_t decoded_value = static_cast<uint32_t>(value);
        uint8_t decoded[4];

        for (int j = 3; j >= 0; --j)
        {
            decoded[j] = decoded_value & 0xFF;
            decoded_value >>= 8;
        }

        for (size_t j = 0; j < chunk_size - 1; ++j)
        {
            result.push_back(decoded[j]);
        }
    }

    return result;
}