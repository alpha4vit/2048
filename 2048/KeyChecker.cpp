#include "KeyChecker.h"

KeyChecker::KeyChecker(Keyboard::Key newKey)
{
    this->key = newKey;
}

bool KeyChecker::isKeyPressure(Event event)
{
    // При зацикленном запросе true отправится один раз, пока клавишу не отпустили.
    if (key == event.key.code) // Выполняется, если это нужная мне клавиша
        switch (event.type)
        {
        case event.KeyReleased: // Если отпустили, то
            isPressure = true; // "Это Нажате" будет нажатие, ведь мы отпустили.
            return false; // Вернуть false, ведь мы отпустили.
        case event.KeyPressed: // Если нажали, то,
            if (isPressure) // если это нажатие, то
            {
                isPressure = false; // "Это Нажатие?" больше не нажатие, а удерживание.
                return true; // Вернуть true!
            }
            else // Иначе
                return false; // вернуть false!
        default:
            break;
        }
    return false; // Вернуть false, если событие не от клавиатуры
}
