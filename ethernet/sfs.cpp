#include "core/sfs.h"
#include <QFile>
#include <QByteArray>
#include "core/macros.h"
#include <QDebug>

#define _SFS_FILE   STRINGIFY(SFS_FILE)

Sfs::Sfs()
{
    static QByteArray sfs_data;

    QFile file(_SFS_FILE);
    if (!file.exists())
        file.setFileName("sfs.bin");
    if (file.open(QIODevice::ReadOnly))
    {
        sfs_data = file.readAll();
        file.close();

        m_head = reinterpret_cast<Entry*>(sfs_data.data());
        m_entry = nullptr;
    }
    else
    {
        qDebug() << "SFS file not found!";
        qDebug() << "Path to SFS file:" << _SFS_FILE;
    }
}

const char *Sfs::open(const ByteArray &name)
{
    for (m_entry = m_head; m_entry; m_entry = m_entry->next())
    {
        ByteArray ename = m_entry->name();
        if (name == ename)
            return m_entry->data();
    }
    return 0L;
}
