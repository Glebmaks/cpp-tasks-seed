#include <gtest/gtest.h>

#include <unistd.h>
#include <sys/wait.h>
#include <vector>
#include <cstdint>
#include <stdexcept>
#include <string.h>

#include "base85ed.h"

const std::vector<std::pair<const char *, const char * >> short_cases =
{
    { "",     ""     },
    { "F#",   "1"    },
    { "F){",  "12"   },
    { "F)}j", "123"  },
    { "F)}kW","1234" }
};

static std::vector<uint8_t> cstr2v(const char *s)
{
    return std::vector<uint8_t>(
               s,
               s + std::string(s).size()
           );
}

// Тесты encode
TEST(Base85ShortsEncode, TrivialShortEncodes)
{
    for (const auto &p : short_cases)
    {
        EXPECT_EQ(base85::encode(cstr2v(p.second)), cstr2v(p.first));
    }
}

// Тесты decode
TEST(Base85ShortsDecode, TrivialShortDecodes)
{
    for (const auto &p : short_cases)
    {
        EXPECT_EQ(base85::decode(cstr2v(p.first)), cstr2v(p.second));
    }
}

TEST(Base85Extra, Empty)
{
    std::vector<uint8_t> data;
    EXPECT_EQ(base85::decode(base85::encode(data)), data);
}

TEST(Base85Extra, SingleByte)
{
    std::vector<uint8_t> data = {42};
    EXPECT_EQ(base85::decode(base85::encode(data)), data);
}

TEST(Base85Extra, RandomData)
{
    std::vector<uint8_t> data = {1, 2, 3, 4, 5, 6, 7};
    EXPECT_EQ(base85::decode(base85::encode(data)), data);
}

TEST(Base85Extra, HelloString)
{
    const char* s = "Hello";
    auto data = cstr2v(s);
    EXPECT_EQ(base85::decode(base85::encode(data)), data);
}

TEST(Base85Roundtrip, Binary)
{
    std::vector<uint8_t> data = {0,1,2,3,4,5,6,7,255};
    EXPECT_EQ(base85::decode(base85::encode(data)), data);
}