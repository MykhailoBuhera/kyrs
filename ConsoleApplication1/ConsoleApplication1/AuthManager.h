#pragma once
#include <vector>
#include <string>
#include <unordered_map>

/**
 * @class AuthManager
 * @brief Клас для керування автентифікацією та обліковими записами користувачів.
 * @details Відповідає за завантаження, збереження, перевірку та керування
 * даними користувачів, включаючи логін, пароль та права доступу (адміністратор).
 */
class AuthManager {
public:
    /**
     * @brief Конструктор за замовчуванням.
     * @details Ініціалізує менеджер та завантажує користувачів з файлу 'users.txt'.
     */
    AuthManager();

    /**
     * @brief Конструктор з параметрами для ініціалізації з вектора.
     * @param users Вектор рядків у форматі "username:password".
     */
    AuthManager(const std::vector<std::string>& users);

    /**
     * @brief Конструктор копіювання.
     */
    AuthManager(const AuthManager& other);

    /**
     * @brief Конструктор переміщення.
     */
    AuthManager(AuthManager&& other) noexcept;

    /**
     * @brief Деструктор.
     * @details Автоматично зберігає всі зміни у файлі користувачів при знищенні об'єкта.
     */
    ~AuthManager();

    /**
     * @brief Завантажує дані користувачів з файлу 'users.txt'.
     */
    void loadUsers();

    /**
     * @brief Зберігає поточні дані користувачів у файл 'users.txt'.
     */
    void saveUsers();

    /**
     * @brief Запускає процес входу користувача в систему.
     * @return true, якщо вхід успішний, інакше false.
     */
    bool login();

    /**
     * @brief Перевіряє, чи є поточний користувач адміністратором.
     * @return true, якщо поточний користувач - 'admin', інакше false.
     */
    bool isAdmin() const;

    /**
     * @brief Дозволяє змінити поточного користувача.
     * @return true, якщо вхід нового користувача успішний, інакше false.
     */
    bool reauthenticate();

    /**
     * @brief Отримує логін поточного залогованого користувача.
     * @return Рядок з логіном поточного користувача.
     */
    std::string getCurrentUser() const;

    /**
     * @brief Додає нового користувача до системи (тільки для адміністратора).
     */
    void addUser();

    /**
     * @brief Видаляє існуючого користувача (тільки для адміністратора).
     */
    void deleteUser();

    /**
     * @brief Виводить список всіх зареєстрованих користувачів.
     */
    void listUsers();

private:
    std::string filename;
    std::unordered_map<std::string, std::string> users;
    std::string currentUser;
    int deleteAttempts;
};