#include <cstddef>
#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <locale>
#include <list>

#include "maze.h"

/// Possible outcomes from the read_file()
#define ERR_FAILED_OPENING_INPUT_FILE 0
#define ERR_MISSING_ENTRY_EXIT 1
#define READ_OK 2

using std::vector;

/// Print out a Position
std::ostream& operator<<( std::ostream& os, const Position & p )
{
    os << "(" << p.row << "," << p.col << ")";
    return os;
}

std::wostream& operator<<( std::wostream& wos, const Position & p )
{
    wos << L"(" << p.row << L"," << p.col << L")";
    return wos;
}

/*!
 * Acha um caminho da entrada até a saída, marcando as células que compõem
 * a solução no objeto maze.
 *
 * @param m O labirinto que queremos solucionar.
 * @param start O ponto (coordenada) de partida do caminho.
 * @param end O ponto (coordenada) de saída do labirinto.
 * @return `true` se existe uma solução; `false` caso contrário.
 */
bool solve_maze( Maze& m, const Position& start, const Position& end, std::list<direction_t> &solution )
{
    std::wcout << L"Entrei na solve_maze\n";
    if (start == end) {
        m.mark_cell(start); // Mark the entry as part of the path.
        std::wcout << start << L'\n';
        return true; // We are already at the exit.
    }

    if (m.is_marked(start)) return false; // We have already visited this cell.
    
    m.mark_cell(start); // Mark the current cell as part of the path.
    m.print();

    std::wcout << start << L'\n';

    for (const auto &dir : {UP, DOWN, LEFT, RIGHT}) {
        Position next = m.walk_to(start, dir);

        if (m.is_outside(next) or m.is_blocked(start, dir)) continue; // Skip if outside or blocked.

        m.mark_cell(next); // Mark the current cell as part of the path.
        m.print();
        
        std::wcout << L"NEXT: " << next << L'\n';

        if (solve_maze(m, next, end, solution)) {
            solution.push_back(dir); // Add the direction to the solution.
            return true; // Found a path to the exit.
        }

        m.unmark_cell(next); // Unmark if no path was found.
    }

    m.unmark_cell(start);
    return false;
}

/// Reads a maze from the input file and returns a matrix of integers representing the input maze.
/*!
 * @param file_name The input file name.
 * @param matrix A bi-dimensional matrix that stores the input data as integers.
 * @return A status code indicating the reading was ok, or the error code, otherwise.
 */
int read_file( std::string file_name, vector<vector<int>> &matrix ){
    // The input file stream.
    std::ifstream ifs { file_name }; // Creating and opening the stream.

    if (not ifs.is_open()) {
        return ERR_FAILED_OPENING_INPUT_FILE;
    }

    std::string line;

    bool has_entry = false, has_exit = false;

    while (std::getline(ifs, line)) {
        std::vector<int> row;
        for (char c : line) {
            if (c == 'm') {
                row.push_back(Maze::cell_type::ENTRY);
                has_entry = true;
            } else if (c == 'e') {
                row.push_back(Maze::cell_type::EXIT);
                has_exit = true;
            } else if (c == '1') {
                row.push_back(Maze::cell_type::WALL);
            } else if (c == ' ' or c == '0') {
                // '0' is used to represent a free cell in some mazes.
                // ' ' is used to represent a free cell in others.
                // We treat both as free cells.
                row.push_back(Maze::cell_type::FREE);
            } else if (c == '.') {
                row.push_back(Maze::cell_type::INV_WALL);
            } else {
                return ERR_FAILED_OPENING_INPUT_FILE;
            }
        }

        matrix.push_back(row);
    }

    ifs.close(); // Close the file stream.

    if (not has_entry or not has_exit) {
        std::cerr << "Error: the maze must contain an entry ('m') and an exit ('e').\n";
        return ERR_MISSING_ENTRY_EXIT;
    }

    return READ_OK;
}

int main( int argc, char *argv[] ){
    std::locale::global(std::locale("pt_BR.UTF-8"));
    std::wcout.imbue(std::locale());

    std::wcout << L"Teste de bloco: █ e ponto: •\n";

    if ( argc != 2 ) {
        std::wcout << L">>> Missing input file!\n"
                  << L"    Sintax: maze [input_file_name]\n\n";
        return 1;
    }

    // Recebe uma matriz de inteiros representando um labirinto.
    vector<vector<int>> input_matrix;
    auto result = read_file( argv[1], input_matrix );
    if ( result == ERR_FAILED_OPENING_INPUT_FILE ) {
        std::cerr << "--> Fail while attempting to open the input maze file [" << argv[1] << "]!\n";
        return 1;
    }
    else if ( result == ERR_MISSING_ENTRY_EXIT ) {
        std::cerr << "--> Maze does not have entry and/or exit cell marked.\n"
                  << "    Please use `m` for the maze's entry, and `e` for the maze's exit.\n\n";
        return 1;
    }
    else if ( result == READ_OK ) {
        std::wcout << L">>> Input file successfuly read!\n";
    }
    else std::cerr << ">>> Undefined error code received!\n";

    // Cria o objeto labirinto.
    Maze maze( input_matrix );
    // Exibe o labirinto ainda sem solução.
    std::wcout << L">>> Input maze is: \n";
    maze.print();
    std::wcout << L"\nEntry is located at " << maze.entry()
              << L", and Exit is located at " << maze.exit() << std::endl << std::endl;

    std::wcout << L">>> Finding a solution, please wait...\n";

    std::list<direction_t> solution; // Lista que armazena a solução do labirinto.
    if ( solve_maze( maze, maze.entry(), maze.exit(), solution ) )
    {
        std::wcout << L"  The `█` represents a wall\n"
                   << L"  The ` ` represents a free cell\n"
                   << L"  The `x` represents the maze's entry point\n"
                   << L"  The `•` represents the path to the exit\n"
                   << L"  The `e` represents the maze's exit.\n\n";
        maze.print(); // Exibe a solução.
    }
    else std::wcout << L">>> Sorry, this maze does not have a solution.!!\n";

    return 0;
}
