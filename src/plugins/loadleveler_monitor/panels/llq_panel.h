#pragma once

#include "../loadleveler_monitor_global.h"
#include "query_panel.h"

namespace LoadLevelerMonitor{

namespace Panels{

class LOADLEVELER_MONITOR_EXPORT LlqPanel : public QueryPanel
{
    Q_OBJECT

public:
    explicit LlqPanel(QWidget *parent = 0);
    ~LlqPanel();

public slots:
    void slotRequestQuery() override;
    void slotReciveCommandResponse(const ProgressUtil::ShellCommandResponse &command_response) override;

private slots:
    // table style
    void slotQueryModelContextMenuRequest(const QPoint &global_point, const QModelIndex &index) override;

private:
    void setupTemplate() override;
    void setupStyle() override;

    void setupOperationAction();

    void cancelSelectedJobs();
    void releaseSelectedJobs();

    // chart style
    void updateChartStylePage() override;

    static QStringList getLlqJobIdList(Model::QueryModel *model,const QList<int> &row_list);

    QPointer<QAction> cancel_action_;
    QPointer<QAction> release_action_;
};

}

}
