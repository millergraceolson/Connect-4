/////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////////////////
//                             Framework Set-up //
/////////////////////////////////////////////////////////////////////////////////////////////
#ifdef CATCH_CONFIG_MAIN
#  undef CATCH_CONFIG_MAIN
#endif
#include "catch.hpp"

/////////////////////////////////////////////////////////////////////////////////////////////
//                                 Includes //
/////////////////////////////////////////////////////////////////////////////////////////////
#include <stdexcept>

#include "board.hpp"

/////////////////////////////////////////////////////////////////////////////////////////////
//                             Helpers/Constants //
/////////////////////////////////////////////////////////////////////////////////////////////
constexpr int kBoardWidth = 7;
constexpr int kBoardHeight = 6;

bool AreEqual(DiskType solution[][kBoardWidth],
              DiskType student[][kBoardWidth]) {
  for (int i = 0; i < kBoardHeight; ++i) {
    for (int j = 0; j < kBoardWidth; ++j) {
      if (solution[i][j] != student[i][j]) return false;
    }
  }
  return true;
}

void CopyBoard(DiskType source[][kBoardWidth], DiskType target[][kBoardWidth]) {
  for (int i = 0; i < kBoardHeight; ++i) {
    for (int j = 0; j < kBoardWidth; ++j) {
      target[i][j] = source[i][j];
    }
  }
}

/////////////////////////////////////////////////////////////////////////////////////////////
//                                Test Cases //
/////////////////////////////////////////////////////////////////////////////////////////////

TEST_CASE("Board initialization", "[board-init]") {
  // SECTION("Can use sections") {}
  // clang-format off
  DiskType solution[kBoardHeight][kBoardWidth] = { 
    {DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty}, 
    {DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty}, 
    {DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty}, 
    {DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty}, 
    {DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty}, 
    {DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty} 
  };
  // clang-format on
  Board student;
  InitBoard(student);
  REQUIRE(AreEqual(solution, student.board));
}

TEST_CASE("Board Bounds", "[board-bounds]") {
  SECTION("upper bound") { REQUIRE(BoardLocationInBounds(5, 6)); }

  SECTION("post upper bound") { REQUIRE_FALSE(BoardLocationInBounds(6, 7)); }

  SECTION("lower bound") { REQUIRE(BoardLocationInBounds(0, 0)); }

  SECTION("below lower bound") { REQUIRE_FALSE(BoardLocationInBounds(-1, -1)); }

  SECTION("middle") { REQUIRE(BoardLocationInBounds(3, 3)); }

  SECTION("bottom") { REQUIRE(BoardLocationInBounds(0, 1)); }

  SECTION("half in-bound half out-bound") {
    REQUIRE_FALSE(BoardLocationInBounds(0, 7));
  }
}

TEST_CASE("Drop disks one column", "[drop-one-column]") {
  // visualization of connect 4 board is flipped because bottom-most rows in a
  // physical board are represented by 0th row at top of array initialization
  // clang-format off
  DiskType solution[kBoardHeight][kBoardWidth] = {
    {DiskType::kEmpty, DiskType::kPlayer2, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty},
    {DiskType::kEmpty, DiskType::kPlayer1, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty},
    {DiskType::kEmpty, DiskType::kPlayer2, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty},
    {DiskType::kEmpty, DiskType::kEmpty,   DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty},
    {DiskType::kEmpty, DiskType::kEmpty,   DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty},
    {DiskType::kEmpty, DiskType::kEmpty,   DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty}
  };
  // clang-format on
  Board student;
  InitBoard(student);
  DropDiskToBoard(student, DiskType::kPlayer2, 1);
  DropDiskToBoard(student, DiskType::kPlayer1, 1);
  DropDiskToBoard(student, DiskType::kPlayer2, 1);
  REQUIRE(AreEqual(solution, student.board));
}

TEST_CASE("Drop disks two columns", "[drop-two-column]") {
  // clang-format off
  DiskType solution[kBoardHeight][kBoardWidth] = {
    {DiskType::kEmpty, DiskType::kPlayer2, DiskType::kPlayer1, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty},
    {DiskType::kEmpty, DiskType::kPlayer1, DiskType::kEmpty,   DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty},
    {DiskType::kEmpty, DiskType::kPlayer2, DiskType::kEmpty,   DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty},
    {DiskType::kEmpty, DiskType::kEmpty,   DiskType::kEmpty,   DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty},
    {DiskType::kEmpty, DiskType::kEmpty,   DiskType::kEmpty,   DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty},
    {DiskType::kEmpty, DiskType::kEmpty,   DiskType::kEmpty,   DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty}
  };
  // clang-format on
  Board student;
  InitBoard(student);
  DropDiskToBoard(student, DiskType::kPlayer2, 1);
  DropDiskToBoard(student, DiskType::kPlayer1, 1);
  DropDiskToBoard(student, DiskType::kPlayer2, 1);
  DropDiskToBoard(student, DiskType::kPlayer1, 2);
  REQUIRE(AreEqual(solution, student.board));
}

TEST_CASE("Drop disks invalid column", "[drop-out-bounds]") {
  Board student;
  InitBoard(student);
  SECTION("below lower bound") {
    REQUIRE_THROWS_AS(DropDiskToBoard(student, DiskType::kPlayer2, -1),
                      std::runtime_error);
  }
  SECTION("above upper bound") {
    REQUIRE_THROWS_AS(DropDiskToBoard(student, DiskType::kPlayer2, 7),
                      std::runtime_error);
  }
}

TEST_CASE("Drop disks column filled", "[drop-column-filled]") {
  // clang-format off
  DiskType source[kBoardHeight][kBoardWidth] = {
    {DiskType::kEmpty, DiskType::kPlayer2, DiskType::kPlayer1, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty},
    {DiskType::kEmpty, DiskType::kPlayer1, DiskType::kEmpty,   DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty},
    {DiskType::kEmpty, DiskType::kPlayer2, DiskType::kEmpty,   DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty},
    {DiskType::kEmpty, DiskType::kPlayer1, DiskType::kEmpty,   DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty},
    {DiskType::kEmpty, DiskType::kPlayer1, DiskType::kEmpty,   DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty},
    {DiskType::kEmpty, DiskType::kPlayer2, DiskType::kEmpty,   DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty}
  };
  // clang-format on
  Board student;
  CopyBoard(source, student.board);
  SECTION("invalid drop") {
    REQUIRE_THROWS_AS(DropDiskToBoard(student, DiskType::kPlayer2, 1),
                      std::runtime_error);
  }
  SECTION("valid drop") {
    DropDiskToBoard(student, DiskType::kPlayer2, 2);
    source[1][2] = DiskType::kPlayer2;
    REQUIRE(AreEqual(source, student.board));
  }
}

TEST_CASE("SearchForWinner(kPlayer1, kHorizontal)",
          "[one-win-horizontal-unit]") {
  Board student;
  SECTION("horizontal win along the bottom") {
    // clang-format off
    DiskType source[kBoardHeight][kBoardWidth] = {
    {DiskType::kPlayer2, DiskType::kPlayer1, DiskType::kPlayer1, DiskType::kPlayer1, DiskType::kPlayer1, DiskType::kEmpty, DiskType::kEmpty},
    {DiskType::kPlayer2, DiskType::kPlayer1, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty},
    {DiskType::kPlayer2, DiskType::kPlayer2, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty},
    {DiskType::kPlayer1, DiskType::kPlayer1, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty},
    {DiskType::kEmpty, DiskType::kPlayer2, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty},
    {DiskType::kEmpty, DiskType::kPlayer2, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty}
    };
    // clang-format on
    CopyBoard(source, student.board);
    REQUIRE(SearchForWinner(
        student, DiskType::kPlayer1, WinningDirection::kHorizontal));
    REQUIRE_FALSE(SearchForWinner(
        student, DiskType::kPlayer2, WinningDirection::kHorizontal));
  }
  SECTION("horizontal win in the middle") {
    // clang-format off
    DiskType source[kBoardHeight][kBoardWidth] = {
    {DiskType::kPlayer2, DiskType::kPlayer2, DiskType::kPlayer1, DiskType::kPlayer1, DiskType::kPlayer1, DiskType::kPlayer2, DiskType::kPlayer2},
    {DiskType::kPlayer1, DiskType::kPlayer1, DiskType::kPlayer2, DiskType::kPlayer2, DiskType::kPlayer2, DiskType::kEmpty, DiskType::kEmpty},
    {DiskType::kEmpty, DiskType::kPlayer2, DiskType::kPlayer2, DiskType::kPlayer1, DiskType::kPlayer2, DiskType::kEmpty, DiskType::kEmpty},
    {DiskType::kEmpty, DiskType::kPlayer1, DiskType::kPlayer1, DiskType::kPlayer1, DiskType::kPlayer1, DiskType::kEmpty, DiskType::kEmpty},
    {DiskType::kEmpty, DiskType::kPlayer1, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty},
    {DiskType::kEmpty, DiskType::kPlayer2, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty}
    };
    // clang-format on
    CopyBoard(source, student.board);
    REQUIRE(SearchForWinner(
        student, DiskType::kPlayer1, WinningDirection::kHorizontal));
    REQUIRE_FALSE(SearchForWinner(
        student, DiskType::kPlayer2, WinningDirection::kHorizontal));
  }

  SECTION("horizontal win along the top") {
    // clang-format off
    DiskType source[kBoardHeight][kBoardWidth] = {
    {DiskType::kPlayer2, DiskType::kPlayer2, DiskType::kPlayer1, DiskType::kPlayer1, DiskType::kPlayer1, DiskType::kEmpty, DiskType::kEmpty},
    {DiskType::kEmpty, DiskType::kPlayer1, DiskType::kPlayer2, DiskType::kPlayer2, DiskType::kPlayer2, DiskType::kEmpty, DiskType::kEmpty},
    {DiskType::kEmpty, DiskType::kPlayer2, DiskType::kPlayer2, DiskType::kPlayer1, DiskType::kPlayer2, DiskType::kEmpty, DiskType::kEmpty},
    {DiskType::kEmpty, DiskType::kPlayer1, DiskType::kPlayer1, DiskType::kPlayer2, DiskType::kPlayer1, DiskType::kEmpty, DiskType::kEmpty},
    {DiskType::kEmpty, DiskType::kPlayer2, DiskType::kPlayer2, DiskType::kPlayer2, DiskType::kPlayer1, DiskType::kEmpty, DiskType::kEmpty},
    {DiskType::kEmpty, DiskType::kPlayer1, DiskType::kPlayer1, DiskType::kPlayer1, DiskType::kPlayer1, DiskType::kEmpty, DiskType::kEmpty}
    };
    // clang-format on
    CopyBoard(source, student.board);
    REQUIRE(SearchForWinner(
        student, DiskType::kPlayer1, WinningDirection::kHorizontal));
    REQUIRE_FALSE(SearchForWinner(
        student, DiskType::kPlayer2, WinningDirection::kHorizontal));
  }
}

TEST_CASE("SearchForWinner(kPlayer2, kHorizontal)",
          "[two-win-horizontal-unit]") {
  Board student;
  SECTION("horizontal win along the bottom") {
    // clang-format off
    DiskType source[kBoardHeight][kBoardWidth] = {
    {DiskType::kPlayer1, DiskType::kPlayer2, DiskType::kPlayer2, DiskType::kPlayer2, DiskType::kPlayer2, DiskType::kEmpty, DiskType::kEmpty},
    {DiskType::kPlayer1, DiskType::kPlayer2, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty},
    {DiskType::kPlayer1, DiskType::kPlayer1, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty},
    {DiskType::kPlayer2, DiskType::kPlayer2, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty},
    {DiskType::kEmpty, DiskType::kPlayer1, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty},
    {DiskType::kEmpty, DiskType::kPlayer1, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty}
    };
    // clang-format on
    CopyBoard(source, student.board);
    REQUIRE(SearchForWinner(
        student, DiskType::kPlayer2, WinningDirection::kHorizontal));
    REQUIRE_FALSE(SearchForWinner(
        student, DiskType::kPlayer1, WinningDirection::kHorizontal));
  }
  SECTION("horizontal win in the middle") {
    // clang-format off
    DiskType source[kBoardHeight][kBoardWidth] = {
    {DiskType::kPlayer1, DiskType::kPlayer1, DiskType::kPlayer2, DiskType::kPlayer2, DiskType::kPlayer2, DiskType::kPlayer1, DiskType::kPlayer1},
    {DiskType::kPlayer2, DiskType::kPlayer2, DiskType::kPlayer1, DiskType::kPlayer1, DiskType::kPlayer1, DiskType::kEmpty, DiskType::kEmpty},
    {DiskType::kEmpty, DiskType::kPlayer1, DiskType::kPlayer1, DiskType::kPlayer2, DiskType::kPlayer1, DiskType::kEmpty, DiskType::kEmpty},
    {DiskType::kEmpty, DiskType::kPlayer2, DiskType::kPlayer2, DiskType::kPlayer2, DiskType::kPlayer2, DiskType::kEmpty, DiskType::kEmpty},
    {DiskType::kEmpty, DiskType::kPlayer2, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty},
    {DiskType::kEmpty, DiskType::kPlayer1, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty}
    };
    // clang-format on
    CopyBoard(source, student.board);
    REQUIRE(SearchForWinner(
        student, DiskType::kPlayer2, WinningDirection::kHorizontal));
    REQUIRE_FALSE(SearchForWinner(
        student, DiskType::kPlayer1, WinningDirection::kHorizontal));
  }

  SECTION("horizontal win along the top") {
    // clang-format off
    DiskType source[kBoardHeight][kBoardWidth] = {
    {DiskType::kPlayer1, DiskType::kPlayer1, DiskType::kPlayer2, DiskType::kPlayer2, DiskType::kPlayer2, DiskType::kEmpty, DiskType::kEmpty},
    {DiskType::kEmpty, DiskType::kPlayer2, DiskType::kPlayer1, DiskType::kPlayer1, DiskType::kPlayer1, DiskType::kEmpty, DiskType::kEmpty},
    {DiskType::kEmpty, DiskType::kPlayer1, DiskType::kPlayer1, DiskType::kPlayer2, DiskType::kPlayer1, DiskType::kEmpty, DiskType::kEmpty},
    {DiskType::kEmpty, DiskType::kPlayer2, DiskType::kPlayer2, DiskType::kPlayer1, DiskType::kPlayer2, DiskType::kEmpty, DiskType::kEmpty},
    {DiskType::kEmpty, DiskType::kPlayer1, DiskType::kPlayer1, DiskType::kPlayer1, DiskType::kPlayer2, DiskType::kEmpty, DiskType::kEmpty},
    {DiskType::kEmpty, DiskType::kPlayer2, DiskType::kPlayer2, DiskType::kPlayer2, DiskType::kPlayer2, DiskType::kEmpty, DiskType::kEmpty}
    };
    // clang-format on
    CopyBoard(source, student.board);
    REQUIRE(SearchForWinner(
        student, DiskType::kPlayer2, WinningDirection::kHorizontal));
    REQUIRE_FALSE(SearchForWinner(
        student, DiskType::kPlayer1, WinningDirection::kHorizontal));
  }
}

TEST_CASE("SearchForWinner(kPlayer1, kVertical)", "[one-win-vertical-unit]") {
  Board student;
  SECTION("along the left edge") {
    // clang-format off
    DiskType source[kBoardHeight][kBoardWidth] = {
    {DiskType::kPlayer2, DiskType::kPlayer2, DiskType::kPlayer2, DiskType::kEmpty, DiskType::kPlayer2, DiskType::kPlayer1, DiskType::kPlayer2},
    {DiskType::kPlayer2, DiskType::kPlayer2, DiskType::kEmpty, DiskType::kEmpty, DiskType::kPlayer1, DiskType::kPlayer1, DiskType::kPlayer2},
    {DiskType::kPlayer1, DiskType::kPlayer1, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty},
    {DiskType::kPlayer1, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty},
    {DiskType::kPlayer1, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty},
    {DiskType::kPlayer1, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty}
    };
    // clang-format on
    CopyBoard(source, student.board);
    REQUIRE_FALSE(SearchForWinner(
        student, DiskType::kPlayer2, WinningDirection::kVertical));
    REQUIRE(SearchForWinner(
        student, DiskType::kPlayer1, WinningDirection::kVertical));
  }

  SECTION("in the middle of the board") {
    // clang-format off
    DiskType source[kBoardHeight][kBoardWidth] = {
    {DiskType::kPlayer2, DiskType::kPlayer2, DiskType::kPlayer2, DiskType::kPlayer1, DiskType::kPlayer2, DiskType::kPlayer2, DiskType::kPlayer2},
    {DiskType::kPlayer2, DiskType::kPlayer2, DiskType::kPlayer1, DiskType::kPlayer1, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty},
    {DiskType::kPlayer1, DiskType::kPlayer1, DiskType::kPlayer1, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty},
    {DiskType::kEmpty, DiskType::kEmpty, DiskType::kPlayer1, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty},
    {DiskType::kEmpty, DiskType::kEmpty, DiskType::kPlayer1, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty},
    {DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty}
    };
    // clang-format on
    CopyBoard(source, student.board);

    REQUIRE_FALSE(SearchForWinner(
        student, DiskType::kPlayer2, WinningDirection::kVertical));
    REQUIRE(SearchForWinner(
        student, DiskType::kPlayer1, WinningDirection::kVertical));
  }

  SECTION("along the right edge") {
    // clang-format off
    DiskType source[kBoardHeight][kBoardWidth] = {
    {DiskType::kPlayer2, DiskType::kPlayer2, DiskType::kPlayer2, DiskType::kPlayer1, DiskType::kPlayer2, DiskType::kEmpty, DiskType::kPlayer1},
    {DiskType::kPlayer2, DiskType::kPlayer2, DiskType::kPlayer1, DiskType::kEmpty, DiskType::kPlayer2, DiskType::kEmpty, DiskType::kPlayer1},
    {DiskType::kEmpty, DiskType::kPlayer1, DiskType::kPlayer1, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kPlayer1},
    {DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kPlayer1},
    {DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty},
    {DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty}
    };
    // clang-format on
    CopyBoard(source, student.board);

    REQUIRE_FALSE(SearchForWinner(
        student, DiskType::kPlayer2, WinningDirection::kVertical));
    REQUIRE(SearchForWinner(
        student, DiskType::kPlayer1, WinningDirection::kVertical));
  }
}

TEST_CASE("SearchForWinner(kPlayer2, kVertical)", "[two-win-vertical-unit]") {
  Board student;
  SECTION("along the left edge") {
    // clang-format off
    DiskType source[kBoardHeight][kBoardWidth] = {
    {DiskType::kPlayer1, DiskType::kPlayer1, DiskType::kPlayer1, DiskType::kEmpty, DiskType::kPlayer1, DiskType::kPlayer2, DiskType::kPlayer1},
    {DiskType::kPlayer1, DiskType::kPlayer1, DiskType::kEmpty, DiskType::kEmpty, DiskType::kPlayer2, DiskType::kPlayer2, DiskType::kPlayer1},
    {DiskType::kPlayer2, DiskType::kPlayer2, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty},
    {DiskType::kPlayer2, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty},
    {DiskType::kPlayer2, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty},
    {DiskType::kPlayer2, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty}
    };
    // clang-format on
    CopyBoard(source, student.board);
    REQUIRE_FALSE(SearchForWinner(
        student, DiskType::kPlayer1, WinningDirection::kVertical));
    REQUIRE(SearchForWinner(
        student, DiskType::kPlayer2, WinningDirection::kVertical));
  }

  SECTION("in the middle of the board") {
    // clang-format off
    DiskType source[kBoardHeight][kBoardWidth] = {
    {DiskType::kPlayer1, DiskType::kPlayer1, DiskType::kPlayer1, DiskType::kPlayer2, DiskType::kPlayer1, DiskType::kPlayer1, DiskType::kPlayer1},
    {DiskType::kPlayer1, DiskType::kPlayer1, DiskType::kPlayer2, DiskType::kPlayer2, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty},
    {DiskType::kPlayer2, DiskType::kPlayer2, DiskType::kPlayer2, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty},
    {DiskType::kEmpty, DiskType::kEmpty, DiskType::kPlayer2, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty},
    {DiskType::kEmpty, DiskType::kEmpty, DiskType::kPlayer2, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty},
    {DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty}
    };
    // clang-format on
    CopyBoard(source, student.board);

    REQUIRE_FALSE(SearchForWinner(
        student, DiskType::kPlayer1, WinningDirection::kVertical));
    REQUIRE(SearchForWinner(
        student, DiskType::kPlayer2, WinningDirection::kVertical));
  }

  SECTION("along the right edge") {
    // clang-format off
    DiskType source[kBoardHeight][kBoardWidth] = {
    {DiskType::kPlayer1, DiskType::kPlayer1, DiskType::kPlayer1, DiskType::kPlayer2, DiskType::kPlayer1, DiskType::kEmpty, DiskType::kPlayer2},
    {DiskType::kPlayer1, DiskType::kPlayer1, DiskType::kPlayer2, DiskType::kEmpty, DiskType::kPlayer1, DiskType::kEmpty, DiskType::kPlayer2},
    {DiskType::kEmpty, DiskType::kPlayer2, DiskType::kPlayer2, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kPlayer2},
    {DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kPlayer2},
    {DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty},
    {DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty}
    };
    // clang-format on
    CopyBoard(source, student.board);

    REQUIRE_FALSE(SearchForWinner(
        student, DiskType::kPlayer1, WinningDirection::kVertical));
    REQUIRE(SearchForWinner(
        student, DiskType::kPlayer2, WinningDirection::kVertical));
  }
}

TEST_CASE("SearchForWinner(kPlayer1, kRightDiag)",
          "[one-win-right-diagonal-unit]") {
  Board student;
  // clang-format off
  SECTION("middle") {
    DiskType source[kBoardHeight][kBoardWidth] = {
    {DiskType::kPlayer2, DiskType::kPlayer1, DiskType::kPlayer2, DiskType::kEmpty, DiskType::kPlayer2, DiskType::kPlayer1, DiskType::kPlayer2},
    {DiskType::kPlayer2, DiskType::kPlayer2, DiskType::kPlayer1, DiskType::kEmpty, DiskType::kPlayer1, DiskType::kPlayer1, DiskType::kPlayer2},
    {DiskType::kPlayer1, DiskType::kPlayer1, DiskType::kEmpty, DiskType::kPlayer1, DiskType::kPlayer2, DiskType::kEmpty, DiskType::kPlayer2},
    {DiskType::kPlayer1, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kPlayer1, DiskType::kEmpty, DiskType::kEmpty},
    {DiskType::kPlayer1, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty},
    {DiskType::kPlayer2, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty}
    };
    // clang-format on
    CopyBoard(source, student.board);

    REQUIRE_FALSE(SearchForWinner(
        student, DiskType::kPlayer2, WinningDirection::kRightDiag));
    REQUIRE(SearchForWinner(
        student, DiskType::kPlayer1, WinningDirection::kRightDiag));
  }

  SECTION("left") {
    // clang-format off
    DiskType source[kBoardHeight][kBoardWidth] = {
    {DiskType::kPlayer1, DiskType::kPlayer2, DiskType::kPlayer2, DiskType::kPlayer1, DiskType::kPlayer2, DiskType::kPlayer2, DiskType::kPlayer2},
    {DiskType::kPlayer2, DiskType::kPlayer1, DiskType::kPlayer1, DiskType::kPlayer1, DiskType::kEmpty, DiskType::kPlayer2, DiskType::kEmpty},
    {DiskType::kPlayer1, DiskType::kPlayer1, DiskType::kPlayer1, DiskType::kPlayer2, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty},
    {DiskType::kPlayer2, DiskType::kEmpty, DiskType::kPlayer2, DiskType::kPlayer1, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty},
    {DiskType::kEmpty, DiskType::kEmpty, DiskType::kPlayer1, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty},
    {DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty}
    };
    // clang-format on
    CopyBoard(source, student.board);

    REQUIRE_FALSE(SearchForWinner(
        student, DiskType::kPlayer2, WinningDirection::kRightDiag));
    REQUIRE(SearchForWinner(
        student, DiskType::kPlayer1, WinningDirection::kRightDiag));
  }

  SECTION("right") {
    // clang-format off
    DiskType source[kBoardHeight][kBoardWidth] = {
    {DiskType::kPlayer2, DiskType::kPlayer2, DiskType::kPlayer2, DiskType::kPlayer1, DiskType::kPlayer2, DiskType::kPlayer1, DiskType::kPlayer1},
    {DiskType::kPlayer2, DiskType::kPlayer2, DiskType::kPlayer1, DiskType::kPlayer1, DiskType::kPlayer2, DiskType::kPlayer2, DiskType::kPlayer1},
    {DiskType::kEmpty, DiskType::kPlayer2, DiskType::kPlayer1, DiskType::kPlayer1, DiskType::kPlayer1, DiskType::kPlayer2, DiskType::kPlayer1},
    {DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kPlayer1, DiskType::kPlayer2},
    {DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kPlayer1},
    {DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty}
    };
    // clang-format on
    CopyBoard(source, student.board);

    REQUIRE_FALSE(SearchForWinner(
        student, DiskType::kPlayer2, WinningDirection::kRightDiag));
    REQUIRE(SearchForWinner(
        student, DiskType::kPlayer1, WinningDirection::kRightDiag));
  }
}

TEST_CASE("SearchForWinner(kPlayer2, kRightDiag)",
          "[two-win-right-diagonal-unit]") {
  Board student;
  // clang-format off
  SECTION("middle") {
    DiskType source[kBoardHeight][kBoardWidth] = {
    {DiskType::kPlayer1, DiskType::kPlayer2, DiskType::kPlayer1, DiskType::kEmpty, DiskType::kPlayer1, DiskType::kPlayer2, DiskType::kPlayer1},
    {DiskType::kPlayer1, DiskType::kPlayer1, DiskType::kPlayer2, DiskType::kEmpty, DiskType::kPlayer2, DiskType::kPlayer2, DiskType::kPlayer1},
    {DiskType::kPlayer2, DiskType::kPlayer2, DiskType::kEmpty, DiskType::kPlayer2, DiskType::kPlayer1, DiskType::kEmpty, DiskType::kPlayer1},
    {DiskType::kPlayer2, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kPlayer2, DiskType::kEmpty, DiskType::kEmpty},
    {DiskType::kPlayer2, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty},
    {DiskType::kPlayer1, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty}
    };
    // clang-format on
    CopyBoard(source, student.board);

    REQUIRE_FALSE(SearchForWinner(
        student, DiskType::kPlayer1, WinningDirection::kRightDiag));
    REQUIRE(SearchForWinner(
        student, DiskType::kPlayer2, WinningDirection::kRightDiag));
  }

  SECTION("left") {
    // clang-format off
    DiskType source[kBoardHeight][kBoardWidth] = {
    {DiskType::kPlayer2, DiskType::kPlayer1, DiskType::kPlayer1, DiskType::kPlayer2, DiskType::kPlayer1, DiskType::kPlayer1, DiskType::kPlayer1},
    {DiskType::kPlayer1, DiskType::kPlayer2, DiskType::kPlayer2, DiskType::kPlayer2, DiskType::kEmpty, DiskType::kPlayer1, DiskType::kEmpty},
    {DiskType::kPlayer2, DiskType::kPlayer2, DiskType::kPlayer2, DiskType::kPlayer1, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty},
    {DiskType::kPlayer1, DiskType::kEmpty, DiskType::kPlayer1, DiskType::kPlayer2, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty},
    {DiskType::kEmpty, DiskType::kEmpty, DiskType::kPlayer2, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty},
    {DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty}
    };
    // clang-format on
    CopyBoard(source, student.board);

    REQUIRE_FALSE(SearchForWinner(
        student, DiskType::kPlayer1, WinningDirection::kRightDiag));
    REQUIRE(SearchForWinner(
        student, DiskType::kPlayer2, WinningDirection::kRightDiag));
  }

  SECTION("right") {
    // clang-format off
    DiskType source[kBoardHeight][kBoardWidth] = {
    {DiskType::kPlayer1, DiskType::kPlayer1, DiskType::kPlayer1, DiskType::kPlayer2, DiskType::kPlayer1, DiskType::kPlayer2, DiskType::kPlayer2},
    {DiskType::kPlayer1, DiskType::kPlayer1, DiskType::kPlayer2, DiskType::kPlayer2, DiskType::kPlayer1, DiskType::kPlayer1, DiskType::kPlayer2},
    {DiskType::kEmpty, DiskType::kPlayer1, DiskType::kPlayer2, DiskType::kPlayer2, DiskType::kPlayer2, DiskType::kPlayer1, DiskType::kPlayer2},
    {DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kPlayer2, DiskType::kPlayer1},
    {DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kPlayer2},
    {DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty}
    };
    // clang-format on
    CopyBoard(source, student.board);

    REQUIRE_FALSE(SearchForWinner(
        student, DiskType::kPlayer1, WinningDirection::kRightDiag));
    REQUIRE(SearchForWinner(
        student, DiskType::kPlayer2, WinningDirection::kRightDiag));
  }
}

TEST_CASE("SearchForWinner(kPlayer1, kLeftDiag)",
          "[one-win-left-diagonal-unit]") {
  Board student;
  // clang-format off
  SECTION("middle") {
    DiskType source[kBoardHeight][kBoardWidth] = {
    {DiskType::kPlayer1, DiskType::kPlayer2, DiskType::kPlayer1, DiskType::kPlayer2, DiskType::kPlayer2, DiskType::kPlayer2, DiskType::kPlayer1},
    {DiskType::kPlayer1, DiskType::kPlayer1, DiskType::kPlayer2, DiskType::kPlayer1, DiskType::kPlayer2, DiskType::kPlayer2, DiskType::kPlayer1},
    {DiskType::kPlayer2, DiskType::kPlayer1, DiskType::kPlayer1, DiskType::kPlayer2, DiskType::kPlayer2, DiskType::kEmpty, DiskType::kEmpty},
    {DiskType::kPlayer2, DiskType::kPlayer1, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty},
    {DiskType::kPlayer1, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty},
    {DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty}
    };
    // clang-format on
    CopyBoard(source, student.board);

    REQUIRE(SearchForWinner(
        student, DiskType::kPlayer1, WinningDirection::kLeftDiag));
    REQUIRE_FALSE(SearchForWinner(
        student, DiskType::kPlayer2, WinningDirection::kLeftDiag));
  }

  SECTION("left") {
    // clang-format off
    DiskType source[kBoardHeight][kBoardWidth] = {
    {DiskType::kPlayer2, DiskType::kPlayer1, DiskType::kPlayer2, DiskType::kPlayer1, DiskType::kPlayer1, DiskType::kEmpty, DiskType::kEmpty},
    {DiskType::kPlayer1, DiskType::kPlayer2, DiskType::kPlayer1, DiskType::kPlayer2, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty},
    {DiskType::kPlayer2, DiskType::kPlayer1, DiskType::kPlayer2, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty},
    {DiskType::kPlayer1, DiskType::kEmpty, DiskType::kPlayer1, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty},
    {DiskType::kEmpty, DiskType::kEmpty, DiskType::kPlayer2, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty},
    {DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty}
    };
    // clang-format on
    CopyBoard(source, student.board);

    REQUIRE(SearchForWinner(
        student, DiskType::kPlayer1, WinningDirection::kLeftDiag));
    REQUIRE_FALSE(SearchForWinner(
        student, DiskType::kPlayer2, WinningDirection::kLeftDiag));
  }

  SECTION("right") {
    // clang-format off
    DiskType source[kBoardHeight][kBoardWidth] = {
    {DiskType::kPlayer1, DiskType::kPlayer1, DiskType::kPlayer1, DiskType::kPlayer2, DiskType::kPlayer1, DiskType::kPlayer1, DiskType::kPlayer1},
    {DiskType::kPlayer1, DiskType::kPlayer1, DiskType::kPlayer2, DiskType::kPlayer2, DiskType::kPlayer1, DiskType::kPlayer1, DiskType::kPlayer2},
    {DiskType::kEmpty, DiskType::kPlayer2, DiskType::kPlayer2, DiskType::kPlayer2, DiskType::kPlayer1, DiskType::kPlayer2, DiskType::kPlayer2},
    {DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kPlayer1, DiskType::kPlayer2, DiskType::kEmpty, DiskType::kPlayer1},
    {DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kPlayer2},
    {DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kPlayer2}
    };
    // clang-format on
    CopyBoard(source, student.board);

    REQUIRE(SearchForWinner(
        student, DiskType::kPlayer1, WinningDirection::kLeftDiag));
    REQUIRE_FALSE(SearchForWinner(
        student, DiskType::kPlayer2, WinningDirection::kLeftDiag));
  }
}

TEST_CASE("SearchForWinner(kPlayer2, kLeftDiag)",
          "[two-win-left-diagonal-unit]") {
  Board student;
  // clang-format off
  SECTION("middle") {
    DiskType source[kBoardHeight][kBoardWidth] = {
    {DiskType::kPlayer2, DiskType::kPlayer1, DiskType::kPlayer2, DiskType::kPlayer1, DiskType::kPlayer1, DiskType::kPlayer1, DiskType::kPlayer2},
    {DiskType::kPlayer2, DiskType::kPlayer2, DiskType::kPlayer1, DiskType::kPlayer2, DiskType::kPlayer1, DiskType::kPlayer1, DiskType::kPlayer2},
    {DiskType::kPlayer1, DiskType::kPlayer2, DiskType::kPlayer2, DiskType::kPlayer1, DiskType::kPlayer1, DiskType::kEmpty, DiskType::kEmpty},
    {DiskType::kPlayer1, DiskType::kPlayer2, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty},
    {DiskType::kPlayer2, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty},
    {DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty}
    };
    // clang-format on
    CopyBoard(source, student.board);

    REQUIRE(SearchForWinner(
        student, DiskType::kPlayer2, WinningDirection::kLeftDiag));
    REQUIRE_FALSE(SearchForWinner(
        student, DiskType::kPlayer1, WinningDirection::kLeftDiag));
  }

  SECTION("left") {
    // clang-format off
    DiskType source[kBoardHeight][kBoardWidth] = {
    {DiskType::kPlayer1, DiskType::kPlayer2, DiskType::kPlayer1, DiskType::kPlayer2, DiskType::kPlayer2, DiskType::kEmpty, DiskType::kEmpty},
    {DiskType::kPlayer2, DiskType::kPlayer1, DiskType::kPlayer2, DiskType::kPlayer1, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty},
    {DiskType::kPlayer1, DiskType::kPlayer2, DiskType::kPlayer1, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty},
    {DiskType::kPlayer2, DiskType::kEmpty, DiskType::kPlayer2, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty},
    {DiskType::kEmpty, DiskType::kEmpty, DiskType::kPlayer1, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty},
    {DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty}
    };
    // clang-format on
    CopyBoard(source, student.board);

    REQUIRE(SearchForWinner(
        student, DiskType::kPlayer2, WinningDirection::kLeftDiag));
    REQUIRE_FALSE(SearchForWinner(
        student, DiskType::kPlayer1, WinningDirection::kLeftDiag));
  }

  SECTION("right") {
    // clang-format off
    DiskType source[kBoardHeight][kBoardWidth] = {
    {DiskType::kPlayer2, DiskType::kPlayer2, DiskType::kPlayer2, DiskType::kPlayer1, DiskType::kPlayer2, DiskType::kPlayer2, DiskType::kPlayer2},
    {DiskType::kPlayer2, DiskType::kPlayer2, DiskType::kPlayer1, DiskType::kPlayer1, DiskType::kPlayer2, DiskType::kPlayer2, DiskType::kPlayer1},
    {DiskType::kEmpty, DiskType::kPlayer1, DiskType::kPlayer1, DiskType::kPlayer1, DiskType::kPlayer2, DiskType::kPlayer1, DiskType::kPlayer1},
    {DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kPlayer2, DiskType::kPlayer1, DiskType::kEmpty, DiskType::kPlayer2},
    {DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kPlayer1},
    {DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kPlayer1}
    };
    // clang-format on
    CopyBoard(source, student.board);

    REQUIRE(SearchForWinner(
        student, DiskType::kPlayer2, WinningDirection::kLeftDiag));
    REQUIRE_FALSE(SearchForWinner(
        student, DiskType::kPlayer1, WinningDirection::kLeftDiag));
  }
}

TEST_CASE(
    "CheckForWinner(student, DiskType::kPlayer2) kHorizontal comprehensive",
    "[comp-one-win-horizontal-unit]") {
  Board student;
  // clang-format off
  SECTION("bottom") {
    DiskType source[kBoardHeight][kBoardWidth] = {
    {DiskType::kPlayer2, DiskType::kPlayer1, DiskType::kPlayer1, DiskType::kPlayer1, DiskType::kPlayer1, DiskType::kEmpty, DiskType::kEmpty},
    {DiskType::kPlayer2, DiskType::kPlayer1, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty},
    {DiskType::kPlayer2, DiskType::kPlayer2, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty},
    {DiskType::kPlayer1, DiskType::kPlayer1, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty},
    {DiskType::kEmpty, DiskType::kPlayer2, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty},
    {DiskType::kEmpty, DiskType::kPlayer2, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty}
    };
    // clang-format on
    CopyBoard(source, student.board);
    SECTION("Check right diagonal") {
      REQUIRE_FALSE(SearchForWinner(
          student, DiskType::kPlayer1, WinningDirection::kRightDiag));
      REQUIRE_FALSE(SearchForWinner(
          student, DiskType::kPlayer2, WinningDirection::kRightDiag));
    }
    SECTION("Check left diagonal") {
      REQUIRE_FALSE(SearchForWinner(
          student, DiskType::kPlayer1, WinningDirection::kLeftDiag));
      REQUIRE_FALSE(SearchForWinner(
          student, DiskType::kPlayer2, WinningDirection::kLeftDiag));
    }
    SECTION("Check horizontal") {
      REQUIRE(SearchForWinner(
          student, DiskType::kPlayer1, WinningDirection::kHorizontal));
      REQUIRE_FALSE(SearchForWinner(
          student, DiskType::kPlayer2, WinningDirection::kHorizontal));
    }
    SECTION("Check vertical") {
      REQUIRE_FALSE(SearchForWinner(
          student, DiskType::kPlayer1, WinningDirection::kVertical));
      REQUIRE_FALSE(SearchForWinner(
          student, DiskType::kPlayer2, WinningDirection::kVertical));
    }
    REQUIRE(CheckForWinner(student, DiskType::kPlayer1));
    REQUIRE_FALSE(CheckForWinner(student, DiskType::kPlayer2));
  }

  SECTION("middle") {
    // clang-format off
    DiskType source[kBoardHeight][kBoardWidth] = {
    {DiskType::kPlayer2, DiskType::kPlayer2, DiskType::kPlayer1, DiskType::kPlayer1, DiskType::kPlayer1, DiskType::kPlayer2, DiskType::kPlayer2},
    {DiskType::kPlayer1, DiskType::kPlayer1, DiskType::kPlayer2, DiskType::kPlayer2, DiskType::kPlayer2, DiskType::kEmpty, DiskType::kEmpty},
    {DiskType::kEmpty, DiskType::kPlayer2, DiskType::kPlayer2, DiskType::kPlayer1, DiskType::kPlayer2, DiskType::kEmpty, DiskType::kEmpty},
    {DiskType::kEmpty, DiskType::kPlayer1, DiskType::kPlayer1, DiskType::kPlayer1, DiskType::kPlayer1, DiskType::kEmpty, DiskType::kEmpty},
    {DiskType::kEmpty, DiskType::kPlayer1, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty},
    {DiskType::kEmpty, DiskType::kPlayer2, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty}
    };
    // clang-format on
    CopyBoard(source, student.board);
    SECTION("Check right diagonal") {
      REQUIRE_FALSE(SearchForWinner(
          student, DiskType::kPlayer1, WinningDirection::kRightDiag));
      REQUIRE_FALSE(SearchForWinner(
          student, DiskType::kPlayer2, WinningDirection::kRightDiag));
    }
    SECTION("Check left diagonal") {
      REQUIRE_FALSE(SearchForWinner(
          student, DiskType::kPlayer1, WinningDirection::kLeftDiag));
      REQUIRE_FALSE(SearchForWinner(
          student, DiskType::kPlayer2, WinningDirection::kLeftDiag));
    }
    SECTION("Check horizontal") {
      REQUIRE(SearchForWinner(
          student, DiskType::kPlayer1, WinningDirection::kHorizontal));
      REQUIRE_FALSE(SearchForWinner(
          student, DiskType::kPlayer2, WinningDirection::kHorizontal));
    }
    SECTION("Check vertical") {
      REQUIRE_FALSE(SearchForWinner(
          student, DiskType::kPlayer1, WinningDirection::kVertical));
      REQUIRE_FALSE(SearchForWinner(
          student, DiskType::kPlayer2, WinningDirection::kVertical));
    }
    REQUIRE(CheckForWinner(student, DiskType::kPlayer1));
    REQUIRE_FALSE(CheckForWinner(student, DiskType::kPlayer2));
  }

  SECTION("top") {
    // clang-format off
    DiskType source[kBoardHeight][kBoardWidth] = {
    {DiskType::kPlayer2, DiskType::kPlayer2, DiskType::kPlayer1, DiskType::kPlayer1, DiskType::kPlayer1, DiskType::kEmpty, DiskType::kEmpty},
    {DiskType::kEmpty, DiskType::kPlayer1, DiskType::kPlayer2, DiskType::kPlayer2, DiskType::kPlayer2, DiskType::kEmpty, DiskType::kEmpty},
    {DiskType::kEmpty, DiskType::kPlayer2, DiskType::kPlayer2, DiskType::kPlayer1, DiskType::kPlayer2, DiskType::kEmpty, DiskType::kEmpty},
    {DiskType::kEmpty, DiskType::kPlayer1, DiskType::kPlayer1, DiskType::kPlayer2, DiskType::kPlayer1, DiskType::kEmpty, DiskType::kEmpty},
    {DiskType::kEmpty, DiskType::kPlayer2, DiskType::kPlayer2, DiskType::kPlayer2, DiskType::kPlayer1, DiskType::kEmpty, DiskType::kEmpty},
    {DiskType::kEmpty, DiskType::kPlayer1, DiskType::kPlayer1, DiskType::kPlayer1, DiskType::kPlayer1, DiskType::kEmpty, DiskType::kEmpty}
    };
    // clang-format on
    CopyBoard(source, student.board);
    SECTION("Check right diagonal") {
      REQUIRE_FALSE(SearchForWinner(
          student, DiskType::kPlayer1, WinningDirection::kRightDiag));
      REQUIRE_FALSE(SearchForWinner(
          student, DiskType::kPlayer2, WinningDirection::kRightDiag));
    }
    SECTION("Check left diagonal") {
      REQUIRE_FALSE(SearchForWinner(
          student, DiskType::kPlayer1, WinningDirection::kLeftDiag));
      REQUIRE_FALSE(SearchForWinner(
          student, DiskType::kPlayer2, WinningDirection::kLeftDiag));
    }
    SECTION("Check horizontal") {
      REQUIRE(SearchForWinner(
          student, DiskType::kPlayer1, WinningDirection::kHorizontal));
      REQUIRE_FALSE(SearchForWinner(
          student, DiskType::kPlayer2, WinningDirection::kHorizontal));
    }
    SECTION("Check vertical") {
      REQUIRE_FALSE(SearchForWinner(
          student, DiskType::kPlayer1, WinningDirection::kVertical));
      REQUIRE_FALSE(SearchForWinner(
          student, DiskType::kPlayer2, WinningDirection::kVertical));
    }
    REQUIRE(CheckForWinner(student, DiskType::kPlayer1));
    REQUIRE_FALSE(CheckForWinner(student, DiskType::kPlayer2));
  }
}

TEST_CASE("CheckForWinner(student, DiskType::kPlayer2) kVertical comprehensive",
          "[comp-two-win-vertical-unit]") {
  Board student;
  // clang-format off
  SECTION("left") {
    DiskType source[kBoardHeight][kBoardWidth] = {
    {DiskType::kPlayer1, DiskType::kPlayer1, DiskType::kPlayer1, DiskType::kEmpty, DiskType::kPlayer1, DiskType::kPlayer2, DiskType::kPlayer1},
    {DiskType::kPlayer1, DiskType::kPlayer1, DiskType::kEmpty, DiskType::kEmpty, DiskType::kPlayer2, DiskType::kPlayer2, DiskType::kPlayer1},
    {DiskType::kPlayer2, DiskType::kPlayer2, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty},
    {DiskType::kPlayer2, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty},
    {DiskType::kPlayer2, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty},
    {DiskType::kPlayer2, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty}
    };
    // clang-format on
    CopyBoard(source, student.board);
    SECTION("Check right diagonal") {
      REQUIRE_FALSE(SearchForWinner(
          student, DiskType::kPlayer1, WinningDirection::kRightDiag));
      REQUIRE_FALSE(SearchForWinner(
          student, DiskType::kPlayer2, WinningDirection::kRightDiag));
    }
    SECTION("Check left diagonal") {
      REQUIRE_FALSE(SearchForWinner(
          student, DiskType::kPlayer1, WinningDirection::kLeftDiag));
      REQUIRE_FALSE(SearchForWinner(
          student, DiskType::kPlayer2, WinningDirection::kLeftDiag));
    }
    SECTION("Check horizontal") {
      REQUIRE_FALSE(SearchForWinner(
          student, DiskType::kPlayer1, WinningDirection::kHorizontal));
      REQUIRE_FALSE(SearchForWinner(
          student, DiskType::kPlayer2, WinningDirection::kHorizontal));
    }
    SECTION("Check vertical") {
      REQUIRE_FALSE(SearchForWinner(
          student, DiskType::kPlayer1, WinningDirection::kVertical));
      REQUIRE(SearchForWinner(
          student, DiskType::kPlayer2, WinningDirection::kVertical));
    }
    REQUIRE_FALSE(CheckForWinner(student, DiskType::kPlayer1));
    REQUIRE(CheckForWinner(student, DiskType::kPlayer2));
  }

  SECTION("middle") {
    // clang-format off
    DiskType source[kBoardHeight][kBoardWidth] = {
    {DiskType::kPlayer1, DiskType::kPlayer1, DiskType::kPlayer1, DiskType::kPlayer2, DiskType::kPlayer1, DiskType::kPlayer1, DiskType::kPlayer1},
    {DiskType::kPlayer1, DiskType::kPlayer1, DiskType::kPlayer2, DiskType::kPlayer2, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty},
    {DiskType::kPlayer2, DiskType::kPlayer2, DiskType::kPlayer2, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty},
    {DiskType::kEmpty, DiskType::kEmpty, DiskType::kPlayer2, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty},
    {DiskType::kEmpty, DiskType::kEmpty, DiskType::kPlayer2, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty},
    {DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty}
    };
    // clang-format on
    CopyBoard(source, student.board);
    SECTION("Check right diagonal") {
      REQUIRE_FALSE(SearchForWinner(
          student, DiskType::kPlayer1, WinningDirection::kRightDiag));
      REQUIRE_FALSE(SearchForWinner(
          student, DiskType::kPlayer2, WinningDirection::kRightDiag));
    }
    SECTION("Check left diagonal") {
      REQUIRE_FALSE(SearchForWinner(
          student, DiskType::kPlayer1, WinningDirection::kLeftDiag));
      REQUIRE_FALSE(SearchForWinner(
          student, DiskType::kPlayer2, WinningDirection::kLeftDiag));
    }
    SECTION("Check horizontal") {
      REQUIRE_FALSE(SearchForWinner(
          student, DiskType::kPlayer1, WinningDirection::kHorizontal));
      REQUIRE_FALSE(SearchForWinner(
          student, DiskType::kPlayer2, WinningDirection::kHorizontal));
    }
    SECTION("Check vertical") {
      REQUIRE_FALSE(SearchForWinner(
          student, DiskType::kPlayer1, WinningDirection::kVertical));
      REQUIRE(SearchForWinner(
          student, DiskType::kPlayer2, WinningDirection::kVertical));
    }
    REQUIRE_FALSE(CheckForWinner(student, DiskType::kPlayer1));
    REQUIRE(CheckForWinner(student, DiskType::kPlayer2));
  }

  SECTION("right") {
    // clang-format off
    DiskType source[kBoardHeight][kBoardWidth] = {
    {DiskType::kPlayer1, DiskType::kPlayer1, DiskType::kPlayer1, DiskType::kPlayer2, DiskType::kPlayer1, DiskType::kEmpty, DiskType::kPlayer2},
    {DiskType::kPlayer1, DiskType::kPlayer1, DiskType::kPlayer2, DiskType::kEmpty, DiskType::kPlayer1, DiskType::kEmpty, DiskType::kPlayer2},
    {DiskType::kEmpty, DiskType::kPlayer2, DiskType::kPlayer2, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kPlayer2},
    {DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kPlayer2},
    {DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty},
    {DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty}
    };
    // clang-format on
    CopyBoard(source, student.board);
    SECTION("Check right diagonal") {
      REQUIRE_FALSE(SearchForWinner(
          student, DiskType::kPlayer1, WinningDirection::kRightDiag));
      REQUIRE_FALSE(SearchForWinner(
          student, DiskType::kPlayer2, WinningDirection::kRightDiag));
    }
    SECTION("Check left diagonal") {
      REQUIRE_FALSE(SearchForWinner(
          student, DiskType::kPlayer1, WinningDirection::kLeftDiag));
      REQUIRE_FALSE(SearchForWinner(
          student, DiskType::kPlayer2, WinningDirection::kLeftDiag));
    }
    SECTION("Check horizontal") {
      REQUIRE_FALSE(SearchForWinner(
          student, DiskType::kPlayer1, WinningDirection::kHorizontal));
      REQUIRE_FALSE(SearchForWinner(
          student, DiskType::kPlayer2, WinningDirection::kHorizontal));
    }
    SECTION("Check vertical") {
      REQUIRE_FALSE(SearchForWinner(
          student, DiskType::kPlayer1, WinningDirection::kVertical));
      REQUIRE(SearchForWinner(
          student, DiskType::kPlayer2, WinningDirection::kVertical));
    }
    REQUIRE_FALSE(CheckForWinner(student, DiskType::kPlayer1));
    REQUIRE(CheckForWinner(student, DiskType::kPlayer2));
  }
}

TEST_CASE(
    "CheckForWinner(student, DiskType::kPlayer2) kRightDiag comprehensive",
    "[comp-two-win-right-diagonal-unit]") {
  Board student;
  // clang-format off
  SECTION("middle") {
    DiskType source[kBoardHeight][kBoardWidth] = {
    {DiskType::kPlayer1, DiskType::kPlayer2, DiskType::kPlayer1, DiskType::kEmpty, DiskType::kPlayer1, DiskType::kPlayer2, DiskType::kPlayer1},
    {DiskType::kPlayer1, DiskType::kPlayer1, DiskType::kPlayer2, DiskType::kEmpty, DiskType::kPlayer2, DiskType::kPlayer2, DiskType::kPlayer1},
    {DiskType::kPlayer2, DiskType::kPlayer2, DiskType::kEmpty, DiskType::kPlayer2, DiskType::kPlayer1, DiskType::kEmpty, DiskType::kPlayer1},
    {DiskType::kPlayer2, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kPlayer2, DiskType::kEmpty, DiskType::kEmpty},
    {DiskType::kPlayer2, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty},
    {DiskType::kPlayer1, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty}
    };
    // clang-format on
    CopyBoard(source, student.board);
    SECTION("Check right diagonal") {
      REQUIRE_FALSE(SearchForWinner(
          student, DiskType::kPlayer1, WinningDirection::kRightDiag));
      REQUIRE(SearchForWinner(
          student, DiskType::kPlayer2, WinningDirection::kRightDiag));
    }
    SECTION("Check left diagonal") {
      REQUIRE_FALSE(SearchForWinner(
          student, DiskType::kPlayer1, WinningDirection::kLeftDiag));
      REQUIRE_FALSE(SearchForWinner(
          student, DiskType::kPlayer2, WinningDirection::kLeftDiag));
    }
    SECTION("Check horizontal") {
      REQUIRE_FALSE(SearchForWinner(
          student, DiskType::kPlayer1, WinningDirection::kHorizontal));
      REQUIRE_FALSE(SearchForWinner(
          student, DiskType::kPlayer2, WinningDirection::kHorizontal));
    }
    SECTION("Check vertical") {
      REQUIRE_FALSE(SearchForWinner(
          student, DiskType::kPlayer1, WinningDirection::kVertical));
      REQUIRE_FALSE(SearchForWinner(
          student, DiskType::kPlayer2, WinningDirection::kVertical));
    }
    REQUIRE_FALSE(CheckForWinner(student, DiskType::kPlayer1));
    REQUIRE(CheckForWinner(student, DiskType::kPlayer2));
  }

  SECTION("left") {
    // clang-format off
    DiskType source[kBoardHeight][kBoardWidth] = {
    {DiskType::kPlayer2, DiskType::kPlayer1, DiskType::kPlayer1, DiskType::kPlayer2, DiskType::kPlayer1, DiskType::kPlayer1, DiskType::kPlayer1},
    {DiskType::kPlayer1, DiskType::kPlayer2, DiskType::kPlayer2, DiskType::kPlayer2, DiskType::kEmpty, DiskType::kPlayer1, DiskType::kEmpty},
    {DiskType::kPlayer2, DiskType::kPlayer2, DiskType::kPlayer2, DiskType::kPlayer1, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty},
    {DiskType::kPlayer1, DiskType::kEmpty, DiskType::kPlayer1, DiskType::kPlayer2, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty},
    {DiskType::kEmpty, DiskType::kEmpty, DiskType::kPlayer2, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty},
    {DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty}
    };
    // clang-format on
    CopyBoard(source, student.board);
    SECTION("Check right diagonal") {
      REQUIRE_FALSE(SearchForWinner(
          student, DiskType::kPlayer1, WinningDirection::kRightDiag));
      REQUIRE(SearchForWinner(
          student, DiskType::kPlayer2, WinningDirection::kRightDiag));
    }
    SECTION("Check left diagonal") {
      REQUIRE_FALSE(SearchForWinner(
          student, DiskType::kPlayer1, WinningDirection::kLeftDiag));
      REQUIRE_FALSE(SearchForWinner(
          student, DiskType::kPlayer2, WinningDirection::kLeftDiag));
    }
    SECTION("Check horizontal") {
      REQUIRE_FALSE(SearchForWinner(
          student, DiskType::kPlayer1, WinningDirection::kHorizontal));
      REQUIRE_FALSE(SearchForWinner(
          student, DiskType::kPlayer2, WinningDirection::kHorizontal));
    }
    SECTION("Check vertical") {
      REQUIRE_FALSE(SearchForWinner(
          student, DiskType::kPlayer1, WinningDirection::kVertical));
      REQUIRE_FALSE(SearchForWinner(
          student, DiskType::kPlayer2, WinningDirection::kVertical));
    }
    REQUIRE_FALSE(CheckForWinner(student, DiskType::kPlayer1));
    REQUIRE(CheckForWinner(student, DiskType::kPlayer2));
  }

  SECTION("right") {
    // clang-format off
    DiskType source[kBoardHeight][kBoardWidth] = {
    {DiskType::kPlayer1, DiskType::kPlayer1, DiskType::kPlayer1, DiskType::kPlayer2, DiskType::kPlayer1, DiskType::kPlayer2, DiskType::kPlayer2},
    {DiskType::kPlayer1, DiskType::kPlayer1, DiskType::kPlayer2, DiskType::kPlayer2, DiskType::kPlayer1, DiskType::kPlayer1, DiskType::kPlayer2},
    {DiskType::kEmpty, DiskType::kPlayer1, DiskType::kPlayer2, DiskType::kPlayer2, DiskType::kPlayer2, DiskType::kPlayer1, DiskType::kPlayer2},
    {DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kPlayer2, DiskType::kPlayer1},
    {DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kPlayer2},
    {DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty}
    };
    // clang-format on
    CopyBoard(source, student.board);
    SECTION("Check right diagonal") {
      REQUIRE_FALSE(SearchForWinner(
          student, DiskType::kPlayer1, WinningDirection::kRightDiag));
      REQUIRE(SearchForWinner(
          student, DiskType::kPlayer2, WinningDirection::kRightDiag));
    }
    SECTION("Check left diagonal") {
      REQUIRE_FALSE(SearchForWinner(
          student, DiskType::kPlayer1, WinningDirection::kLeftDiag));
      REQUIRE_FALSE(SearchForWinner(
          student, DiskType::kPlayer2, WinningDirection::kLeftDiag));
    }
    SECTION("Check horizontal") {
      REQUIRE_FALSE(SearchForWinner(
          student, DiskType::kPlayer1, WinningDirection::kHorizontal));
      REQUIRE_FALSE(SearchForWinner(
          student, DiskType::kPlayer2, WinningDirection::kHorizontal));
    }
    SECTION("Check vertical") {
      REQUIRE_FALSE(SearchForWinner(
          student, DiskType::kPlayer1, WinningDirection::kVertical));
      REQUIRE_FALSE(SearchForWinner(
          student, DiskType::kPlayer2, WinningDirection::kVertical));
    }
    REQUIRE_FALSE(CheckForWinner(student, DiskType::kPlayer1));
    REQUIRE(CheckForWinner(student, DiskType::kPlayer2));
  }
}

TEST_CASE("CheckForWinner(student, DiskType::kPlayer1) kLeftDiag comprehensive",
          "[comp-one-win-left-diagonal-unit]") {
  Board student;
  // clang-format off
  SECTION("middle") {
    DiskType source[kBoardHeight][kBoardWidth] = {
    {DiskType::kPlayer1, DiskType::kPlayer2, DiskType::kPlayer1, DiskType::kPlayer2, DiskType::kPlayer2, DiskType::kPlayer2, DiskType::kPlayer1},
    {DiskType::kPlayer1, DiskType::kPlayer1, DiskType::kPlayer2, DiskType::kPlayer1, DiskType::kPlayer2, DiskType::kPlayer2, DiskType::kPlayer1},
    {DiskType::kPlayer2, DiskType::kPlayer1, DiskType::kPlayer1, DiskType::kPlayer2, DiskType::kPlayer2, DiskType::kEmpty, DiskType::kEmpty},
    {DiskType::kPlayer2, DiskType::kPlayer1, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty},
    {DiskType::kPlayer1, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty},
    {DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty}
    };
    // clang-format on
    CopyBoard(source, student.board);
    SECTION("Check right diagonal") {
      REQUIRE_FALSE(SearchForWinner(
          student, DiskType::kPlayer1, WinningDirection::kRightDiag));
      REQUIRE_FALSE(SearchForWinner(
          student, DiskType::kPlayer2, WinningDirection::kRightDiag));
    }
    SECTION("Check left diagonal") {
      REQUIRE(SearchForWinner(
          student, DiskType::kPlayer1, WinningDirection::kLeftDiag));
      REQUIRE_FALSE(SearchForWinner(
          student, DiskType::kPlayer2, WinningDirection::kLeftDiag));
    }
    SECTION("Check horizontal") {
      REQUIRE_FALSE(SearchForWinner(
          student, DiskType::kPlayer1, WinningDirection::kHorizontal));
      REQUIRE_FALSE(SearchForWinner(
          student, DiskType::kPlayer2, WinningDirection::kHorizontal));
    }
    SECTION("Check vertical") {
      REQUIRE_FALSE(SearchForWinner(
          student, DiskType::kPlayer1, WinningDirection::kVertical));
      REQUIRE_FALSE(SearchForWinner(
          student, DiskType::kPlayer2, WinningDirection::kVertical));
    }
    REQUIRE(CheckForWinner(student, DiskType::kPlayer1));
    REQUIRE_FALSE(CheckForWinner(student, DiskType::kPlayer2));
  }

  SECTION("left") {
    // clang-format off
    DiskType source[kBoardHeight][kBoardWidth] = {
    {DiskType::kPlayer2, DiskType::kPlayer1, DiskType::kPlayer2, DiskType::kPlayer1, DiskType::kPlayer1, DiskType::kEmpty, DiskType::kEmpty},
    {DiskType::kPlayer1, DiskType::kPlayer2, DiskType::kPlayer1, DiskType::kPlayer2, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty},
    {DiskType::kPlayer2, DiskType::kPlayer1, DiskType::kPlayer2, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty},
    {DiskType::kPlayer1, DiskType::kEmpty, DiskType::kPlayer1, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty},
    {DiskType::kEmpty, DiskType::kEmpty, DiskType::kPlayer2, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty},
    {DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty}
    };
    // clang-format on
    CopyBoard(source, student.board);
    SECTION("Check right diagonal") {
      REQUIRE_FALSE(SearchForWinner(
          student, DiskType::kPlayer1, WinningDirection::kRightDiag));
      REQUIRE_FALSE(SearchForWinner(
          student, DiskType::kPlayer2, WinningDirection::kRightDiag));
    }
    SECTION("Check left diagonal") {
      REQUIRE(SearchForWinner(
          student, DiskType::kPlayer1, WinningDirection::kLeftDiag));
      REQUIRE_FALSE(SearchForWinner(
          student, DiskType::kPlayer2, WinningDirection::kLeftDiag));
    }
    SECTION("Check horizontal") {
      REQUIRE_FALSE(SearchForWinner(
          student, DiskType::kPlayer1, WinningDirection::kHorizontal));
      REQUIRE_FALSE(SearchForWinner(
          student, DiskType::kPlayer2, WinningDirection::kHorizontal));
    }
    SECTION("Check vertical") {
      REQUIRE_FALSE(SearchForWinner(
          student, DiskType::kPlayer1, WinningDirection::kVertical));
      REQUIRE_FALSE(SearchForWinner(
          student, DiskType::kPlayer2, WinningDirection::kVertical));
    }
    REQUIRE(CheckForWinner(student, DiskType::kPlayer1));
    REQUIRE_FALSE(CheckForWinner(student, DiskType::kPlayer2));
  }

  SECTION("right") {
    // clang-format off
    DiskType source[kBoardHeight][kBoardWidth] = {
    {DiskType::kPlayer1, DiskType::kPlayer1, DiskType::kPlayer1, DiskType::kPlayer2, DiskType::kPlayer1, DiskType::kPlayer1, DiskType::kPlayer1},
    {DiskType::kPlayer1, DiskType::kPlayer1, DiskType::kPlayer2, DiskType::kPlayer2, DiskType::kPlayer1, DiskType::kPlayer1, DiskType::kPlayer2},
    {DiskType::kEmpty, DiskType::kPlayer2, DiskType::kPlayer2, DiskType::kPlayer2, DiskType::kPlayer1, DiskType::kPlayer2, DiskType::kPlayer2},
    {DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kPlayer1, DiskType::kPlayer2, DiskType::kEmpty, DiskType::kPlayer1},
    {DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kPlayer2},
    {DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kPlayer2}
    };
    // clang-format on
    CopyBoard(source, student.board);
    SECTION("Check right diagonal") {
      REQUIRE_FALSE(SearchForWinner(
          student, DiskType::kPlayer1, WinningDirection::kRightDiag));
      REQUIRE_FALSE(SearchForWinner(
          student, DiskType::kPlayer2, WinningDirection::kRightDiag));
    }
    SECTION("Check left diagonal") {
      REQUIRE(SearchForWinner(
          student, DiskType::kPlayer1, WinningDirection::kLeftDiag));
      REQUIRE_FALSE(SearchForWinner(
          student, DiskType::kPlayer2, WinningDirection::kLeftDiag));
    }
    SECTION("Check horizontal") {
      REQUIRE_FALSE(SearchForWinner(
          student, DiskType::kPlayer1, WinningDirection::kHorizontal));
      REQUIRE_FALSE(SearchForWinner(
          student, DiskType::kPlayer2, WinningDirection::kHorizontal));
    }
    SECTION("Check vertical") {
      REQUIRE_FALSE(SearchForWinner(
          student, DiskType::kPlayer1, WinningDirection::kVertical));
      REQUIRE_FALSE(SearchForWinner(
          student, DiskType::kPlayer2, WinningDirection::kVertical));
    }
    REQUIRE(CheckForWinner(student, DiskType::kPlayer1));
    REQUIRE_FALSE(CheckForWinner(student, DiskType::kPlayer2));
  }
}

TEST_CASE("Player One wins diagonally complete",
          "[drop-one-win-left-diagonal]") {
  Board b;  // NOLINT
  InitBoard(b);
  DropDiskToBoard(b, DiskType::kPlayer1, 6);  // NOLINT
  REQUIRE_FALSE(CheckForWinner(b, DiskType::kPlayer1));
  DropDiskToBoard(b, DiskType::kPlayer2, 5);  // NOLINT
  DropDiskToBoard(b, DiskType::kPlayer1, 5);  // NOLINT
  REQUIRE_FALSE(CheckForWinner(b, DiskType::kPlayer1));
  DropDiskToBoard(b, DiskType::kPlayer2, 4);  // NOLINT
  DropDiskToBoard(b, DiskType::kPlayer2, 4);  // NOLINT
  DropDiskToBoard(b, DiskType::kPlayer1, 4);  // NOLINT
  DropDiskToBoard(b, DiskType::kPlayer2, 3);  // NOLINT
  DropDiskToBoard(b, DiskType::kPlayer1, 6);
  DropDiskToBoard(b, DiskType::kPlayer2, 3);  // NOLINT
  DropDiskToBoard(b, DiskType::kPlayer1, 6);
  DropDiskToBoard(b, DiskType::kPlayer2, 3);  // NOLINT
  DropDiskToBoard(b, DiskType::kPlayer1, 3);
  SECTION("Check right diagonal") {
    REQUIRE_FALSE(
        SearchForWinner(b, DiskType::kPlayer1, WinningDirection::kRightDiag));
  }
  SECTION("Check left diagonal") {
    REQUIRE(
        SearchForWinner(b, DiskType::kPlayer1, WinningDirection::kLeftDiag));
  }
  SECTION("Check horizontal") {
    REQUIRE_FALSE(
        SearchForWinner(b, DiskType::kPlayer1, WinningDirection::kHorizontal));
  }
  SECTION("Check vertical") {
    REQUIRE_FALSE(
        SearchForWinner(b, DiskType::kPlayer1, WinningDirection::kVertical));
  }
  REQUIRE(CheckForWinner(b, DiskType::kPlayer1));
  REQUIRE_FALSE(CheckForWinner(b, DiskType::kPlayer2));
}

TEST_CASE("Player Two wins diagonally complete",
          "[drop-two-win-left-diagonal]") {
  Board b;  // NOLINT
  InitBoard(b);
  DropDiskToBoard(b, DiskType::kPlayer2, 6);  // NOLINT
  REQUIRE_FALSE(CheckForWinner(b, DiskType::kPlayer2));
  DropDiskToBoard(b, DiskType::kPlayer1, 5);  // NOLINT
  DropDiskToBoard(b, DiskType::kPlayer2, 5);  // NOLINT
  REQUIRE_FALSE(CheckForWinner(b, DiskType::kPlayer2));
  DropDiskToBoard(b, DiskType::kPlayer1, 4);  // NOLINT
  DropDiskToBoard(b, DiskType::kPlayer1, 4);  // NOLINT
  DropDiskToBoard(b, DiskType::kPlayer2, 4);  // NOLINT
  DropDiskToBoard(b, DiskType::kPlayer1, 3);  // NOLINT
  DropDiskToBoard(b, DiskType::kPlayer2, 6);
  DropDiskToBoard(b, DiskType::kPlayer1, 3);  // NOLINT
  DropDiskToBoard(b, DiskType::kPlayer2, 6);
  DropDiskToBoard(b, DiskType::kPlayer1, 3);  // NOLINT
  DropDiskToBoard(b, DiskType::kPlayer2, 3);  // NOLINT
  SECTION("Check right diagonal") {
    REQUIRE_FALSE(
        SearchForWinner(b, DiskType::kPlayer2, WinningDirection::kRightDiag));
  }
  SECTION("Check left diagonal") {
    REQUIRE(
        SearchForWinner(b, DiskType::kPlayer2, WinningDirection::kLeftDiag));
  }
  SECTION("Check horizontal") {
    REQUIRE_FALSE(
        SearchForWinner(b, DiskType::kPlayer2, WinningDirection::kHorizontal));
  }
  SECTION("Check vertical") {
    REQUIRE_FALSE(
        SearchForWinner(b, DiskType::kPlayer2, WinningDirection::kVertical));
  }
  REQUIRE(CheckForWinner(b, DiskType::kPlayer2));
  REQUIRE_FALSE(CheckForWinner(b, DiskType::kPlayer1));
}

TEST_CASE("Player Two wins horizontally on bottom row complete",
          "[drop-two-win-horizontal-bottom]") {
  Board b;
  InitBoard(b);
  DropDiskToBoard(b, DiskType::kPlayer2, 6);
  DropDiskToBoard(b, DiskType::kPlayer1, 6);
  DropDiskToBoard(b, DiskType::kPlayer2, 5);
  DropDiskToBoard(b, DiskType::kPlayer1, 6);
  DropDiskToBoard(b, DiskType::kPlayer2, 4);
  DropDiskToBoard(b, DiskType::kPlayer1, 6);
  REQUIRE_FALSE(CheckForWinner(b, DiskType::kPlayer2));
  REQUIRE_FALSE(CheckForWinner(b, DiskType::kPlayer1));
  DropDiskToBoard(b, DiskType::kPlayer2, 3);
  DropDiskToBoard(b, DiskType::kPlayer1, 3);
  SECTION("Check right diagonal") {
    REQUIRE_FALSE(
        SearchForWinner(b, DiskType::kPlayer2, WinningDirection::kRightDiag));
  }
  SECTION("Check left diagonal") {
    REQUIRE_FALSE(
        SearchForWinner(b, DiskType::kPlayer2, WinningDirection::kLeftDiag));
  }
  SECTION("Check horizontal") {
    REQUIRE(
        SearchForWinner(b, DiskType::kPlayer2, WinningDirection::kHorizontal));
  }
  SECTION("Check vertical") {
    REQUIRE_FALSE(
        SearchForWinner(b, DiskType::kPlayer2, WinningDirection::kVertical));
  }
  REQUIRE(CheckForWinner(b, DiskType::kPlayer2));
}

TEST_CASE("Player One wins horizontally on middle row complete",
          "[drop-one-win-horizontal-middle]") {
  Board b;
  InitBoard(b);
  DropDiskToBoard(b, DiskType::kPlayer1, 5);
  DropDiskToBoard(b, DiskType::kPlayer2, 4);
  DropDiskToBoard(b, DiskType::kPlayer1, 4);
  DropDiskToBoard(b, DiskType::kPlayer2, 5);
  DropDiskToBoard(b, DiskType::kPlayer1, 3);
  DropDiskToBoard(b, DiskType::kPlayer2, 2);
  DropDiskToBoard(b, DiskType::kPlayer1, 2);
  DropDiskToBoard(b, DiskType::kPlayer2, 3);
  DropDiskToBoard(b, DiskType::kPlayer1, 5);
  DropDiskToBoard(b, DiskType::kPlayer2, 0);
  DropDiskToBoard(b, DiskType::kPlayer1, 4);
  DropDiskToBoard(b, DiskType::kPlayer2, 0);
  DropDiskToBoard(b, DiskType::kPlayer1, 3);
  DropDiskToBoard(b, DiskType::kPlayer2, 0);
  DropDiskToBoard(b, DiskType::kPlayer1, 2);
  SECTION("Check right diagonal") {
    REQUIRE_FALSE(
        SearchForWinner(b, DiskType::kPlayer1, WinningDirection::kRightDiag));
  }
  SECTION("Check left diagonal") {
    REQUIRE_FALSE(
        SearchForWinner(b, DiskType::kPlayer1, WinningDirection::kLeftDiag));
  }
  SECTION("Check horizontal") {
    REQUIRE(
        SearchForWinner(b, DiskType::kPlayer1, WinningDirection::kHorizontal));
  }
  SECTION("Check vertical") {
    REQUIRE_FALSE(
        SearchForWinner(b, DiskType::kPlayer1, WinningDirection::kVertical));
  }
  REQUIRE(CheckForWinner(b, DiskType::kPlayer1));
}

/////////////////////////////////////////////////////////////////////////////////////////////
