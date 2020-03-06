
#ifndef __SYMBOID_SDK_DOX_QDOCUMENTFOLDERMODEL_H__
#define __SYMBOID_SDK_DOX_QDOCUMENTFOLDERMODEL_H__

#include "sdk/dox-qt/defs.h"
#include <QAbstractListModel>
#include <QDir>

class QDocumentFolderModel : public QAbstractListModel
{
    Q_OBJECT
public:
    static constexpr const char* qml_name = "DocumentFolderModel";
public:
    QDocumentFolderModel(QObject* parent = Q_NULLPTR);

public:
    int rowCount(const QModelIndex& index = QModelIndex()) const override;
    QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override;

public:
    enum Roles
    {
        DocumentTitle = Qt::UserRole,
        DocumentPath,
    };
    Q_ENUM(Roles)
    QHash<int, QByteArray> roleNames() const override;

private:
    QDir mCurrentFolder;
    QFileInfoList mFileInfoList;
    static QDir documentsFolder();
};

#endif // __SYMBOID_SDK_DOX_QDOCUMENTFOLDERMODEL_H__
