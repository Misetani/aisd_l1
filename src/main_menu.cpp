#include <iostream>
#include <limits> // for numeric_limits
#include <cstdlib> // for cin.ignore

#include "../list.h"
#include "../array_exception.h"

namespace Color {
    const std::string RESET = "\033[0m";
    const std::string BLACK = "\033[30m";
    const std::string RED = "\033[31m";
    const std::string GREEN = "\033[32m";
    const std::string YELLOW = "\033[33m";
    const std::string BLUE = "\033[34m";
    const std::string MAGENTA = "\033[35m";
    const std::string CYAN = "\033[36m";
    const std::string WHITE = "\033[37m";
    const std::string BOLD_BLACK = "\033[1m\033[30m";
    const std::string BOLD_RED = "\033[1m\033[31m";
    const std::string BOLD_GREEN = "\033[1m\033[32m";
    const std::string BOLD_YELLOW = "\033[1m\033[33m";
    const std::string BOLD_BLUE = "\033[1m\033[34m";
    const std::string BOLD_MAGENTA = "\033[1m\033[35m";
    const std::string BOLD_CYAN = "\033[1m\033[36m";
    const std::string BOLD_WHITE = "\033[1m\033[37m";
}

template <typename T>
void run_menu();

void main_menu();

int main() {
    main_menu();

    return 0;
}

int get_choice(int min, int max) {
    int choice;
    while (true) {
        std::cout << Color::BOLD_GREEN << "Enter your choice: " << Color::RESET;
        if (std::cin >> choice && choice >= min && choice <= max) {
            break;
        } else {
            std::cout << Color::BOLD_RED << "Invalid input. Please enter a number between " 
                << min << " and " << max << "." << Color::RESET << std::endl;
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
    }
    return choice;
}

void print_element(const std::string& message) {
    std::cout << Color::BOLD_BLUE << message.substr(0, 1) << Color::RESET;
    std::cout << message.substr(1, message.length() - 2);
    std::cout << Color::BOLD_BLUE << message.substr(message.length() - 1, 1) << Color::RESET;
    std::cout << std::endl;
}

void print_menu() {
    using std::cout;
    using std::endl;

    cout << "\n";
    cout << Color::BOLD_BLUE << "+--------------------------+" << Color::RESET << endl;
    cout << Color::BOLD_BLUE << "|" << Color::BOLD_BLACK 
        << " List Menu                " << Color::BOLD_BLUE << "|" << Color::RESET << endl;
    cout << Color::BOLD_BLUE << "+--------------------------+" << Color::RESET << endl;
    print_element("| 1. Append                |");
    print_element("| 2. Insert                |");
    print_element("| 3. Remove                |");
    print_element("| 4. Clear                 |");
    print_element("| 5. Print                 |");
    print_element("| 6. Get Size              |");
    print_element("| 7. Get Value at Index    |");
    print_element("| 8. Set Value at Index    |");
    print_element("| 9. Check if Value Exists |");
    print_element("| 10. Get Index of Value   |");
    print_element("| 0. Exit                  |");
    cout << Color::BOLD_BLUE << "+--------------------------+" << Color::RESET << endl;
}

void print_main_menu() {
    using std::cout;
    using std::endl;

    cout << "\n";
    cout << Color::BOLD_BLUE << "+--------------------------+" << Color::RESET << endl;
    cout << Color::BOLD_BLUE << "|" << Color::BOLD_BLACK 
        << " Main Menu                " << Color::BOLD_BLUE << "|" << Color::RESET << endl;
    cout << Color::BOLD_BLUE << "+--------------------------+" << Color::RESET << endl;

    print_element("| 1. Int                   |");
    print_element("| 2. Double                |");
    print_element("| 3. String                |");
    print_element("| 0. Exit                  |");
    cout << Color::BOLD_BLUE << "+--------------------------+" << Color::RESET << endl;
}

void main_menu() {
    int choice { 0 };

    while (true) {
        print_main_menu();
        choice = get_choice(0, 3);

        switch (choice) {
            case 0:
                std::cout << Color::BOLD_BLACK << "Exiting..." << Color::BOLD_BLACK << std::endl;
                return;
            case 1:
                run_menu<int>();
                break;
            case 2:
                run_menu<double>();
                break;
            case 3:
                run_menu<std::string>();
                break;
            default:
                std::cout << Color::BOLD_RED << "Invalid choice." << Color::RESET << std::endl;
                break;
        }
    }
}

template <typename T>
void run_menu() {
    using namespace std;

    List<T> myList;
    int choice { 0 };

    while (true) {
        print_menu();
        choice = get_choice(0, 10);

        switch (choice) {
            case 1: {
                T value;
                cout << "Enter value to append: ";
                cin >> value;
                myList.append(value);
                cout << "Value appended to the list." << endl;
                break;
            }
            case 2: {
                int index;
                T value;
                cout << "Enter index to insert: ";
                cin >> index;
                cout << "Enter value to insert: ";
                cin >> value;
                if (myList.insert(index, value)) {
                    cout << "Value inserted at index " << index << "." << endl;
                } else {
                    cout << Color::BOLD_RED << "Invalid index." << Color::RESET << endl;
                }
                break;
            }
            case 3: {
                T value;
                cout << "Enter value to remove: ";
                cin >> value;
                if (myList.remove(value)) {
                    cout << "Value removed from the list." << endl;
                } else {
                    cout << Color::BOLD_RED << "Value not found in the list." << Color::RESET << endl;
                }
                break;
            }
            case 4: {
                myList.clear();
                cout << "List cleared." << endl;
                break;
            }
            case 5: {
                myList.print();
                break;
            }
            case 6: {
                int size = myList.get_size();
                cout << "List size: " << size << endl;
                break;
            }
            case 7: {
                int index;
                cout << "Enter index: ";
                cin >> index;
                try {
                    T value = myList.get(index);
                    cout << "Value at index " << index << ": " << value << endl;
                } catch (const Array_exception& e) {
                    cout << Color::BOLD_RED << "Error: " << e.get_error() << Color::RESET << endl;
                }
                break;
            }
            case 8: {
                int index;
                T value;
                cout << "Enter index: ";
                cin >> index;
                cout << "Enter value: ";
                cin >> value;
                if (myList.set(index, value)) {
                    cout << "Value set at index " << index << "." << endl;
                } else {
                    cout << Color::BOLD_RED << "Invalid index." << Color::RESET << endl;
                }
                break;
            }
            case 9: {
                T value;
                cout << "Enter value to check: ";
                cin >> value;
                if (myList.contains(value)) {
                    cout << "Value exists in the list." << endl;
                } else {
                    cout << "Value does not exist in the list." << endl;
                }
                break;
            }
            case 10: {
                T value;
                cout << "Enter value to get index: ";
                cin >> value;
                int index = myList.index_of(value);
                if (index != -1) {
                    cout << "Index of value " << value << ": " << index << endl;
                } else {
                    cout << Color::BOLD_RED << "Value not found in the list." << Color::RESET << endl;
                }
                break;
            }
            case 0:
                cout << Color::BOLD_BLACK << "Exiting..." << Color::BOLD_BLACK << endl;
                return;
            default:
                cout << Color::BOLD_RED << "Invalid choice." << Color::RESET << endl;
        }
    }
}