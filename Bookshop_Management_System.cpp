#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

// ------------------ Book Class ------------------
class Book
{
private:
    string author, title, publisher;
    float price;
    int stock;

public:
    Book() {}
    Book(string t, string a, string p, float pr, int s) : title(t), author(a), publisher(p), price(pr), stock(s) {}

    void feedData();
    void editData();
    void showData();
    void displayShelf();
    bool search(const string &t, const string &a);
    void buyBook();
    string getTitle() { return title; }
    string getAuthor() { return author; }
    string getPublisher() { return publisher; }
    float getPrice() { return price; }
    int getStock() { return stock; }
    void saveToFile(ofstream &fout);
    static Book *loadFromFile(ifstream &fin);
};

void Book::feedData()
{
    cin.ignore();
    cout << "\nEnter Author Name: ";
    getline(cin, author);
    cout << "Enter Title Name: ";
    getline(cin, title);
    cout << "Enter Publisher Name: ";
    getline(cin, publisher);
    cout << "Enter Price: ";
    cin >> price;
    cout << "Enter Stock Position: ";
    cin >> stock;
}

void Book::editData()
{
    cin.ignore();
    cout << "\nEdit Author Name: ";
    getline(cin, author);
    cout << "Edit Title Name: ";
    getline(cin, title);
    cout << "Edit Publisher Name: ";
    getline(cin, publisher);
    cout << "Edit Price: ";
    cin >> price;
    cout << "Edit Stock Position: ";
    cin >> stock;
}

void Book::showData()
{
    cout << "\n===============================";
    cout << "\nTitle: " << title;
    cout << "\nAuthor: " << author;
    cout << "\nPublisher: " << publisher;
    cout << "\nPrice: $" << price;
    cout << "\nStock: " << stock;
    cout << "\n===============================";
}

void Book::displayShelf()
{
    cout << "\n[ " << title << " | " << author << " | $" << price << " | Stock: " << stock << " ]";
}

bool Book::search(const string &t, const string &a)
{
    return (t == title && a == author);
}

void Book::buyBook()
{
    int count;
    cout << "\nEnter number of books to buy: ";
    cin >> count;

    if (count <= stock)
    {
        stock -= count;
        cout << "\nBooks Bought Successfully!";
        cout << "\nAmount: $" << price * count;
        if (stock < 3)
        {
            cout << "\nNote: Stock is low (" << stock << " remaining). Consider restocking.";
        }
    }
    else
    {
        cout << "\nNot enough copies in stock!";
    }
}

void Book::saveToFile(ofstream &fout)
{
    fout << title << '\n'
         << author << '\n'
         << publisher << '\n'
         << price << '\n'
         << stock << '\n';
}

Book *Book::loadFromFile(ifstream &fin)
{
    string t, a, p;
    float pr;
    int s;
    if (getline(fin, t) && getline(fin, a) && getline(fin, p) && fin >> pr >> s)
    {
        fin.ignore(); // consume newline
        return new Book(t, a, p, pr, s);
    }
    return nullptr;
}

// ------------------ User Management ------------------
bool userExists(const string &uname)
{
    ifstream fin("users.txt");
    string fileU, fileP, fileR;
    while (fin >> fileU >> fileP >> fileR)
    {
        if (fileU == uname)
            return true;
    }
    return false;
}

void registerUser()
{
    string uname, pass, role;

    cout << "\n--- User Registration ---";
    cout << "\nChoose username: ";
    cin >> uname;

    if (userExists(uname))
    {
        cout << "Username already exists. Please try another.\n";
        return;
    }

    cout << "Choose password: ";
    cin >> pass;

    cout << "Select role (admin/customer): ";
    cin >> role;

    if (role != "admin" && role != "customer")
    {
        cout << "Invalid role. Choose either 'admin' or 'customer'.\n";
        return;
    }

    ofstream fout("users.txt", ios::app);
    fout << uname << " " << pass << " " << role << "\n";
    fout.close();

    cout << "\nUser registered successfully! You can now login.\n";
}

bool login(string &role)
{
    string uname, pass, fileU, fileP, fileR;
    cout << "\n--- Login ---";
    cout << "\nUsername: ";
    cin >> uname;
    cout << "Password: ";
    cin >> pass;

    ifstream fin("users.txt");
    while (fin >> fileU >> fileP >> fileR)
    {
        if (fileU == uname && fileP == pass)
        {
            role = fileR;
            cout << "\nLogin successful as " << role << "!\n";
            return true;
        }
    }
    cout << "\nLogin failed. Invalid credentials.\n";
    return false;
}

// ------------------ Book File Helpers ------------------
void saveAllBooks(const vector<Book *> &books)
{
    ofstream fout("books.txt");
    for (auto b : books)
        b->saveToFile(fout);
    fout.close();
}

void loadAllBooks(vector<Book *> &books)
{
    ifstream fin("books.txt");
    Book *b;
    while ((b = Book::loadFromFile(fin)))
    {
        books.push_back(b);
    }
    fin.close();
}

bool compareByTitle(Book *a, Book *b)
{
    return a->getTitle() < b->getTitle();
}

// ------------------ Admin Menu ------------------
void menuAdmin(vector<Book *> &library)
{
    int choice;
    string titleSearch, authorSearch;
    do
    {
        cout << "\n\n ==== Admin Menu ==== \n";
        cout << "1. Add New Book\n"
             << "2. Display All Books\n"
             << "3. Buy Book\n"
             << "4. Search Book\n"
             << "5. Edit Book\n"
             << "6. Remove Book\n"
             << "7. Sort by Title\n"
             << "8. Search by Price Range\n"
             << "9. Save & Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
        {
            Book *b = new Book();
            b->feedData();
            library.push_back(b);
            break;
        }
        case 2:
            for (auto b : library)
                b->displayShelf();
            break;
        case 3:
            cin.ignore();
            cout << "\nTitle: ";
            getline(cin, titleSearch);
            cout << "Author: ";
            getline(cin, authorSearch);
            for (auto b : library)
            {
                if (b->search(titleSearch, authorSearch))
                {
                    b->buyBook();
                    break;
                }
            }
            break;
        case 4:
            cin.ignore();
            cout << "\nTitle: ";
            getline(cin, titleSearch);
            cout << "Author: ";
            getline(cin, authorSearch);
            for (auto b : library)
            {
                if (b->search(titleSearch, authorSearch))
                {
                    b->showData();
                    break;
                }
            }
            break;
        case 5:
            cin.ignore();
            cout << "\nTitle: ";
            getline(cin, titleSearch);
            cout << "Author: ";
            getline(cin, authorSearch);
            for (auto b : library)
            {
                if (b->search(titleSearch, authorSearch))
                {
                    b->editData();
                    break;
                }
            }
            break;
        case 6:
            cin.ignore();
            cout << "\nTitle: ";
            getline(cin, titleSearch);
            cout << "Author: ";
            getline(cin, authorSearch);
            for (auto it = library.begin(); it != library.end(); ++it)
            {
                if ((*it)->search(titleSearch, authorSearch))
                {
                    delete *it;
                    library.erase(it);
                    cout << "\nBook removed.";
                    break;
                }
            }
            break;
        case 7:
            sort(library.begin(), library.end(), compareByTitle);
            cout << "\nSorted alphabetically.";
            break;
        case 8:
        {
            float minP, maxP;
            cout << "\nMin Price: ";
            cin >> minP;
            cout << "Max Price: ";
            cin >> maxP;
            for (auto b : library)
            {
                if (b->getPrice() >= minP && b->getPrice() <= maxP)
                    b->displayShelf();
            }
            break;
        }
        case 9:
            saveAllBooks(library);
            cout << "\nBooks saved. Goodbye!\n";
            for (auto b : library)
                delete b;
            exit(0);
        default:
            cout << "\nInvalid choice.";
        }
    } while (true);
}

// ------------------ Customer Menu ------------------
void menuCustomer(vector<Book *> &library)
{
    int choice;
    string titleSearch, authorSearch;
    do
    {
        cout << "\n\n ==== Customer Menu ==== \n";
        cout << "1. View Books\n"
             << "2. Buy Book\n"
             << "3. Search Book\n"
             << "4. Search by Price Range\n"
             << "5. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
            for (auto b : library)
                b->displayShelf();
            break;
        case 2:
            cin.ignore();
            cout << "\nTitle: ";
            getline(cin, titleSearch);
            cout << "Author: ";
            getline(cin, authorSearch);
            for (auto b : library)
            {
                if (b->search(titleSearch, authorSearch))
                {
                    b->buyBook();
                    break;
                }
            }
            break;
        case 3:
            cin.ignore();
            cout << "\nTitle: ";
            getline(cin, titleSearch);
            cout << "Author: ";
            getline(cin, authorSearch);
            for (auto b : library)
            {
                if (b->search(titleSearch, authorSearch))
                {
                    b->showData();
                    break;
                }
            }
            break;
        case 4:
        {
            float minP, maxP;
            cout << "\nMin Price: ";
            cin >> minP;
            cout << "Max Price: ";
            cin >> maxP;
            for (auto b : library)
            {
                if (b->getPrice() >= minP && b->getPrice() <= maxP)
                    b->displayShelf();
            }
            break;
        }
        case 5:
            cout << "\nGoodbye!\n";
            for (auto b : library)
                delete b;
            exit(0);
        default:
            cout << "\nInvalid choice.";
        }
    } while (true);
}

// ------------------ Main ------------------
int main()
{
    vector<Book *> library;
    loadAllBooks(library);

    string role;
    int authChoice;

    cout << "\n Welcome to Book Shop Management System \n";
    cout << "1. Login\n2. Register\nChoose option: ";
    cin >> authChoice;

    if (authChoice == 2)
    {
        registerUser();
        cout << "\nNow login to continue.\n";
    }

    if (!login(role))
        return 0;

    if (role == "admin")
        menuAdmin(library);
    else
        menuCustomer(library);

    return 0;
}
