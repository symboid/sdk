
#ifndef __SYMBOID_SDK_DOX_QT_DOCUMENT_H__
#define __SYMBOID_SDK_DOX_QT_DOCUMENT_H__

#include "sdk/dox-qt/defs.h"
#include <QObject>
#include <QList>
#include <QQmlListProperty>
#include <QJsonObject>
#include <QJsonArray>

template <class QmlList, class ListItem>
class ListProperty
{
private:
    static void append(QQmlListProperty<ListItem>* listProperty, ListItem* value)
    {
        if (QmlList* itemList = qobject_cast<QmlList*>(listProperty->object))
        {
            itemList->mList.append(value);
        }
    }

    static ListItem* at(QQmlListProperty<ListItem>* listProperty, int index)
    {
        QmlList* itemList = qobject_cast<QmlList*>(listProperty->object);
        return itemList ? itemList->mList.at(index) : Q_NULLPTR;
    }

    static void clear(QQmlListProperty<ListItem>* listProperty)
    {
        if (QmlList* itemList = qobject_cast<QmlList*>(listProperty->object))
        {
            itemList->mList.clear();
        }

    }

    static int count(QQmlListProperty<ListItem>* listProperty)
    {
        QmlList* itemList = qobject_cast<QmlList*>(listProperty->object);
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

class QDocumentNode : public QObject, public ListProperty<QDocumentNode, QDocumentNode> {
    Q_OBJECT
    Q_CLASSINFO("DefaultProperty", "childNodes")
public:
    static constexpr const char* qml_name = "DocumentNode";
public:
    QDocumentNode(QObject* parent = Q_NULLPTR);

public:
    Q_PROPERTY(QQmlListProperty<QDocumentNode> childNodes READ childNodes NOTIFY childNodesChanged)
private:
    QQmlListProperty<QDocumentNode> childNodes();
signals:
    void childNodesChanged();

protected:
    QJsonObject toJsonObject() const;
};

class QDocument : public QDocumentNode
{
    Q_OBJECT
public:
    static constexpr const char* qml_name = "Document";
public:
    QDocument(QObject* parent = Q_NULLPTR);

public:
    Q_PROPERTY(QString title MEMBER mTitle WRITE setTitle NOTIFY titleChanged)
private:
    QString mTitle;
    void setTitle(const QString& title);
signals:
    void titleChanged();

public:
    Q_INVOKABLE void save();
};


#endif // __SYMBOID_SDK_DOX_QT_DOCUMENT_H__
