#include "eeprom.h"

Eeprom::Eeprom(int size)
{
    setFileName("eeprom.bin");
    if (!exists())
    {
        QByteArray dummy(size, '\0');
        open();
        write(dummy);
        close();
    }
}

void Eeprom::open()
{
    QFile::open(QIODevice::ReadWrite);
}
