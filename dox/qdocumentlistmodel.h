
#ifndef __SYMBOID_SDK_DOX_QDOCUMENTLISTMODEL_H__
#define __SYMBOID_SDK_DOX_QDOCUMENTLISTMODEL_H__

#include "sdk/dox/setup.h"
#include "sdk/controls/qjsonsyncmodel.h"

class QDocumentInfo : public QJsonSyncNode
{
    Q_OBJECT

public:
    static constexpr const char* qml_name = "DocumentInfo";

    QDocumentInfo(QObject* parent = Q_NULLPTR) : QJsonSyncNode(parent) {}

    Q_PROPERTY(QString documentTitle MEMBER mDocumentTitle CONSTANT)
    QString mDocumentTitle;

    Q_PROPERTY(QString itemTitle MEMBER mDocumentTitle CONSTANT)

    Q_PROPERTY(QString documentPath MEMBER mDocumentPath CONSTANT)
    QString mDocumentPath;
};

class QDocumentListModel : public QJsonSyncModel<QDocumentInfo>
{
    Q_OBJECT

public:
    QDocumentListModel(QObject* parent = Q_NULLPTR)
        : QJsonSyncModel<QDocumentInfo>(parent)
    {
    }

public:
    enum Roles
    {
        DocumentTitle = Qt::UserRole,
        ItemTitle,
        DocumentPath,
    };
    Q_ENUM(Roles)
};

#endif // __SYMBOID_SDK_DOX_QDOCUMENTLISTMODEL_H__
