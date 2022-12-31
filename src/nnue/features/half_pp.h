/*
  Stockfish, a UCI chess playing engine derived from Glaurung 2.1
  Copyright (C) 2004-2022 The Stockfish developers (see AUTHORS file)

  Stockfish is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 3 of the License, or
  (at your option) any later version.

  Stockfish is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

//Definition of input features HalfPP of NNUE evaluation function

#ifndef NNUE_FEATURES_HALF_PP_H_INCLUDED
#define NNUE_FEATURES_HALF_PP_H_INCLUDED

#include "../nnue_common.h"

#include "../../evaluate.h"
#include "../../misc.h"

namespace Stockfish {
  struct StateInfo;
}

namespace Stockfish::Eval::NNUE::Features {

  // Feature HalfPP: Combination of the position of pieces.
  class HalfPP {

    // unique number for each piece type on each square
    enum {
      PS_NONE      =  0,
      PS_W_ROOK    =  0,
      PS_B_ROOK    =  1  * SQUARE_NB,
      PS_W_ADVISOR =  2  * SQUARE_NB,
      PS_B_ADVISOR =  3  * SQUARE_NB,
      PS_W_CANNON  =  4  * SQUARE_NB,
      PS_B_CANNON  =  5  * SQUARE_NB,
      PS_W_PAWN    =  6  * SQUARE_NB,
      PS_B_PAWN    =  7  * SQUARE_NB,
      PS_W_KNIGHT  =  8  * SQUARE_NB,
      PS_B_KNIGHT  =  9  * SQUARE_NB,
      PS_W_BISHOP  =  10 * SQUARE_NB,
      PS_B_BISHOP  =  11 * SQUARE_NB,
      PS_W_KING    =  12 * SQUARE_NB,
      PS_B_KING    =  13 * SQUARE_NB,
      PS_NB        =  14 * SQUARE_NB
    };

    static constexpr IndexType PieceSquareIndex[COLOR_NB][PIECE_NB] = {
      // convention: W - us, B - them
      // viewed from other side, W and B are reversed
      { PS_NONE, PS_W_ROOK, PS_W_ADVISOR, PS_W_CANNON, PS_W_PAWN, PS_W_KNIGHT, PS_W_BISHOP, PS_W_KING,
        PS_NONE, PS_B_ROOK, PS_B_ADVISOR, PS_B_CANNON, PS_B_PAWN, PS_B_KNIGHT, PS_B_BISHOP, PS_B_KING },
      { PS_NONE, PS_B_ROOK, PS_B_ADVISOR, PS_B_CANNON, PS_B_PAWN, PS_B_KNIGHT, PS_B_BISHOP, PS_B_KING,
        PS_NONE, PS_W_ROOK, PS_W_ADVISOR, PS_W_CANNON, PS_W_PAWN, PS_W_KNIGHT, PS_W_BISHOP, PS_W_KING, }
    };

    // Index of a feature for a given piece position and another piece on some square
    template<Color Perspective>
    static IndexType make_index(Square s1, Piece p1, Square s2, Piece p2);

   public:
    // Feature name
    static constexpr const char* Name = "HalfPP";

    // Hash value embedded in the evaluation file
    static constexpr std::uint32_t HashValue = 0x7f234cb8;

    // Number of feature dimensions
    static constexpr IndexType Dimensions = PS_NB * PS_NB;

    // Rotate a square by 180
    static constexpr int Rotate[SQUARE_NB] = {
       81, 82, 83, 84, 85, 86, 87, 88, 89,
       72, 73, 74, 75, 76, 77, 78, 79, 80,
       63, 64, 65, 66, 67, 68, 69, 70, 71,
       54, 55, 56, 57, 58, 59, 60, 61, 62,
       45, 46, 47, 48, 49, 50, 51, 52, 53,
       36, 37, 38, 39, 40, 41, 42, 43, 44,
       27, 28, 29, 30, 31, 32, 33, 34, 35,
       18, 19, 20, 21, 22, 23, 24, 25, 26,
        9, 10, 11, 12, 13, 14, 15, 16, 17,
        0,  1,  2,  3,  4,  5,  6,  7,  8,
    };

    // Maximum number of simultaneously active features.
    static constexpr IndexType MaxActiveDimensions = 32 * 32;
    using IndexList = ValueList<IndexType, MaxActiveDimensions>;

    // Get a list of indices for active features
    template<Color Perspective>
    static void append_active_indices(
      const Position& pos,
      IndexList& active);

    // Get a list of indices for recently changed features
    template<Color Perspective>
    static void append_changed_indices(
      const Position& pos,
      IndexList& removed,
      IndexList& added
    );
  };

}  // namespace Stockfish::Eval::NNUE::Features

#endif // #ifndef NNUE_FEATURES_HALF_PP_H_INCLUDED
