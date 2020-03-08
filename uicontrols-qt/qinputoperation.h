
#ifndef __SYMBOID_SDK_UICONTROLS_QT_QINPUTITEMOBJECT_H__
#define __SYMBOID_SDK_UICONTROLS_QT_QINPUTITEMOBJECT_H__

#include "sdk/uicontrols-qt/defs.h"
#include <QObject>
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
    Q_PROPERTY(QQuickItem* control MEMBER mControl WRITE setControl NOTIFY controlChanged)
private:
    QQuickItem* mControl;
    void setControl(QQuickItem* control);
signals:
    void controlChanged();

public:
    Q_PROPERTY(QQuickItem* execPane MEMBER mExecPane WRITE setExecPane NOTIFY execPaneChanged)
private:
    QQuickItem* mExecPane;
    void setExecPane(QQuickItem* execPane);
signals:
    void execPaneChanged();

public:
    Q_PROPERTY(bool canExec MEMBER mCanExec WRITE setCanExec NOTIFY canExecChanged)
private:
    bool mCanExec;
    void setCanExec(bool canExec);
signals:
    void canExecChanged();

signals:
    void exec();
public slots:
    Q_INVOKABLE void execute();
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
