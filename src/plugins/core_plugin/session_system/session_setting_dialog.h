#pragma

#include <QDialog>

namespace Core{

namespace SessionSystem{

namespace Ui {
class SessionSettingDialog;
}

class SessionSettingDialog : public QDialog
{
    Q_OBJECT

public:
    explicit SessionSettingDialog(QWidget *parent = 0);
    ~SessionSettingDialog();

private:
    Ui::SessionSettingDialog *ui;
};

}

}
