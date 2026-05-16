#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define PRODUCT_COUNT 5

/* ---------- STRUCTURES ---------- */

typedef struct {
    char name[30];
    int price;
    int stock;
} Product;

typedef struct {
    char name[30];
    int quantity;
} Inventory;

/* ---------- GLOBAL VARIABLES ---------- */

Product products[PRODUCT_COUNT];
Inventory inventory[PRODUCT_COUNT];
int money = 500;

/* ---------- FUNCTION DECLARATIONS ---------- */

void loadProducts();
void saveProducts();

void loadStudentData();
void saveStudentData();

void showProducts();
void buyProduct();
void showInventory();

/* ---------- MAIN ---------- */

int main() {

    int choice;

    loadProducts();
    loadStudentData();

    do {

        printf("\n===== VENDING MACHINE =====\n");
        printf("1. View Products\n");
        printf("2. Buy Product\n");
        printf("3. View Inventory\n");
        printf("4. Exit\n");
        printf("Enter choice: ");

        scanf("%d", &choice);

        switch(choice) {

            case 1:
                showProducts();
                break;

            case 2:
                buyProduct();
                break;

            case 3:
                showInventory();
                break;

            case 4:
                saveProducts();
                saveStudentData();
                printf("Goodbye!\n");
                break;

            default:
                printf("Invalid choice.\n");
        }

    } while(choice != 4);

    return 0;
}

/* ---------- LOAD PRODUCTS ---------- */

void loadProducts() {

    FILE *file = fopen("inventory.txt", "r");

    if(file == NULL) {

        printf("inventory.txt not found. Creating default products...\n");

        strcpy(products[0].name, "Coke");
        products[0].price = 20;
        products[0].stock = 100;

        strcpy(products[1].name, "Sprite");
        products[1].price = 20;
        products[1].stock = 100;

        strcpy(products[2].name, "Royal");
        products[2].price = 20;
        products[2].stock = 80;

        strcpy(products[3].name, "Water");
        products[3].price = 15;
        products[3].stock = 150;

        strcpy(products[4].name, "Pepsi");
        products[4].price = 20;
        products[4].stock = 120;

        saveProducts();
        return;
    }

    for(int i = 0; i < PRODUCT_COUNT; i++) {
        fscanf(file, "%s %d %d",
               products[i].name,
               &products[i].price,
               &products[i].stock);
    }

    fclose(file);
}

/* ---------- SAVE PRODUCTS ---------- */

void saveProducts() {

    FILE *file = fopen("inventory.txt", "w");

    for(int i = 0; i < PRODUCT_COUNT; i++) {
        fprintf(file, "%s %d %d\n",
                products[i].name,
                products[i].price,
                products[i].stock);
    }

    fclose(file);
}

/* ---------- LOAD STUDENT DATA ---------- */

void loadStudentData() {

    FILE *file = fopen("student.txt", "r");

    if(file == NULL) {

        money = 500;

        for(int i = 0; i < PRODUCT_COUNT; i++) {
            strcpy(inventory[i].name, products[i].name);
            inventory[i].quantity = 0;
        }

        saveStudentData();
        return;
    }

    fscanf(file, "%d", &money);

    for(int i = 0; i < PRODUCT_COUNT; i++) {
        fscanf(file, "%s %d",
               inventory[i].name,
               &inventory[i].quantity);
    }

    fclose(file);
}

/* ---------- SAVE STUDENT DATA ---------- */

void saveStudentData() {

    FILE *file = fopen("student.txt", "w");

    fprintf(file, "%d\n", money);

    for(int i = 0; i < PRODUCT_COUNT; i++) {
        fprintf(file, "%s %d\n",
                inventory[i].name,
                inventory[i].quantity);
    }

    fclose(file);
}

/* ---------- SHOW PRODUCTS ---------- */

void showProducts() {

    printf("\n=========================================\n");
    printf("| NO | PRODUCT | PRICE | STOCK |\n");
    printf("=========================================\n");

    for(int i = 0; i < PRODUCT_COUNT; i++) {
        printf("| %-2d | %-7s | %-5d | %-5d |\n",
               i + 1,
               products[i].name,
               products[i].price,
               products[i].stock);
    }

    printf("=========================================\n");
}

/* ---------- BUY PRODUCT (WITH CART SUMMARY FIX) ---------- */

void buyProduct() {

    int choice, quantity;
    int totalCost = 0;
    char again, proceed;

    int cart[PRODUCT_COUNT] = {0};

    do {

        showProducts();

        printf("\nEnter product number: ");
        scanf("%d", &choice);
        choice--;

        if(choice < 0 || choice >= PRODUCT_COUNT) {
            printf("Invalid product.\n");
            continue;
        }

        printf("Enter quantity: ");
        scanf("%d", &quantity);

        if(quantity <= 0) {
            printf("Invalid quantity.\n");
            continue;
        }

        if(quantity > products[choice].stock) {
            printf("Not enough stock.\n");
            continue;
        }

        cart[choice] += quantity;
        totalCost += products[choice].price * quantity;

        printf("Added %d %s\n", quantity, products[choice].name);
        printf("Current Total: PHP %d\n", totalCost);

        printf("Add more? (y/n): ");
        scanf(" %c", &again);

    } while(again == 'y' || again == 'Y');

    /* ---------- CART SUMMARY (NEW PART) ---------- */

    printf("\n================ CART SUMMARY ================\n");

    int hasItem = 0;

    for(int i = 0; i < PRODUCT_COUNT; i++) {

        if(cart[i] > 0) {
            printf("%s x %d = PHP %d\n",
                   products[i].name,
                   cart[i],
                   cart[i] * products[i].price);
            hasItem = 1;
        }
    }

    if(!hasItem) {
        printf("No items selected.\n");
    }

    printf("=============================================\n");
    printf("TOTAL: PHP %d\n", totalCost);

    /* ---------- CONFIRM PURCHASE ---------- */

    printf("\nProceed purchase? (y/n): ");
    scanf(" %c", &proceed);

    if(proceed != 'y' && proceed != 'Y') {
        printf("Cancelled.\n");
        return;
    }

    if(totalCost > money) {
        printf("Not enough money!\n");
        return;
    }

    /* ---------- FINALIZE ---------- */

    money -= totalCost;

    for(int i = 0; i < PRODUCT_COUNT; i++) {
        if(cart[i] > 0) {
            products[i].stock -= cart[i];
            inventory[i].quantity += cart[i];
        }
    }

    saveProducts();
    saveStudentData();

    printf("\nPurchase successful!\n");
    printf("Remaining money: PHP %d\n", money);
}

/* ---------- SHOW INVENTORY ---------- */

void showInventory() {

    printf("\n===== YOUR INVENTORY =====\n");

    int empty = 1;

    for(int i = 0; i < PRODUCT_COUNT; i++) {

        if(inventory[i].quantity > 0) {
            printf("%s x %d\n",
                   inventory[i].name,
                   inventory[i].quantity);
            empty = 0;
        }
    }

    if(empty) {
        printf("No items yet.\n");
    }

    printf("Remaining Money: PHP %d\n", money);
}
