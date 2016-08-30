#include <plugin_manager/plugin_manager.h>

#include <QApplication>
#include <QDir>
#include <QThreadPool>
#include <QSplashScreen>
#include <QPixmap>

using namespace PluginSystem;

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    QPixmap pixmap("://screen.png");
    QSplashScreen splash(pixmap);
    splash.show();
    app.processEvents();

    splash.showMessage("Loading basic settings...");
    // 设置线程池大小
    const int threadCount = QThreadPool::globalInstance()->maxThreadCount();
    QThreadPool::globalInstance()->setMaxThreadCount(qMax(4, 2 * threadCount));

    // 加载插件
    splash.showMessage("Loading plugins...");
    app.processEvents();
    PluginManager plugin_manager;

    QStringList plugin_paths;
    QDir rootDir = QApplication::applicationDirPath();
    rootDir.cdUp();
    const QString rootDirPath = rootDir.canonicalPath();
    QString plugin_path = rootDirPath + "/plugins";
    plugin_paths.append(plugin_path);

    PluginManager::setPluginPaths(plugin_paths);
    PluginManager::loadPlugins();

    splash.clearMessage();
    app.processEvents();
    splash.finish(nullptr);

    return app.exec();
}
