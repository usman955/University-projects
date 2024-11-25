#include <iostream>
#include <string>

using namespace std;

class Product {
private:
    int id; 
protected:
    string name;
    int price;
    int quantity;
    string category;

public:
    // Constructor
    Product(int _id, string _name, int _price, int _quantity, string _category)
        : id(_id), name(_name), price(_price), quantity(_quantity), category(_category) {}

    // Display product details
    virtual void Display() const {
        cout << "| " << name << "\t\t" << price << " \t\t" << category << "\t\t" << quantity ;
    }

    // Update selling price
    virtual void UpdateSellingPrice(int newSellingPrice) = 0;

    // Sell products
    virtual void Sell(int soldQuantity) = 0;

    // Handle damage or return
    virtual void HandleDamageOrReturn(int damageQuantity) = 0;

    void setName(const string& newName) {
        name = newName;
    }
    // Set price
    void setPrice(int newPrice) {
        price = newPrice;
    }

    // Set quantity
    void setQuantity(int newQuantity) {
        quantity = newQuantity;
    }

    // Set category
    void setCategory(const string& newCategory) {
        category = newCategory;
    }

    // Set selling price
    void setSellingPrice(int newSellingPrice) {
        // You may implement additional logic here if needed
        price = newSellingPrice;
    }
    // Get category
    string GetCategory() const {
        return category;
    }
    int getID() const {
        return id;
    }
    
};

class SalesReport {
private:
    int count;

public:
    // Constructor
    SalesReport() : count(0) {}

    // Increment sales count
    void IncrementSalesCount() {
        count++;
    }

    // Get sales count
    int GetSalesCount() const {
        return count;
    }
};

class Store {
private:
    static const int MAX_PRODUCTS = 100;
    Product* products[MAX_PRODUCTS];
    int productCount;
    SalesReport salesReport;

public:
    // Constructor
    Store() : productCount(0) {}

    // Add product to store
    void AddProduct(Product* newProduct) {
        if (productCount < MAX_PRODUCTS) {
            products[productCount++] = newProduct;
        } else {
            cout << "Cannot add more products. Store is full." << endl;
        }
    }

    // Display all products in store
    void DisplayProducts() const {
        cout << "Products in Store:" << endl;
        for (int i = 0; i < productCount; ++i) {
            products[i]->Display();
        }
    }

    // Update selling price of all products
   void UpdateSellingPrice(int newSellingPrice) {
    for (int i = 0; i < productCount; ++i) {
        products[i]->UpdateSellingPrice(newSellingPrice);
    }
}

    // Sell products
    void Sell(int productId, int soldQuantity) {
        if (productId >= 0 && productId < productCount) {
            products[productId]->Sell(soldQuantity);
            salesReport.IncrementSalesCount();
        } else {
            cout << endl << "------------- Invalid product ID ---------------" << endl;
        }
    }

    // Display products by category
    void DisplayCategory(string sCategory) const {
        cout << "Products in Category " << sCategory << ":" << endl;
        for (int i = 0; i < productCount; ++i) {
            if (products[i]->GetCategory() == sCategory) {
                products[i]->Display();
            }
        }
    }

    // Get total sales count
    int GetTotalSalesCount() const {
        return salesReport.GetSalesCount();
    }

    // Handle damage or return for a product
    void HandleDamageOrReturn(int productId, int damageQuantity) {
        if (productId >= 0 && productId < productCount) {
            products[productId]->HandleDamageOrReturn(damageQuantity);
        } else {
            cout << endl << "------------- Invalid product ID ---------------" << endl;
        }
    }

    // Find product by ID
    Product* FindProductByID(int ID) const {
        for (int i = 0; i < productCount; ++i) {
            if (products[i]->getID() == ID) {
                return products[i];
            }
        }
        return nullptr; // Product not found
    }

    // Remove product by ID
    void RemoveProduct(int ID) {
        for (int i = 0; i < productCount; ++i) {
            if (products[i]->getID() == ID) {
                delete products[i];
                for (int j = i; j < productCount - 1; ++j) {
                    products[j] = products[j + 1];
                }
                productCount--;
                cout << "--------------- Product with ID " << ID << " removed successfully ------------" << endl;
                return;
            }
        }
        cout << "----------------- Product with ID " << ID << " not found --------------" << endl;
    }

    // Print receipt
    void PrintReceipt() {
        // Implement this method according to your requirements
        cout << "------------------- Receipt printed -------------------" << endl;
    }
    // Get product count
    int getProductCount() const {
        return productCount;
    }
};

class Admin {
private:
    string username;
    string password;

public:
    // Constructor
    Admin(const string& u, const string& p) : username(u), password(p) {}

    // Authenticate admin
    bool Authenticate(const string& u, const string& p) const {
        return (username == u && password == p);
    }

    // Get username
    string GetUsername() const {
        return username;
    }

    // Get password
    string GetPassword() const {
        return password;
    }

    // Set password
    void SetPassword(const string& newPass) {
        password = newPass;
    }
};

class ProductDetails : public Product {
private:
    int selling;
    int totalAmount;
    int profit;

public:
    // Constructor
    ProductDetails(string p_name, int p_price, string p_category, int p_quantity, int p_selling, int p_profit)
        : Product(0, p_name, p_price, p_quantity, p_category), selling(p_selling), profit(p_profit) {
        totalAmount = price * quantity;
    }
   void setprofit(int profit){
	this->profit=profit;
}
    // Display product details
    void Display() const override {
    	cout << "\t\t _________________________________________________________________________________________\n";
        cout << "\t\t|  Name     Buying Price    Selling Price     Category         Quantity            Profit |\n";
        cout << "\t\t|_________________________________________________________________________________________|\n";
        cout << "\t\t|  " << name << "\t\t" << price << " \t\t" << selling << "\t\t" << category << "\t\t" << quantity << "\t\t   " << profit << "     |\n";
        cout << "\t\t|_________________________________________________________________________________________|\n";
    }

    // Update selling price
    void UpdateSellingPrice(int newSellingPrice) override {
        selling = newSellingPrice;
        profit = (selling - price) * quantity;
    }

    // Sell products
    void Sell(int soldQuantity) override {
        if (soldQuantity <= quantity) {
            quantity -= soldQuantity;
            totalAmount -= (selling * soldQuantity);
            profit -= (selling - price) * soldQuantity;
        } else {
            cout << endl << "----------- Insufficient stock ------------" << endl;
        }
    }

    // Handle damage or return
    void HandleDamageOrReturn(int damageQuantity) override {
        if (damageQuantity <= quantity) {
            quantity -= damageQuantity;
            totalAmount -= (selling * damageQuantity);
            profit -= (selling - price) * damageQuantity;
        } else {
            cout << "-------------- Invalid quantity for damage or return ------------------" << endl;
        }
    }
};

int main() {
    Admin admin("Admin", "Admin");
    Store store;

    string user_name;
    string password;

    do {
    cout << "\t\t\t\t\t _____________________________________\n";
    cout << "\t\t\t\t\t|              Username               |\n";
    cout << "\t\t\t\t\t|-------------------------------------|\n";
    cout << "\t\t\t\t\t|\t\t";
    getline(cin, user_name);
    cout << "\t\t\t\t\t|-------------------------------------|\n";
    cout << "\t\t\t\t\t|              Password               |\n";
    cout << "\t\t\t\t\t|-------------------------------------|\n";
    cout << "\t\t\t\t\t|\t\t";
    getline(cin, password);
    cout << "\t\t\t\t\t|_____________________________________|\n";

        if (admin.Authenticate(user_name, password)) {
            cout << "\n\t\t\t\t\tWelcome to General Store Management System\n";

            int user_choice;
            do {
            	cout << "\t\t\t\t\t _____________________________________\n";
            	cout << "\t\t\t\t\t|                                     |\n";
                cout << "\t\t\t\t\t|  1 : ADD PRODUCT                    |\n";
                cout << "\t\t\t\t\t|  2 : UPDATE PRODUCT                 |\n";
                cout << "\t\t\t\t\t|  3 : DISPLAY CATEGORY               |\n";
                cout << "\t\t\t\t\t|  4 : DISPLAY PRODUCTS               |\n";
                cout << "\t\t\t\t\t|  5 : REMOVE PRODUCT                 |\n";
                cout << "\t\t\t\t\t|  6 : REPORTS                        |\n";
                cout << "\t\t\t\t\t|  7 : RECEIPT                        |\n";
                cout << "\t\t\t\t\t|  8 : DAMAGE/RETURN                  |\n";
                cout << "\t\t\t\t\t|  9 : CHANGE PASSWORD                |\n";
                cout << "\t\t\t\t\t|  0 : LOG OUT                        |\n";
                cout << "\t\t\t\t\t|_____________________________________|\n";
                cout << "Select Option : ";
                cin >> user_choice;
                cout<<endl;
                switch (user_choice) {
    case 1: {
        // Code for adding a product
        string name;
        int price;
        string category;
        char choice;
        int quantity;
        int totalAmount;
        int profit;
        int selling;
        do {
            cout << "\nEnter Product Name : ";
            cin.ignore();
            getline(cin, name);
            cout << "Enter Buying Price of Product : ";
            cin >> price;
            cout << "Enter the Selling Price of Product : ";
            cin >> selling;
            cout << "Enter Category of Product : ";
            cin.ignore();
            getline(cin, category);
            cout << "Enter Stock of Product : ";
            cin >> quantity;
            totalAmount = quantity * price;
            profit = (selling - price) * quantity;
            ProductDetails* new_product = new ProductDetails(name, price, category, quantity, selling, profit);
            store.AddProduct(new_product);
            cout << endl << "Do you want to Add another Product : y/n : ";
            cin >> choice;
        } while (choice == 'y' || choice == 'Y');
        break;
    }
    case 2: {
        // Code for updating a product
        int ID;
        cout << endl << "Enter the ID OF product : ";
        cin >> ID;
        // Search for the product with the given ID
        Product* productToUpdate = store.FindProductByID(ID);
        if (productToUpdate != nullptr) {
            // Display options to update product details
            int choice5;
            do {
                cout << "\t\t\t\t\t _____________________________________\n";
                cout << "\t\t\t\t\t|                                     |\n";
                cout << "\t\t\t\t\t| PRESS 1 : TO CHANGE NAME            |\n";
                cout << "\t\t\t\t\t| PRESS 2 : TO CHANGE BUYING PRICE    |\n";
                cout << "\t\t\t\t\t| PRESS 3 : TO CHANGE QUANTITY        |\n";
                cout << "\t\t\t\t\t| PRESS 4 : TO CHANGE CATEGORY        |\n";
                cout << "\t\t\t\t\t| Press 5 : To CHANGE SELLING PRICE   |\n";
				cout << "\t\t\t\t\t| PRESS 0 : BACK                      |\n";
                cout << "\t\t\t\t\t|_____________________________________|\n";
                cout << endl;
                cout << "Select Option : ";
                cin >> choice5;
                // Update product details based on user's choice
                switch (choice5) {
                    case 1: {
                        string new_name;
                        cout << "Enter New Name : ";
                        cin.ignore();
                        getline(cin, new_name);
                        productToUpdate->setName(new_name);
                        break;
                    }
                    case 2: {
                        int new_price;
                        cout << "Enter New Price : ";
                        cin >> new_price;
                        productToUpdate->setPrice(new_price);
                        break;
                    }
                    case 3: {
                        int stock;
                        cout << "Enter New Stock : ";
                        cin >> stock;
                        productToUpdate->setQuantity(stock);
                        break;
                    }
                    case 4: {
                        string new_category;
                        cout << "Enter New Category : ";
                        cin.ignore();
                        getline(cin, new_category);
                        productToUpdate->setCategory(new_category);
                        break;
                    }
                    case 5: {
                        int new_sellprice;
                        cout << "Enter New Selling Price of Product : ";
                        cin >> new_sellprice;
                        productToUpdate->setSellingPrice(new_sellprice);
                        break;
                    }
                    case 6: {
                    	int newProfit;
                    	cout<<(new_sellprice-new_price)*new_price;
                    	productToUpdate->UpdateSellingPrice(new_sellprice);
						break;
					}
                    case 0: {
                        break; // Go back
                    }
                    default: {
                        cout << "Invalid Data : Please Try Again !!" << endl;
                        break;
                    }
                }
            } while (choice5 != 0);
        } else {
            cout << "\nProduct not found with the given ID!!\n";
        }
        break;
    }
    case 3: {
        // Code for displaying products by category
        string s_category;
        cout << "Enter Category to Display: ";
        cin.ignore();
        getline(cin, s_category);
        store.DisplayCategory(s_category);
        break;
    }
    case 4: {
        // Code for displaying all products
        store.DisplayProducts();
        break;
    }
    case 5: {
        // Code for removing a product
        char choice4;
        do {
            if (store.getProductCount() > 0) {
                store.DisplayProducts();
                int id;
                cout << "Enter ID of Product : ";
                cin >> id;
                char choice6;
                cout << "Confirm TO Delete The Product : Y/N : ";
                cin >> choice6;
                if (choice6 == 'y' || choice6 == 'Y') {
                    store.RemoveProduct(id);
                }
                else if (choice6 == 'n' || choice6 == 'N') {
                    break;
                }
                else {
                    cout << "\nInvalid Data : Please Try Again !!\n";
                }
            }
            else {
                 cout <<endl << "------------ No Product Added Yet ------------" << endl;
                break;
            }
            cout << "Do you want to remove another product : y/n : ";
            cin >> choice4;
        } while (choice4 == 'y' || choice4 == 'Y');
        break;
    }
    case 6: {
        // Code for generating reports
        cout << "Total Sales Count: " << store.GetTotalSalesCount() << endl;
        break;
    }
    case 7: {
        // Code for generating receipt
        if (store.getProductCount() > 0) {
            char select;
            store.DisplayProducts();
            do {
                int id;
                int quantity;
                cout << "Enter the product id : ";
                cin >> id;
                cout << "Enter the quantity : ";
                cin >> quantity;
                store.Sell(id, quantity);
                cout << endl << "Do you want to add another product to cart : ";
                cin >> select;
            } while (select == 'y' || select == 'Y');
            cout << "\nReceipt:\n";
            store.PrintReceipt();
        }
        else {
            cout <<endl << "------------ No Product Added Yet ------------" << endl;
        }
        break;
    }
    case 8: {
        // Code for handling damage/return
        if (store.getProductCount() > 0) {
            int id;
            int quantity;
            int choice7;
            do {
                cout << "\t\t\t\t\t _______________________________ \n";
                cout << "\t\t\t\t\t|                               |\n";
                cout << "\t\t\t\t\t| PRESS 1 : Return Products     |\n";
                cout << "\t\t\t\t\t| PRESS 2 : Damage Products     |\n";
                cout << "\t\t\t\t\t| PRESS 0 : Back                |\n";
                cout << "\t\t\t\t\t|_______________________________|\n";
                cout << endl;
                cout << "Select Option : ";
                cin >> choice7;
                if (choice7 == 1 || choice7 == 2) {
                    store.DisplayProducts();
                    cout << endl << "Enter ID of Product : ";
                    cin >> id;
                    cout << "Enter Quantity : ";
                    cin >> quantity;
                    cout << endl;
                    store.HandleDamageOrReturn(id, quantity);
                }
                else if (choice7 == 0) {
                    break;
                }
                else {
                    cout << "------------------- Invalid Data ------------------";
                }
            } while (choice7 != 0);
        }
        else {
             cout <<endl << "------------ No Product Added Yet ------------" << endl;
        }
        break;
    }
    case 9: {
        // Code for changing password
        string new_pass;
        cout << "Enter New Password : ";
        cin >> new_pass;
        admin.SetPassword(new_pass);
        cout << "Password Changed Successfully.\n";
        break;
    }
    case 0: {
        // Code for logging out
        cout << "Logging out...\n";
        break;
    }
    default: {
        cout << "\nInvalid Option : Please Try again !!\n";
        break;
    }
}

            } while (user_choice != 0);
        } else {
            cout << "\nPlease Try Again !! \n";
        }
    } while (user_name != admin.GetUsername() && password != admin.GetPassword());
    cout << "\nThank You for Using Our Program.\n";

    return 0;
}
