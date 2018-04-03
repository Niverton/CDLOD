#include "ArgvParser.h"

#define ARGC 5

bool test(){
  char* argv[ARGC] =
  { "./Argv_parser",
    "SIMPLEX",
    "--width=400",
    "--max-height=0.5",
    "--help"
  };

  ArgvParser parser { ARGC, argv };

  unsigned int width = 0;
  parser.GetCmdInt<unsigned int>("--width", &width);
  if (width != 400)    return false;

  float max_height=0.0;
  parser.GetCmdFloat("--max-height", &max_height);
  if (max_height != 0.5)    return false;

  bool help = false;
  parser.GetCmdBool("--help", &help);
  if (help != true)   return false;

  return true;
}
