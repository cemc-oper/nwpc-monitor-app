#include "node.h"

#include <QJsonArray>
#include <QBrush>

using namespace SmsMonitor::SmsModel;

Node::Node() :
    QStandardItem()
{

}

Node::Node(const QString &text):
    QStandardItem(text)
{

}

Node::~Node()
{

}

Node *Node::buildFromJsonStatus(const QJsonObject &data)
{
    Node *node = new Node{};

    QString name = data["name"].toString();
    QString status = data["status"].toString();

    node->setData(name, Qt::DisplayRole);
    node->setData(name, Node::DataType::Name);
    node->setData(status, Node::DataType::Status);

    QJsonArray children = data["children"].toArray();

    foreach(QJsonValue a_child, children)
    {
        QJsonObject a_child_object = a_child.toObject();
        Node *a_child_node = Node::buildFromJsonStatus(a_child_object);
        node->appendRow(a_child_node);
    }

    return node;
}

QVariant Node::data(int role) const
{
    if( role == DataType::Name)
    {
        return name_;
    }
    else if(role == DataType::Status)
    {
        return status_;
    }
    else if(role == DataType::Children)
    {
        QList<QStandardItem*> children;
        int row_count = this->rowCount();
        for(int i=0; i<row_count; i++)
        {
            children.append(this->child(i));
        }
        return QVariant::fromValue(children);
    }
    else if(role == Qt::BackgroundRole)
    {
        if(status_ == "unk")
            return QBrush(QColor(179,179,179));
        else if(status_ == "com")
            return QBrush(QColor(255,255,0));
        else if(status_ == "que")
            return QBrush(QColor(153,204,255));
        else if(status_ == "sub")
            return QBrush(QColor(0,255,255));
        else if(status_ == "act")
            return QBrush(QColor(0,255,0));
        else if(status_ == "sus")
            return QBrush(QColor(255,153,0));
        else if(status_ == "abo")
            return QBrush(QColor(255,0,0));
        else if(status_ == "shu")
            return QBrush(QColor(255,153,204));
        else if(status_ == "hal")
            return QBrush(QColor(204,153,255));
        else
            return QStandardItem::data(role);
    }
    else
    {
        return QStandardItem::data(role);
    }
}

void Node::setData(const QVariant &value, int role)
{
    if(role == DataType::Name)
    {
        name_ = value.toString();
        emit emitDataChanged();
        return;
    }
    else if(role == DataType::Status)
    {
        status_ = value.toString();
        emit emitDataChanged();
        return;
    }
    else
    {
        QStandardItem::setData(value, role);
        return;
    }
}

QString Node::getNodePath()
{
    QStringList path_token;
    QStandardItem *item = this;
    while(item != model()->invisibleRootItem())
    {
        path_token.push_front(item->data(Node::DataType::Name).toString());
        item = item->parent();
    }

    QString path = path_token.join('/');
    return path;
}
