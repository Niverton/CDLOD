#pragma once

#include <iostream> // for operator<<, endl, istream, basic_istream::read
#include <string>   // for string

class BinaryReader {
public:
  BinaryReader() = default;
  ~BinaryReader() {
    Close();
  };

  template <class T>
  T Read() {
    if (m_pReader == nullptr) {
      std::cerr << "[ERROR] BinaryReader doesn't exist!\nUnable to read binary "
                   "data..."
                << std::endl;
      return T();
    }

    T value;
    m_pReader->read(reinterpret_cast<char *>(&value), sizeof(T));
    return value;
  }

  std::string ReadString();
  std::string ReadLongString();
  std::string ReadNullString();

  int GetBufferPosition();
  bool SetBufferPosition(int pos);
  bool MoveBufferPosition(int move);
  bool Exists() const {
    return m_Exists;
  }

  void Open(const std::string &binaryFile);
  void Open(char *s, unsigned int size);
  void Close();

private:
  bool m_Exists = false;
  std::istream *m_pReader = nullptr;
};
