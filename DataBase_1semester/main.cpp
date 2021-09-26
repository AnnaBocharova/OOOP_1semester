#define _CRT_SECURE_NO_WARNINGS
#include "function.h"

void Command() {
    printf("\nChoose the number of a command: \n");
    printf("[1] - insert-m\n");
    printf("[2] - insert-s\n");
    printf("[3] - get-m\n");
    printf("[4] - get-s\n");
    printf("[5] - update-m\n");
    printf("[6] - update-s\n");
    printf("[7] - del-m\n");
    printf("[8] - del-s\n");
    printf("[9] - ut-m\n");
    printf("[10] - ut-s\n");
    printf("[11] - all information\n");
    printf("[12] - clear all files\n");
    printf("\n[0] - exit\n");
}

//________________________________SECONDARY FUNCTION_________________________________//
void clearAllFiles() {
    FILE* categoryIndex = fopen("categories.ind", "w");
    fclose(categoryIndex);

    FILE* categoryFile = fopen("categories.fl", "w");
    fclose(categoryFile);

    FILE* dishesFile = fopen("dishes.fl", "w");
    fclose(dishesFile);

    FILE* inform = fopen("inform.dat", "w+b");
    struct Inform info;
    info.idInsertedCategories = info.countOfExistingCategories = info.countOfExistingDishes = info.idInsertedDishes = 0;
    fwrite(&info, sizeof(struct Inform), 1, inform);
    fclose(inform);
}

void outputCategoriesIndex() {
    struct Inform inform;
    struct IndexCategories currentIndexCategory;
    inform = collectInformation();

    FILE* categoryIndex = fopen("categories.ind", "r+b");
    printf("Index categories:");
    for (int i = 0; i < inform.idInsertedCategories; i++) {
        fread(&currentIndexCategory, sizeof(struct IndexCategories), 1, categoryIndex);
        if (currentIndexCategory.isExist) {
            printf("\n[%d] - ", i);
            outputTheIndexCategories(currentIndexCategory);
        }
    }
    printf("\n");
    fclose(categoryIndex);
}

void outputDishesFile() {
    struct Inform inform;
    inform = collectInformation();
    struct Dish currentDish;

    printf("All dishes:\n");
    FILE* dishFile = fopen("dishes.fl", "r+b");
    for (int i = 0; i < inform.idInsertedDishes; i++) {
        fread(&currentDish, sizeof(struct Dish), 1, dishFile);
        outputTheDish(currentDish);
    }

    fclose(dishFile);
}

int chooseIndexOfIdCategories(struct Inform inform) {
    struct IndexCategories* arrayOfIndexCategories = getArrayOfIndexCategories(inform);

    int index;
    outputCategoriesIndex();
    printf("Choose index of category:\n");
    scanf("%d", &index);
    while (index < 0 || index > inform.idInsertedCategories - 1 || !arrayOfIndexCategories[index].isExist) {
        printf("Wrong id! Please, try again\n");
        outputCategoriesIndex();
        scanf("%d", &index);
    }
    return index;
}



//________________________________________CATEGORIES___________________________________//

struct Categories createNewCategory(const struct Inform inform) {
    struct Categories newCategory;

    printf("Enter name of the category:\n");
    scanf("%19s", newCategory.name);
   
    newCategory.id = inform.idInsertedCategories;
    newCategory.addressNextDish = -1;
    newCategory.countDishes = 0;
    newCategory.isExist = true;

    return newCategory;
}


void printCategory(const struct Categories category) {
    printf("\nCategory Id = %d", category.id);
    printf("\nCategory name = %s", category.name);
    printf("\nAddress next dish = %d", category.addressNextDish);
    printf("\nCount of dish = %d", category.countDishes);
    printf("\nIs exist? = %d\n", category.isExist);
}


struct Categories* getArrayOfCategories(struct Inform inform) {
    struct Categories* arrayOfCategories;
    struct Categories currentCategory;
    arrayOfCategories = (struct Categories*)malloc(inform.idInsertedCategories * sizeof(struct Categories));
    FILE* categoryFile = fopen("categories.fl", "r+b");
    for (int i = 0; i < inform.idInsertedCategories; i++) {
        fread(&currentCategory, sizeof(struct Categories), 1, categoryFile);
        arrayOfCategories[i] = currentCategory;
    }
    fclose(categoryFile);

    return arrayOfCategories;
}


void updateFileOfCategories(struct Inform inform, struct Categories* arrayOfCategories) {
    FILE* categoriesFile = fopen("categories.fl", "w+b");
    for (int i = 0; i < inform.idInsertedCategories; i++)
        fwrite(&arrayOfCategories[i], sizeof(struct Categories), 1, categoriesFile);
    fclose(categoriesFile);
}


//___________________________________INDEX FILE_________________________________________//
struct IndexCategories createNewIndexCategories(struct Categories category, const struct Inform inform) {
    struct IndexCategories newIndexCategory;

    newIndexCategory.id = category.id;
    newIndexCategory.address = inform.idInsertedCategories * (sizeof(struct Categories));
    newIndexCategory.isExist = true;

    return newIndexCategory;
}


void outputTheIndexCategories(const struct IndexCategories indexCategory) {
    printf("id = %d, address = %d, isExist = %d", indexCategory.id, indexCategory.address, indexCategory.isExist);
}


struct IndexCategories* getArrayOfIndexCategories(struct Inform inform) {
    struct IndexCategories* arrayOfIndexCategories;
    struct IndexCategories currentIndexCategory;
    arrayOfIndexCategories = (struct IndexCategories*)malloc(inform.idInsertedCategories * sizeof(struct IndexCategories));
    FILE* categoriesIndex = fopen("categories.ind", "r+b");
    for (int i = 0; i < inform.idInsertedCategories; i++) {
        fread(&currentIndexCategory, sizeof(struct IndexCategories), 1, categoriesIndex);
        arrayOfIndexCategories[i] = currentIndexCategory;
    }
    fclose(categoriesIndex);

    return arrayOfIndexCategories;
}


struct Categories getCategoryById(struct Inform inform) {
    struct IndexCategories* arrayOfIndexCategories = getArrayOfIndexCategories(inform);
    int index = chooseIndexOfIdCategories(inform);
    struct IndexCategories indexCategory = arrayOfIndexCategories[index];

    FILE* categoriesFile = fopen("categories.fl", "r+b");
    struct Categories category;
    fseek(categoriesFile, indexCategory.address, 0);
    fread(&category, sizeof(struct Categories), 1, categoriesFile);
    fclose(categoriesFile);
    return category;
}



void updateFileIndex(struct Inform inform, struct IndexCategories* arrayOfIndexCategories) {
    FILE* categoriesIndex = fopen("categories.ind", "w+b");
    for (int i = 0; i < inform.idInsertedCategories; i++)
        fwrite(&arrayOfIndexCategories[i], sizeof(struct IndexCategories), 1, categoriesIndex);
    fclose(categoriesIndex);
}



//_______________________________________DISHES__________________________________________________//


struct Dish createNewDish(const struct Inform inform) {
    struct Dish newDish;
    struct Categories currentCategory;

    printf("Enter name of the dish:\n");
    scanf("%19s", newDish.name);
    printf("Enter weight of the dish:\n");
    scanf("%d", &newDish.weight);
    printf("Enter price of the dish:\n");
    scanf("%d", &newDish.price);

    newDish.id = inform.idInsertedDishes;
    currentCategory = get_m();
    newDish.idCategories = currentCategory.id;
    newDish.addressNextDish = -1;
    newDish.isExist = true;

    return newDish;
}


void outputTheDish(const struct Dish dish) {
    printf("\n\tDish id = %d", dish.id);
    printf("\n\tDish name = %s", dish.name);
    printf("\n\tDish weight(in kg) = %d", dish.weight);
    printf("\n\tPrice (in UAH) = %d", dish.price);
    printf("\n\tCategories id = %d", dish.idCategories);
    printf("\n\tAddress of next dish = %d", dish.addressNextDish);
    printf("\n\tIs exist? = %d\n", dish.isExist);
}



struct Dish* getArrayOfDish(struct Inform inform) {
    struct Dish* arrayOfDishes;
    struct Dish currentDish;
    arrayOfDishes = (struct Dish*)malloc(inform.idInsertedDishes * sizeof(struct Dish));
    FILE* dishtFile = fopen("dishes.fl", "r+b");
    for (int i = 0; i < inform.idInsertedDishes; i++) {
        fread(&currentDish, sizeof(struct Dish), 1, dishtFile);
        arrayOfDishes[i] = currentDish;
    }
    fclose(dishtFile);

    return arrayOfDishes;
}



struct Dish* getArrayOfSlavesDish(struct Categories category) {
    int sizeArray = category.countDishes;
    struct Dish* arrayOfSlavesDishes;
    struct Dish temp;
    arrayOfSlavesDishes = (struct Dish*)malloc(sizeArray * sizeof(struct Dish));

    int i = 0;
    FILE* dishesFile = fopen("dishes.fl", "r+b");
    fseek(dishesFile, category.addressNextDish, 0);
    fread(&temp, sizeof(struct Dish), 1, dishesFile);
    if (temp.isExist) {
        arrayOfSlavesDishes[i] = temp;
        i++;
    }

    while (temp.addressNextDish != -1) {
        fseek(dishesFile, temp.addressNextDish, 0);
        fread(&temp, sizeof(struct Dish), 1, dishesFile);
        if (temp.isExist) {
            arrayOfSlavesDishes[i] = temp;
            i++;
        }
    }
    fclose(dishesFile);

    return arrayOfSlavesDishes;
}



void updateDishFile(struct Inform inform, struct Dish* arrayOfDishes) {
    FILE* dishesFile = fopen("dishes.fl", "w+b");
    for (int i = 0; i < inform.idInsertedDishes; i++)
        fwrite(&arrayOfDishes[i], sizeof(struct Dish), 1, dishesFile);
    fclose(dishesFile);
}


//_______________________INFORMATION FILE______________________________________//


void checkInformFile() {
    FILE* size = fopen("inform.dat", "r+b");

    fseek(size, 0, SEEK_END);
    int pos = ftell(size);
    fseek(size, 0, SEEK_SET);
    fclose(size);

    if (pos == -1)
        DefaultInform();
}


struct Inform collectInformation() {
    struct Inform inform;

    FILE* size = fopen("inform.dat", "r+b");
    fread(&inform, sizeof(struct Inform), 1, size);
    fclose(size);
    return inform;
}


void DefaultInform() {
    FILE* info = fopen("inform.dat", "w+b");
    struct Inform inform;
    printf("Data base is empty\n");
    printf("Filling...\n");
    inform.idInsertedDishes = 0;
    inform.idInsertedCategories = 0;
    inform.countOfExistingCategories = 0;
    inform.countOfExistingDishes = 0;
    fwrite(&inform, sizeof(struct Inform), 1, info);
    fclose(info);
}


void updateInformFile(struct Inform inform) {
    FILE* info = fopen("inform.dat", "w+b");
    fwrite(&inform, sizeof(struct Inform), 1, info);
    fclose(info);
}



void outputInformFromFile() {
    struct Inform inform;
    inform = collectInformation();
    printf("\n------------------------------------------------");
    printf("\nCount of Categories is %d", inform.countOfExistingCategories);
    printf("\nCount of dishes is %d\n\n", inform.countOfExistingDishes);

    struct Categories* arrayOfCategories = getArrayOfCategories(inform);
    for (int i = 0; i < inform.idInsertedCategories; i++) {
        if (arrayOfCategories[i].isExist)
            printf("[%d] Categories count of dish: %d\n", arrayOfCategories[i].id, arrayOfCategories[i].countDishes);
    }
}







//_______________________MAIN FUNCTIONS______________________________________//


void insert_m() {
    struct Inform inform;
    inform = collectInformation();

    struct Categories newCategory;
    struct IndexCategories newIndexCategory;

    newCategory = createNewCategory(inform);
    newIndexCategory = createNewIndexCategories(newCategory, inform);

    FILE* categoryFile = fopen("categories.fl", "a+b");
    fwrite(&newCategory, sizeof(struct Categories), 1, categoryFile);
    fclose(categoryFile);

    FILE* categoriesIndex = fopen("categories.ind", "a+b");
    fwrite(&newIndexCategory, sizeof(struct IndexCategories), 1, categoriesIndex);
    fclose(categoriesIndex);

    inform.countOfExistingCategories++;
    inform.idInsertedCategories++;
    updateInformFile(inform);
}


void insert_s() {
    struct Inform inform;
    inform = collectInformation();

    struct Dish newDish;
    newDish = createNewDish(inform);

    struct IndexCategories* arrayOfIndexCategories = getArrayOfIndexCategories(inform);

    int index = 0;
    for (int i = 0; i < inform.idInsertedCategories; i++)
        if (arrayOfIndexCategories[i].id == newDish.idCategories)
            index = i;

    struct Categories currentCategory;
    FILE* categoryFile = fopen("categories.fl", "r+b");
    fseek(categoryFile, arrayOfIndexCategories[index].address, 0);
    fread(&currentCategory, sizeof(struct Categories), 1, categoryFile);
    fclose(categoryFile);

    if (currentCategory.addressNextDish == -1) {
        FILE* dishFile = fopen("dishes.fl", "a+b");
        fwrite(&newDish, sizeof(struct Dish), 1, dishFile);
        fclose(dishFile);

        struct Categories* arrayOfCategories = getArrayOfCategories(inform);
        FILE* categoriesInput = fopen("categories.fl", "w+b");
        for (int i = 0; i < inform.idInsertedCategories; i++) {
            if (arrayOfCategories[i].id == newDish.idCategories) {
                arrayOfCategories[i].addressNextDish = inform.idInsertedDishes * sizeof(struct Dish);
                arrayOfCategories[i].countDishes++;
            }
            fwrite(&arrayOfCategories[i], sizeof(struct Categories), 1, categoriesInput);
        }

        fclose(categoriesInput);
    }
    else {

        int index = currentCategory.addressNextDish / sizeof(struct Dish);
        struct Dish* arrayOfDishes = getArrayOfDish(inform);

        while (arrayOfDishes[index].addressNextDish != -1)
            index = arrayOfDishes[index].addressNextDish / sizeof(struct Dish);

        arrayOfDishes[index].addressNextDish = inform.idInsertedDishes * sizeof(struct Dish);

        FILE* dishFile = fopen("dishes.fl", "w+b");
        for (int i = 0; i < inform.idInsertedDishes; i++)
            fwrite(&arrayOfDishes[i], sizeof(struct Dish), 1, dishFile);
        fwrite(&newDish, sizeof(struct Dish), 1, dishFile);
        fclose(dishFile);

        struct Categories* arrayOfCategories = getArrayOfCategories(inform);
        FILE* categoriesInput = fopen("categories.fl", "w+b");
        for (int i = 0; i < inform.idInsertedCategories; i++) {
            if (arrayOfCategories[i].id == newDish.idCategories)
                arrayOfCategories[i].countDishes++;
            fwrite(&arrayOfCategories[i], sizeof(struct Categories), 1, categoriesInput);
        }
        fclose(categoriesInput);
    }

    inform.countOfExistingDishes++;
    inform.idInsertedDishes++;
    updateInformFile(inform);
}



struct Categories get_m() {
    struct Inform inform;
    inform = collectInformation();

    struct IndexCategories* arrayOfIndexCategories = getArrayOfIndexCategories(inform);
    int index = chooseIndexOfIdCategories(inform);

    struct Categories currentCategory;
    FILE* categoriesFile = fopen("categories.fl", "r+b");
    fseek(categoriesFile, arrayOfIndexCategories[index].address, 0);
    fread(&currentCategory, sizeof(struct Categories), 1, categoriesFile);
    fclose(categoriesFile);

    return currentCategory;
}



struct Dish get_s() {
    struct Inform inform;
    inform = collectInformation();

    struct Categories category = getCategoryById(inform);

    if (category.countDishes == 0) {
        printf("This truck hasn't got a product yet\n");
        struct Dish random;
        random.addressNextDish = INT_MIN;
        return random;
    }

    int sizeArrayDish = category.countDishes;
    struct Dish* arrayOfSlavesDish = getArrayOfSlavesDish(category);

    for (int i = 0; i < sizeArrayDish; i++)
        printf("[%d] ", i);

    printf("\nChoose the index of the dish: ");
    int index;
    scanf("%d", &index);
    return arrayOfSlavesDish[index];
}



void update_m() {
    struct Inform inform;
    inform = collectInformation();

    struct IndexCategories* arrayOfIndexCategories = getArrayOfIndexCategories(inform);
    int index = chooseIndexOfIdCategories(inform);

    struct Categories updatedCategory;
    FILE* categoriesFile = fopen("categories.fl", "r+b");
    fseek(categoriesFile, arrayOfIndexCategories[index].address, 0);
    fread(&updatedCategory, sizeof(struct Categories), 1, categoriesFile);
    fclose(categoriesFile);

    printCategory(updatedCategory);
    printf("Choose what you want to change:\n");
    printf("[0] - name\n");
    
    int choose;
    scanf("%d", &choose);
    if (choose == 0) {
        printf("Enter a new name:\n");
        scanf("%s", updatedCategory.name);
    }
   
    struct Categories* arrayOfCategories = getArrayOfCategories(inform);
    int indexOfCategory = arrayOfIndexCategories[index].address / sizeof(struct Categories);
    arrayOfCategories[indexOfCategory] = updatedCategory;

    categoriesFile = fopen("categories.fl", "w+b");
    for (int i = 0; i < inform.idInsertedCategories; i++)
        fwrite(&arrayOfCategories[i], sizeof(struct Categories), 1, categoriesFile);
    fclose(categoriesFile);
}



void update_s() {
    struct Inform inform;
    inform = collectInformation();

    struct Categories category = getCategoryById(inform);

    if (category.countDishes == 0) {
        printf("This category hasn't got a dish yet\n");
        return;
    }

    int sizeArrayDish = category.countDishes;
    struct Dish* arrayOfSlavesDish = getArrayOfSlavesDish(category);

    for (int i = 0; i < sizeArrayDish; i++)
        printf("[%d] ", i);

    printf("\nChoose the index of the dish: ");
    int index;
    scanf("%d", &index);
    outputTheDish(arrayOfSlavesDish[index]);
    struct Dish updatedDish = arrayOfSlavesDish[index];


    printf("Choose the field you want to change\n");
    printf("[0] - name\n");
    printf("[1]-price\n");
    printf("[2] - weight\n");
    int choose;
    scanf("%d", &choose);
    if (choose == 0) {
        printf("Enter a new name:\n");
        scanf("%s", updatedDish.name);
    }
    else if (choose == 1) {
        printf("Enter a new price: \n");
        scanf("%d", &updatedDish.price);
    }
    else {
        printf("Enter a new weight:\n");
        scanf("%d", &updatedDish.weight);
    }

    struct Dish* arrayOfDishes = getArrayOfDish(inform);
    if (index == 0)
        index = category.addressNextDish / sizeof(struct Dish);
    else
        index = arrayOfSlavesDish[index - 1].addressNextDish / sizeof(struct Dish);
    arrayOfDishes[index] = updatedDish;

    FILE* dishesFile = fopen("dishes.fl", "w+b");
    for (int i = 0; i < inform.idInsertedDishes; i++)
        fwrite(&arrayOfDishes[i], sizeof(struct Dish), 1, dishesFile);
    fclose(dishesFile);
}


void del_m() {
    struct Inform inform;
    inform = collectInformation();

    struct Categories* arrayOfCategories = getArrayOfCategories(inform);
    struct Dish* arrayOfDishes = getArrayOfDish(inform);
    struct IndexCategories* arrayOfIndexCategories = getArrayOfIndexCategories(inform);

    int index = chooseIndexOfIdCategories(inform);
    struct Categories* deletedCategory = &arrayOfCategories[index];

    arrayOfIndexCategories[deletedCategory->id].isExist = false;
    deletedCategory->isExist = false;

    if (deletedCategory->countDishes != 0) {
        struct Dish* slaveDishes = &arrayOfDishes[deletedCategory->addressNextDish / sizeof(struct Dish)];
        if (slaveDishes->isExist)
            slaveDishes->isExist = false;
        while (slaveDishes->addressNextDish != -1) {
            slaveDishes = &arrayOfDishes[slaveDishes->addressNextDish / sizeof(struct Dish)];
            slaveDishes->isExist = false;
        }
    }

    updateFileOfCategories(inform, arrayOfCategories);
    updateFileIndex(inform, arrayOfIndexCategories);
    updateDishFile(inform, arrayOfDishes);
    inform.countOfExistingDishes -= deletedCategory->countDishes;
    inform.countOfExistingCategories--;
    updateInformFile(inform);

}


void del_s() {
    struct Inform inform;
    inform = collectInformation();

    struct Categories* arrayOfCategories = getArrayOfCategories(inform);
    struct Dish* arrayOfDishes = getArrayOfDish(inform);
    struct IndexCategories* arrayOfIndexCategories = getArrayOfIndexCategories(inform);

    int index = chooseIndexOfIdCategories(inform);
    struct Categories* deletedCategoryDish = &arrayOfCategories[index];

    if (deletedCategoryDish->countDishes == 0) {
        printf("This category hasn't got a dish yet\n");
        return;
    }

    struct Dish* arrayOfSlavesDishes = getArrayOfSlavesDish(*deletedCategoryDish);
    for (int i = 0; i < deletedCategoryDish->countDishes; i++)
        printf("[%d] ", arrayOfSlavesDishes[i].id);
    printf("\nChoose the id of deleted dish: ");
    int idDish;
    scanf("%d", &idDish);
    arrayOfDishes[idDish].isExist = false;
    deletedCategoryDish->countDishes--;

    updateDishFile(inform, arrayOfDishes);
    updateFileOfCategories(inform, arrayOfCategories);
    inform.countOfExistingDishes--;
    updateInformFile(inform);


}



//
void ut_m() {
    struct Inform inform;
    struct Categories currentÑategory;
    inform = collectInformation();

    printf("ALL Categories:\n");
    FILE* categoriesFile = fopen("categories.fl", "r+b");
    for (int i = 0; i < inform.idInsertedCategories; i++) {
        fread(&currentÑategory, sizeof(struct Categories), 1, categoriesFile);
        if (currentÑategory.isExist)
            printCategory(currentÑategory);
    }

    fclose(categoriesFile);
}
void ut_s() {
    struct Inform inform;
    struct Categories currentCategory;
    inform = collectInformation();

    printf("All dishes:\n");
    printf("__________________________________________________________________________\n");
    FILE* categoriesFile = fopen("categories.fl", "r+b");
    for (int i = 0; i < inform.idInsertedCategories; i++) {
        fread(&currentCategory, sizeof(struct Categories), 1, categoriesFile);
        if (currentCategory.isExist) {
            printCategory(currentCategory);
            if (currentCategory.countDishes > 0) {
                struct Dish* arrayOfSlavesDishes = getArrayOfSlavesDish(currentCategory);
                printf("\nDishes: \n");
                for (int j = 0; j < currentCategory.countDishes; j++)
                    outputTheDish(arrayOfSlavesDishes[j]);

            }
            printf("__________________________________________________________________________\n");
        }
    }

    fclose(categoriesFile);
}
