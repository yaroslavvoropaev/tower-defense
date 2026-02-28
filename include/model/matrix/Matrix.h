#pragma once

#include <iterator>
#include <memory>
#include <limits>
#include <vector>

/// @brief Основной шаблонный класс Matrix
template<std::default_initializable T>
class Matrix;
/**
 * @class MatrixIterator
 * @brief Итератор произвольного доступа для класса Matrix
 * 
 * @tparam T Тип элементов матрицы
 * @tparam is_const Флаг константности итератора
 * 
 * Итератор поддерживает все операции, требуемые для итераторов произвольного доступа,
 * включая сравнение, арифметические операции и доступ к элементам.
 */
template<typename T, bool is_const>
class MatrixIterator {
public:
    /// @brief Тип разницы между итераторами
    using difference_type = std::ptrdiff_t;
    /// @brief Тип значений, на которые ссылается итератор
    using value_type = T;
    /// @brief Тип указателя (константный или нет в зависимости от is_const)
    using pointer = std::conditional_t<is_const, const T, T> *;
    /// @brief Тип ссылки (константная или нет в зависимости от is_const)
    using reference = std::conditional_t<is_const, const T, T> &;
    /// @brief Категория итератора
    using iterator_category = std::random_access_iterator_tag;

    /**
     * @brief Конструктор по умолчанию
     * @note Создает невалидный итератор
     */
    MatrixIterator() noexcept;

    /**
     * @brief Конструктор из указателя
     * @param ptr Указатель на элемент матрицы
     */
    explicit MatrixIterator(pointer ptr) noexcept;

    /**
     * @brief Конструктор преобразования от другого итератора
     * 
     * @tparam other_const Флаг константности другого итератора
     * @param other Другой итератор для копирования
     * @note Преобразование возможно только от неконстантного к константному
     */
    template<bool other_const>
    explicit MatrixIterator(const MatrixIterator<T, other_const> &other) noexcept 
        requires (is_const >= other_const);

    /**
     * @brief Оператор присваивания от другого итератора
     * 
     * @tparam other_const Флаг константности другого итератора
     * @param other Другой итератор для присваивания
     * @return Ссылка на текущий итератор
     * @note Присваивание возможно только от неконстантного к константному
     */
    template<bool other_const>
    MatrixIterator &operator=(const MatrixIterator<T, other_const> &other) noexcept 
        requires (is_const >= other_const);

    /**
     * @brief Оператор разыменования
     * @return Ссылка на элемент, на который указывает итератор
     */
    reference operator*() const noexcept;
    
    /**
     * @brief Оператор доступа к члену
     * @return Указатель на элемент, на который указывает итератор
     */
    pointer operator->() const noexcept;
    
    /**
     * @brief Оператор индексирования
     * @param index Смещение относительно текущей позиции
     * @return Ссылка на элемент по указанному смещению
     */
    reference operator[](difference_type index) const noexcept;

    /// @brief Оператор сравнения на равенство
    bool operator==(const MatrixIterator& other) const noexcept = default;
    
    /// @brief Оператор трехстороннего сравнения
    auto operator<=>(const MatrixIterator& other) const noexcept = default;

    /**
     * @brief Префиксный инкремент
     * @return Ссылка на итератор после инкремента
     */
    MatrixIterator &operator++() noexcept;
    
    /**
     * @brief Постфиксный инкремент
     * @return Итератор до инкремента
     */
    MatrixIterator operator++(int) noexcept;

    /**
     * @brief Префиксный декремент
     * @return Ссылка на итератор после декремента
     */
    MatrixIterator &operator--() noexcept;
    
    /**
     * @brief Постфиксный декремент
     * @return Итератор до декремента
     */
    MatrixIterator operator--(int) noexcept;

    /**
     * @brief Оператор сложения с присваиванием
     * @param offset Смещение
     * @return Ссылка на итератор после смещения
     */
    MatrixIterator &operator+=(difference_type offset) noexcept;
    
    /**
     * @brief Оператор вычитания с присваиванием
     * @param offset Смещение
     * @return Ссылка на итератор после смещения
     */
    MatrixIterator &operator-=(difference_type offset) noexcept;

    /**
     * @brief Оператор сложения
     * @param offset Смещение
     * @return Новый итератор, смещенный вперед
     */
    MatrixIterator operator+(difference_type offset) const noexcept;
    
    /**
     * @brief Оператор вычитания
     * @param offset Смещение
     * @return Новый итератор, смещенный назад
     */
    MatrixIterator operator-(difference_type offset) const noexcept;

    /**
     * @brief Оператор разности итераторов
     * 
     * @tparam other_const Флаг константности другого итератора
     * @param other Другой итератор
     * @return Разница в позициях между итераторами
     */
    template<bool other_const>
    difference_type operator-(const MatrixIterator<T, other_const> &other) const noexcept;

    /**
     * @brief Дружественная функция для сложения числа и итератора
     * @param offset Смещение
     * @param it Итератор
     * @return Новый итератор, смещенный вперед
     */
    friend MatrixIterator operator+(difference_type offset, const MatrixIterator &it) noexcept {
        return it + offset;
    }

private:
    pointer ptr_; ///< Указатель на текущий элемент

    friend Matrix<T>;
    friend MatrixIterator<T, !is_const>;
};

/**
 * @class MatrixProxy
 * @brief Прокси-класс для доступа к строкам матрицы
 * 
 * @tparam T Тип элементов матрицы
 * @tparam is_const Флаг константности прокси
 * 
 * Используется для обеспечения двумерного доступа к элементам матрицы
 * через оператор [].
 */
template<typename T, bool is_const>
class MatrixProxy {
    using pointer = std::conditional_t<is_const, const T, T>*;
    pointer row_start_; ///< Указатель на начало строки
    
public:
    /**
     * @brief Конструктор
     * @param row_start Указатель на начало строки
     */
    explicit MatrixProxy(pointer row_start) : row_start_(row_start) {}

    /**
     * @brief Оператор доступа к элементу строки (неконстантная версия)
     * @param col Индекс столбца
     * @return Ссылка на элемент
     * @note Доступен только для неконстантного прокси
     */
    template<bool is_const_proxy = is_const> requires (!is_const_proxy)
    T &operator[](size_t col) {
        return row_start_[col];
    }

    /**
     * @brief Оператор доступа к элементу строки (константная версия)
     * @param col Индекс столбца
     * @return Константная ссылка на элемент
     */
    const T &operator[](size_t col) const {
        return row_start_[col];
    }
};

/**
 * @class Matrix
 * @brief Шаблонный класс для работы с двумерными матрицами
 * 
 * @tparam T Тип элементов матрицы, должен быть std::default_initializable
 * 
 * Класс предоставляет функциональность для создания, модификации и доступа
 * к элементам матрицы. Поддерживает копирование, перемещение, вставку и удаление
 * строк и столбцов, а также предоставляет итераторы для обхода элементов.
 */
template<std::default_initializable T>
class Matrix {
public:
    using value_type = T;               ///< Тип элементов матрицы
    using reference = T&;               ///< Тип ссылки на элемент
    using const_reference = const T&;   ///< Тип константной ссылки на элемент
    using iterator = MatrixIterator<T, false>;          ///< Тип итератора
    using const_iterator = MatrixIterator<T, true>;     ///< Тип константного итератора
    using difference_type = std::ptrdiff_t;             ///< Тип разницы между позициями
    using size_type = std::size_t;                      ///< Тип размера
    using reverse_iterator = std::reverse_iterator<iterator>;           ///< Обратный итератор
    using const_reverse_iterator = std::reverse_iterator<const_iterator>; ///< Константный обратный итератор

private:
    T *data_;       ///< Указатель на данные матрицы
    size_type rows_; ///< Количество строк
    size_type cols_; ///< Количество столбцов

public:
    /**
     * @brief Конструктор по умолчанию
     * @note Создает пустую матрицу 0x0
     */
    Matrix() noexcept;

    /**
     * @brief Конструктор копирования
     * @param other Матрица для копирования
     * @requires std::copy_constructible<T>
     */
    Matrix(const Matrix &other) requires std::copy_constructible<T>;

    /**
     * @brief Конструктор перемещения
     * @param other Матрица для перемещения
     * @requires std::move_constructible<T>
     */
    Matrix(Matrix &&other) noexcept requires std::move_constructible<T>;

    /**
     * @brief Конструктор с указанием размеров и значения
     * 
     * @param rows Количество строк
     * @param cols Количество столбцов
     * @param value Значение для инициализации всех элементов (по умолчанию T())
     * @requires std::copy_constructible<T>
     */
    explicit Matrix(size_type rows, size_type cols, const T &value = T()) 
        requires std::copy_constructible<T>;

    /**
     * @brief Оператор присваивания копированием
     * @param other Матрица для копирования
     * @return Ссылка на текущую матрицу
     * @requires std::copy_constructible<T>
     */
    Matrix &operator=(const Matrix &other) requires std::copy_constructible<T>;
    
    /**
     * @brief Оператор присваивания перемещением
     * @param other Матрица для перемещения
     * @return Ссылка на текущую матрицу
     */
    Matrix &operator=(Matrix &&other) noexcept;

    /**
     * @brief Оператор доступа к строке (константная версия)
     * @param row Индекс строки
     * @return MatrixProxy для доступа к элементам строки
     */
    MatrixProxy<T, true> operator[](size_type row) const;
    
    /**
     * @brief Оператор доступа к строке (неконстантная версия)
     * @param row Индекс строки
     * @return MatrixProxy для доступа к элементам строки
     */
    MatrixProxy<T, false> operator[](size_type row);

    /**
     * @brief Доступ к элементу с проверкой границ (неконстантная версия)
     * @param pos Позиция элемента (линейный индекс)
     * @return Ссылка на элемент
     * @throw std::out_of_range если позиция выходит за границы
     */
    reference at(size_type pos);
    
    /**
     * @brief Доступ к элементу с проверкой границ (константная версия)
     * @param pos Позиция элемента (линейный индекс)
     * @return Константная ссылка на элемент
     * @throw std::out_of_range если позиция выходит за границы
     */
    const_reference at(size_type pos) const;

    /// @brief Деструктор
    ~Matrix();

    /**
     * @brief Итератор на начало матрицы (неконстантная версия)
     * @return Итератор на первый элемент
     */
    iterator begin() noexcept;
    
    /**
     * @brief Итератор на конец матрицы (неконстантная версия)
     * @return Итератор на позицию после последнего элемента
     */
    iterator end() noexcept;

    /**
     * @brief Итератор на начало матрицы (константная версия)
     * @return Константный итератор на первый элемент
     */
    const_iterator begin() const noexcept;
    
    /**
     * @brief Итератор на конец матрицы (константная версия)
     * @return Константный итератор на позицию после последнего элемента
     */
    const_iterator end() const noexcept;

    /**
     * @brief Константный итератор на начало матрицы
     * @return Константный итератор на первый элемент
     */
    const_iterator cbegin() const noexcept;
    
    /**
     * @brief Константный итератор на конец матрицы
     * @return Константный итератор на позицию после последнего элемента
     */
    const_iterator cend() const noexcept;

    /**
     * @brief Оператор сравнения на равенство
     * @param other Другая матрица для сравнения
     * @return true если матрицы имеют одинаковые размеры и элементы
     */
    bool operator==(const Matrix &other) const;
    
    /**
     * @brief Обмен содержимым с другой матрицей
     * @param other Матрица для обмена
     */
    void swap(Matrix &other) noexcept;

    /**
     * @brief Получить количество строк
     * @return Количество строк
     */
    [[nodiscard]] size_type rows() const noexcept;
    
    /**
     * @brief Получить количество столбцов
     * @return Количество столбцов
     */
    [[nodiscard]] size_type cols() const noexcept;
    
    /**
     * @brief Получить общее количество элементов
     * @return rows() * cols()
     */
    [[nodiscard]] size_type size() const noexcept;
    
    /**
     * @brief Получить максимально возможный размер матрицы
     * @return Максимальный размер, который может хранить матрица
     */
    [[nodiscard]] static size_type max_size() noexcept;
    
    /**
     * @brief Проверить, пуста ли матрица
     * @return true если матрица не содержит элементов (размер 0x0)
     */
    [[nodiscard]] bool empty() const noexcept;

    /**
     * @brief Создать элемент на месте
     * 
     * @tparam Args Типы аргументов для конструктора
     * @param pos Позиция для вставки
     * @param args Аргументы для конструктора элемента
     * @return Итератор на вставленный элемент
     * @throw std::out_of_range если позиция невалидна
     * @requires std::constructible_from<T, Args...>
     */
    template<typename ... Args>
    iterator emplace(const_iterator pos, Args &&...args)
    requires std::constructible_from<T, Args...> && std::is_nothrow_swappable_v<T>;

    /**
     * @brief Вставить элемент копированием
     * @param pos Позиция для вставки
     * @param value Значение для вставки
     * @return Итератор на вставленный элемент
     * @requires std::copy_constructible<T>
     */
    iterator insert(const_iterator pos, const T &value) 
        requires std::copy_constructible<T>;

    /**
     * @brief Вставить элемент перемещением
     * @param pos Позиция для вставки
     * @param value Значение для вставки
     * @return Итератор на вставленный элемент
     * @requires std::move_constructible<T>
     */
    iterator insert(const_iterator pos, const T &&value) 
    requires std::move_constructible<T> ;

    /**
     * @brief Вставить несколько одинаковых элементов
     * @param pos Позиция для вставки
     * @param count Количество элементов для вставки
     * @param value Значение для вставки
     * @return Итератор на позицию после последнего вставленного элемента
     * @requires std::copy_constructible<T>
     */
    iterator insert(const_iterator pos, size_type count, const T &value) 
        requires std::copy_constructible<T> && std::is_nothrow_swappable_v<T>;

    /**
     * @brief Вставить диапазон элементов
     * 
     * @tparam InputIt Тип итератора ввода
     * @param pos Позиция для вставки
     * @param first Начало диапазона
     * @param last Конец диапазона
     * @return Итератор на позицию после последнего вставленного элемента
     * @requires std::copy_constructible<T>
     */
    template<std::input_iterator InputIt>
    iterator insert(const_iterator pos, InputIt first, InputIt last) 
        requires std::copy_constructible<T> && std::is_nothrow_swappable_v<T>;
        
    /**
     * @brief Вставить список инициализации
     * @param pos Позиция для вставки
     * @param il Список инициализации
     * @return Итератор на позицию после последнего вставленного элемента
     * @requires std::move_constructible<T>
     */
    iterator insert(const_iterator pos, std::initializer_list<T> il) 
        requires std::move_constructible<T>;
    /**
     * @brief Заменить содержимое матрицы элементами из диапазона
     * 
     * @tparam InputIt Тип итератора ввода
     * @param first Начало диапазона
     * @param last Конец диапазона
     * @requires std::copy_constructible<T>
     */
    template<std::input_iterator InputIt>
    void assign(InputIt first, InputIt last) 
        requires std::copy_constructible<T>;
        
    /**
     * @brief Заменить содержимое матрицы списком инициализации
     * @param il Список инициализации
     * @requires std::copy_constructible<T>
     */
    void assign(std::initializer_list<T> il) 
        requires std::copy_constructible<T>;

    /**
     * @brief Вставить новую строку
     * 
     * @param row_index Индекс, куда вставить новую строку
     * @param il Значения для новой строки (должно совпадать с количеством столбцов или быть пустым)
     * @throw std::out_of_range если индекс строки невалиден
     * @throw std::invalid_argument если размер списка не соответствует количеству столбцов
     * @requires std::copy_constructible<T> && std::move_constructible<T>
     */
    void insert_row(size_type row_index, std::initializer_list<T> il) 
        requires std::copy_constructible<T> && std::move_constructible<T>;
        
    /**
     * @brief Вставить новый столбец
     * 
     * @param col_index Индекс, куда вставить новый столбец
     * @param il Значения для нового столбца (должно совпадать с количеством строк или быть пустым)
     * @throw std::out_of_range если индекс столбца невалиден
     * @throw std::invalid_argument если размер списка не соответствует количеству строк
     * @requires std::copy_constructible<T> && std::move_constructible<T>
     */
    void insert_col(size_type col_index, std::initializer_list<T> il) 
        requires std::copy_constructible<T> && std::move_constructible<T>;

    /**
     * @brief Удалить строку
     * @param row_index Индекс удаляемой строки
     * @throw std::out_of_range если индекс строки невалиден
     */
    void erase_row(size_type row_index) noexcept(std::is_nothrow_move_assignable_v<T> && std::is_nothrow_move_constructible_v<T>);
    /**
     * @brief Удалить столбец
     * @param col_index Индекс удаляемого столбца
     * @throw std::out_of_range если индекс столбца невалиден
     */
    void erase_col(size_type col_index) noexcept(std::is_nothrow_move_assignable_v<T> && std::is_nothrow_move_constructible_v<T>);

    /**
     * @brief Очистить матрицу
     * @note После вызова матрица становится пустой (0x0)
     */
    void clear() noexcept;
};

// Реализация MatrixIterator
template<typename T, bool is_const>
MatrixIterator<T, is_const>::MatrixIterator() noexcept : ptr_(nullptr) {}

template<typename T, bool is_const>
MatrixIterator<T, is_const>::MatrixIterator(pointer ptr) noexcept : ptr_(ptr) {}

template<typename T, bool is_const>
template<bool other_const>
MatrixIterator<T, is_const>::MatrixIterator(const MatrixIterator<T, other_const> &other) noexcept
    requires (is_const >= other_const) : ptr_(other.ptr_) {}

template<typename T, bool is_const>
template<bool other_const>
MatrixIterator<T, is_const> &MatrixIterator<T, is_const>::operator=(const MatrixIterator<T, other_const> &other) noexcept
    requires (is_const >= other_const) {
    ptr_ = other.ptr_;
    return *this;
}

template<typename T, bool is_const>
MatrixIterator<T, is_const>::reference MatrixIterator<T, is_const>::operator *() const noexcept {
    return *ptr_;
}

template<typename T, bool is_const>
MatrixIterator<T, is_const>::pointer MatrixIterator<T, is_const>::operator->() const noexcept {
    return ptr_;
}

template<typename T, bool is_const>
MatrixIterator<T, is_const>::reference MatrixIterator<T, is_const>::operator[](difference_type index) const noexcept {
    return ptr_[index];
}

template<typename T, bool is_const>
MatrixIterator<T, is_const> &MatrixIterator<T, is_const>::operator++() noexcept {
    ++ptr_;
    return *this;
}

template<typename T, bool is_const>
MatrixIterator<T, is_const> MatrixIterator<T, is_const>::operator++(int) noexcept {
    MatrixIterator tmp = *this;
    ++ptr_;
    return tmp;
}

template<typename T, bool is_const>
MatrixIterator<T, is_const> &MatrixIterator<T, is_const>::operator--() noexcept {
    --ptr_;
    return *this;
}

template<typename T, bool is_const>
MatrixIterator<T, is_const> MatrixIterator<T, is_const>::operator--(int) noexcept {
    MatrixIterator temp = *this;
    --ptr_;
    return temp;
}

template<typename T, bool is_const>
MatrixIterator<T, is_const> MatrixIterator<T, is_const>::operator+(difference_type offset) const noexcept {
    return MatrixIterator(ptr_ + offset);
}

template<typename T, bool is_const>
MatrixIterator<T, is_const> MatrixIterator<T, is_const>::operator-(difference_type offset) const noexcept {
    return MatrixIterator(ptr_ - offset);
}

template<typename T, bool is_const>
template<bool other_const>
MatrixIterator<T, is_const>::difference_type MatrixIterator<T, is_const>::operator - (const MatrixIterator<T, other_const> &other) const noexcept {
    return ptr_ - other.ptr_;
}

template<typename T, bool is_const>
MatrixIterator<T, is_const> &MatrixIterator<T, is_const>::operator += (difference_type offset) noexcept {
    ptr_ += offset;
    return *this;
}

template<typename T, bool is_const>
MatrixIterator<T, is_const> &MatrixIterator<T, is_const>::operator -= (difference_type offset) noexcept {
    ptr_ -= offset;
    return *this;
}

// Реализация Matrix
template <std::default_initializable T>
Matrix<T>::Matrix() noexcept : data_(nullptr), rows_(0), cols_(0) {}

template <std::default_initializable T>
Matrix<T>::Matrix(size_type rows, size_type cols, const T &value) 
    requires std::copy_constructible<T> : data_(nullptr), rows_(rows), cols_(cols) {
    if (rows > 0 && cols > 0) {
        std::unique_ptr<T[]> tmp(new T[rows * cols]);
        std::fill(tmp.get(), tmp.get() + rows * cols, value);
        data_ = tmp.release();
        rows_ = rows;
        cols_ = cols;
    }
}

template <std::default_initializable T>
Matrix<T>::Matrix(const Matrix &other) requires std::copy_constructible<T> 
    : data_(nullptr), rows_(0), cols_(0) {
    if (other.data_) {
        std::unique_ptr<T[]> tmp(new T[other.cols() * other.rows()]);
        std::copy(other.begin(), other.end(), tmp.get());
        data_ = tmp.release();
        rows_ = other.rows_;
        cols_ = other.cols_;
    }
}

template <std::default_initializable T>
Matrix<T>::Matrix(Matrix &&other) noexcept requires std::move_constructible<T> : Matrix() {
    swap(other);
}

template <std::default_initializable T>
Matrix<T> &Matrix<T>::operator=(const Matrix &other) requires std::copy_constructible<T> {
    if (this == &other) {
        return *this;
    }
    std::unique_ptr<T[]> tmp;
    if (other.data_) {
        tmp.reset(new T[other.size()]);
        std::copy(other.begin(), other.end() , tmp.get());
    }
    delete [] data_;
    data_ = tmp.release();
    rows_ = other.rows_;
    cols_ = other.cols_;
    return *this;
}

template <std::default_initializable T>
Matrix<T> &Matrix<T>::operator=(Matrix &&other) noexcept {
    swap(other);
    return *this;
}

template <std::default_initializable T>
Matrix<T>::reference Matrix<T>::at(size_type pos)  {
    if (pos >= rows_ * cols_) {
        throw std::out_of_range("Out of range");
    }
    return *(data_ + pos);
}

template <std::default_initializable T>
Matrix<T>::const_reference Matrix<T>::at(size_type pos) const {
    if (pos >= rows_ * cols_) {
        throw std::out_of_range("Out of range");
    }
    return *(data_ + pos);
}

template <std::default_initializable T>
Matrix<T>::iterator Matrix<T>::begin() noexcept {
    return iterator(data_);
}

template <std::default_initializable T>
Matrix<T>::const_iterator Matrix<T>::begin() const noexcept {
    return const_iterator(data_);
}

template <std::default_initializable T>
Matrix<T>::const_iterator Matrix<T>::cbegin() const noexcept {
    return const_iterator(data_);
}

template <std::default_initializable T>
Matrix<T>::iterator Matrix<T>::end() noexcept {
    return iterator(data_ + cols_ * rows_);
}

template <std::default_initializable T>
Matrix<T>::const_iterator Matrix<T>::end() const noexcept {
    return const_iterator(data_ + rows_ * cols_);
}

template <std::default_initializable T>
Matrix<T>::const_iterator Matrix<T>::cend() const noexcept {
    return const_iterator(data_ + rows_ * cols_);
}

template <std::default_initializable T>
bool Matrix<T>::operator==(const Matrix& other) const {
    if (rows_ != other.rows_ || cols_ != other.cols_) {
        return false;
    }
    return std::equal(begin(), end(),other.begin(), other.end());
}

template <std::default_initializable T>
void Matrix<T>::swap(Matrix& other) noexcept {
    std::swap(rows_, other.rows_);
    std::swap(cols_, other.cols_);
    std::swap(data_, other.data_);
}

template <std::default_initializable T>
Matrix<T>::size_type Matrix<T>::rows() const noexcept {
    return rows_;
}

template <std::default_initializable T>
Matrix<T>::size_type Matrix<T>::cols() const noexcept {
    return cols_;
}

template <std::default_initializable T>
Matrix<T>::size_type Matrix<T>::size() const noexcept {
    return rows_ * cols_;
}

template <std::default_initializable T>
Matrix<T>::size_type Matrix<T>::max_size() noexcept {
    return std::numeric_limits<size_t>::max();
}

template <std::default_initializable T>
bool Matrix<T>::empty() const noexcept {
    return data_ == nullptr;
}

template <std::default_initializable T>
template <typename... Args>
Matrix<T>::iterator Matrix<T>::emplace(const_iterator pos, Args&&... args) requires std::constructible_from<T, Args...> && std::is_nothrow_swappable_v<T> {
    if (pos < cbegin() || pos >= cend()) {
        throw std::out_of_range("Iterator out of range");
    }
    size_type index = std::distance(cbegin(), pos);

    T tmp(std::forward<Args>(args)...);

    std::swap(data_[index], tmp);

    return iterator(data_ + index);
}

template <std::default_initializable T>
Matrix<T>::iterator Matrix<T>::insert(const_iterator pos, const T &value) requires std::copy_constructible<T> {
    return emplace(pos, value);
}

template <std::default_initializable T>
Matrix<T>::iterator Matrix<T>::insert(const_iterator pos, const T &&value) requires std::move_constructible<T> {
    return emplace(pos, std::move(value));
}

template <std::default_initializable T>
Matrix<T>::iterator Matrix<T>::insert(const_iterator pos, size_type count, const T &value) requires std::copy_constructible<T> && std::is_nothrow_swappable_v<T> {
    if (pos < cbegin() || pos >= cend()) {
        throw std::out_of_range("Iterator out of range");
    }

    size_type start_pos = pos - cbegin();
    size_type end_pos   = std::min(start_pos + count, rows_ * cols_);
    size_type cnt = end_pos - start_pos;

    std::vector<T> tmp(cnt, value);

    for (size_type i = 0; i < cnt; ++i) {
        std::swap(data_[start_pos + i], tmp[i]);
    }

    return iterator(data_ + end_pos);
}

template <std::default_initializable T>
template <std::input_iterator InputIt>
Matrix<T>::iterator  Matrix<T>::insert(const_iterator pos, InputIt first, InputIt last) requires std::copy_constructible<T> && std::is_nothrow_swappable_v<T>
{
    if (pos < cbegin() || pos > cend()) {
        throw std::out_of_range("Iterator out of range");
    }

    size_type start_index = pos - cbegin();
    size_type cnt = rows_ * cols_ - start_index;

    std::vector<T> tmp;
    tmp.reserve(cnt);

    InputIt it = first;
    for (; it != last && tmp.size() < cnt; ++it) {
        tmp.emplace_back(*it);
    }
    for (size_type i = 0; i < tmp.size(); ++i) {
        std::swap(data_[start_index + i], tmp[i]);
    }

    return iterator(data_ + start_index + tmp.size());
}

template <std::default_initializable T>
Matrix<T>::iterator Matrix<T>::insert(const_iterator pos, std::initializer_list<T> il) requires std::move_constructible<T> {
    if (pos < cbegin() || pos >= cend()) {
        throw std::out_of_range("Iterator out of range");
    }

    size_t offset = pos - cbegin();
    insert(pos, il.begin(), il.end());
    return begin() + (offset + il.size());
}

template <std::default_initializable T>
void Matrix<T>::insert_row(size_type row_index, std::initializer_list<T> il) requires std::copy_constructible<T> && std::move_constructible<T> {
    if (row_index > rows_) {
        throw std::out_of_range("Row index out of range");
    }

    if (il.size() != 0 && il.size() != cols_) {
        throw std::invalid_argument("Row values size must match number of columns or be empty");
    }


    size_type new_rows = rows_ + 1;
    size_type new_cols = cols_;
    size_type new_size = new_rows * new_cols;


    std::unique_ptr<T[]> new_data(new T[new_size]);

    if (il.size() != 0) {
        std::copy(il.begin(), il.end(), new_data.get() + row_index * new_cols);
    }

    for (size_type i = 0; i < row_index; ++i) {
        for (size_type j = 0; j < cols_; ++j) {
            new_data[i * new_cols + j] = std::move_if_noexcept(data_[i * cols_ + j]);
        }
    }

    for (size_type i = row_index; i < rows_; ++i) {
        for (size_type j = 0; j < cols_; ++j) {
            new_data[(i + 1) * new_cols + j] = std::move_if_noexcept(data_[i * cols_ + j]);
        }
    }
    delete[] data_;
    data_ = new_data.release();
    rows_ = new_rows;
}




template <std::default_initializable T>
void Matrix<T>::insert_col(size_type col_index, std::initializer_list<T> il) requires std::copy_constructible<T> && std::move_constructible<T> {
    if (col_index > cols_) {
        throw std::out_of_range("Column index out of range");
    }

    if (il.size() != 0 && il.size() != rows_) {
        throw std::invalid_argument("Column values size must match number of rows or be empty");
    }

    const size_type new_rows = rows_;
    const size_type new_cols = cols_ + 1;
    const size_type new_size = new_rows * new_cols;

    std::unique_ptr<T[]> tmp(new T[new_size]);

    for (size_type i = 0; i < new_rows; ++i) {
        if (il.size() != 0) {
            tmp[i * new_cols + col_index] = *(il.begin() + i);
        }
    }
    for (size_type i = 0; i < rows_; ++i) {
        for (size_type j = 0; j < col_index; ++j) {
            tmp[i * new_cols + j] = std::move_if_noexcept(data_[i * cols_ + j]);
        }

        for (size_type j = col_index; j < cols_; ++j) {
            tmp[i * new_cols + j + 1] = std::move_if_noexcept(data_[i * cols_ + j]);
        }
    }

    delete[] data_;
    data_ = tmp.release();
    cols_ = new_cols;
}

template <std::default_initializable T>
void Matrix<T>::erase_row(size_type row_index) noexcept(std::is_nothrow_move_assignable_v<T> && std::is_nothrow_move_constructible_v<T>) {
    if (row_index >= rows_ ) {
        row_index = rows_ - 1;
    }
    if (rows_ == 1) {
        delete[] data_;
        data_ = nullptr;
        rows_ = 0;
        cols_ = 0;
        return;
    }

    const size_type new_rows = rows_ - 1;
    const size_type new_cols = cols_;
    const size_type new_size = new_rows * new_cols;

    std::unique_ptr<T[]> tmp(new T[new_size]);

    size_type cnt = 0;
    for (size_type i = 0; i < rows_; ++i) {
        if (i == row_index) continue;
        for (size_type j = 0; j < cols_; ++j) {
            tmp[cnt++] = std::move_if_noexcept(data_[i * cols_ + j]);
        }
    }

    delete[] data_;
    data_ = tmp.release();
    rows_ = new_rows;
}

template <std::default_initializable T>
void Matrix<T>::erase_col(size_type col_index) noexcept(std::is_nothrow_move_assignable_v<T> && std::is_nothrow_move_constructible_v<T>) {
    if (col_index >= cols_) {
        col_index = cols_ - 1;
    }

    if (cols_ == 1) {
        delete[] data_;
        data_ = nullptr;
        rows_ = 0;
        cols_ = 0;
        return;
    }

    const size_type new_rows = rows_;
    const size_type new_cols = cols_ - 1;
    const size_type new_size = new_rows * new_cols;

    std::unique_ptr<T[]> tmp(new T[new_size]);

    for (size_type i = 0; i < rows_; ++i) {
        size_type cnt = i * new_cols;
        for (size_type j = 0; j < cols_; ++j) {
            if (j == col_index) continue;
            tmp[cnt++] = std::move(data_[i * cols_ + j]);
        }
    }

    delete[] data_;
    data_ = tmp.release();
    cols_ = new_cols;
}

template<std::default_initializable T>
void Matrix<T>::clear() noexcept {
    delete[] data_;
    data_ = nullptr;
    rows_ = 0;
    cols_ = 0;
}

template<std::default_initializable T>
MatrixProxy<T, true> Matrix<T>::operator[](size_type row) const {
    return MatrixProxy<T, true>(data_ + row * cols_);
}

template<std::default_initializable T>
MatrixProxy<T, false> Matrix<T>::operator[](size_type row)  {
    return MatrixProxy<T, false>(data_ + row * cols_);
}

template <std::default_initializable T>
template <std::input_iterator InputIt>
void Matrix<T>::assign(InputIt first, InputIt last) requires std::copy_constructible<T> {
    size_t dist = std::distance(first, last);
    Matrix<T> tmp{1, dist};
    try {
        auto it = first;
        for (size_t i = 0; i < tmp.size(); ++i) {
            tmp[0][i] = *it;
            ++it;
        }
        swap(tmp);
    } catch (...) {
        tmp.clear();
        throw;
    }
}

template <std::default_initializable T>
void Matrix<T>::assign(std::initializer_list<T> il) requires std::copy_constructible<T> {
    assign(il.begin(), il.end());
}

template <std::default_initializable T>
Matrix<T>::~Matrix() {
    clear();
}


static_assert(std::random_access_iterator<MatrixIterator<int, false>>);
static_assert(std::random_access_iterator<MatrixIterator<int, true>>);