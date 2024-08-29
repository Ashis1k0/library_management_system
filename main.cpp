#include <bits/stdc++.h>
using namespace std;

class Book {
public:
    int AccNo;
    string title;
    string author;
    int price;
    int copies;

    Book(int accNo, const string& t, const string& a, int p, int c)
        : AccNo(accNo), title(t), author(a), price(p), copies(c) {}

    void showDetails() {
        cout << "Accession Number: " << AccNo << endl;
        cout << "Title: " << title << endl;
        cout << "Author: " << author << endl;
        cout << "Price: " << price << endl;
        cout << "Available Copies: " << copies << endl;
    }
};

class Student {
public:
    int regdNo;
    string name;
    vector<int> issuedBooks;

    Student(int r, const string& n) : regdNo(r), name(n) {}

    void showDetails() {
        cout << "Registration Number: " << regdNo << endl;
        cout << "Name: " << name << endl;
        cout << "Books Issued: " << issuedBooks.size() << endl;
        if (!issuedBooks.empty()) {
            cout << "Accession Numbers of Books Issued: ";
            for (int accNo : issuedBooks) {
                cout << accNo << " ";
            }
            cout << endl;
        }
    }

    void issueBook(int accNo) {
        issuedBooks.push_back(accNo);
    }

    void returnBook(int accNo) {
        issuedBooks.erase(remove(issuedBooks.begin(), issuedBooks.end(), accNo), issuedBooks.end());
    }
};

class Library {
    vector<Book> books;
    vector<Student> students;

    template <typename T>
    T getValidInput(const string& prompt) {
        T value;
        while (true) {
            cout << prompt;
            if (cin >> value) {
                break;
            } else {
                cout << "Invalid input. Please enter a valid " << typeid(T).name() << "." << endl;
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }
        }
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        return value;
    }

public:
    void addBook() {
        char choice = 'n';
        cout << "Do you want to add a new book or add copies to an existing book? (N for new, E for existing): ";
        cin >> choice;
        cin.ignore();

        if (choice == 'N' || choice == 'n') {
            int accNo = getValidInput<int>("Enter Accession Number: ");
            cout << "Enter Title: ";
            string title;
            getline(cin, title);
            cout << "Enter Author: ";
            string author;
            getline(cin, author);
            int price = getValidInput<int>("Enter Price: ");
            int copies = getValidInput<int>("Enter Number of Copies: ");
            books.push_back(Book(accNo, title, author, price, copies));
        } else if (choice == 'E' || choice == 'e') {
            int accNo = getValidInput<int>("Enter Accession Number of the book: ");
            int copies = getValidInput<int>("Enter Number of Copies to add: ");
            bool found = false;
            for (Book& book : books) {
                if (book.AccNo == accNo) {
                    book.copies += copies;
                    found = true;
                    cout << "Added " << copies << " copies to the book with Accession Number " << accNo << "." << endl;
                    break;
                }
            }
            if (!found) {
                cout << "Book with Accession Number " << accNo << " not found." << endl;
            }
        } else {
            cout << "Invalid option selected." << endl;
        }
    }

    void addStudent() {
        int regdNo = getValidInput<int>("Enter Registration Number: ");
        cout << "Enter Name: ";
        string name;
        getline(cin, name);
        students.push_back(Student(regdNo, name));
    }

    void issueBook() {
        int accNo = getValidInput<int>("Enter Accession Number: ");
        int regdNo = getValidInput<int>("Enter Registration Number: ");
        bool bookFound = false;
        bool studentFound = false;

        for (Book& book : books) {
            if (book.AccNo == accNo) {
                bookFound = true;
                if (book.copies > 0) {
                    for (Student& student : students) {
                        if (student.regdNo == regdNo) {
                            student.issueBook(accNo);
                            book.copies--;
                            cout << "Book issued successfully to student " << regdNo << "." << endl;
                            studentFound = true;
                            break;
                        }
                    }
                    if (!studentFound) {
                        cout << "The Registration Number is invalid." << endl;
                    }
                } else {
                    cout << "Book is available in the library, but no copies are left." << endl;
                }
                break;
            }
        }
        if (!bookFound) {
            cout << "The book is not available in the library." << endl;
        }
    }

    void returnBook() {
        int accNo = getValidInput<int>("Enter Accession Number: ");
        int regdNo = getValidInput<int>("Enter Registration Number: ");
        bool bookFound = false;
        bool studentFound = false;

        for (Book& book : books) {
            if (book.AccNo == accNo) {
                bookFound = true;
                for (Student& student : students) {
                    if (student.regdNo == regdNo) {
                        student.returnBook(accNo);
                        book.copies++;
                        cout << "Book returned successfully by student " << regdNo << "." << endl;
                        studentFound = true;
                        break;
                    }
                }
                if (!studentFound) {
                    cout << "The Registration Number is invalid." << endl;
                }
                break;
            }
        }
        if (!bookFound) {
            cout << "The book is not available in the library." << endl;
        }
    }

    void showDetails() {
        int choice = getValidInput<int>("1. Show Student Details\n2. Show Book Details\nEnter your choice: ");

        if (choice == 1) {
            int regdNo = getValidInput<int>("Enter Registration Number: ");
            bool studentFound = false;
            for (Student& student : students) {
                if (student.regdNo == regdNo) {
                    student.showDetails();
                    studentFound = true;
                    break;
                }
            }
            if (!studentFound) {
                cout << "Student not found. Please add the student or check the registration number." << endl;
            }
        } else if (choice == 2) {
            int accNo = getValidInput<int>("Enter Accession Number: ");
            bool bookFound = false;
            for (Book& book : books) {
                if (book.AccNo == accNo) {
                    book.showDetails();
                    bookFound = true;
                    break;
                }
            }
            if (!bookFound) {
                cout << "Book not found." << endl;
            }
        } else {
            cout << "Invalid option selected." << endl;
        }
    }

    void menu() {
        int choice;
        do {
            cout << "1. Add new Book\n2. Add new Student\n3. Issue Book\n4. Return Book\n5. Show Details\n6. Exit\n";
            choice = getValidInput<int>("Enter your choice: ");
            switch (choice) {
                case 1:
                    addBook();
                    break;
                case 2:
                    addStudent();
                    break;
                case 3:
                    issueBook();
                    break;
                case 4:
                    returnBook();
                    break;
                case 5:
                    showDetails();
                    break;
                case 6:
                    cout << "Exiting..." << endl;
                    break;
                default:
                    cout << "Invalid input." << endl;
                    break;
            }
        } while (choice != 6);
    }
};

int main() {
    Library lib;
    lib.menu();
    return 0;
}
