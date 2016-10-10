#include "query_category_list.h"

#include <QtDebug>
#include <algorithm>

using namespace LoadLevelerMonitor::Model;

QueryCategoryList::QueryCategoryList()
{

}

const QVector<QueryCategory> &QueryCategoryList::categoryList() const
{
    return list_;
}

void QueryCategoryList::clear()
{
    list_.clear();
    id_to_category_map_.clear();
    label_to_category_map_.clear();
}

void QueryCategoryList::append(const LoadLevelerMonitor::Model::QueryCategory &category)
{
    list_.append(category);
    registerCategory(list_.length()-1);
}

void QueryCategoryList::insert(int pos, const QueryCategory &category)
{
    list_.insert(pos, category);
    registerCategory(0);
}

QueryCategory &QueryCategoryList::operator[](int i)
{
    return list_[i];
}

const QueryCategory &QueryCategoryList::operator[](int i) const
{
    return list_[i];
}

int QueryCategoryList::indexFromId(const QString &id) const
{
    if(containsId(id))
        return id_to_category_map_[id];
    else
        return -1;
}

bool QueryCategoryList::containsId(const QString &id) const
{
    return id_to_category_map_.contains(id);
}

const QueryCategory &QueryCategoryList::categoryFromId(const QString &id) const
{
    int index = indexFromId(id);
    if(index != -1)
        return list_[index];
    else
        return valid_category_;
}

int QueryCategoryList::indexFromLabel(const QString &label) const
{
    if(containsLabel(label))
        return label_to_category_map_[label];
    else
        return -1;
}

bool QueryCategoryList::containsLabel(const QString &label) const
{
    return label_to_category_map_.contains(label);
}

const QueryCategory &QueryCategoryList::categoryFromLabel(const QString &label) const
{
    int index = indexFromLabel(label);
    if(index != -1)
        return list_[index];
    else
        return valid_category_;
}

void QueryCategoryList::registerCategory(int index)
{
    if(id_to_category_map_.contains(list_[index].id_))
    {
        qWarning()<<"[QueryCategoryList::registerCategory] Id:"<<list_[index].id_<<"is already registed, now update to new category.";
    }
    if(index == 0)
    {
        std::transform(id_to_category_map_.begin(), id_to_category_map_.end(), id_to_category_map_.begin(),
                       [=](int i){ return i+1; });
        id_to_category_map_[list_[index].id_] = index;
    }
    else if(index == list_.length()-1)
    {
        id_to_category_map_[list_[index].id_] = index;
    }
    else {
        qWarning()<<"[QueryCategoryList::registerCategory] index must be 0 or length()-1. Rebuilding hash...";
        rebuildHashMap();
    }


    if(label_to_category_map_.contains(list_[index].label_))
    {
        qWarning()<<"[QueryCategoryList::registerCategory] Label:"<<list_[index].label_<<"is already registed, now update to new category.";
    }


    if(index == 0)
    {
        std::transform(label_to_category_map_.begin(), label_to_category_map_.end(), label_to_category_map_.begin(),
                       [=](int i){ return i+1; });
        label_to_category_map_[list_[index].label_] = index;
    }
    else if(index == list_.length()-1)
    {
        label_to_category_map_[list_[index].label_] = index;
    }
    else {
        qWarning()<<"[QueryCategoryList::registerCategory] index must be 0 or length()-1. Rebuilding hash...";
        rebuildHashMap();
    }
}

void QueryCategoryList::rebuildHashMap()
{
    id_to_category_map_.clear();
    label_to_category_map_.clear();
    for( int i = 0; i< list_.size(); i++)
    {
        QueryCategory c = list_[i];
        id_to_category_map_[c.id_] = i;
        label_to_category_map_[c.label_] = i;
    }
}
