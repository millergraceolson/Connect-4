#include "board.hpp"

#include "stdexcept"

// you might need additional includes
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>

/**************************************************************************/
/* your function definitions                                              */
/**************************************************************************/

// Checks Diagonal Right
bool DiagonalRight(Board& b, DiskType disk) {
  // do something
  bool result = false;
  for (int idx = 0; idx < Board::kBoardHeight; ++idx) {
    for (int i = 0; i < 4; ++i) {
      if (b.board[idx][i] == disk && b.board[idx + 1][i + 1] == disk &&
          b.board[idx + 2][i + 2] == disk && b.board[idx + 3][i + 3] == disk) {
        result = true;
      }
    }
  }
  return result;
}
// Checks Diagonal Left
bool DiagonalLeft(Board& b, DiskType disk) {
  // do something

  for (int idx = 0; idx < Board::kBoardHeight; ++idx) {
    for (int i = 0; i < Board::kBoardWidth; ++i) {
      if (b.board[idx][i] == disk && b.board[idx + 1][i - 1] == disk &&
          b.board[idx + 2][i - 2] == disk && b.board[idx + 3][i - 3] == disk) {
        return true;
      }
    }
  }
  return false;
}
// Checks Horizontal
bool CheckHorizontal(Board& b, DiskType disk) {
  // do something

  for (int idx = 0; idx < Board::kBoardHeight; idx++) {
    for (int i = 0; i < 4; i++) {
      if (b.board[idx][i] == disk && b.board[idx][i + 1] == disk &&
          b.board[idx][i + 2] == disk && b.board[idx][i + 3] == disk) {
        return true;
      }
    }
  }
  return false;
}

// Checks vertical
bool CheckVertical(Board& b, DiskType disk) {
  // do something

  for (int idx = 0; idx < Board::kBoardWidth; ++idx) {
    for (int i = 0; i < 3; ++i) {
      if (b.board[i][idx] == disk && b.board[i + 1][idx] == disk &&
          b.board[i + 2][idx] == disk && b.board[i + 3][idx] == disk) {
        return true;
      }
    }
  }
  return false;
}

void InitBoard(Board& b) {
  // define this function
  for (unsigned int row = 0; row < Board::kBoardHeight; ++row) {
    for (unsigned int col = 0; col < Board::kBoardWidth; ++col) {
      b.board[row][col] = DiskType::kEmpty;
    }
  }
}

void DropDiskToBoard(Board& b, DiskType disk, int col) {
  if (col > Board::kBoardWidth - 1 || col < 0) {
    throw std::runtime_error("Column Invalid");
  }

  for (int idx = 0; idx < Board::kBoardHeight; ++idx) {
    if (b.board[idx][col] == DiskType::kEmpty) {
      b.board[idx][col] = disk;
      return;
    }
  }
  throw std::runtime_error("");
}

bool CheckForWinner(Board& b, DiskType disk) {
  bool result = false;
  if (SearchForWinner(b, disk, WinningDirection::kRightDiag)) {
    result = true;
  }
  if (SearchForWinner(b, disk, WinningDirection::kLeftDiag)) {
    result = true;
  }
  if (SearchForWinner(b, disk, WinningDirection::kHorizontal)) {
    result = true;
  }
  if (SearchForWinner(b, disk, WinningDirection::kVertical)) {
    result = true;
  }
  return result;
}

bool SearchForWinner(Board& b, DiskType disk, WinningDirection to_check) {
  // define this function
  // the return statement below is only there so that the starter code compiles
  // against the test suite.
  if (to_check == WinningDirection::kRightDiag) {
    return DiagonalRight(b, disk);
  }
  if (to_check == WinningDirection::kLeftDiag) {
    return DiagonalLeft(b, disk);
  }
  if (to_check == WinningDirection::kHorizontal) {
    return CheckHorizontal(b, disk);
  }
  if (to_check == WinningDirection::kVertical) {
    return CheckVertical(b, disk);
  }

  return false;
}
bool BoardLocationInBounds(int row, int col) {
  if (row >= 0 && col >= 0) {
    if (col < Board::kBoardWidth && row < Board::kBoardHeight) {
      return true;
    }
  }
  return false;
}

/**************************************************************************/
/* provided to you                                                        */
/**************************************************************************/
std::string BoardToStr(const Board& b) {
  constexpr int kTotalWidth = Board::kBoardWidth * 11 - Board::kBoardHeight - 1;
  std::stringstream ss;
  ss << std::endl;
  for (int row = Board::kBoardHeight; row > 0; --row) {
    ss << " |";
    for (int col = 0; col < Board::kBoardWidth; ++col) {
      std::string value_here;
      value_here.push_back(static_cast<char>(b.board[row - 1][col]));
      ss << ' ' << CenterStr(value_here, Board::kBoardWidth + 1) << '|';
    }
    ss << std::endl;
    ss << " |" << std::setw(kTotalWidth) << std::setfill('-') << '|'
       << std::endl;
  }
  ss << " |";
  for (int col = 0; col < Board::kBoardWidth; ++col) {
    ss << ' ' << CenterStr(std::to_string(col), Board::kBoardWidth + 1) << '|';
  }
  return ss.str();
}

std::string CenterStr(const std::string& str, int col_width) {
  // quick and easy (but error-prone) implementation
  auto padl = (col_width - str.length()) / 2;
  auto padr = (col_width - str.length()) - padl;
  std::string strf = std::string(padl, ' ') + str + std::string(padr, ' ');
  return strf;
}
