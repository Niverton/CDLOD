#pragma once

#include <vector>
#include <string>
#include <tuple>
#include <iostream>

class ArgvParser {
  using Argv_t = std::tuple<std::string, std::string>;
public:
  ArgvParser(int argc, char** argv);
  ~ArgvParser() {}

  // Use integer type for T such as int or unsigned int
  template <typename T>
  void GetCmdInt(const std::string& cmd, T* ret){
    for (auto& t: m_Tokens){
      std::string token, value;
      std::tie(token, value) = t;
      if (token == cmd){
        *ret = std::stoi(value);
        return;
      }
    }
    *ret = 0;
  }

  // Use float type for T such as float or unsigned float
  template <typename T>
  void GetCmdFloat(const std::string& cmd, T* ret){
    for (auto& t: m_Tokens){
      std::string token, value;
      std::tie(token, value) = t;
      int r;
      if (token == cmd){
        r = std::stof(value);
        return;
      }
    }
    *ret = 0.0;
    }

  std::string GetMode() { return m_Mode; }
private:
  std::string m_Mode;
  std::vector<Argv_t> m_Tokens;


  Argv_t Split(char* cmd, char sep);
};
