#include "ArgvParser.h"
#include <array>
#include <sstream>

#define ARGC 5

bool test() {
  std::array<const char *, ARGC> argv = {
      "./Argv_parser", "SIMPLEX", "--width=400", "--max-height=0.5", "--help"};

  ArgvParser parser{ARGC, const_cast<char **>(argv.data())};

  unsigned int width = 0;
  parser.GetCmdInt<unsigned int>("--width", &width);
  if (width != 400)
    return false;

  float max_height = 0.0;
  parser.GetCmdFloat("--max-height", &max_height);
  if (max_height != 0.5)
    return false;

  bool help = false;
  parser.GetCmdBool("--help", &help);
  if (help != true)
    return false;

  return true;
}
