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
const array<char, 65> base64_chars = {
    "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/"};

template <size_t N>
auto find(const array<char, N> base_64_chars, const char ch) {
  return distance(begin(base_64_chars),
                  std::find(begin(base_64_chars), end(base_64_chars), ch));
}

auto is_base64(const char c) {
  return (isalnum(c) || (c == '+') || (c == '/'));
}

} // namespace

auto encode(const string_view input) {
  string ret;
  int i = 0;

  using CharT = string_view::value_type;
  using SizeT = string_view::size_type;

  CharT char_array_3[3] = {0, 0, 0};
  CharT char_array_4[4] = {0, 0, 0, 0};

  auto in_len = input.length();
  auto input_ptr = input.data();

  while (in_len--) {
    char_array_3[i++] = *(input_ptr++);
    if (i == 3) {
      char_array_4[0] = (char_array_3[0] & 0xfc) >> 2;
      char_array_4[1] = static_cast<CharT>(((char_array_3[0] & 0x03) << 4) +
                                           ((char_array_3[1] & 0xf0) >> 4));
      char_array_4[2] = static_cast<CharT>(((char_array_3[1] & 0x0f) << 2) +
                                           ((char_array_3[2] & 0xc0) >> 6));
      char_array_4[3] = char_array_3[2] & 0x3f;

      for (i = 0; i < 4; i++)
        ret += base64_chars[static_cast<SizeT>(char_array_4[i])];
      i = 0;
    }
  }

  {
    if (i) {
      for (auto j = i; j < 3; j++)
        char_array_3[j] = '\0';

      char_array_4[0] = (char_array_3[0] & 0xfc) >> 2;
      char_array_4[1] = static_cast<CharT>(((char_array_3[0] & 0x03) << 4) +
                                           ((char_array_3[1] & 0xf0) >> 4));
      char_array_4[2] = static_cast<CharT>(((char_array_3[1] & 0x0f) << 2) +
                                           ((char_array_3[2] & 0xc0) >> 6));

      for (auto j = 0; j < i + 1; j++)
        ret += base64_chars[static_cast<size_t>(char_array_4[j])];

      while (i++ < 3)
        ret += '=';
    }
  }

  return ret;
}

auto decode(const string_view input) {
  int i = 0;

  using CharT = string_view::value_type;
  using SizeT = string_view::size_type;

  CharT char_array_4[4] = {0, 0, 0, 0};
  CharT char_array_3[3] = {0, 0, 0};
  string ret;

  {
    int in_ = 0;
    auto in_len = input.size();
    while (in_len-- && (input[static_cast<SizeT>(in_)] != '=') &&
           is_base64(input[static_cast<SizeT>(in_)])) {
      char_array_4[i++] = input[static_cast<SizeT>(in_)];
      in_++;
      if (i == 4) {
        for (i = 0; i < 4; i++)
          char_array_4[i] =
              static_cast<CharT>(find(base64_chars, char_array_4[i]) & 0xff);

        char_array_3[0] = static_cast<CharT>((char_array_4[0] << 2) +
                                             ((char_array_4[1] & 0x30) >> 4));

        char_array_3[1] = static_cast<CharT>(((char_array_4[1] & 0xf) << 4) +
                                             ((char_array_4[2] & 0x3c) >> 2));

        char_array_3[2] = static_cast<CharT>(((char_array_4[2] & 0x3) << 6) +
                                             char_array_4[3]);

        for (i = 0; (i < 3); i++)
          ret += char_array_3[i];
        i = 0;
      }
    }
  }

  if (i) {
    for (auto j = 0; j < i; j++)
      char_array_4[j] =
          static_cast<CharT>(find(base64_chars, char_array_4[j]) & 0xff);

    char_array_3[0] = static_cast<CharT>((char_array_4[0] << 2) +
                                         ((char_array_4[1] & 0x30) >> 4));

    char_array_3[1] = static_cast<CharT>(((char_array_4[1] & 0xf) << 4) +
                                         ((char_array_4[2] & 0x3c) >> 2));

    for (auto j = 0; j < i - 1; j++)
      ret += char_array_3[j];
  }

  return ret;
}

} // namespace b64

#endif /* B64_H */
