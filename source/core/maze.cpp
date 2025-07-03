#include "maze.h"

#include <iostream>

Maze::Maze( const vector< vector<int> > & input_matrix )
    : m_maze{input_matrix}{

    // Find the entry and exit cells.
    for (auto i{0}; i < m_maze.size(); ++i) {
        for (auto j{0}; j < m_maze[0].size(); ++j) {
            if (m_maze[i][j] == cell_type::ENTRY) {
                m_entry.row = i;
                m_entry.col = j;
            } else if (m_maze[i][j] == cell_type::EXIT) {
                m_exit.row = i;
                m_exit.col = j;
            }
        }
    }
}

void Maze::print() const{
    for (auto i{0}; i < m_maze.size(); ++i) {
        for (auto j{0}; j < m_maze[0].size(); ++j) {
            std::wcout << cell_2_symbol.at(static_cast<cell_type>(m_maze[i][j]));
        }

        std::wcout << L'\n';
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
    Position new_pos = pos;

    switch (dir) {
        case UP:
            new_pos.row = pos.row - 1;
            break;
        case DOWN:
            new_pos.row = pos.row + 1;
            break;
        case LEFT:
            new_pos.col = pos.col - 1;
            break;
        case RIGHT:
            new_pos.col = pos.col + 1;
            break;
    }

    return new_pos;
}
