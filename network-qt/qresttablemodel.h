
#ifndef __SYMBOID_SDK_NETWORK_QT_QRESTTABLEMODEL_H__
#define __SYMBOID_SDK_NETWORK_QT_QRESTTABLEMODEL_H__

#include "sdk/network-qt/defs.h"
#include "sdk/network-qt/qrestmodel.h"
#include <QJsonArray>

class SDK_NETWORK_QT_API QRestTableJSON : public QRestCaller
{
    Q_OBJECT

public:
    QRestTableJSON(QObject* parent = Q_NULLPTR);

private:
    void fetchResult(QNetworkReply* reply) override;

private:
    QJsonArray mResultArray;
    int mRowCount;

public:
    int rowCount() const;
    QVariant value(int rowIndex, const QString& columnName) const;
};

class SDK_NETWORK_QT_API QRestTableModel : public QRestModel
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
    Q_PROPERTY(QStringList columnNames MEMBER mColumnNames WRITE setColumnNames NOTIFY columnNamesChanged)
    void setColumnNames(const QStringList& columnNames);
private:
    QStringList mColumnNames;
signals:
    void columnNamesChanged();
};

#endif // __SYMBOID_SDK_NETWORK_QT_QRESTTABLEMODEL_H__
