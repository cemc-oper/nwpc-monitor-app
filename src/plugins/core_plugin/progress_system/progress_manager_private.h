#pragma once

#include "progress_view.h"

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

    void setProgressView(ProgressView *view){
        progress_view_ = view;
    }

    ProgressView *progressView(){
        return progress_view_;
    }

    ProgressItemWidget *addTask(const QFuture<void> &future, const QString &title);

signals:

public slots:

private:
    ProgressManager *p;

    QVector<QFutureWatcher<void> *> task_list_;
    QPointer<ProgressView> progress_view_;

    friend class ProgressManager;
};

}
}
