#ifndef EEPROM_H
#define EEPROM_H

#include <QFile>

class Eeprom : public QFile
{
public:
    Eeprom(int size);

    void open();

private:
};

#endif // EEPROM_H
