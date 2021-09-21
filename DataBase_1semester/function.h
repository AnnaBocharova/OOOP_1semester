#pragma once


#include <stdbool.h>
#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>

struct Categories {
    int id;
    char name[20];

    int addressNextDish;
    int countDishes;
    bool isExist;
};

struct IndexCategories {
    int id;
    int address;
    bool isExist=true;
};

struct Dish {
    int id;
    char name[20];
    int weight;
    int price;
    int idCategories;

    int addressNextDish;
    bool isExist;
};

struct Inform {
    int idInsertedCategories;
    int idInsertedDishes;

    int countOfExistingCategories;
    int countOfExistingDishes;
};




void Command();

struct Inform collectInformation();
void updateInformFile(const struct Inform inform);
void DefaultInform();
void outputInformFromFile();
void checkInformFile();

struct Categories createNewCategory(const struct Inform inform);
void printCategory(const struct Categories category);
struct Categories* getArrayOfCategories(struct Inform inform);
void updateFileOfCategories(struct Inform inform, struct Categories* arrayOfTrucks);
struct Categories getCategoryById(struct Inform inform);

struct IndexCategories createNewIndexCategories(struct Categories category, const struct Inform inform);
void outputTheIndexCategories(const struct IndexCategories indexCategory);
struct IndexCategories* getArrayOfIndexCategories(const struct Inform inform);
void updateFileIndex(struct Inform inform, struct IndexCategories* arrayOfIndexTrucks);

struct Dish createNewDish(const struct Inform inform);
void outputTheDish(const struct Dish dish);
struct Dish* getArrayOfDish(const struct Inform inform);
void updateDishFile(struct Inform inform, struct Dish* arrayOfProducts);
struct Dish* getArrayOfSlavesDish(struct Categories category);
void deleteLastOneProduct(struct Inform inform, struct Categories category);
void deleteLastProduct(struct Inform inform, struct Categories category);

void insert_m();
void insert_s();
void del_m();
void del_s();
struct Categories get_m();
struct Dish get_s();
void update_m();
void update_s();
void ut_m();
void ut_s();

void clearAllFiles();
void outputCategoriesIndex();
void outputDishesFile();
int binarySearchIndex(int left, int right, int neededIndex, struct IndexCategories* arrayOfIndexTrucks);
int chooseIndexOfIdCategories(struct Inform Inform);
