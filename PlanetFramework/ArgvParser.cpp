#include "ArgvParser.h"
#include <iostream>
#include <sstream>

ArgvParser::ArgvParser(int argc, char** argv){
  m_Mode = std::string (argv[1]);
  for (int i=2; i<argc; i++){
    m_Tokens.emplace_back(Split(argv[i], '='));
  }

  for (auto& t: m_Tokens){
    std::string e1, e2;
    std::tie(e1, e2) = t;
  }
}

ArgvParser::Argv_t ArgvParser::Split(char* cmd, char sep){
  std::istringstream input;
  input.str(std::string(cmd));

  std::vector<std::string> param;
  for (std::string line; std::getline(input, line, sep); ){
    param.emplace_back(line);
  }
  for (auto& t: param){
  }
  if (param.size() == 1){
    //true because cmd is set even if value is nil
    return std::make_tuple(param[0], "true");
  }

  return std::make_tuple(param[0], param[1]);
}



