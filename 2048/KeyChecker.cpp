#include "KeyChecker.h"

KeyChecker::KeyChecker(Keyboard::Key newKey)
{
    this->key = newKey;
}

bool KeyChecker::isKeyPressure(Event event)
{
    // ��� ����������� ������� true ���������� ���� ���, ���� ������� �� ���������.
    if (key == event.key.code) // �����������, ���� ��� ������ ��� �������
        switch (event.type)
        {
        case event.KeyReleased: // ���� ���������, ��
            isPressure = true; // "��� ������" ����� �������, ���� �� ���������.
            return false; // ������� false, ���� �� ���������.
        case event.KeyPressed: // ���� ������, ��,
            if (isPressure) // ���� ��� �������, ��
            {
                isPressure = false; // "��� �������?" ������ �� �������, � �����������.
                return true; // ������� true!
            }
            else // �����
                return false; // ������� false!
        default:
            break;
        }
    return false; // ������� false, ���� ������� �� �� ����������
}
