#include "maze.h"

#include <iostream>

Maze::Maze( const vector< vector<int> > & input_matrix )
    : m_maze{input_matrix}{
}

void Maze::print() const{
    for (auto i{0}; i < m_maze.size(); ++i) {
        for (auto j{0}; j < m_maze[0].size(); ++j) {
            std::cout << m_maze[i][j];
        }

        std::cout << '\n';
    }
}

bool Maze::is_blocked( const Position& pos, const direction_t & dir ) const{
    Position new_pos = walk_to(pos, dir);

    return m_maze[new_pos.row][new_pos.col] == cell_type::WALL;
}

bool Maze::is_outside( const Position & pos ) const{
    auto n_lines = m_maze.size();
    auto n_cols = m_maze[0].size();

    return (pos.row < 0 or pos.row >= n_lines or pos.col < 0 or pos.col >= n_cols);
}

Position Maze::walk_to( const Position & pos, const direction_t & dir ) const{
    Position new_pos;

    switch (dir) {
        case UP:
            new_pos.row = pos.row + 1;
            new_pos.col = pos.col;
        case DOWN:
            new_pos.row = pos.row - 1;
            new_pos.col = pos.col;
        case LEFT:
            new_pos.row = pos.row;
            new_pos.col = pos.col - 1;
        case RIGHT:
            new_pos.row = pos.row;
            new_pos.col = pos.col + 1;
    }

    return new_pos;
}
