#pragma once

#include <iostream>
#include <string>
#include <tuple>
#include <vector>

class ArgvParser {
  using Argv_t = std::tuple<std::string, std::string>;

public:
  ArgvParser(int argc, char **argv);
  ~ArgvParser() = default;

  template <typename T>
  void GetCmdInt(const std::string &cmd, T *ret) const {
    for (auto &t : m_Tokens) {
      std::string token, value;
      std::tie(token, value) = t;
      if (token == cmd) {
        try {
          *ret = std::stoi(value);
        } catch (...) {
          std::cerr << "Error: " << value << " is an invalid value for "
                    << token << " parameter\n";
          std::exit(EXIT_FAILURE);
        }
        return;
      }
    }
    *ret = 0;
  }

  void GetCmdFloat(const std::string &cmd, float *ret) const {
    for (auto &t : m_Tokens) {
      std::string token, value;
      std::tie(token, value) = t;
      if (token == cmd) {
        try {
          *ret = std::stof(value);
        } catch (...) {
          std::cerr << "Error: " << value << " is an invalid value for "
                    << token << " parameter\n";
          std::exit(EXIT_FAILURE);
        }
        return;
      }
    }
    *ret = 0.0;
  }

  void GetCmdBool(const std::string &cmd, bool *ret) const {
    for (auto &t : m_Tokens) {
      std::string token, value;
      std::tie(token, value) = t;
      if (token == cmd) {
        if (value == "true") {
          *ret = true;
        }
        return;
      }
    }
    *ret = false;
  }

  std::string GetMode() const {
    return m_Mode;
  }

private:
  std::string m_Mode;
  std::vector<Argv_t> m_Tokens;

  Argv_t Split(char *cmd, char sep);
};
