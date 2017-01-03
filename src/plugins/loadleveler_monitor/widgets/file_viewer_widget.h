#pragma once

#include <QWidget>
#include <QPointer>
#include <QMap>

QT_BEGIN_NAMESPACE
class QAction;
class QActionGroup;
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

    void setRequestArguments(const QMap<QString, QString> args);
    void setFilePath(const QString &path);
    void setFileContext(const QString &context);

public slots:
    void receiveResponse(const QString &response);

private slots:
    void slotStyleActionTriggered(QAction *action);

    // TODO: repeat is evil: text browser
    void slotScrollToEnd(bool flag);
    void scrollToEnd();

private:
    void setupActions();
    void setupStyle();
    void showInWebPage(const QString &script);

    Ui::FileViewerWidget *ui;
    QPointer<QWebEnginePage> web_page_;

    QVector<QAction *> style_action_list_;
    QPointer<QActionGroup> style_action_group_;

    QMap<QString, QString> request_args_;
    bool is_scroll_to_end_;
};

}
}
