
#include "sdk/dox-qt/setup.h"
#include "sdk/dox-qt/qdocumentfoldermodel.h"
#include <QStandardPaths>

QDocumentFolderModel::QDocumentFolderModel(QObject* parent)
    : QAbstractListModel(parent)
    , mCurrentFolder(documentsFolder())
    , mFileInfoList(mCurrentFolder.entryInfoList())
{
}

QDir QDocumentFolderModel::documentsFolder()
{
    QDir systemDocuments = QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation);
    return systemDocuments;
}

int QDocumentFolderModel::rowCount(const QModelIndex& index) const
{
    return mFileInfoList.size();
}

QVariant QDocumentFolderModel::data(const QModelIndex& index, int) const
{
    return mFileInfoList.at(index.row()).fileName();
}

QHash<int, QByteArray> QDocumentFolderModel::roleNames() const
{
    QHash<int, QByteArray> roles = QAbstractListModel::roleNames();
    roles[DocumentTitle] = "documentTitle";
    roles[DocumentPath] = "documentPath";
    return roles;
}

