#pragma once

#include "query_panel.h"

namespace LoadLevelerMonitor{

namespace Panels{

class LlclassPanel : public QueryPanel
{
    Q_OBJECT

public:
    explicit LlclassPanel(QWidget *parent = 0);
    ~LlclassPanel();

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
