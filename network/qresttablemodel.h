
#ifndef __SYMBOID_SDK_NETWORK_QRESTTABLEMODEL_H__
#define __SYMBOID_SDK_NETWORK_QRESTTABLEMODEL_H__

#include "sdk/network/defs.h"
#include "sdk/network/qrestmodel.h"
#include <QJsonArray>
#include <QJsonObject>

class SDK_NETWORK_API QRestTableJSON : public QRestCaller
{
    Q_OBJECT

public:
    QRestTableJSON(QObject* parent = Q_NULLPTR);

private:
    void fetchResult(QNetworkReply* reply) override;

private:
    QJsonArray mResultArray;
public:
    const QJsonArray& resultArray() const;

public:
    QString mArrayPath;
};

class SDK_NETWORK_API QRestTableModel : public QRestModel
{
    Q_OBJECT

public:
    static constexpr const char* qml_name = "RestTableModel";

public:
    QRestTableModel(QObject* parent = Q_NULLPTR);

public:
    int rowCount(const QModelIndex& parent = QModelIndex()) const override;
    QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override;
    QHash<int, QByteArray> roleNames() const override;

private:
    QRestCaller* restCaller() override { return &mRestTable; }
    QRestTableJSON mRestTable;
public:
    const QRestTableJSON& restTable() const;

public:
    Q_PROPERTY(QStringList columnNames READ columnNames WRITE setColumnNames NOTIFY columnNamesChanged)
    const QStringList& columnNames() const;
    void setColumnNames(const QStringList& columnNames);
private:
    QStringList mColumnNames;
signals:
    void columnNamesChanged();


public:
    Q_INVOKABLE QJsonObject object(int objectIndex) const;
    Q_PROPERTY(int objectCount READ objectCount NOTIFY objectCountChanged)
    Q_PROPERTY(QJsonObject firstObject READ firstObject NOTIFY firstObjectChanged)
private:
    int objectCount() const;
    QJsonObject firstObject() const;
signals:
    void objectCountChanged();
    void firstObjectChanged();

public:
    Q_PROPERTY(QString extraValue MEMBER mExtraValue WRITE setExtraValue NOTIFY extraValueChanged)
    void setExtraValue(const QString& extraValue);
private:
    QString mExtraValue;
signals:
    void extraValueChanged();

public:
    Q_PROPERTY(QString arrayPath READ arrayPath WRITE setArrayPath NOTIFY arrayPathChanged)
    QString arrayPath() const;
    void setArrayPath(const QString& arrayPath);
signals:
    void arrayPathChanged();
};

#endif // __SYMBOID_SDK_NETWORK_QRESTTABLEMODEL_H__
