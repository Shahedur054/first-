
#include <stdio.h>
#include <string.h>

#define MAX_PRODUCTS 100

// Structure to hold product details
struct Product {
    int productID;
    char name[50];
    int quantity;
};

// Array to store products and count of products
struct Product inventory[MAX_PRODUCTS];
int productCount = 0;

void addProduct() {
    if (productCount >= MAX_PRODUCTS) {
        printf("Inventory is full! Cannot add more products.\n");
        return;
    }

    struct Product p;
    printf("Enter product name: ");
    scanf(" %[^\n]s", p.name); // Allows spaces in name
    printf("Enter product ID: ");
    scanf("%d", &p.productID);
    printf("Enter stock quantity: ");
    scanf("%d", &p.quantity);

    inventory[productCount] = p;
    productCount++;
    printf("Product added successfully!\n");
}

void viewInventory() {
    if (productCount == 0) {
        printf("Inventory is empty!\n");
        return;
    }

    printf("Inventory List:\n");
    for (int i = 0; i < productCount; i++) {
        printf("Product ID: %d, Name: %s, Stock: %d\n", inventory[i].productID, inventory[i].name, inventory[i].quantity);
    }
}

void updateStockQuantity() {
    int id, newQuantity;
    printf("Enter Product ID to update: ");
    scanf("%d", &id);

    for (int i = 0; i < productCount; i++) {
        if (inventory[i].productID == id) {
            printf("Enter new stock quantity: ");
            scanf("%d", &newQuantity);
            inventory[i].quantity = newQuantity;
            printf("Stock updated successfully!\n");
            return;
        }
    }
    printf("Product ID not found!\n");
}

void removeProduct() {
    int id;
    printf("Enter Product ID to remove: ");
    scanf("%d", &id);

    for (int i = 0; i < productCount; i++) {
        if (inventory[i].productID == id) {
            for (int j = i; j < productCount - 1; j++) {
                inventory[j] = inventory[j + 1];
            }
            productCount--;
            printf("Product removed successfully!\n");
            return;
        }
    }
    printf("Product ID not found!\n");
}

int main() {
    int choice;
    while (1) {
        printf("________________Management System________________\n");
        printf("1. Add Product\n");
        printf("2. View Inventory\n");
        printf("3. Update Stock Quantity\n");
        printf("4. Remove Product\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                addProduct();
                break;
            case 2:
                viewInventory();
                break;
            case 3:
                updateStockQuantity();
                break;
            case 4:
                removeProduct();
                break;
            case 5:
                printf("Exiting the system...\n");
                printf("Thank you for using the Inventory Management System!\n");
                return 0;
            default:
                printf("Invalid choice! Please try again.\n");
        }
    }
    return 0;
}