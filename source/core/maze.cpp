#include "maze.h"

Maze::Maze( const vector< vector<int> > & input_matrix )
    : m_maze{input_matrix}{
}

void Maze::print() const{
}

bool Maze::is_blocked( const Position& pos, const direction_t & dir ) const{
}

bool Maze::is_outside( const Position & pos ) const{
}

Position Maze::walk_to( const Position & pos, const direction_t & dir ) const{
}
