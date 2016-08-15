#pragma once

#include <QString>

namespace Core{

namespace Constrants {

namespace MenuBar {
const QString MENU_BAR = "NwpcMonitorApp.MenuBar";
}

namespace Menu {

const QString MENU_FILE = "NwpcMonitorApp.Menu.File";
const QString MENU_WINDOW = "NwpcMonitorApp.Menu.Window";
const QString MENU_PERSPECTIVE = "NwpcMonitorApp.Menu.Perspective";

namespace Window{
const QString MENU_VIEW = "NwpcMonitorApp.Menu.Window.View";
}

const QString MENU_HELP = "NwpcMonitorApp.Menu.Help";

}

namespace Action {

const QString ACTION_EXIT = "NwpcMonitorApp.Action.Exit";
const QString ACTION_ABOUT = "NwpcMonitorApp.Action.About";

const QString ACTION_PERSPECTIVE_PREFIX = "NwpcMonitorApp.Action.Perspective";
const QString ACTION_VIEW_PREFIX = "NwpcMonitorApp.Action.View";

}

namespace ActionGruop {
const QString ACTION_GROUP_PERSPECTIVE = "NwpcMonitorApp.ActionGroup.Perspective";
}

}

}
