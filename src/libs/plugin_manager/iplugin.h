#ifndef IPLUGIN_H
#define IPLUGIN_H

#include "plugin_system_global.h"

#include <QObject>
#include <QString>

class PLUGIN_SYSTEM_EXPORT IPlugin : public QObject
{
    Q_OBJECT
public:
    explicit IPlugin(QObject *parent = 0);
    ~IPlugin();

    virtual bool initialize(const QStringList& arguments, QString* error_string) = 0;
    virtual void pluginsInitialized() = 0;
    virtual void aboutToShutDown() = 0;

    void addObject(QObject *obj);
    void removeObject(QObject *obj);

signals:

public slots:
};

#endif // IPLUGIN_H
