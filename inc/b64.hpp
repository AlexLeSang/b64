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

template <class T> auto lenght(const T);
template <> auto lenght<const char *>(const char *c_str) {
  return strlen(c_str);
}
// template <> auto lenght<string_view>(const string_view t) { return
// t.length(); }

template <class T> auto data(const T);
template <> auto data<const char *>(const char *c_str) { return c_str; }
// template <> auto data<string_view>(const string_view t) { return t.data(); }

// template <class T> auto find(const T);

template <size_t N>
auto find(const array<char, N> base_64_chars, const char ch) {
  // const string base64_chars_str =
  //     "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

  // return base64_chars_str.find(ch);
  return distance(begin(base_64_chars),
                  std::find(begin(base_64_chars), end(base_64_chars), ch));
}

} // namespace

template <class T> auto encode(const T input) {
  string ret = "";
  int i = 0;

  char char_array_3[3] = {0, 0, 0};
  char char_array_4[4] = {0, 0, 0, 0};

  auto in_len = lenght<T>(input);
  auto input_ptr = data<T>(input);

  while (in_len--) {
    char_array_3[i++] = *(input_ptr++);
    if (i == 3) {
      char_array_4[0] = (char_array_3[0] & 0xfc) >> 2;
      char_array_4[1] = static_cast<char>(((char_array_3[0] & 0x03) << 4) +
                                          ((char_array_3[1] & 0xf0) >> 4));
      char_array_4[2] = static_cast<char>(((char_array_3[1] & 0x0f) << 2) +
                                          ((char_array_3[2] & 0xc0) >> 6));
      char_array_4[3] = char_array_3[2] & 0x3f;

      for (i = 0; (i < 4); i++)
        ret += base64_chars[static_cast<size_t>(char_array_4[i])];
      i = 0;
    }
  }

  {
    int j = 0;
    if (i) {
      for (j = i; j < 3; j++)
        char_array_3[j] = '\0';

      char_array_4[0] = (char_array_3[0] & 0xfc) >> 2;
      char_array_4[1] = static_cast<char>(((char_array_3[0] & 0x03) << 4) +
                                          ((char_array_3[1] & 0xf0) >> 4));
      char_array_4[2] = static_cast<char>(((char_array_3[1] & 0x0f) << 2) +
                                          ((char_array_3[2] & 0xc0) >> 6));

      for (j = 0; (j < i + 1); j++)
        ret += base64_chars[static_cast<size_t>(char_array_4[j])];

      while ((i++ < 3))
        ret += '=';
    }
  }

  return ret;
}

auto is_base64(const char c) {
  return (isalnum(c) || (c == '+') || (c == '/'));
}

template <class T> auto decode(const T input) {
  int i = 0;
  char char_array_4[4] = {0, 0, 0, 0};
  char char_array_3[3] = {0, 0, 0};
  string ret;

  {
    int in_ = 0;
    auto in_len = input.size();
    while (in_len-- && (input[static_cast<size_t>(in_)] != '=') &&
           is_base64(input[static_cast<size_t>(in_)])) {
      char_array_4[i++] = input[static_cast<size_t>(in_)];
      in_++;
      if (i == 4) {
        for (i = 0; i < 4; i++)
          char_array_4[i] =
              static_cast<char>(find(base64_chars, char_array_4[i]) & 0xff);

        char_array_3[0] = static_cast<char>((char_array_4[0] << 2) +
                                            ((char_array_4[1] & 0x30) >> 4));

        char_array_3[1] = static_cast<char>(((char_array_4[1] & 0xf) << 4) +
                                            ((char_array_4[2] & 0x3c) >> 2));

        char_array_3[2] =
            static_cast<char>(((char_array_4[2] & 0x3) << 6) + char_array_4[3]);

        for (i = 0; (i < 3); i++)
          ret += char_array_3[i];
        i = 0;
      }
    }
  }

  if (i) {
    int j = 0;
    for (j = 0; j < i; j++)
      char_array_4[j] =
          static_cast<char>(find(base64_chars, char_array_4[j]) & 0xff);

    char_array_3[0] = static_cast<char>((char_array_4[0] << 2) +
                                        ((char_array_4[1] & 0x30) >> 4));

    char_array_3[1] = static_cast<char>(((char_array_4[1] & 0xf) << 4) +
                                        ((char_array_4[2] & 0x3c) >> 2));

    for (j = 0; (j < i - 1); j++)
      ret += char_array_3[j];
  }

  return ret;
}

} // namespace b64

#endif /* B64_H */
