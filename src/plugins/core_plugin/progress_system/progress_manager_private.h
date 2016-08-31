#pragma once

#include "progress_view.h"
#include "progress_status_bar_widget.h"

#include <QObject>
#include <QVector>
#include <QFuture>
#include <QFutureWatcher>
#include <QPointer>

namespace Core{

namespace ProgressSystem{

class ProgressManager;
class ProgressItemWidget;

class ProgressManagerPrivate : public QObject
{
    Q_OBJECT
public:
    explicit ProgressManagerPrivate(ProgressManager *parent = 0);
    ~ProgressManagerPrivate();

    void init();

    void setProgressView(ProgressView *view);
    ProgressView *progressView();

    ProgressStatusBarWidget *statusBarWidget();

    ProgressItemWidget *addTask(const QFuture<void> &future, const QString &title);

signals:

public slots:

private:
    void updateStatusBarWidget();

    ProgressManager *p;

    QVector<QFutureWatcher<void> *> task_list_;
    QPointer<ProgressView> progress_view_; // owned by mianwindow
    QPointer<ProgressStatusBarWidget> status_bar_widget_; // owned by this

    friend class ProgressManager;
};

}
}
