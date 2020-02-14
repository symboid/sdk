
#include "sdk/uicontrols-qt/setup.h"
#include "sdk/uicontrols-qt/qinputoperation.h"

QInputOperation::QInputOperation(QObject *parent)
    : QObject(parent)
{
}

void QInputOperation::setTitle(const QString& title)
{
    if (mTitle != title) {
        mTitle = title;
        emit titleChanged();
    }
}

void QInputOperation::setControl(QQmlComponent* control)
{
    if (mControl != control) {
        mControl = control;
        emit controlChanged();
    }
}

void QInputOperation::setCanExec(bool canExec)
{
    if (mCanExec != canExec) {
        mCanExec = canExec;
        emit canExecChanged();
    }
}

void QInputOperationsItem::append(QQmlListProperty<QInputOperation>* list, QInputOperation* value)
{
    if (QInputOperationsItem* itemList = qobject_cast<QInputOperationsItem*>(list->object))
    {
        itemList->mList.append(value);
    }
}

QInputOperation* QInputOperationsItem::at(QQmlListProperty<QInputOperation>* list, int index)
{
    QInputOperationsItem* itemList = qobject_cast<QInputOperationsItem*>(list->object);
    return itemList ? itemList->mList.at(index) : Q_NULLPTR;
}

void QInputOperationsItem::clear(QQmlListProperty<QInputOperation>* list)
{
    if (QInputOperationsItem* itemList = qobject_cast<QInputOperationsItem*>(list->object))
    {
        itemList->mList.clear();
    }

}

int QInputOperationsItem::count(QQmlListProperty<QInputOperation>* list)
{
    QInputOperationsItem* itemList = qobject_cast<QInputOperationsItem*>(list->object);
    return itemList ? itemList->mList.size() : 0;
}

QInputOperationsItem::QInputOperationsItem(QQuickItem* parent)
    : QQuickItem(parent)
{
}

QQmlListProperty<QInputOperation> QInputOperationsItem::operations()
{
    return QQmlListProperty<QInputOperation>(this, &mList, &append, &count, &at, &clear);
}

int QInputOperationsItem::operationCount() const
{
    return mList.size();
}
