
#ifndef __SYMBOID_SDK_DOX_QT_QDOCUMENTLISTMODEL_H__
#define __SYMBOID_SDK_DOX_QT_QDOCUMENTLISTMODEL_H__

#include "sdk/dox-qt/setup.h"
#include <QAbstractListModel>

class QDocumentListModel : public QAbstractListModel
{
    Q_OBJECT

public:
    QDocumentListModel(QObject* parent = nullptr);

public:
    int rowCount(const QModelIndex& index = QModelIndex()) const override;
    QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override;

public:
    enum Roles
    {
        DocumentTitle = Qt::UserRole,
        ItemTitle,
        DocumentPath,
    };
    Q_ENUM(Roles)
    QHash<int, QByteArray> roleNames() const override;

protected:
    struct DocumentInfo
    {
        QString mTitle;
        QString mPath;
    };
    QList<DocumentInfo> mDocumentList;
};

#endif // __SYMBOID_SDK_DOX_QT_QDOCUMENTLISTMODEL_H__
