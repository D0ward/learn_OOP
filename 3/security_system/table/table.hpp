#pragma once

#include <cstddef>
#include <utility>
#include <functional>
#include <optional>
#include <memory>
#include <type_traits>
#include <stdexcept>
#include <algorithm>
#include <limits>
#include <iterator>

namespace Security_system
{
    /**
     * @brief Динамический массив с безопасным управлением памятью и итераторами.
     *
     * Table — это шаблонный класс, представляющий собой контейнер с динамическим изменением размера,
     * обеспечивающий безопасность работы с памятью и поддержку прямых итераторов.
     *
     * @tparam T Тип элементов, хранящихся в таблице. Должен поддерживать операции копирования и перемещения.
     */
    template <typename T>
    class Table
    {
    private:
        size_t capacity_ = 0; ///< Текущая ёмкость выделенной памяти
        size_t size_ = 0;     ///< Текущее количество элементов в таблице
        T *data_ = nullptr;   ///< Указатель на массив элементов

        /**
         * @brief Увеличивает ёмкость таблицы вдвое плюс один элемент.
         *
         * Используется при добавлении элементов, когда текущая ёмкость недостаточна.
         */
        void resize()
        {
            size_t new_capacity = capacity_ * 2 + 1;
            T *new_data = new T[new_capacity];

            if (data_ != nullptr)
            {
                std::copy(data_, data_ + size_, new_data);
                delete[] data_;
            }

            capacity_ = new_capacity;
            data_ = new_data;
        }

        /**
         * @brief Изменяет ёмкость таблицы до указанного размера.
         *
         * @param new_capacity Новая ёмкость таблицы.
         */
        void resize(size_t new_capacity)
        {
            T *new_data = new T[new_capacity];

            if (data_ != nullptr)
            {
                std::copy(data_, data_ + size_, new_data);
                delete[] data_;
            }

            capacity_ = new_capacity;
            data_ = new_data;
        }

    public:
        /**
         * @brief Шаблонный итератор для Table с поддержкой const и non-const версий.
         *
         * @tparam is_const Если true, итератор является константным.
         */
        template <bool is_const>
        class Iterator
        {
        public:
            using iterator_category = std::random_access_iterator_tag;
            using value_type = std::conditional_t<is_const, const T, T>;
            using difference_type = std::ptrdiff_t;
            using pointer = value_type *;
            using reference = value_type &;

        private:
            pointer ptr_ = nullptr;   ///< Текущий указатель на элемент
            pointer start_ = nullptr; ///< Указатель на начало массива данных
            pointer end_ = nullptr;   ///< Указатель на конец массива данных (за последним элементом)

            friend Table<T>;
            template <bool>
            friend class Iterator;

        public:
            /**
             * @brief Конструктор по умолчанию.
             */
            Iterator() noexcept = default;

            /**
             * @brief Конструктор итератора.
             *
             * @param ptr   Текущий указатель на элемент
             * @param start Указатель на начало массива
             * @param end   Указатель на конец массива
             */
            Iterator(pointer ptr, pointer start, pointer end) noexcept
                : ptr_(ptr), start_(start), end_(end) {}
            /**
             * @brief Конструктор копирования с конвертацией const-ness.
             *
             * @tparam other_const Константность исходного итератора
             * @param o Исходный итератор
             */
            template <bool other_const>
            Iterator(const Iterator<other_const> &o) noexcept
                requires(is_const >= other_const)
                : ptr_(o.ptr_), start_(o.start_), end_(o.end_)
            {
            }

            /**
             * @brief Оператор присваивания с конвертацией const-ness.
             *
             * @tparam other_const Константность исходного итератора
             * @param o Исходный итератор
             * @return Iterator& Ссылка на текущий итератор
             */
            template <bool other_const>
            Iterator &operator=(const Iterator<other_const> &o) noexcept
                requires(is_const >= other_const)
            {
                ptr_ = o.ptr_;
                start_ = o.start_;
                end_ = o.end_;
                return *this;
            }

            /**
             * @brief Оператор разыменования.
             *
             * @return reference Ссылка на текущий элемент
             */
            reference operator*() const noexcept
            {
                return *ptr_;
            }

            /**
             * @brief Оператор доступа к члену.
             *
             * @return pointer Указатель на текущий элемент
             */
            pointer operator->() const noexcept
            {
                return ptr_;
            }

            /**
             * @brief Оператор индексации.
             *
             * @param n Смещение от текущей позиции
             * @return reference Ссылка на элемент со смещением n
             */
            reference operator[](difference_type n) const
            {
                return *(ptr_ + n);
            }

            /**
             * @brief Префиксный инкремент.
             *
             * @return Iterator& Ссылка на итератор, указывающий на следующий элемент
             */
            Iterator &operator++() noexcept
            {
                ++ptr_;
                return *this;
            }

            /**
             * @brief Постфиксный инкремент.
             *
             * @return Iterator Копия итератора до инкремента
             */
            Iterator operator++(int) noexcept
            {
                Iterator tmp = *this;
                ++ptr_;
                return tmp;
            }

            /**
             * @brief Префиксный декремент.
             *
             * @return Iterator& Ссылка на итератор, указывающий на предыдущий элемент
             */
            Iterator &operator--() noexcept
            {
                --ptr_;
                return *this;
            }

            /**
             * @brief Постфиксный декремент.
             *
             * @return Iterator Копия итератора до декремента
             */
            Iterator operator--(int) noexcept
            {
                Iterator tmp = *this;
                --ptr_;
                return tmp;
            }

            /**
             * @brief Оператор сложения с целым числом.
             *
             * @param n Смещение
             * @return Iterator Новый итератор со смещением
             */
            Iterator operator+(difference_type n) const
            {
                return Iterator(ptr_ + n, start_, end_);
            }

            /**
             * @brief Оператор вычитания с целым числом.
             *
             * @param n Смещение
             * @return Iterator Новый итератор со смещением
             */
            Iterator operator-(difference_type n) const
            {
                return Iterator(ptr_ - n, start_, end_);
            }

            /**
             * @brief Оператор добавления смещения.
             *
             * @param n Смещение
             * @return Iterator& Ссылка на текущий итератор
             */
            Iterator &operator+=(difference_type n)
            {
                ptr_ += n;
                return *this;
            }

            /**
             * @brief Оператор вычитания смещения.
             *
             * @param n Смещение
             * @return Iterator& Ссылка на текущий итератор
             */
            Iterator &operator-=(difference_type n)
            {
                ptr_ -= n;
                return *this;
            }

            /**
             * @brief Оператор разности итераторов.
             *
             * @tparam other_const Константность другого итератора
             * @param other Другой итератор
             * @return difference_type Расстояние между итераторами
             */
            template <bool other_const>
            difference_type operator-(const Iterator<other_const> &other) const noexcept
            {
                return ptr_ - other.ptr_;
            }

            /**
             * @brief Оператор сравнения на равенство.
             *
             * @tparam other_const Константность другого итератора
             * @param other Другой итератор
             * @return true Если итераторы указывают на один элемент
             */
            template <bool other_const>
            bool operator==(const Iterator<other_const> &other) const noexcept
            {
                return ptr_ == other.ptr_;
            }

            /**
             * @brief Оператор сравнения на неравенство.
             *
             * @tparam other_const Константность другого итератора
             * @param other Другой итератор
             * @return true Если итераторы указывают на разные элементы
             */
            template <bool other_const>
            bool operator!=(const Iterator<other_const> &other) const noexcept
            {
                return ptr_ != other.ptr_;
            }

            /**
             * @brief Оператор меньше.
             *
             * @tparam other_const Константность другого итератора
             * @param other Другой итератор
             * @return true Если текущий итератор указывает на более ранний элемент
             */
            template <bool other_const>
            bool operator<(const Iterator<other_const> &other) const noexcept
            {
                return ptr_ < other.ptr_;
            }

            /**
             * @brief Оператор меньше или равно.
             *
             * @tparam other_const Константность другого итератора
             * @param other Другой итератор
             * @return true Если текущий итератор указывает на тот же или более ранний элемент
             */
            template <bool other_const>
            bool operator<=(const Iterator<other_const> &other) const noexcept
            {
                return ptr_ <= other.ptr_;
            }

            /**
             * @brief Оператор больше.
             *
             * @tparam other_const Константность другого итератора
             * @param other Другой итератор
             * @return true Если текущий итератор указывает на более поздний элемент
             */
            template <bool other_const>
            bool operator>(const Iterator<other_const> &other) const noexcept
            {
                return ptr_ > other.ptr_;
            }

            /**
             * @brief Оператор больше или равно.
             *
             * @tparam other_const Константность другого итератора
             * @param other Другой итератор
             * @return true Если текущий итератор указывает на тот же или более поздний элемент
             */
            template <bool other_const>
            bool operator>=(const Iterator<other_const> &other) const noexcept
            {
                return ptr_ >= other.ptr_;
            }

            /**
             * @brief Дружественная функция для сложения числа и итератора.
             *
             * @param n Смещение
             * @param it Итератор
             * @return Iterator Новый итератор со смещением
             */
            friend Iterator operator+(difference_type n, const Iterator &it) noexcept
            {
                return it + n;
            }

            /**
             * @brief Перемещает итератор к следующему элементу, удовлетворяющему условию.
             *
             * @tparam Predicate Тип предиката (функции или лямбды)
             * @param condition Предикат, принимающий элемент типа T
             * @return Iterator& Ссылка на текущий итератор
             */
            template <typename Predicate>
            Iterator &operator+=(Predicate condition)
            {
                if (ptr_ == nullptr || ptr_ == end_)
                    return *this;

                if (condition(*ptr_) && ptr_ != start_)
                    ++ptr_;

                while (ptr_ != end_ && !condition(*ptr_))
                {
                    ++ptr_;
                }

                return *this;
            }

            /**
             * @brief Возвращает индекс текущего элемента в таблице.
             *
             * @return size_t Индекс элемента
             * @throws std::logic_error Если итератор невалиден
             */
            size_t get_index() const
            {
                if (ptr_ == nullptr || start_ == nullptr)
                    throw std::logic_error("Iterator does not point to valid element");
                return ptr_ - start_;
            }

            /**
             * @brief Проверяет, является ли итератор валидным.
             *
             * @return true Если итератор указывает на элемент в пределах таблицы
             */
            bool is_valid() const
            {
                return ptr_ != nullptr && start_ != nullptr &&
                       ptr_ >= start_ && ptr_ < end_;
            }
        };

        using value_type = T;
        using reference = T &;
        using const_reference = const T &;
        using iterator = Iterator<false>;      ///< Тип неконстантного итератора
        using const_iterator = Iterator<true>; ///< Тип константного итератора
        using difference_type = std::ptrdiff_t;
        using size_type = size_t;

        /**
         * @brief Конструктор по умолчанию.
         */
        Table() noexcept(std::is_nothrow_default_constructible_v<T>) = default;

        /**
         * @brief Конструктор с заданным размером.
         *
         * @param s Начальный размер таблицы
         */
        Table(size_t s) : capacity_(s), size_(s), data_(s > 0 ? new T[s] : nullptr)
        {
        }

        /**
         * @brief Конструктор копирования.
         *
         * @param other Таблица для копирования
         */
        Table(const Table &other) : capacity_(other.capacity_), size_(other.size_)
        {
            if (other.data_)
            {
                data_ = new T[capacity_];
                std::copy(other.data_, other.data_ + size_, data_);
            }
        }

        /**
         * @brief Конструктор перемещения.
         *
         * @param other Таблица для перемещения
         */
        Table(Table &&other) noexcept : capacity_(other.capacity_), size_(other.size_), data_(other.data_)
        {
            other.size_ = 0;
            other.capacity_ = 0;
            other.data_ = nullptr;
        }

        /**
         * @brief Деструктор.
         */
        ~Table() { delete[] data_; }

        /**
         * @brief Оператор присваивания копированием.
         *
         * @param other Таблица для копирования
         * @return Table& Ссылка на текущую таблицу
         */
        Table &operator=(const Table &other)
        {
            if (this != &other)
            {
                Table tmp(other);
                swap(tmp);
            }
            return *this;
        }

        /**
         * @brief Оператор присваивания перемещением.
         *
         * @param other Таблица для перемещения
         * @return Table& Ссылка на текущую таблицу
         */
        Table &operator=(Table &&other) noexcept
        {
            if (this != &other)
            {
                delete[] data_;
                size_ = other.size_;
                capacity_ = other.capacity_;
                data_ = other.data_;
                other.size_ = 0;
                other.capacity_ = 0;
                other.data_ = nullptr;
            }
            return *this;
        }

        /**
         * @brief Возвращает итератор на начало таблицы.
         *
         * @return iterator Неконстантный итератор
         */
        iterator begin() { return iterator(data_, data_, data_ + size_); }

        /**
         * @brief Возвращает итератор на конец таблицы.
         *
         * @return iterator Неконстантный итератор
         */
        iterator end() { return iterator(data_ + size_, data_, data_ + size_); }

        /**
         * @brief Возвращает константный итератор на начало таблицы.
         *
         * @return const_iterator Константный итератор
         */
        const_iterator begin() const { return const_iterator(data_, data_, data_ + size_); }

        /**
         * @brief Возвращает константный итератор на конец таблицы.
         *
         * @return const_iterator Константный итератор
         */
        const_iterator end() const { return const_iterator(data_ + size_, data_, data_ + size_); }

        /**
         * @brief Возвращает константный итератор на начало таблицы.
         *
         * @return const_iterator Константный итератор
         */
        const_iterator cbegin() const { return const_iterator(data_, data_, data_ + size_); }

        /**
         * @brief Возвращает константный итератор на конец таблицы.
         *
         * @return const_iterator Константный итератор
         */
        const_iterator cend() const { return const_iterator(data_ + size_, data_, data_ + size_); }

        /**
         * @brief Добавляет элемент в конец таблицы (копированием).
         *
         * @param new_value Новый элемент
         * @requires std::copy_constructible<T>
         */
        void add_elem(const T &new_value)
            requires std::copy_constructible<T>
        {
            if (size_ + 1 > capacity_)
            {
                resize();
            }
            data_[size_++] = new_value;
        }

        /**
         * @brief Добавляет элемент в конец таблицы (перемещением).
         *
         * @param new_value Новый элемент
         * @requires std::move_constructible<T>
         */
        void add_elem(T &&new_value)
            requires std::move_constructible<T>
        {
            if (size_ + 1 > capacity_)
            {
                resize();
            }
            data_[size_++] = std::move(new_value);
        }

        /**
         * @brief Удаляет элемент по индексу.
         *
         * @param ind Индекс удаляемого элемента
         * @throws std::out_of_range Если индекс вне диапазона
         */
        void delete_elem(size_type ind)
        {
            if (ind >= size_)
                throw std::out_of_range("Index out of range");

            for (size_type i = ind; i < size_ - 1; ++i)
            {
                data_[i] = std::move(data_[i + 1]);
            }
            --size_;
        }

        /**
         * @brief Удаляет элемент по итератору.
         *
         * @param pos Итератор на удаляемый элемент
         * @return iterator Итератор на элемент, следующий за удалённым
         * @throws std::out_of_range Если итератор невалиден
         */
        iterator erase(iterator pos)
        {
            if (!pos.is_valid() || pos.ptr_ < data_ || pos.ptr_ >= data_ + size_)
                throw std::out_of_range("Iterator out of range");

            size_t index = pos.get_index();

            // Сдвигаем элементы
            for (size_t i = index; i < size_ - 1; ++i)
            {
                data_[i] = std::move(data_[i + 1]);
            }
            --size_;

            if (index < size_)
                return iterator(data_ + index, data_, data_ + size_);
            else
                return end();
        }

        /**
         * @brief Возвращает текущее количество элементов.
         *
         * @return size_type Текущий размер таблицы
         */
        size_type size() const
        {
            return size_;
        }

        /**
         * @brief Возвращает максимально возможный размер таблицы.
         *
         * @return size_type Максимальный размер
         */
        size_type max_size() const noexcept
        {
            return std::numeric_limits<size_type>::max();
        }

        /**
         * @brief Проверяет, пуста ли таблица.
         *
         * @return true Если таблица пуста
         */
        bool empty() const noexcept { return size_ == 0; }

        /**
         * @brief Обменивает содержимое двух таблиц.
         *
         * @param o Таблица для обмена
         */
        void swap(Table &o) noexcept
        {
            std::swap(size_, o.size_);
            std::swap(capacity_, o.capacity_);
            std::swap(data_, o.data_);
        }

        /**
         * @brief Оператор доступа к элементу по индексу (неконстантный).
         *
         * @param index Индекс элемента
         * @return reference Ссылка на элемент
         * @throws std::out_of_range Если индекс вне диапазона
         */
        T &operator[](size_t index)
        {
            if (index >= size_)
                throw std::out_of_range("Index out of range");
            return data_[index];
        }

        /**
         * @brief Оператор доступа к элементу по индексу (константный).
         *
         * @param index Индекс элемента
         * @return const_reference Константная ссылка на элемент
         * @throws std::out_of_range Если индекс вне диапазона
         */
        const T &operator[](size_t index) const
        {
            if (index >= size_)
                throw std::out_of_range("Index out of range");
            return data_[index];
        }

        /**
         * @brief Очищает таблицу (не освобождает память).
         */
        void clear() noexcept
        {
            size_ = 0;
        }

        /**
         * @brief Возвращает текущую ёмкость таблицы.
         *
         * @return size_type Текущая ёмкость
         */
        size_type capacity() const noexcept
        {
            return capacity_;
        }

        /**
         * @brief Резервирует память для указанного количества элементов.
         *
         * @param new_capacity Новая ёмкость таблицы
         */
        void reserve(size_type new_capacity)
        {
            if (new_capacity > capacity_)
            {
                resize(new_capacity);
            }
        }
    };
}
