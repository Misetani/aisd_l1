#ifndef LIST_H
#define LIST_H

#include <cstddef>
#include <iostream>

// Структура данных – кольцевая, односвязная, на базе адресных
// указателей, с использованием фиктивного элемента.

template <typename T>
class List {
private:
    struct Node {
        T data;
        Node *next;
        Node () {}
        Node(const T& value) : data(value), next(nullptr) {}
    };

    int size{ 0 };
    Node nil; // Барьерный узел

public:
    /**
     * @brief Конструтор по умолчанию
    */
    List() { 
        std::cout << "I am a constructor!\n";
        nil.next = &nil; }

    /**
     * @brief Конструктор копирования
    */
    List(const List<T>& other);

    /**
     * @brief Опрос размера списка
    */
    int get_size() const;

    /**
     * @brief Очистка списка
    */
    void clear();

    /**
     * @brief Проверка списка на пустоту
    */
    bool isEmpty() const;

    /**
     * @brief Проверка наличия заданного значения
    */
    bool contains(const T& value) const;

    /**
     * @brief Получение значения с заданным номером в списке
    */
    T get(int index);

    /**
     * @brief Установка значения с заданным номером в списке
    */
    bool set(int index, const T& value);

    /**
     * @brief Получение позиции в списке для заданного значения
    */
    int indexOf(const T& value) const;

    /**
     * @brief Включение нового значения в конец списка
    */
    void append(const T& value);

    /**
     * @brief Включение нового значения в позицию с заданным номером
    */
    void insert(int index, const T& value);

    /**
     * @brief Удаление заданного значения из списка
    */
    bool remove(const T& value);

    /**
     * @brief Удаление значения из позиции с заданным номером
    */
    bool removeAt(int index);

    /**
     * @brief Вывод на экран последовательности значений
    */
    void print() const;

    /**
     * @brief Деструктор
    */
    ~List() { clear(); }

    class Iterator {
    private:
        const List<T>& list;
        Node *current;

    public:
        /**
         * @brief Конструктор
        */
        Iterator(const List<T>& l) : list(l) {}

        /**
         * @brief Оператор сравнения итераторов на равенство
        */
        bool operator==(const Iterator& other) const;

        /**
         * @brief Оператор сравнения итераторов на неравенство
        */
        bool operator!=(const Iterator& other) const;

        /**
         * @brief Оператор разыменования итератора
        */
        T& operator*() const;

        /**
         * @brief Оператор инкремента итератора (prefix version)
        */
        Iterator& operator++();
    };

    /**
     * @brief Возвращение прямого итератора, указывающего на первый элемент списка
    */
    Iterator begin() const;

    /**
     * @brief Возвращение "неустановленного" прямого итератора
    */
    Iterator end() const;
};

template <typename T>
List<T>::List(const List<T>& other) : List() {
    Node *p = other.nil.next;
    while (p != &other.nil) {
        append(p->data);
        p = p->next;
    }
}

template <typename T>
int List<T>::get_size() const {
    return size;
}

template <typename T>
void List<T>::clear() {
    Node *p = nil.next;
    while (p != &nil) {
        Node *next_node = p->next;
        free(p);
        p = next_node;
    }

    nil.next = &nil;
    size = 0;
}

template <typename T>
bool List<T>::isEmpty() const {
    return size == 0;
}

template <typename T>
bool List<T>::contains(const T& value) const {
    Node *p = nil.next;
    while (p != &nil) {
        if (p->data == value) {
            return true;
        }

        p = p->next;
    }

    return false;
}

template <typename T>
T List<T>::get(int index) {
    // if index < 0 or index > size throw exception
    // don't remember how to

    Node *p = nil.next;
    for (int i = 0; i < index; ++i) {
        p = p->next;
    }

    return p->data;
}

template <typename T>
bool List<T>::set(int index, const T& value) {
    if (index < 0 || index >= size) {
        return false;
    }

    Node *p = nil.next;
    for (int i = 0; i < index; ++i) {
        p = p->next;
    }

    p->data = value;

    return true;
}

template <typename T>
int List<T>::indexOf(const T& value) const {
    Node *p = nil.next;
    int i = 0;
    while (p->data != value && p != &nil) {
        p = p->next;
        ++i;
    }

    if (p == &nil) {
        return -1;
    } else {
        return i;
    }
}

template <typename T>
void List<T>::append(const T& value) {
    Node *p = nil.next;
    while (p->next != &nil) {
        p = p->next;
    }

    Node *new_node = new Node(value);

    p->next = new_node;
    new_node->next = &nil;

    ++size;
}

template <typename T>
void List<T>::insert(int index, const T& value) {
    // if index < 0 or index > size throw exception
    // don't remember how to

    Node *p = nil.next;
    Node *prev = &nil;
    while (p != &nil && index != 0) {
        prev = p;
        p = p->next;
        --index;
    }

    Node *new_node = new Node(value);
    prev->next = new_node;
    new_node->next = p;

    ++size;
}

template <typename T>
bool List<T>::remove(const T& value) {
    Node *p = nil.next;
    Node *prev = &nil;
    while (p != &nil && p->data != value) {
        prev = p;
        p = p->next;
    }

    if (p != &nil) {
        prev->next = p->next;
        free(p);
        --size;
        return true;
    } else {
        return false;
    }
}

template <typename T>
bool List<T>::removeAt(int index) {
    if(index < 0 || index >= size) {
        return false;
    }

    Node *p = nil.next;
    Node *prev = &nil;
    while(p != &nil && index != 0) {
        prev = p;
        p = p->next;
        --index;
    }

    if(p != &nil) {
        prev->next = p->next;
        free(p);
        --size;

        return true;
    } else {
        return false;
    }
}

template <typename T>
void List<T>::print() const {
    // лучше всего делать через итераторы, но пока их нет
    // будем обходиться как можем
    std::cout << "List: ";
    Node *p = nil.next;
    while (p != &nil) {
        std::cout << p->data << " ";
        p = p->next;
    }
    std::cout << std::endl;
}

#endif