#ifndef IPLUGIN_H
#define IPLUGIN_H

#include "plugin_system_global.h"

#include <QObject>

class IPlugin : public QObject
{
    Q_OBJECT
public:
    explicit IPlugin(QObject *parent = 0);

signals:

public slots:
};

#endif // IPLUGIN_H
