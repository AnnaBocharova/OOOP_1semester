#pragma once

#include "../lab1/date.h"
#include "../lab1/graph.h"
#include "../lab1/matrix.h"
#include "doctest.h"

TEST_CASE("DATE") {
    Date first_date{ 1, 1, 1,1,1,1 };
    Records record{};
    record.sec = 50;

    SUBCASE("Operator +=, -=") {
        CHECK(first_date.countSecForData() == 90061);
        first_date += record;
        CHECK(first_date.countSecForData() == 90111);
        first_date -= record;
        CHECK(first_date.countSecForData() == 90061);
    }

    Date second_date{};
    second_date.createNewDataBySec(90061);

    SUBCASE("Create date by sec") {
        CHECK(first_date == second_date);
    }

    first_date += record;
    SUBCASE("Operator -") {
        record = first_date - second_date;
        CHECK(record.sec == 50);
    }

    SUBCASE("Operator <, >") {
        CHECK((first_date > second_date) == 0);
        CHECK((first_date < second_date) == 0);
        first_date += record;
        CHECK((first_date > second_date) == 1);
        CHECK((first_date < second_date) == 0);
    }

   

};
TEST_CASE("GRAPH") {
    Graph<int> graph;

    SUBCASE("Empty") {
        CHECK(graph.getEdges() == 0);
        CHECK(graph.getVertex() == 0);
    }

    graph.addVertex();
    SUBCASE("Vertexes") {

        CHECK(graph.getVertex() == 1);
        graph.addVertex();

        CHECK(graph.getVertex() == 2);

        graph.deletedVertex(0);
        CHECK(graph.getVertex() == 1);
    }

    SUBCASE("Edges") {
        graph.addEdge(0, 1, 10);
        CHECK(graph.getEdges() == 1);
        graph.deletedEdge(0, 1);
        CHECK(graph.getEdges() == 0);

             
    }
       
     
};

