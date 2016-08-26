#include "llclass_panel.h"
#include "ui_query_panel.h"

using namespace LoadLevelerMonitor::Panels;

LlclassPanel::LlclassPanel(QWidget *parent) :
    QueryPanel(parent)
{
    setupTemplate();
    setupStyle();
}

LlclassPanel::~LlclassPanel()
{

}

void LlclassPanel::slotRequestQuery()
{

}

void LlclassPanel::slotReciveCommandResponse(const ProgressUtil::ShellCommandResponse &command_response)
{

}

void LlclassPanel::slotQueryModelContextMenuRequest(const QPoint &global_point, const QModelIndex &index)
{

}

void LlclassPanel::setupTemplate()
{

}

void LlclassPanel::setupStyle()
{

}

void LlclassPanel::updateChartStylePage()
{

}
