
#ifndef __SYMBOID_SDK_UICONTROLS_QT_QINPUTITEMOBJECT_H__
#define __SYMBOID_SDK_UICONTROLS_QT_QINPUTITEMOBJECT_H__

#include "sdk/uicontrols-qt/defs.h"
#include <QObject>
#include <QQmlComponent>
#include <QQmlListProperty>
#include <QQuickItem>

class QInputOperation : public QObject
{
    Q_OBJECT

public:
    static constexpr const char* qml_name = "InputOperation";

public:
    QInputOperation(QObject* parent = Q_NULLPTR);

public:
    Q_PROPERTY(QString title MEMBER mTitle WRITE setTitle NOTIFY titleChanged)
private:
    QString mTitle;
    void setTitle(const QString& title);
signals:
    void titleChanged();

public:
    Q_PROPERTY(QQmlComponent* control MEMBER mControl WRITE setControl NOTIFY controlChanged)
private:
    QQmlComponent* mControl;
    void setControl(QQmlComponent* control);
signals:
    void controlChanged();

public:
    Q_PROPERTY(bool canExec MEMBER mCanExec WRITE setCanExec NOTIFY canExecChanged)
private:
    bool mCanExec;
    void setCanExec(bool canExec);
signals:
    void canExecChanged();

signals:
    void exec();
};

class QInputOperationsItem : public QQuickItem
{
    Q_OBJECT

    static void append(QQmlListProperty<QInputOperation>* list, QInputOperation* value);
    static QInputOperation* at(QQmlListProperty<QInputOperation>* list, int index);
    static void clear(QQmlListProperty<QInputOperation>* list);
    static int count(QQmlListProperty<QInputOperation>* list);

public:
    static constexpr const char* qml_name = "InputOperations";

public:
    QInputOperationsItem(QQuickItem* parent = Q_NULLPTR);

public:
    Q_PROPERTY(QQmlListProperty<QInputOperation> operations READ operations NOTIFY operationsChanged)
private:
    QQmlListProperty<QInputOperation> operations();
signals:
    void operationsChanged();

public:
    Q_PROPERTY(int operationCount READ operationCount NOTIFY operationCountChanged)
private:
    int operationCount() const;
signals:
    void operationCountChanged();

private:
    QList<QInputOperation*> mList;
};

#endif // __SYMBOID_SDK_UICONTROLS_QT_QINPUTITEMOBJECT_H__
