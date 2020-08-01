
#include "sdk/dox-qt/setup.h"
#include "sdk/dox-qt/qdocumentlistmodel.h"

QDocumentListModel::QDocumentListModel(QObject* parent)
    : QAbstractListModel(parent)
{
}

int QDocumentListModel::rowCount(const QModelIndex& index) const
{
    Q_UNUSED(index);
    return mDocumentList.size();
}

QVariant QDocumentListModel::data(const QModelIndex& index, int role) const
{
    QVariant documentData;
    switch (role)
    {
    case DocumentTitle: case ItemTitle:
                        documentData = mDocumentList.at(index.row()).mTitle; break;
    case DocumentPath:  documentData = mDocumentList.at(index.row()).mPath; break;
    }
    return documentData;
}

QHash<int, QByteArray> QDocumentListModel::roleNames() const
{
    QHash<int, QByteArray> roles = QAbstractListModel::roleNames();
    roles[DocumentTitle] = "documentTitle";
    roles[ItemTitle] = "itemTitle";
    roles[DocumentPath] = "documentPath";
    return roles;
}
