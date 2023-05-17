#include"includes.h"
class KeyChecker 
{
private:
    Keyboard::Key key;
    bool isPressure = false;
public:
    KeyChecker(Keyboard::Key newKey);
    bool isKeyPressure(Event event);
};