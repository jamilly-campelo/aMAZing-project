#include <iostream>
#include <vector>
#include <fstream>

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


/*!
 * Acha um caminho da entrada até a saída, marcando as células que compõem
 * a solução no objeto maze.
 *
 * @param m O labirinto que queremos solucionar.
 * @param start O ponto (coordenada) de partida do caminho.
 * @param end O ponto (coordenada) de saída do labirinto.
 * @return `true` se existe uma solução; `false` caso contrário.
 */
bool solve_maze( Maze& m, const Position& start, const Position& end )
{
    // TODO

    return false;
}

/// Reads a maze from the input file and returns a matrix of integers representing the input maze.
/*!
 * @param file_name The input file name.
 * @param matrix A bi-dimensional matrix that stores the input data as integers.
 * @return A status code indicating the reading was ok, or the error code, otherwise.
 */
int read_file( std::string file_name, vector<vector<int>> &matrix ){
    // TODO:
    // The input file strem.
    std::ifstream ifs { file_name }; // Creating and Opening the stream.

    return READ_OK;
}

int main( int argc, char *argv[] ){
    if ( argc != 2 ) {
        std::cout << ">>> Missing input file!\n"
                  << "    Sintax: maze [inpu_file_name]\n\n";
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
        std::cout << ">>> Input file successfuly read!\n";
    }
    else std::cerr << ">>> Undefined error code received!\n";

    // Cria o objeto labirinto.
    Maze maze( input_matrix );
    // Exibe o labirinto ainda sem solução.
    std::cout << ">>> Input maze is: \n";
    maze.print();
    std::cout << "    Entry is located at " << maze.entry()
              << ", and Exit is located at " << maze.exit() << std::endl << std::endl;

    std::cout << ">>> Finding a solution, please wait...\n";
    if ( solve_maze( maze, maze.entry(), maze.exit() ) )
    {
        std::cout << "  The `█` represents a wall\n"
                  << "  The ` ` represents a free cell\n"
                  << "  The `x` represents the maze's entry point\n"
                  << "  The `•` represents the path to the exit\n"
                  << "  The `e` represents the maze's exit.\n\n";
        maze.print(); // Exibe a solução.
    }
    else std::cout << ">>> Sorry, this maze does not have a solution.!!\n";

    return 0;
}
