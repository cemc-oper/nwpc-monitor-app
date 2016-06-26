#include <plugin_manager/plugin_manager.h>

#include <QApplication>
#include <QDir>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    PluginManager plugin_manager;

    QStringList plugin_paths;

    QDir rootDir = QApplication::applicationDirPath();
    rootDir.cdUp();
    const QString rootDirPath = rootDir.canonicalPath();
    QString plugin_path = rootDirPath + "/plugins";

    plugin_paths.append(plugin_path);

    PluginManager::setPluginPaths(plugin_paths);
    PluginManager::loadPlugins();

    return app.exec();
}
