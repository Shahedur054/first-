#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdbool.h>

#define MAX_PRODUCTS 50
#define MAX_CART_ITEMS 50
#define MAX_NAME_LENGTH 50
#define MAX_DESC_LENGTH 200
#define MAX_SIZE_LENGTH 10
#define MAX_SIZES 5
#define CUSTOMER_FILE "customer_data.txt"
#define HISTORY_FILE "shopping_history.txt"
#define MAX_CUSTOMERS 100

typedef struct {
    char name[MAX_NAME_LENGTH];
    char description[MAX_DESC_LENGTH];
    float price;
    char sizes[MAX_SIZES][MAX_SIZE_LENGTH];
    int size_count;
    int stock;
} Product;

typedef struct {
    Product product;
    char selected_size[MAX_SIZE_LENGTH];
    int quantity;
} CartItem;

typedef struct {
    char name[MAX_NAME_LENGTH];
    char address[100];
    char birthday[11];
    char gender[10];
    char email[50];
    char password[50];
    char number[15];
    CartItem cart[MAX_CART_ITEMS];
    int cart_size;
} Customer;

Customer current_customer;
Product men_products[MAX_PRODUCTS];
Product women_products[MAX_PRODUCTS];
Product kids_products[MAX_PRODUCTS];
int men_product_count = 0;
int women_product_count = 0;
int kids_product_count = 0;

// Function prototypes
void initialize_products();
void print_header();
void print_welcome();
void clear_input_buffer();
void press_enter_to_continue();
bool save_customer_data(Customer *customer);
bool load_customer_data(const char* phone, Customer *customer);
void show_product_details(Product p);
void show_products_menu(int category);
void show_category_menu();
void view_cart();
void checkout();
void process_payment(float total);
void show_receipt(float total);
void create_account();
void login_account();
void show_main_menu();
void save_purchase_history(float total);

void initialize_products() {
    // Men's Products
    strcpy(men_products[0].name, "Premium Casual Shirt");
    strcpy(men_products[0].description, "Double lacoste cotton fabric, slim fit");
    men_products[0].price = 2500.0;
    strcpy(men_products[0].sizes[0], "S");
    strcpy(men_products[0].sizes[1], "M");
    strcpy(men_products[0].sizes[2], "L");
    strcpy(men_products[0].sizes[3], "XL");
    men_products[0].size_count = 4;
    men_products[0].stock = 15;

    strcpy(men_products[1].name, "Classic Denim Jeans");
    strcpy(men_products[1].description, "Stretchable denim with modern fit");
    men_products[1].price = 3200.0;
    strcpy(men_products[1].sizes[0], "28");
    strcpy(men_products[1].sizes[1], "30");
    strcpy(men_products[1].sizes[2], "32");
    men_products[1].size_count = 3;
    men_products[1].stock = 12;

    strcpy(men_products[2].name, "Formal Blazer");
    strcpy(men_products[2].description, "Wool blend formal blazer");
    men_products[2].price = 5500.0;
    strcpy(men_products[2].sizes[0], "S");
    strcpy(men_products[2].sizes[1], "M");
    strcpy(men_products[2].sizes[2], "L");
    men_products[2].size_count = 3;
    men_products[2].stock = 8;

    strcpy(men_products[3].name, "Sports T-Shirt");
    strcpy(men_products[3].description, "Quick-dry fabric for workouts");
    men_products[3].price = 1200.0;
    strcpy(men_products[3].sizes[0], "S");
    strcpy(men_products[3].sizes[1], "M");
    strcpy(men_products[3].sizes[2], "L");
    strcpy(men_products[3].sizes[3], "XL");
    men_products[3].size_count = 4;
    men_products[3].stock = 20;

    strcpy(men_products[4].name, "Winter Jacket");
    strcpy(men_products[4].description, "Waterproof with thermal lining");
    men_products[4].price = 4500.0;
    strcpy(men_products[4].sizes[0], "M");
    strcpy(men_products[4].sizes[1], "L");
    strcpy(men_products[4].sizes[2], "XL");
    men_products[4].size_count = 3;
    men_products[4].stock = 10;

    men_product_count = 5;

    // Women's Products
    strcpy(women_products[0].name, "Silk Jamdani Saree");
    strcpy(women_products[0].description, "Royal blue with multicolor buti");
    women_products[0].price = 2400.0;
    strcpy(women_products[0].sizes[0], "One Size");
    women_products[0].size_count = 1;
    women_products[0].stock = 10;

    strcpy(women_products[1].name, "Floral Summer Dress");
    strcpy(women_products[1].description, "Lightweight cotton with floral print");
    women_products[1].price = 1800.0;
    strcpy(women_products[1].sizes[0], "S");
    strcpy(women_products[1].sizes[1], "M");
    strcpy(women_products[1].sizes[2], "L");
    women_products[1].size_count = 3;
    women_products[1].stock = 14;

    strcpy(women_products[2].name, "Designer Abaya");
    strcpy(women_products[2].description, "Black with intricate embroidery");
    women_products[2].price = 3800.0;
    strcpy(women_products[2].sizes[0], "S");
    strcpy(women_products[2].sizes[1], "M");
    strcpy(women_products[2].sizes[2], "L");
    women_products[2].size_count = 3;
    women_products[2].stock = 9;

    strcpy(women_products[3].name, "Casual Top");
    strcpy(women_products[3].description, "Comfortable everyday wear");
    women_products[3].price = 950.0;
    strcpy(women_products[3].sizes[0], "S");
    strcpy(women_products[3].sizes[1], "M");
    strcpy(women_products[3].sizes[2], "L");
    women_products[3].size_count = 3;
    women_products[3].stock = 18;

    strcpy(women_products[4].name, "Casual Maxi Dress");
    strcpy(women_products[4].description, "Comfortable long dress for all occasions");
    women_products[4].price = 2200.0;
    strcpy(women_products[4].sizes[0], "S");
    strcpy(women_products[4].sizes[1], "M");
    strcpy(women_products[4].sizes[2], "L");
    women_products[4].size_count = 3;
    women_products[4].stock = 12;

    women_product_count = 5;

    // Children's Products
    strcpy(kids_products[0].name, "Cartoon T-Shirt");
    strcpy(kids_products[0].description, "Colorful cartoon printed cotton t-shirt");
    kids_products[0].price = 800.0;
    strcpy(kids_products[0].sizes[0], "XS");
    strcpy(kids_products[0].sizes[1], "S");
    strcpy(kids_products[0].sizes[2], "M");
    kids_products[0].size_count = 3;
    kids_products[0].stock = 20;

    strcpy(kids_products[1].name, "Denim Shorts");
    strcpy(kids_products[1].description, "Comfortable denim shorts for kids");
    kids_products[1].price = 950.0;
    strcpy(kids_products[1].sizes[0], "XS");
    strcpy(kids_products[1].sizes[1], "S");
    strcpy(kids_products[1].sizes[2], "M");
    kids_products[1].size_count = 3;
    kids_products[1].stock = 15;

    strcpy(kids_products[2].name, "Fleece Jacket");
    strcpy(kids_products[2].description, "Warm fleece jacket for winter");
    kids_products[2].price = 1200.0;
    strcpy(kids_products[2].sizes[0], "XS");
    strcpy(kids_products[2].sizes[1], "S");
    strcpy(kids_products[2].sizes[2], "M");
    kids_products[2].size_count = 3;
    kids_products[2].stock = 10;

    strcpy(kids_products[3].name, "School Uniform Set");
    strcpy(kids_products[3].description, "Complete school uniform set");
    kids_products[3].price = 1500.0;
    strcpy(kids_products[3].sizes[0], "XS");
    strcpy(kids_products[3].sizes[1], "S");
    strcpy(kids_products[3].sizes[2], "M");
    kids_products[3].size_count = 3;
    kids_products[3].stock = 18;

    strcpy(kids_products[4].name, "Party Dress");
    strcpy(kids_products[4].description, "Elegant party dress for special occasions");
    kids_products[4].price = 1800.0;
    strcpy(kids_products[4].sizes[0], "XS");
    strcpy(kids_products[4].sizes[1], "S");
    strcpy(kids_products[4].sizes[2], "M");
    kids_products[4].size_count = 3;
    kids_products[4].stock = 12;

    kids_product_count = 5;
}

void print_header() {
    printf("\n");
    printf("==================================================\n");
    printf("                OHSAM Clothing\n");
    printf("==================================================\n");
}

void print_welcome() {
    printf("\n");
    printf("==================================================\n");
    printf("             WELCOME TO OUR STORE\n");
    printf("==================================================\n");
    printf("   Special Offer! 13%% Discount on All Products\n\n");
}

void print_line(char c, int length) {
    for (int i = 0; i < length; i++) {
        putchar(c);
    }
    putchar('\n');
}

void clear_input_buffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

void press_enter_to_continue() {
    printf("\nPress Enter to continue...");
    clear_input_buffer();
    getchar();
}

bool save_customer_data(Customer *customer) {
    FILE *file = fopen(CUSTOMER_FILE, "a+");
    if (!file) return false;

    // First check if customer already exists
    FILE *temp_file = fopen("temp.txt", "w");
    if (!temp_file) {
        fclose(file);
        return false;
    }

    char line[256];
    bool customer_exists = false;
    rewind(file);

    // Copy all customers to temp file, replacing if found
    while (fgets(line, sizeof(line), file)) {
        if (strstr(line, customer->number)) {
            // Skip the existing customer data
            customer_exists = true;
            while (fgets(line, sizeof(line), file) && strcmp(line, "----------\n") != 0);
        } else {
            fputs(line, temp_file);
        }
    }

    // Write the customer data
    fprintf(temp_file, "Mobile: %s\n", customer->number);
    fprintf(temp_file, "Name: %s\n", customer->name);
    fprintf(temp_file, "Address: %s\n", customer->address);
    fprintf(temp_file, "Birthdate: %s\n", customer->birthday);
    fprintf(temp_file, "Gender: %s\n", customer->gender);
    fprintf(temp_file, "Email: %s\n", customer->email);
    fprintf(temp_file, "Password: %s\n", customer->password);
    fprintf(temp_file, "Cart Items: %d\n", customer->cart_size);

    // Save cart items if any
    for (int i = 0; i < customer->cart_size; i++) {
        fprintf(temp_file, "CartItem: %s|%s|%d\n",
               customer->cart[i].product.name,
               customer->cart[i].selected_size,
               customer->cart[i].quantity);
    }
    fprintf(temp_file, "----------\n");

    fclose(file);
    fclose(temp_file);

    remove(CUSTOMER_FILE);
    rename("temp.txt", CUSTOMER_FILE);

    return true;
}

bool load_customer_data(const char* phone, Customer *customer) {
    FILE *file = fopen(CUSTOMER_FILE, "r");
    if (!file) return false;

    char line[256];
    bool found = false;
    int cart_items = 0;

    while (fgets(line, sizeof(line), file)) {
        line[strcspn(line, "\n")] = '\0';

        if (strstr(line, phone)) {
            found = true;
            strcpy(customer->number, phone);

            // Read customer details
            while (fgets(line, sizeof(line), file) && strcmp(line, "----------\n") != 0) {
                line[strcspn(line, "\n")] = '\0';

                if (strstr(line, "Name: ")) {
                    strcpy(customer->name, line + 6);
                } else if (strstr(line, "Address: ")) {
                    strcpy(customer->address, line + 9);
                } else if (strstr(line, "Birthdate: ")) {
                    strcpy(customer->birthday, line + 11);
                } else if (strstr(line, "Gender: ")) {
                    strcpy(customer->gender, line + 8);
                } else if (strstr(line, "Email: ")) {
                    strcpy(customer->email, line + 7);
                } else if (strstr(line, "Password: ")) {
                    strcpy(customer->password, line + 10);
                } else if (strstr(line, "Cart Items: ")) {
                    cart_items = atoi(line + 12);
                    customer->cart_size = cart_items;
                } else if (strstr(line, "CartItem: ")) {
                    if (cart_items > 0) {
                        CartItem item;
                        char *token = strtok(line + 10, "|");
                        if (token) {
                            // Find the product in our inventory
                            bool product_found = false;

                            // Search in men's products
                            for (int i = 0; i < men_product_count && !product_found; i++) {
                                if (strcmp(men_products[i].name, token) == 0) {
                                    item.product = men_products[i];
                                    product_found = true;
                                }
                            }

                            // Search in women's products
                            for (int i = 0; i < women_product_count && !product_found; i++) {
                                if (strcmp(women_products[i].name, token) == 0) {
                                    item.product = women_products[i];
                                    product_found = true;
                                }
                            }

                            // Search in kids' products
                            for (int i = 0; i < kids_product_count && !product_found; i++) {
                                if (strcmp(kids_products[i].name, token) == 0) {
                                    item.product = kids_products[i];
                                    product_found = true;
                                }
                            }

                            if (product_found) {
                                token = strtok(NULL, "|");
                                if (token) strcpy(item.selected_size, token);

                                token = strtok(NULL, "|");
                                if (token) item.quantity = atoi(token);

                                customer->cart[customer->cart_size - cart_items] = item;
                                cart_items--;
                            }
                        }
                    }
                }
            }
            break;
        }
    }

    fclose(file);
    return found;
}

void show_product_details(Product p) {
    int choice;
    do {
        system("clear || cls");
        print_header();

        printf("\n%s\n", p.name);
        print_line('=', 50);
        printf("Description: %s\n", p.description);
        printf("Price: %.2f tk\n", p.price);

        if (p.size_count > 0 && strcmp(p.sizes[0], "One Size") != 0 && strcmp(p.sizes[0], "Free Size") != 0) {
            printf("Available Sizes: ");
            for (int i = 0; i < p.size_count; i++) printf("%s ", p.sizes[i]);
            printf("\n");
        }

        printf("Stock: %d available\n", p.stock);
        print_line('-', 50);
        printf("1. Add to Cart\n");
        printf("2. Back to Products\n");
        printf("Enter your choice: ");

        if (scanf("%d", &choice) != 1) {
            printf("Invalid input. Please enter a number.\n");
            clear_input_buffer();
            press_enter_to_continue();
            continue;
        }
        clear_input_buffer();

        if (choice == 1) {
            if (current_customer.cart_size >= MAX_CART_ITEMS) {
                printf("Your cart is full!\n");
                press_enter_to_continue();
                return;
            }

            char size[MAX_SIZE_LENGTH] = "";
            int quantity;

            if (p.size_count > 0 && strcmp(p.sizes[0], "One Size") != 0 && strcmp(p.sizes[0], "Free Size") != 0) {
                bool valid_size = false;
                do {
                    printf("Enter size: ");
                    fgets(size, MAX_SIZE_LENGTH, stdin);
                    size[strcspn(size, "\n")] = '\0';

                    for (int i = 0; i < p.size_count; i++) {
                        if (strcasecmp(p.sizes[i], size) == 0) {
                            valid_size = true;
                            strcpy(size, p.sizes[i]);
                            break;
                        }
                    }

                    if (!valid_size) {
                        printf("Invalid size. Available sizes: ");
                        for (int i = 0; i < p.size_count; i++) printf("%s ", p.sizes[i]);
                        printf("\n");
                    }
                } while (!valid_size);
            } else {
                printf("This product has no specific size. Press Enter to continue.\n");
                fgets(size, MAX_SIZE_LENGTH, stdin);
                strcpy(size, "One Size");
            }

            do {
                printf("Enter quantity (1-%d): ", p.stock);
                if (scanf("%d", &quantity) != 1) {
                    printf("Invalid input. Please enter a number.\n");
                    clear_input_buffer();
                    continue;
                }
                clear_input_buffer();

                if (quantity <= 0 || quantity > p.stock) {
                    printf("Invalid quantity. Please enter between 1 and %d.\n", p.stock);
                }
            } while (quantity <= 0 || quantity > p.stock);

            CartItem new_item;
            new_item.product = p;
            strcpy(new_item.selected_size, size);
            new_item.quantity = quantity;
            current_customer.cart[current_customer.cart_size++] = new_item;

            // Save the updated cart to file
            save_customer_data(&current_customer);

            printf("\n%s added to your cart!\n", p.name);
            press_enter_to_continue();
            return;
        } else if (choice == 2) {
            return;
        } else {
            printf("Invalid choice. Please try again.\n");
            press_enter_to_continue();
        }
    } while (1);
}

void show_products_menu(int category) {
    Product* products;
    int count;
    char* category_name;

    switch(category) {
        case 1:
            products = men_products;
            count = men_product_count;
            category_name = "MEN'S";
            break;
        case 2:
            products = women_products;
            count = women_product_count;
            category_name = "WOMEN'S";
            break;
        case 3:
            products = kids_products;
            count = kids_product_count;
            category_name = "CHILDREN'S";
            break;
        default:
            return;
    }

    int choice;
    do {
        system("clear || cls");
        print_header();
        printf("\n%s COLLECTION\n", category_name);
        print_line('-', 50);

        for (int i = 0; i < count; i++) {
            printf("%d. %s - %.2f tk\n", i+1, products[i].name, products[i].price);
        }
        printf("%d. Back to Categories\n", count+1);
        printf("Enter your choice: ");

        if (scanf("%d", &choice) != 1) {
            printf("Invalid input. Please enter a number.\n");
            clear_input_buffer();
            press_enter_to_continue();
            continue;
        }
        clear_input_buffer();

        if (choice >= 1 && choice <= count) {
            show_product_details(products[choice-1]);
        } else if (choice == count+1) {
            return;
        } else {
            printf("Invalid choice. Please try again.\n");
            press_enter_to_continue();
        }
    } while (1);
}

void show_category_menu() {
    int choice;
    do {
        system("clear || cls");
        print_header();
        printf("\nCATEGORIES\n");
        print_line('-', 50);
        printf("1. Men's Collection\n");
        printf("2. Women's Collection\n");
        printf("3. Children's Collection\n");
        printf("4. Back to Main Menu\n");
        printf("Enter your choice: ");

        if (scanf("%d", &choice) != 1) {
            printf("Invalid input. Please enter a number.\n");
            clear_input_buffer();
            press_enter_to_continue();
            continue;
        }
        clear_input_buffer();

        switch (choice) {
            case 1:
            case 2:
            case 3:
                show_products_menu(choice);
                break;
            case 4:
                return;
            default:
                printf("Invalid choice. Please try again.\n");
                press_enter_to_continue();
        }
    } while (1);
}

void view_cart() {
    if (current_customer.cart_size == 0) {
        printf("Your cart is empty!\n");
        press_enter_to_continue();
        return;
    }

    system("clear || cls");
    print_header();
    printf("\nYOUR SHOPPING CART\n");
    print_line('-', 50);

    float total = 0.0;
    for (int i = 0; i < current_customer.cart_size; i++) {
        CartItem item = current_customer.cart[i];
        printf("%d. %s", i+1, item.product.name);
        if (strcmp(item.selected_size, "One Size") != 0 && strcmp(item.selected_size, "Free Size") != 0) {
            printf(" (%s)", item.selected_size);
        }
        printf(" x%d - %.2f tk\n", item.quantity, item.product.price * item.quantity);
        total += item.product.price * item.quantity;
    }

    float discount = total * 0.13;
    float subtotal = total - discount;
    float tax = subtotal * 0.05;
    float grand_total = subtotal + tax;

    print_line('-', 50);
    printf("Subtotal: %.2f tk\n", total);
    printf("Discount (13%%): -%.2f tk\n", discount);
    printf("Tax (5%%): +%.2f tk\n", tax);
    printf("GRAND TOTAL: %.2f tk\n", grand_total);
    print_line('-', 50);

    printf("\n1. Proceed to Checkout\n");
    printf("2. Continue Shopping\n");
    printf("3. Remove Item\n");
    printf("4. Back to Main Menu\n");
    printf("Enter your choice: ");

    int choice;
    if (scanf("%d", &choice) != 1) {
        printf("Invalid input. Please enter a number.\n");
        clear_input_buffer();
        press_enter_to_continue();
        return;
    }
    clear_input_buffer();

    switch (choice) {
        case 1:
            checkout();
            break;
        case 2:
            return;
        case 3: {
            if (current_customer.cart_size == 0) {
                printf("Your cart is already empty!\n");
                press_enter_to_continue();
                return;
            }

            int item_num;
            printf("Enter item number to remove (1-%d): ", current_customer.cart_size);
            if (scanf("%d", &item_num) != 1) {
                printf("Invalid input. Please enter a number.\n");
                clear_input_buffer();
                press_enter_to_continue();
                return;
            }
            clear_input_buffer();

            if (item_num < 1 || item_num > current_customer.cart_size) {
                printf("Invalid item number. Please try again.\n");
                press_enter_to_continue();
                return;
            }

            for (int i = item_num - 1; i < current_customer.cart_size - 1; i++) {
                current_customer.cart[i] = current_customer.cart[i + 1];
            }

            current_customer.cart_size--;
            save_customer_data(&current_customer);
            printf("Item removed from your cart.\n");
            press_enter_to_continue();
            break;
        }
        case 4:
            return;
        default:
            printf("Invalid choice.\n");
            press_enter_to_continue();
    }
}

void process_payment(float total) {
    int choice;
    system("clear || cls");
    print_header();
    printf("\nPAYMENT METHODS\n");
    print_line('-', 50);
    printf("1. Credit/Debit Card\n");
    printf("2. Mobile Banking\n");
    printf("3. Cancel Order\n");
    printf("Enter your choice: ");

    if (scanf("%d", &choice) != 1) {
        printf("Invalid input. Please enter a number.\n");
        clear_input_buffer();
        press_enter_to_continue();
        return;
    }
    clear_input_buffer();

    if (choice == 1) {
        char card_number[20], card_name[50], expiry[10], cvv[5];

        printf("\nCREDIT/DEBIT CARD PAYMENT\n");
        print_line('-', 50);

        printf("Enter card number (16 digits): ");
        fgets(card_number, 20, stdin);
        card_number[strcspn(card_number, "\n")] = '\0';

        printf("Enter name on card: ");
        fgets(card_name, 50, stdin);
        card_name[strcspn(card_name, "\n")] = '\0';

        printf("Enter expiry date (MM/YY): ");
        fgets(expiry, 10, stdin);
        expiry[strcspn(expiry, "\n")] = '\0';

        printf("Enter CVV (3 digits): ");
        fgets(cvv, 5, stdin);
        cvv[strcspn(cvv, "\n")] = '\0';

        printf("\nProcessing payment...\n");
    } else if (choice == 2) {
        char provider[10], mobile_number[15], transaction_id[20];

        printf("\nMOBILE BANKING PAYMENT\n");
        print_line('-', 50);

        printf("Select provider (bKash/Nagad/Rocket): ");
        fgets(provider, 10, stdin);
        provider[strcspn(provider, "\n")] = '\0';

        printf("Enter mobile number (11 digits): ");
        fgets(mobile_number, 15, stdin);
        mobile_number[strcspn(mobile_number, "\n")] = '\0';

        printf("Enter transaction ID: ");
        fgets(transaction_id, 20, stdin);
        transaction_id[strcspn(transaction_id, "\n")] = '\0';

        printf("\nProcessing payment...\n");
    } else {
        printf("Order cancelled.\n");
        press_enter_to_continue();
        return;
    }

    // If payment was successful
    show_receipt(total);
}

void show_receipt(float total) {
    time_t now;
    time(&now);
    struct tm* local = localtime(&now);
    char timestamp[20];
    strftime(timestamp, 20, "%d-%m-%Y %H:%M:%S", local);

    system("clear || cls");
    print_header();
    printf("\nORDER RECEIPT\n");
    printf("==================================================\n");
    printf("Date: %s\n", timestamp);
    printf("Customer: %s\n", current_customer.name);
    printf("Mobile: %s\n", current_customer.number);
    print_line('-', 50);

    for (int i = 0; i < current_customer.cart_size; i++) {
        CartItem item = current_customer.cart[i];
        printf("%s", item.product.name);
        if (strcmp(item.selected_size, "One Size") != 0 && strcmp(item.selected_size, "Free Size") != 0) {
            printf(" (%s)", item.selected_size);
        }
        printf(" x%d\n", item.quantity);
        printf("  %.2f tk\n", item.product.price * item.quantity);
    }

    float discount = total * 0.13;
    float subtotal = total - discount;
    float tax = subtotal * 0.05;
    float grand_total = subtotal + tax;

    print_line('-', 50);
    printf("Subtotal: %.2f tk\n", total);
    printf("Discount (13%%): -%.2f tk\n", discount);
    printf("Tax (5%%): +%.2f tk\n", tax);
    printf("GRAND TOTAL: %.2f tk\n", grand_total);
    printf("==================================================\n");
    printf("Thank you for your purchase!\n");
    printf("Your order will be delivered soon.\n");
    printf("==================================================\n");

    save_purchase_history(total);
    current_customer.cart_size = 0;
    save_customer_data(&current_customer);
    press_enter_to_continue();
}

void save_purchase_history(float total) {
    FILE* file = fopen(HISTORY_FILE, "a");
    if (!file) return;

    time_t now;
    time(&now);
    struct tm* local = localtime(&now);
    char timestamp[20];
    strftime(timestamp, 20, "%d-%m-%Y %H:%M:%S", local);

    fprintf(file, "\n========================================\n");
    fprintf(file, "Customer Details:\n");
    fprintf(file, "Name: %s\n", current_customer.name);
    fprintf(file, "Address: %s\n", current_customer.address);
    fprintf(file, "Birthdate: %s\n", current_customer.birthday);
    fprintf(file, "Gender: %s\n", current_customer.gender);
    fprintf(file, "Mobile: %s\n", current_customer.number);
    fprintf(file, "Email: %s\n", current_customer.email);
    fprintf(file, "\nPurchase History:\n");
    fprintf(file, "Date: %s\n", timestamp);
    fprintf(file, "Items Purchased:\n");

    for (int i = 0; i < current_customer.cart_size; i++) {
        CartItem item = current_customer.cart[i];
        fprintf(file, "- %s", item.product.name);
        if (strcmp(item.selected_size, "One Size") != 0 && strcmp(item.selected_size, "Free Size") != 0) {
            fprintf(file, " (%s)", item.selected_size);
        }
        fprintf(file, " x%d - %.2f tk\n", item.quantity, item.product.price * item.quantity);
    }

    float discount = total * 0.13;
    float subtotal = total - discount;
    float tax = subtotal * 0.05;
    float grand_total = subtotal + tax;

    fprintf(file, "Subtotal: %.2f tk\n", total);
    fprintf(file, "Discount (13%%): -%.2f tk\n", discount);
    fprintf(file, "Tax (5%%): +%.2f tk\n", tax);
    fprintf(file, "GRAND TOTAL: %.2f tk\n", grand_total);
    fprintf(file, "========================================\n");

    fclose(file);
}

void checkout() {
    system("clear || cls");
    print_header();
    printf("\nCHECKOUT\n");
    print_line('-', 50);

    float total = 0.0;
    for (int i = 0; i < current_customer.cart_size; i++) {
        CartItem item = current_customer.cart[i];
        printf("%s", item.product.name);
        if (strcmp(item.selected_size, "One Size") != 0 && strcmp(item.selected_size, "Free Size") != 0) {
            printf(" (%s)", item.selected_size);
        }
        printf(" x%d - %.2f tk\n", item.quantity, item.product.price * item.quantity);
        total += item.product.price * item.quantity;
    }

    float discount = total * 0.13;
    float subtotal = total - discount;
    float tax = subtotal * 0.05;
    float grand_total = subtotal + tax;

    print_line('-', 50);
    printf("Subtotal: %.2f tk\n", total);
    printf("Discount (13%%): -%.2f tk\n", discount);
    printf("Tax (5%%): +%.2f tk\n", tax);
    printf("GRAND TOTAL: %.2f tk\n", grand_total);
    print_line('-', 50);

    printf("\n1. Confirm Order\n");
    printf("2. Cancel\n");
    printf("Enter your choice: ");

    int choice;
    if (scanf("%d", &choice) != 1) {
        printf("Invalid input. Please enter a number.\n");
        clear_input_buffer();
        press_enter_to_continue();
        return;
    }
    clear_input_buffer();

    if (choice == 1) {
        process_payment(total);
    }
}

void create_account() {
    bool valid_input = false;
    char choice;

    printf("\n1. Create New Account\n");
    printf("2. Login with Existing Account\n");
    printf("Enter your choice: ");
    scanf(" %c", &choice);
    clear_input_buffer();

    if (choice == '2') {
        login_account();
        return;
    }

    printf("\nCREATE ACCOUNT\n");
    print_line('-', 50);

    do {
        printf("\nEnter your full name: ");
        fgets(current_customer.name, MAX_NAME_LENGTH, stdin);
        current_customer.name[strcspn(current_customer.name, "\n")] = '\0';
        valid_input = strlen(current_customer.name) > 0;
        if (!valid_input) printf("Name cannot be empty. Please try again.\n");
    } while (!valid_input);

    do {
        printf("Enter your address: ");
        fgets(current_customer.address, 100, stdin);
        current_customer.address[strcspn(current_customer.address, "\n")] = '\0';
        valid_input = strlen(current_customer.address) > 0;
        if (!valid_input) printf("Address cannot be empty. Please try again.\n");
    } while (!valid_input);

    do {
        printf("Enter your birthdate (DD-MM-YYYY): ");
        fgets(current_customer.birthday, 11, stdin);
        current_customer.birthday[strcspn(current_customer.birthday, "\n")] = '\0';
        valid_input = strlen(current_customer.birthday) == 10 &&
                     current_customer.birthday[2] == '-' &&
                     current_customer.birthday[5] == '-';
        if (!valid_input) printf("Invalid date format. Please use DD-MM-YYYY.\n");
    } while (!valid_input);

    do {
        printf("Enter your gender: ");
        fgets(current_customer.gender, 10, stdin);
        current_customer.gender[strcspn(current_customer.gender, "\n")] = '\0';

        char lower_gender[10];
        for(int i = 0; current_customer.gender[i]; i++) {
            lower_gender[i] = tolower(current_customer.gender[i]);
        }
        lower_gender[strlen(current_customer.gender)] = '\0';

        valid_input = (strcmp(lower_gender, "male") == 0 ||
                     strcmp(lower_gender, "female") == 0 ||
                     strcmp(lower_gender, "other") == 0 ||
                     strcmp(lower_gender, "m") == 0 ||
                     strcmp(lower_gender, "f") == 0 ||
                     strcmp(lower_gender, "o") == 0);

        if (!valid_input) {
            printf("\nPlease enter:\n");
            printf("- Male or M\n");
            printf("- Female or F\n");
            printf("- Other or O\n\n");
        } else {
            if (strcmp(lower_gender, "m") == 0) strcpy(current_customer.gender, "Male");
            else if (strcmp(lower_gender, "f") == 0) strcpy(current_customer.gender, "Female");
            else if (strcmp(lower_gender, "o") == 0) strcpy(current_customer.gender, "Other");
            else {
                current_customer.gender[0] = toupper(current_customer.gender[0]);
                for(int i = 1; current_customer.gender[i]; i++) {
                    current_customer.gender[i] = tolower(current_customer.gender[i]);
                }
            }
        }
    } while (!valid_input);

    do {
        printf("Enter mobile number (11 digits, starts with 01): ");
        fgets(current_customer.number, 15, stdin);
        current_customer.number[strcspn(current_customer.number, "\n")] = '\0';
        valid_input = strlen(current_customer.number) == 11 &&
                     current_customer.number[0] == '0' &&
                     current_customer.number[1] == '1';
        if (!valid_input) printf("Invalid phone number. Please enter 11 digits starting with 01.\n");
    } while (!valid_input);

    do {
        printf("Enter your email: ");
        fgets(current_customer.email, 50, stdin);
        current_customer.email[strcspn(current_customer.email, "\n")] = '\0';
        int at_count = 0, dot_count = 0;
        for (int i = 0; current_customer.email[i] != '\0'; i++) {
            if (current_customer.email[i] == '@') at_count++;
            if (current_customer.email[i] == '.') dot_count++;
        }
        valid_input = at_count == 1 && dot_count >= 1 && strlen(current_customer.email) >= 5;
        if (!valid_input) printf("Invalid email format. Please try again.\n");
    } while (!valid_input);

    do {
        printf("Create password (min 6 characters): ");
        fgets(current_customer.password, 50, stdin);
        current_customer.password[strcspn(current_customer.password, "\n")] = '\0';
        valid_input = strlen(current_customer.password) >= 6;
        if (!valid_input) printf("Password must be at least 6 characters.\n");
    } while (!valid_input);

    current_customer.cart_size = 0;

    // Save the new customer data
    if (save_customer_data(&current_customer)) {
        printf("\nAccount Created Successfully!\n");
    } else {
        printf("\nError saving account. Please try again.\n");
    }
    press_enter_to_continue();
}

void login_account() {
    char phone[15];
    char password[50];

    printf("\nLOGIN TO YOUR ACCOUNT\n");
    print_line('-', 50);

    printf("Enter your mobile number: ");
    fgets(phone, 15, stdin);
    phone[strcspn(phone, "\n")] = '\0';

    printf("Enter your password: ");
    fgets(password, 50, stdin);
    password[strcspn(password, "\n")] = '\0';

    if (load_customer_data(phone, &current_customer)) {
        if (strcmp(current_customer.password, password) == 0) {
            printf("\nLogin successful! Welcome back, %s!\n", current_customer.name);
        } else {
            printf("\nIncorrect password. Please try again.\n");
            current_customer.cart_size = 0;
            press_enter_to_continue();
            create_account();
            return;
        }
    } else {
        printf("\nAccount not found. Creating new account.\n");
        press_enter_to_continue();
        create_account();
        return;
    }
    press_enter_to_continue();
}

void show_main_menu() {
    int choice;
    do {
        system("clear || cls");
        print_header();
        printf("\nMAIN MENU\n");
        print_line('-', 50);
        printf("1. Shop\n");
        printf("2. View Cart\n");
        printf("3. Checkout\n");
        printf("4. View Account\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");

        if (scanf("%d", &choice) != 1) {
            printf("Invalid input. Please enter a number.\n");
            clear_input_buffer();
            press_enter_to_continue();
            continue;
        }
        clear_input_buffer();

        switch (choice) {
            case 1:
                show_category_menu();
                break;
            case 2:
                view_cart();
                break;
            case 3:
                if (current_customer.cart_size > 0) checkout();
                else {
                    printf("Your cart is empty!\n");
                    press_enter_to_continue();
                }
                break;
            case 4:
                system("clear || cls");
                print_header();
                printf("\nACCOUNT DETAILS\n");
                print_line('-', 50);
                printf("Name: %s\n", current_customer.name);
                printf("Address: %s\n", current_customer.address);
                printf("Birthdate: %s\n", current_customer.birthday);
                printf("Gender: %s\n", current_customer.gender);
                printf("Mobile: %s\n", current_customer.number);
                printf("Email: %s\n", current_customer.email);
                print_line('-', 50);
                press_enter_to_continue();
                break;
            case 5:
                printf("\nThank you for shopping with us!\n");
                exit(0);
            default:
                printf("Invalid choice. Please try again.\n");
                press_enter_to_continue();
        }
    } while (1);
}

int main() {
    initialize_products();
    print_header();
    printf("               ASSALAMUALAIKUM");
    print_welcome();
    create_account();
    show_main_menu();
    return 0;
}
