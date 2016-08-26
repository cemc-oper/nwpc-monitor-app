#pragma once

#include "query_panel.h"

namespace LoadLevelerMonitor{

namespace Panels{

class LlqPanel : public QueryPanel
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

    // chart style
    void updateChartStylePage() override;
};

}

}
