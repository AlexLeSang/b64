#ifndef B64_H
#define B64_H

#include <array>
#include <cstring>
#include <iterator>
#include <string>
#include <string_view>

namespace b64 {
using namespace std;

namespace {
constexpr array<char, 65> base64_chars = {
    "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/"};

template <class CharT> constexpr auto find(const CharT ch) {
  return distance(begin(base64_chars),
                  std::find(begin(base64_chars), end(base64_chars), ch));
}

template <class CharT> constexpr auto is_base64(const CharT c) {
  return (isalnum(c) || (c == '+') || (c == '/'));
}

} // namespace

auto encode(const string_view input) {
  string ret;
  int i = 0;

  using CharT = string_view::value_type;

  CharT char_array_3[3];
  CharT char_array_4[4];

  auto input_ptr = input.data();

  for (auto in_len = input.length(); in_len > 0; in_len--, input_ptr++) {
    char_array_3[i++] = *input_ptr;
    if (i == 3) {
      char_array_4[0] = (char_array_3[0] & 0xfc) >> 2;
      char_array_4[1] =
          ((char_array_3[0] & 0x03) << 4) + ((char_array_3[1] & 0xf0) >> 4);
      char_array_4[2] =
          ((char_array_3[1] & 0x0f) << 2) + ((char_array_3[2] & 0xc0) >> 6);
      char_array_4[3] = char_array_3[2] & 0x3f;

      for (auto j = 0; j < 4; j++) {
        ret += base64_chars[char_array_4[j]];
      }

      i = 0;
    }
  }

  {
    if (i) {
      for (auto j = i; j < 3; j++) {
        char_array_3[j] = '\0';
      }

      char_array_4[0] = (char_array_3[0] & 0xfc) >> 2;
      char_array_4[1] =
          ((char_array_3[0] & 0x03) << 4) + ((char_array_3[1] & 0xf0) >> 4);
      char_array_4[2] =
          ((char_array_3[1] & 0x0f) << 2) + ((char_array_3[2] & 0xc0) >> 6);

      for (auto j = 0; j < i + 1; j++) {
        ret += base64_chars[char_array_4[j]];
      }

      for (; i < 3; i++) {
        ret += '=';
      }
    }
  }

  return ret;
}

auto decode(const string_view input) {
  int i = 0;

  using CharT = string_view::value_type;

  CharT char_array_4[4];
  CharT char_array_3[3];
  string ret;

  {
    int in_ = 0;
    auto in_len = input.size();
    while (in_len-- && (input[in_] != '=') && is_base64(input[in_])) {
      char_array_4[i++] = input[in_];
      in_++;
      if (i == 4) {
        for (auto i = 0; i < 4; i++) {
          char_array_4[i] = find(char_array_4[i]) & 0xff;
        }

        char_array_3[0] =
            (char_array_4[0] << 2) + ((char_array_4[1] & 0x30) >> 4);

        char_array_3[1] =
            ((char_array_4[1] & 0xf) << 4) + ((char_array_4[2] & 0x3c) >> 2);

        char_array_3[2] = ((char_array_4[2] & 0x3) << 6) + char_array_4[3];

        for (auto i = 0; i < 3; i++) {
          ret += char_array_3[i];
        }

        i = 0;
      }
    }
  }

  if (i) {
    for (auto j = 0; j < i; j++)
      char_array_4[j] = find(char_array_4[j]) & 0xff;

    char_array_3[0] = (char_array_4[0] << 2) + ((char_array_4[1] & 0x30) >> 4);

    char_array_3[1] =
        ((char_array_4[1] & 0xf) << 4) + ((char_array_4[2] & 0x3c) >> 2);

    for (auto j = 0; j < i - 1; j++)
      ret += char_array_3[j];
  }

  return ret;
}

} // namespace b64

#endif /* B64_H */
