#include<iostream>
#include "date.h"
#include "matrix.h"
#include "graph.h"

#include <iostream>
#include "graph.h"
#include "date.h"





void menu_graph() {

    Graph<Date> graph;
    Date edgeWeight{};
    bool flag = true;
    int choose;

    while (flag) {
        std::cout << "Choose commands: " << std::endl;
        std::cout << "[1] - add vertex" << std::endl
            << "[2] - add edge" << std::endl
            << "[3] - delete vertex" << std::endl
            << "[4] - delete edge" << std::endl
            << "[5] - output graph" << std::endl
            << "[6] - MST_Kruskala" << std::endl
            << "[0] - exit" << std::endl;;
        std::cin >> choose;
        switch (choose) {
        case 1:
            graph.addVertex();
            break;
        case 2:
            int first_vertex, second_vertex;
            std::cout << "Enter [firstVertex]/[secondVertex]\n";
            graph.chooseVertex();
            std::cin >> first_vertex >> second_vertex >> edgeWeight;
            graph.addEdge(first_vertex, second_vertex, edgeWeight);
            break;
        case 3:
            int indexVertex;
            std::cout << "Enter [indexVertex]\n";
            graph.chooseVertex();
            std::cin >> indexVertex;
            graph.deletedVertex(indexVertex);
            break;
        case 4:
            std::cout << "Enter [firstVertex]/[secondVertex]\n";
            graph.chooseVertex();
            std::cin >> first_vertex >> second_vertex;
            graph.deletedEdge(first_vertex, second_vertex);
            break;
        case 5:
            std::cout << graph;
            break;
        case 6:
            graph.MST_Kruskala();
            break;
        case 0:
            flag = false;
            break;
        default:
            std::cout << "Wrong case\n";
        }
        
    }
    

  }



int choose_matrix() {
    std::cout << "what matrix do you want to output?" << std::endl
        << "[1]- A" << std::endl
        << "[2]- B" << std::endl;
    int choose_matrix;
    std::cin >> choose_matrix;
    return choose_matrix;
}

void menu_matrix() {
    bool flag = true;
    int choose;
    fill_file("matrixA.dat");
    fill_file("matrixB.dat");


    Matrix<int> horizontal_A[order], horizontal_B[order];

    create_matrix(horizontal_A, "matrixA.dat");
    create_matrix(horizontal_B, "matrixB.dat");

    while (flag) {
        std::cout << "Choose commands: " << std::endl;
        std::cout << "[1] - print matrix" << std::endl
            << "[2] - sum matrix" << std::endl
            << "[3] - matrix mulriplication" << std::endl
            << "[4] - transponse matrix" << std::endl
            << "[5] - mulriplication matrix by vector" << std::endl
            << "[6] - search by indexes" << std::endl
            << "[7] - search by value" << std::endl
            << "[8] - search all elements by value" << std::endl
            << "[0] - exit" << std::endl;;
        std::cin >> choose;
        int ring = 0;
        switch (choose) {
        case 1:
            ring = choose_matrix();
            if (ring == 1)
                print_matrix(horizontal_A);
            if (ring == 2)
                print_matrix(horizontal_B);
            break;
        case 2:
            main_sum_matrix(horizontal_A, horizontal_B);
            break;
        case 3:
            main_multiplication(horizontal_A, horizontal_B);
            break;
        case 4:
            ring = choose_matrix();
            if (ring == 1)
                main_transponse(horizontal_A);
            if (ring == 2)
                main_transponse(horizontal_B);
            break;
        case 5:
            ring = choose_matrix();
            if (ring == 1)
                main_multiplication_by_vector(horizontal_A);
            if (ring == 2)
                main_multiplication_by_vector(horizontal_B);
            break;
        case 6:
            ring = choose_matrix();
            if (ring == 1)
                main_search_by_index(horizontal_A);
            if (ring == 2)
                main_search_by_index(horizontal_B);
            break;
        case 7:
            ring = choose_matrix();
            if (ring == 1)
                main_search_by_value(horizontal_A);
            if (ring == 2)
                main_search_by_value(horizontal_B);
            break;
        case 8:
            ring = choose_matrix();
            if (ring == 1)
                main_all_search_by_value(horizontal_A);
            if (ring == 2)
                main_all_search_by_value(horizontal_B);
            break;
        case 0:
            flag = false;
            break;
        default:
            std::cout << "Wrong case\n";
        }

    }
}

int main() {
    menu_graph();
    menu_matrix();
    return 0;
}