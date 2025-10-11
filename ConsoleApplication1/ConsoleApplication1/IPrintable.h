#pragma once
#include <string>

/**
 * @class IPrintable
 * @brief Інтерфейс, що визначає контракт для об'єктів, які можна роздрукувати.
 * @details Будь-який клас, що реалізує цей інтерфейс, зобов'язаний
 * надати реалізацію методів print() та toCSV().
 */
class IPrintable {
public:
    /**
     * @brief Чисто віртуальний метод для виводу інформації в консоль.
     */
    virtual void print() const = 0;

    /**
     * @brief Чисто віртуальний метод для серіалізації об'єкта в CSV-формат.
     * @return Рядок у форматі CSV.
     */
    virtual std::string toCSV() const = 0;

    /**
     * @brief Віртуальний деструктор для коректного поліморфного видалення.
     */
    virtual ~IPrintable() {}
};