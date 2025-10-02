#ifndef IFUSEMANAGER_H
#define IFUSEMANAGER_H

#include <QObject>

class iFuseManager : public QObject
{
    Q_OBJECT
public:
// explicit iFuseManager(QObject *parent = nullptr);
#ifdef Q_OS_LINUX
    static QList<QString> getMountPoints();
#endif
    static QStringList getMountArg(std::string &udid, QString &path);
    // TODO: need to implement a cross-platform mount and unmount method
    static bool linuxUnmount(const QString &path);
signals:
};

#endif // IFUSEMANAGER_H
