#ifndef CIRCULAR_LINKED_LIST_H
#define CIRCULAR_LINKED_LIST_H

template <typename T>
class CircularLinkedList {
private:
    class Node {
        T data;
        Node *next;
        Node(const T& value) : data(value), next(nullptr) {}
    }

    size_t size;
    Node *head;

public:
    /**
     * @brief Конструтор по умолчанию
    */
    CircularLinkedList();

    /**
     * @brief Конструктор копирования
    */
    CircularLinkedList(const CircularLinkedList<T>& other);

    /**
     * @brief Опрос размера списка
    */
    size_t size() const;

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
    size_t indexOf(const T& value) const;

    /**ra
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
    ~CircularLinkedList();


    class Iterator {
    private:
        const CircularLinkedList<T>& list;
        Node *current;

    public:
        /**
         * @brief Конструктор
        */
        Iterator(const CircularLinkedList<T>& l) : list(l) {}

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
    }

    /**
     * @brief Возвращение прямого итератора, указывающего на первый элемент списка
    */
    Iterator begin() const;

    /**
     * @brief Возвращение "неустановленного" прямого итератора
    */
    Iterator end() const;
};

#endif