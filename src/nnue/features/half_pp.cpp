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

// Definition of input features HalfPP of NNUE evaluation function

#include "half_pp.h"

#include "../../position.h"

namespace Stockfish::Eval::NNUE::Features {

  // Index of a feature for a given king position and another piece on some square
  template<Color Perspective>
  inline IndexType HalfPP::make_index(Square s1, Piece p1, Square s2, Piece p2) {
    s1 = Square( Perspective == BLACK ? Rotate[s1] : s1);
    s2 = Square( Perspective == BLACK ? Rotate[s2] : s2);
    return IndexType((s1 + PieceSquareIndex[Perspective][p1]) * PS_NB + s2 + PieceSquareIndex[Perspective][p2]);
  }

  // Get a list of indices for active features
  template<Color Perspective>
  void HalfPP::append_active_indices(
    const Position& pos,
    IndexList& active
  ) {
    Bitboard b = pos.pieces();
    while (b)
    {
      Square s1 = pop_lsb(b);
      Piece p1 = pos.piece_on(s1);
      Bitboard bb = pos.pieces();
      while (bb) {
        Square s2 = pop_lsb(bb);
        Piece p2 = pos.piece_on(s2);
        active.push_back(make_index<Perspective>(s1, p1, s2, p2));
      }
    }
  }

  // Explicit template instantiations
  template void HalfPP::append_active_indices<WHITE>(const Position& pos, IndexList& active);
  template void HalfPP::append_active_indices<BLACK>(const Position& pos, IndexList& active);

  // append_changed_indices() : get a list of indices for recently changed features
  template<Color Perspective>
  void HalfPP::append_changed_indices(
    const Position& pos,
    IndexList& removed,
    IndexList& added
  ) {
    auto &dp = pos.state()->dirtyPiece;
    Bitboard bb = pos.pieces();
    while (bb) {
        Square s = pop_lsb(bb);
        Piece p = pos.piece_on(s);
        for (int i = 0; i < dp.dirty_num; ++i) {
            if (dp.from[i] != SQ_NONE) {
                removed.push_back(make_index<Perspective>(dp.from[i], dp.piece[i], s, p));
                removed.push_back(make_index<Perspective>(s, p, dp.from[i], dp.piece[i]));
            }
            if (dp.to[i] != SQ_NONE) {
                added.push_back(make_index<Perspective>(dp.to[i], dp.piece[i], s, p));
                added.push_back(make_index<Perspective>(s, p, dp.to[i], dp.piece[i]));
            }
        }
    }
  }

  // Explicit template instantiations
  template void HalfPP::append_changed_indices<WHITE>(const Position& pos, IndexList& removed, IndexList& added);
  template void HalfPP::append_changed_indices<BLACK>(const Position& pos, IndexList& removed, IndexList& added);

}  // namespace Stockfish::Eval::NNUE::Features
