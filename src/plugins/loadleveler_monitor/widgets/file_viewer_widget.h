#pragma once

#include <QWidget>

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
    Ui::FileViewerWidget *ui;
};

}
}
