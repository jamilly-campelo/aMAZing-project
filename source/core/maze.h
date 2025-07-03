#ifndef MAZE_H
#define MAZE_H

#include <algorithm>
#include <cstdint>
#include <iostream>
#include <unordered_map>
#include <vector>

using std::vector;

/// Represents a location within the maze, as a coordinate pair (row,col).
struct Position {
  int row, col; //!< public members.
  /// Constructor.
  Position(int r = 0, int c = 0) : row{r}, col{c} { /* empty */ }
};

/// Basic comparison of locations.
inline bool operator==(const Position &p1, const Position &p2) {
  return p1.row == p2.row and p1.col == p2.col;
}

/// Possible directions from a cell.
enum direction_t : std::uint8_t { UP, DOWN, LEFT, RIGHT };

/*!
 * Represents a (prefect) maze.
 *
 * Internally a maze is represented as a 2D matrix of numbers
 * corresponding to `cells`.
 *
 * A cell might be either be empty, a wall, an empty cell that
 * is part of the solution, the entry point, or the exit point.
 *
 * This class also provides methods to read information from the maze,
 * and methods to mark empty cells as part of the path (solution of)
 * inside the maze.
 */
class Maze {

private:
  vector<vector<int>> m_maze; //!< The maze stored a 2D matrix.
  Position m_entry;           //!< Location of the entry cell.
  Position m_exit;            //!< Location of the exit cell.

public:
  /// Types of cell inside the maze.
  enum cell_type : std::uint8_t {
    FREE = 0, //!< A free empty cell.
    WALL,     //!< A wall inside the maze.
    INV_WALL, //!< An invisible wall, to support irregular shape mazes.
    ENTRY,    //!< A cell marking the maze's entry point.
    EXIT,     //!< A cell marking the maze's exit point.
    PATH //!< A cell that has been marked as part of the path that leads from
         //!< the maze's entry point to the maze's exit point.
  };
  
  /// A map that associates each cell type with a character symbol.
  const std::unordered_map<cell_type, wchar_t> cell_2_symbol = {
      {FREE, L' '},       //!< Free cell.
      {WALL, L'█'},       //!< Wall cell.
      {INV_WALL, L'.'},   //!< Invisible wall cell.
      {ENTRY, L'x'},      //!< Entry cell.
      {EXIT, L'e'},       //!< Exit cell.
      {PATH, L'•'}        //!< Path cell.
  };

  /// Basic constructor. Receives a matrix corresponding to the maze.
  Maze(const vector<vector<int>> &);

  /// Return the location (coordinate) of the maze's entry cell.
  [[nodiscard]] Position entry() const { return m_entry; }

  /// Return the location (coordinate) of the maze's exit cell.
  [[nodiscard]] Position exit() const { return m_exit; }

  /// Return `true` if the neighbor cell towards the requested direction is a
  /// wall; returns `false` otherwise.
  /*!
   * @param pos The position we are coming from.
   * @param dir The direction we want to go to.
   * @return `true` if the cell towards the requested direction is a wall,
   * `false` otherwise.
   */
  bool is_blocked(const Position &pos, const direction_t &dir) const;

  /// Marks a cell as part of the path that leads to the exit (solution).
  inline void mark_cell(const Position &pos) {
    // We only mark the cell if this is a free cell.
    // It does not change the entry, which is also part of the path.
    if (m_maze[pos.row][pos.col] == cell_type::FREE)
      m_maze[pos.row][pos.col] = cell_type::PATH;
  }

  /// UNmarks a cell as part of the path that leads to the exit (solution).
  inline void unmark_cell(const Position &pos) {
    // We only UNmark the cell if this is a PATH cell.
    // It does not change the entry, which is also part of the path.
    if (m_maze[pos.row][pos.col] == cell_type::PATH)
      m_maze[pos.row][pos.col] = cell_type::FREE;
  }

  /// Checks whether a cell is marked as part of the path that leads to the exit
  /// (solution).
  inline bool is_marked(const Position &pos) const {
    return (m_maze[pos.row][pos.col] == cell_type::PATH);
  }

  /// Returns the position of the neighbor cell based on the provided direction.
  Position walk_to(const Position &, const direction_t &) const;

  /// Checks whether a cell is outside the maze or not.
  bool is_outside(const Position &) const;

  /// Prints a maze representation on the standard output.
  void print(void) const;
};

#endif
