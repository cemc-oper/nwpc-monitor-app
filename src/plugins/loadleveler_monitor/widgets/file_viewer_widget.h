#pragma once

#include <QWidget>
#include <QPointer>

QT_BEGIN_NAMESPACE
class QWebEnginePage;
QT_END_NAMESPACE
namespace LoadLevelerMonitor{

namespace Widgets{
namespace Ui {
class FileViewerWidget;
}

class FileViewerWidget : public QWidget
{
    Q_OBJECT

public:
    explicit FileViewerWidget(QWidget *parent = 0);
    ~FileViewerWidget();

    void setFilePath(const QString &path);
    void setFileContext(const QString &context);

public slots:
    void receiveResponse(const QString &response);

private:
    void showInWebPage(const QString &script);

    Ui::FileViewerWidget *ui;
    QPointer<QWebEnginePage> web_page_;
};

}
}
