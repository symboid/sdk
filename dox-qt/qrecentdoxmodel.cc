
#include "sdk/dox-qt/setup.h"
#include "sdk/dox-qt/qrecentdoxmodel.h"

QRecentDoxModel::QRecentDoxModel(QObject* parent)
    : QDocumentListModel(parent)
{
}

void QRecentDoxModel::add(const QString& title, const QString& filePath)
{
    beginResetModel();
    DocumentInfo documentInfo;
    documentInfo.mTitle = title;
    documentInfo.mPath = filePath;
    mDocumentList.push_front(documentInfo);
    endResetModel();
}
