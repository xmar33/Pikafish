/*
  Stockfish, a UCI chess playing engine derived from Glaurung 2.1
  Copyright (C) 2004-2023 The Stockfish developers (see AUTHORS file)
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


#include "psqt.h"

#include <algorithm>

#include "bitboard.h"
#include "types.h"

namespace Stockfish {

namespace
{

auto constexpr S = make_score;
auto constexpr NEVER_IN_USE = S(0, 0);

// 'Bonus' contains Piece-Square parameters.
// Scores are explicit for files A to E, implicitly mirrored for F to I.
constexpr Score Bonus[][RANK_NB][int(FILE_NB) / 2 + 1] = {
  { },// NoPiece
  { // Rook
   { S(-193, -437), S(  57, -171), S( -68, -186), S(-111,  -48), S(  76,   37) },
   { S( -72, -294), S(-132,  153), S(-139,  121), S(  12,  119), S(  87, -245) },
   { S( -94, -255), S(-123,  193), S( -10,    5), S(-124,  125), S(  20,  218) },
   { S( -49,  244), S(  43,  -96), S( 134, -124), S( -50,  239), S(-207,  198) },
   { S(  93,   13), S( 135, -101), S( 167, -133), S(  86,  -62), S(-104,  -67) },
   { S(-195,  246), S( 114, -174), S( 167,  -70), S(  41,   34), S( -16,   24) },
   { S(   2, -289), S(  70,  176), S( 152,    5), S( 154, -113), S( -17, -264) },
   { S( -40, -220), S( -57, -176), S( -68,  141), S( 183,   70), S( -62,   63) },
   { S( 180, -220), S( 151,   89), S(  13,  119), S( 427,   94), S(  55, -144) },
   { S(  78,  103), S(  60,  104), S(  -6,  139), S(-107,   71), S( 281,  -41) },
  },
  { // Advisor
   { S(-143,  355), S(-218,   12), S(  96,  102), S( -14, -137), S(-142,  -16) },
   { S(   3,   29), S( -58,   -6), S(  44,  148), S(  33,  -20), S( 314,  232) },
   { S(  28,   68), S(  50,  -22), S( -28, -131), S(  76,  100), S( 110,   40) },
   { S( 116,  -94), S(-177, -153), S(   6,   17), S(  65,  -91), S( -29,  -39) },
   { S( -74, -131), S(  70,  -31), S(  65,   81), S( -55,   25), S( -32, -137) },
   { S( 139,  253), S( -72, -129), S(-175, -124), S(  94,  130), S(-126,   81) },
   { S(-127,  167), S(  42,  243), S( -24,   53), S( 246,   46), S(  89,   44) },
   { S( -59,  -18), S(  81,   16), S( -25,  -28), S( -16, -128), S( 133,    8) },
   { S( -78,  149), S(  96,  -29), S( -52,   57), S(  26,  201), S(-303,  105) },
   { S( -48,  141), S( 146,  -16), S(-251,   29), S( -35,  -71), S(-157,  113) },
  },
  { // Cannon
   { S( -98, -124), S( -86,  -85), S(  15,  168), S( 107,  -55), S(  64,   45) },
   { S( -13,    6), S(  15, -105), S( 133,  -56), S(  67,   42), S( -23,   40) },
   { S(  81,    6), S(  62,  -26), S( 158,  249), S( 136,  158), S( -89,  165) },
   { S(  61,   -6), S( -44,  -11), S(  27,  -11), S( -37,   76), S( 265,  -61) },
   { S(  84,  -88), S(  31,    8), S(  47, -112), S( 150,  -47), S( -62,  157) },
   { S(  88,  -45), S(-131,   30), S( -53,   51), S( -11,   30), S(  46,   93) },
   { S(  -3,  -45), S( -41,  238), S( -52,    7), S( 111,   77), S(  47,  207) },
   { S(  39,   93), S(-114, -148), S( -48,  104), S( -84, -108), S( 177,  139) },
   { S(  72,   12), S(  16,    7), S( 150,  -16), S(  43,   96), S(  66,   40) },
   { S( -40,    9), S(  32,  -43), S( -69,  -49), S( -94,  -10), S( -87, -167) },
  },
  { // Pawn
   { NEVER_IN_USE , NEVER_IN_USE , NEVER_IN_USE , NEVER_IN_USE , NEVER_IN_USE  },
   { NEVER_IN_USE , NEVER_IN_USE , NEVER_IN_USE , NEVER_IN_USE , NEVER_IN_USE  },
   { NEVER_IN_USE , NEVER_IN_USE , NEVER_IN_USE , NEVER_IN_USE , NEVER_IN_USE  },
   { S(  19,   57), NEVER_IN_USE , S(-107,  -49), NEVER_IN_USE , S( 104,  109) },
   { S( -22,   65), NEVER_IN_USE , S(  -9,  107), NEVER_IN_USE , S(  83,   -1) },
   { S( 137,  -90), S( 178,   -3), S( 275,   81), S( 242,  -70), S( 213,   87) },
   { S( -91,   35), S( -37,  -46), S(  40,   52), S( 185, -121), S(  -1,  -18) },
   { S( 159,   71), S( -97,  -15), S( -21,  -35), S( 141,   -3), S( 118,   18) },
   { S( 122, -100), S(  -4,  186), S( 131,   11), S(  71,   78), S(   2, -138) },
   { S(   6,   18), S(  73,    7), S( 114,    2), S( -18,   -5), S(  35,   -7) },
  },
  { // Knight
   { S( -97,   40), S(-358,  -44), S(  15,   14), S(-139, -245), S( -71,  -60) },
   { S(-141,  -46), S( -56,  -90), S( -77,  111), S( -45, -140), S(  74,  141) },
   { S( -89,    1), S( -34,  -50), S( -21,  -48), S(  72,   34), S(  18,   -9) },
   { S( -94,  -58), S( -54, -171), S( -13,   80), S(-150,  -97), S( 161,  -65) },
   { S(-125,  -26), S(   3,  -91), S(  92,  136), S( 103,   -4), S(-146,  -89) },
   { S(  98,  153), S( -65,  -80), S(-106, -233), S(  72,  103), S( -59,   29) },
   { S(-197,   62), S(  10,  113), S(   0,  134), S( 317,   87), S(  11,   55) },
   { S(  21,  -47), S( -14,   13), S( 170,   83), S( -72,  -57), S( 165,  -37) },
   { S(-121,   41), S( -45,  -70), S( -82,   46), S( -36,  131), S(-224,  104) },
   { S(-100,  -55), S( 152,   37), S( -60,   89), S(-155,  -31), S( -91,   79) },
  },
  { // Bishop
   { NEVER_IN_USE , NEVER_IN_USE , S(  35,   56), NEVER_IN_USE , NEVER_IN_USE  },
   { NEVER_IN_USE , NEVER_IN_USE , NEVER_IN_USE , NEVER_IN_USE , NEVER_IN_USE  },
   { S( -51,   40), NEVER_IN_USE , NEVER_IN_USE , NEVER_IN_USE , S(  54,   45) },
   { NEVER_IN_USE , NEVER_IN_USE , NEVER_IN_USE , NEVER_IN_USE , NEVER_IN_USE  },
   { NEVER_IN_USE , NEVER_IN_USE , S(-104,    8), NEVER_IN_USE , NEVER_IN_USE  }
  },
  { // King
   { NEVER_IN_USE , NEVER_IN_USE , NEVER_IN_USE , S( -72,  -77), S( 245,   97) },
   { NEVER_IN_USE , NEVER_IN_USE , NEVER_IN_USE , S( -41,   59), S(  66,  138) },
   { NEVER_IN_USE , NEVER_IN_USE , NEVER_IN_USE , S(-203,   -3), S( -27,   51) }
  }
};

} // namespace


namespace PSQT
{

Score psq[PIECE_NB][SQUARE_NB];

// PSQT::init() initializes piece-square tables: the white halves of the tables are
// copied from Bonus[], adding the piece value, then the black halves of the tables
// are initialized by flipping and changing the sign of the white scores.
void init() {

  for (Piece pc : {W_ROOK, W_ADVISOR, W_CANNON, W_PAWN, W_KNIGHT, W_BISHOP, W_KING})
  {
    Score score = make_score(PieceValue[MG][pc], PieceValue[EG][pc]);

    for (Square s = SQ_A0; s <= SQ_I9; ++s)
    {
      File f = File(edge_distance(file_of(s)));
      psq[ pc][s] = score + Bonus[pc][rank_of(s)][f];
      psq[~pc][flip_rank(s)] = -psq[ pc][s];
    }
  }
}

} // namespace PSQT

} // namespace Stockfish
