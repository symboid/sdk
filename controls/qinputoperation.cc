
#include "sdk/controls/setup.h"
#include "sdk/controls/qinputoperation.h"

QInputOperation::QInputOperation(QObject *parent)
    : QObject(parent)
    , mControl(nullptr)
    , mExecPane(nullptr)
    , mWithButtons(true)
{
}

void QInputOperation::setTitle(const QString& title)
{
    if (mTitle != title)
    {
        mTitle = title;
        emit titleChanged();
    }
}

void QInputOperation::setControl(QQuickItem* control)
{
    if (mControl != control)
    {
        mControl = control;
        emit controlChanged();
    }
}

void QInputOperation::setExecPane(QQuickItem *execPane)
{
    if (mExecPane != execPane)
    {
        mExecPane = execPane;
        emit execPaneChanged();
    }
}

void QInputOperation::setCanExec(bool canExec)
{
    if (mCanExec != canExec)
    {
        mCanExec = canExec;
        emit canExecChanged();
    }
}

void QInputOperation::setLeftAligned(bool leftAligned)
{
    if (mLeftAligned != leftAligned)
    {
        mLeftAligned = leftAligned;
        emit leftAlignedChanged();
    }
}

void QInputOperation::setWithButtons(bool withButtons)
{
    if (mWithButtons != withButtons)
    {
        mWithButtons = withButtons;
        emit withButtonsChanged();
    }
}

void QInputOperation::execute()
{
    emit exec();
    emit finishExec();
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
