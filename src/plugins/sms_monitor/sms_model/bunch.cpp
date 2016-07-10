#include "bunch.h"

#include "node.h"

using namespace SmsMonitor::SmsModel;

Bunch::Bunch(QObject *parent):
    QStandardItemModel{parent}
{

}

/**
 * @brief Bunch::buildFromJsonStatus
 * @param json_object
 *          {
                'owner': owner,
                'repo': repo,
                'sms_name': sms_name,
                'sms_user': sms_user,
                'time': current_time,
                'status': bunch_dict
            }
 * @param parent
 * @return
 */
Bunch *Bunch::buildFromJsonStatus(const QJsonObject &data, QObject *parent)
{
    Bunch *bunch = new Bunch(parent);

    QString owner = data["owner"].toString();
    QString repo = data["repo"].toString();
    QString sms_name = data["sms_name"].toString();
    QString sms_user = data["sms_user"].toString();

    bunch->owner_ = owner;
    bunch->repo_ = repo;
    bunch->sms_name_ = sms_name;
    bunch->sms_user_ = sms_user;

//    QString time = data["time"].toString();

    QJsonObject status = data["status"].toObject();

    Node *node = Node::buildFromJsonStatus(status);

    bunch->invisibleRootItem()->appendRow(node);

    return bunch;
}
