
#ifndef __SYMBOID_SDK_UICONTROLS_QT_LISTPROPERTYADAPTER_H__
#define __SYMBOID_SDK_UICONTROLS_QT_LISTPROPERTYADAPTER_H__

#include "sdk/uicontrols-qt/defs.h"
#include <QQmlListProperty>
#include <QList>

template <class QmlList, class ListItem>
class ListPropertyAdapter
{
private:
    inline static QmlList* qml_list_cast(QQmlListProperty<ListItem>* listProperty)
    {
        return qobject_cast<QmlList*>(listProperty->object);
    }

    static void append(QQmlListProperty<ListItem>* listProperty, ListItem* value)
    {
        if (QmlList* itemList = qml_list_cast(listProperty))
        {
            itemList->mList.append(value);
        }
    }

    static ListItem* at(QQmlListProperty<ListItem>* listProperty, int index)
    {
        QmlList* itemList = qml_list_cast(listProperty);
        return itemList ? itemList->mList.at(index) : Q_NULLPTR;
    }

    static void clear(QQmlListProperty<ListItem>* listProperty)
    {
        if (QmlList* itemList = qml_list_cast(listProperty))
        {
            itemList->mList.clear();
        }

    }

    static int count(QQmlListProperty<ListItem>* listProperty)
    {
        QmlList* itemList = qml_list_cast(listProperty);
        return itemList ? itemList->mList.size() : 0;
    }

protected:
    QList<ListItem*> mList;

public:
    QQmlListProperty<ListItem> qmlList(QObject* parent)
    {
        return QQmlListProperty<ListItem>(parent, &mList, &append, &count, &at, &clear);
    }
};

#endif // __SYMBOID_SDK_UICONTROLS_QT_LISTPROPERTYADAPTER_H__
