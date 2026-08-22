#ifndef S21_CONTAINERS_SRC_S21_ARRAY_H
#define S21_CONTAINERS_SRC_S21_ARRAY_H

/**
 * @namespace s21
 * Пространство имён для пользовательских контейнеров.
 */

namespace s21 {
/**
 * @class array
 * @brief Класс шаблонного статического массива фиксированного размера.
 * @tparam T Тип элементов массива.
 * @tparam N Размер массива.
 */
template <typename T, size_t N>
class array {
 public:
  using value_type = T;   ///< Тип элементов массива
  using reference = T &;  ///< Ссылка на элемент массива
  using const_reference = const T &;  ///< Константная ссылка
  using iterator = T *;  ///< Итератор (указатель на T)
  using const_iterator = const T *;  ///< Константный итератор
  using size_type = std::size_t;  ///< Тип для размеров и индексов

  /**
   * @brief Конструктор по умолчанию
   * Инициализирует все элементы массива значениями по умолчанию типа T
   */
  array();

  /**
   * @brief Конструктор из initializer_list
   * Инициализирует массив элементами из списка, остальные заполняет значениями
   * по умолчанию
   * @param items список инициализации
   */
  array(std::initializer_list<value_type> const &items);

  /**
   * @brief Конструктор копирования
   * Копирует элементы из другого массива
   * @param a другой массив
   */
  array(const array &a);

  /**
   * @brief Конструктор перемещения
   * Перемещает элементы из другого массива
   * @param a другой массив (rvalue-ссылка)
   */
  array(array &&a) noexcept;

  /**
   * @brief Деструктор по умолчанию
   */
  ~array();

  /**
   * @brief Оператор присваивания перемещением
   * @param a другой объект для перемещения
   * @return ссылка на текущий объект
   */
  array &operator=(array &&a);

  /**
   * @brief Доступ к элементу с проверкой
   * @param pos индекс элемента
   * @return ссылка на элемент
   * @throws std::out_of_range если индекс вне диапазона
   */
  reference at(size_type pos);

  /**
   * @brief Доступ к элементу без проверки
   * @param pos индекс элемента
   * @return ссылка на элемент
   */
  reference operator[](size_type pos);

  /**
   * @brief Получение первого элемента массива
   * @return константная ссылка на первый элемент
   */
  const_reference front() const;

  /**
   * @brief Получение последнего элемента массива
   * @return константная ссылка на последний элемент
   */
  const_reference back() const;

  /**
   * @brief Получить указатель на внутренний массив
   * @return указатель на нулевой элемент
   */
  iterator data();

  /**
   * @brief Итератор на начало массива
   * @return итератор (указатель) на первый элемент
   */
  iterator begin();

  /**
   * @brief Итератор на элемент после последнего
   * @return итератор (указатель) на позицию после последнего элемента
   */
  iterator end();

  /**
   * @brief Проверка, пустой ли массив
   * @return false, так как размер статический и всегда > 0
   */
  bool empty() const;

  /**
   * @brief Получить размер массива
   * @return размер массива
   */
  size_type size() const;

  /**
   * @brief Максимальный размер массива
   * @return максимальный размер массива (равен size)
   */
  size_type max_size() const;

  /**
   * @brief Обмен содержимым с другим массивом
   * @param other другой массив
   */
  void swap(array &other);

  /**
   * @brief Заполнить все элементы заданным значением
   * @param value значение для заполнения
   */
  void fill(const_reference value);

 private:
  // необходимо для хранения всех элементов контейнера внутри класса
  value_type arr[N];  ///< Внутренний статический массив
};

// Реализации методов

template <typename T, size_t N>
array<T, N>::array() {
  for (size_t i = 0; i < N; i++) {
    arr[i] = T{};  // Заполнение нулями (или значениями по умолчанию)
  }
}

template <typename T, size_t N>
array<T, N>::array(const array &a) {
  for (size_t i = 0; i < N; i++) {
    arr[i] = a.arr[i];  // копируем элементы из а
  }
}

template <typename T, size_t N>
array<T, N>::array(std::initializer_list<value_type> const &items) {
  size_t i = 0;
  for (const auto &item : items) {
    if (i < N) {
      arr[i++] = item;  // инициализируем из списка
    } else
      break;
  }
  for (; i < N; ++i) {
    arr[i] = T{};  // заполняем остаток значениями по умолчанию
  }
}

template <typename T, size_t N>
array<T, N>::array(array &&a) noexcept {
  for (size_t i = 0; i < N; ++i) {
    arr[i] = std::move(a.arr[i]);  // перемещаем элементы из а
  }
}

template <typename T, size_t N>  // деструктор
array<T, N>::~array() = default;

template <typename T, size_t N>  // возвращает ссылку на элемент
typename array<T, N>::reference array<T, N>::operator[](size_type pos) {
  return arr[pos];  // доступ по индексу без проверки
}

template <typename T, size_t N>  // проверяет, не вышел ли индекс за границы, и
                                 // выбрасывает исключение std::out_of_range.
typename array<T, N>::reference array<T, N>::at(size_type pos) {
  if (pos >= N) {
    throw std::out_of_range(
        "Index out of range");  // проверка на выход за границы
  }
  return arr[pos];
}

template <typename T, size_t N>
typename array<T, N>::const_reference array<T, N>::front() const {
  return arr[0];
}

template <typename T, size_t N>
typename array<T, N>::const_reference array<T, N>::back() const {
  return arr[N - 1];  // последний элемент массива по ссылке, метод не изменяет
                      // объект (const)
}

template <typename T, size_t N>
typename array<T, N>::iterator array<T, N>::data() {
  return arr;  // указатель на первый элемент массива (начало данных)
}

template <typename T, size_t N>
typename array<T, N>::iterator
array<T, N>::begin() {  // объявляем метод begin(), возвращающий iterator (T*)
  return arr;  // возвращаем указатель на первый элемент массива arr (arr ==
               // &arr[0])
}

template <typename T, size_t N>
typename array<T, N>::iterator
array<T, N>::end() {  // метод end(), возвращающий iterator
  return arr + N;  // возвращаем указатель на позицию после последнего элемента
}

template <typename T, size_t N>
bool array<T, N>::empty() const {
  return N == 0;  // массив пуст, если размер 0
}

template <typename T, size_t N>
typename array<T, N>::size_type array<T, N>::size() const {
  return N;  // возвращаем размер массива
}

template <typename T, size_t N>
typename array<T, N>::size_type array<T, N>::max_size() const {
  return N;  // максимальный размер равен размеру
}

template <typename T, size_t N>
void array<T, N>::swap(array &other) {
  for (size_type i = 0; i < N; i++) {
    std::swap(arr[i], other.arr[i]);  // обмениваем элементы с other
  }
}

template <typename T, size_t N>
void array<T, N>::fill(const_reference value) {
  for (size_type i = 0; i < N; i++) {
    arr[i] = value;  // заполняем все элементы значением
  }
}

template <typename T, size_t N>
array<T, N> &array<T, N>::operator=(array &&a) {
  if (this != &a) {
    for (size_t i = 0; i < N; ++i) {
      arr[i] = std::move(a.arr[i]);
    }
  }
  return *this;
}

}  // namespace s21

#endif  // S21_CONTAINERS_SRC_S21_ARRAY_H
