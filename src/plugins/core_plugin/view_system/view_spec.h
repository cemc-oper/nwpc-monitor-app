#pragma once

#include <QObject>
#include <QString>
#include <QPointer>

namespace PluginSystem{
class PluginSpec;
}

namespace Core{

namespace ViewSystem{

class IView;

class ViewSpec : public QObject
{
    Q_OBJECT
public:
    explicit ViewSpec(QObject *parent = 0);
    ~ViewSpec();

    PluginSystem::PluginSpec *pluginSpec() const;
    void setPluginSpec(PluginSystem::PluginSpec *plugin_spec);

    QString id() const;
    void setId(const QString &id);

    QString name() const;
    void setName(const QString &name);

    QStringList pathList() const;
    QString path() const;
    void setPathList(const QStringList &pathList);

    IView *view();
    void setView(IView *view);

signals:

public slots:

private:
    // 所属
    PluginSystem::PluginSpec *plugin_spec_;

    // 名称和路径
    QString id_;
    QString name_;
    QStringList path_list_;

    // 内容
    QPointer<IView> view_;
};

}

}
