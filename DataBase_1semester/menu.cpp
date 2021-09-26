#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include "function.h"

int main() {
   
    int command;
    bool flag = true;
    struct Categories category;
    struct Dish dish;

   
    while (flag) {
        Command();
        scanf("%d", &command);

        switch (command) {
        case 1:
            insert_m();
            break;
        case 2:
            insert_s();
            break;
        case 3:
            category = get_m();
            printCategory(category);
            break;
        case 4:
            dish = get_s();
            if (dish.addressNextDish != -2)
                outputTheDish(dish);
            break;
        case 5:
            update_m();
            break;
        case 6:
            update_s();
            break;
        case 7:
            del_m();
            break;
        case 8:
            del_s();
            break;
        case 9:
            ut_m();
            break;
        case 10:
            ut_s();
            break;
        case 11:
            outputInformFromFile();
            break;
        case 12:
            clearAllFiles();
            break;
        case 0:
            flag = false;
            break;
        default:
            printf("Wrong input! Try again\n");

        }
    }
}

