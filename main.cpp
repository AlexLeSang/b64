#include <cxxopts.hpp>
#include <b64.hpp>

constexpr auto VERSION = "0.0.1";

int main(int argc, char *argv[]) {
  using namespace std;
  cxxopts::Options options{
      "b64",
      "Base64 encode or decode FILE, or standard input, to standard output."};

  bool decode = false;
  // clang-format off
  options.add_options()
    ("h,help", "display this help and exit")
    ("v,version", "output version information and exit")
    ("d,decode", "decode input stream", cxxopts::value(decode))
    ;
  // clang-format on

  const auto result = options.parse(argc, argv);

  if (result.count("h")) {
    cout << options.help() << endl;
  }

  if (result.count("v")) {
    cout << "Version: " << VERSION << endl;
  }

  if (decode) {
    string s;
    cin >> s;
    cout << b64::decode(s) << endl;
  } else {
    string s;
    cin >> s;
    cout << b64::encode(s) << endl;
  }

  return 0;
}
