#include "BinaryReader.h"
#include "utils.h"  // for SafeDelete, UINT, UINT32
#include <fstream>  // for basic_ifstream
#include <iostream> // for operator<<, endl, stringstream, basic_ostream, cout
#include <sstream>
#include <string> // for basic_string, string, operator<<, getline, char_...

std::string BinaryReader::ReadLongString() {
  if (m_pReader == nullptr) {
    std::cout << "BinaryReader doesn't exist!\nUnable to read binary data..."
              << std::endl;
  }

  auto stringLength = Read<unsigned int>();

  std::stringstream ss;
  for (UINT i = 0; i < stringLength; ++i) {
    ss << Read<char>();
  }

  return ss.str();
}

std::string BinaryReader::ReadNullString() {
  if (m_pReader == nullptr) {
    std::cout << "BinaryReader doesn't exist!\nUnable to read binary data..."
              << std::endl;
    return "";
  }

  std::string buff;
  std::getline(*m_pReader, buff, '\0');

  return std::string(buff.begin(), buff.end());
}

std::string BinaryReader::ReadString() {
  if (m_pReader == nullptr) {
    std::cout << "BinaryReader doesn't exist!\nUnable to read binary data..."
              << std::endl;
  }

  auto stringLength = static_cast<int>(Read<char>());

  std::stringstream ss;
  for (int i = 0; i < stringLength; ++i) {
    ss << Read<char>();
  }

  return ss.str();
}

void BinaryReader::Open(const std::string &binaryFile) {
  Close();

  auto temp = new std::ifstream();
  temp->open(binaryFile, std::ios::in | std::ios::binary);
  if (temp->is_open()) {
    m_pReader = temp;
    m_Exists = true;
  } else {
    std::stringstream ss;
    ss << L"BinaryReader::Open> Failed to open the file!\nBinaryFile: ";
    ss << binaryFile;
    std::cout << "[WARNING] " << ss.str() << std::endl;
    Close();
  }
}

void BinaryReader::Open(char *s, UINT32 size) {
  Close();

  std::string data(s, size);
  m_pReader = new std::stringstream(data);
  m_Exists = true;
}

void BinaryReader::Close() {
  SafeDelete(m_pReader);
  m_Exists = false;
}

int BinaryReader::GetBufferPosition() {
  if (not m_pReader->fail()) {
    return static_cast<int>(m_pReader->tellg());
  }

  std::cout << "[WARNING] "
            << L"BinaryReader::GetBufferPosition> m_pReader doesn't exist"
            << std::endl;
  return -1;
}

bool BinaryReader::SetBufferPosition(int pos) {
  if (not m_pReader->fail()) {
    m_pReader->seekg(pos);
    return true;
  }

  std::cout << "[WARNING] "
            << L"BinaryReader::SetBufferPosition> m_pReader doesn't exist"
            << std::endl;
  return false;
}

bool BinaryReader::MoveBufferPosition(int move) {
  auto currPos = GetBufferPosition();
  if (currPos > 0) {
    return SetBufferPosition(currPos + move);
  }

  return false;
}
