
#include "sdk/dox-qt/setup.h"
#include "sdk/dox-qt/qdocumentfoldermodel.h"
#include <QStandardPaths>

QDocumentFolderModel::QDocumentFolderModel(QObject* parent)
    : QAbstractListModel(parent)
    , mFilterText("")
{
    QStringList documentNameFilters(QString("*.") + sDocumentExtension);
    mCurrentFolder.setNameFilters(documentNameFilters);
    mCurrentFolder.setFilter(QDir::Files | QDir::NoDot | QDir::NoDotDot);
    connect(this, SIGNAL(currentFolderChanged()), this, SLOT(updateDocumentList()));

    QString systemDocuments = QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation);
    setCurrentFolder(systemDocuments);

    connect(this, SIGNAL(filterTextChanged()), this, SLOT(updateDocumentList()));
}

QString QDocumentFolderModel::currentFolder() const
{
    return mCurrentFolder.path();
}

void QDocumentFolderModel::setCurrentFolder(const QString& currentFolder)
{
    if (mCurrentFolder.path() != currentFolder)
    {
        mCurrentFolder.setPath(currentFolder);
        emit currentFolderChanged();
    }
}

void QDocumentFolderModel::setFilterText(const QString& filterText)
{
    if (mFilterText != filterText)
    {
        mFilterText = filterText;
        emit filterTextChanged();
    }
}

void QDocumentFolderModel::updateDocumentList()
{
    beginResetModel();
    QRegExp filterExpression(QString(".*") + mFilterText + ".*");
    QFileInfoList docFileInfoList = mCurrentFolder.entryInfoList();
    mDocumentList.clear();
    for (QFileInfo docFileInfo : docFileInfoList)
    {
        const QString title = docFileInfo.fileName();
        if (filterExpression.exactMatch(title))
        {
            DocumentInfo documentInfo;
            documentInfo.mTitle = title;
            documentInfo.mPath = docFileInfo.filePath();
            mDocumentList << documentInfo;
        }
    }
    endResetModel();
}

int QDocumentFolderModel::rowCount(const QModelIndex& index) const
{
    Q_UNUSED(index);
    return mDocumentList.size();
}

QVariant QDocumentFolderModel::data(const QModelIndex& index, int role) const
{
    QVariant documentData;
    switch (role)
    {
    case DocumentTitle: documentData = mDocumentList.at(index.row()).mTitle; break;
    case DocumentPath: documentData = mDocumentList.at(index.row()).mPath; break;
    }
    return documentData;
}

QHash<int, QByteArray> QDocumentFolderModel::roleNames() const
{
    QHash<int, QByteArray> roles = QAbstractListModel::roleNames();
    roles[DocumentTitle] = "documentTitle";
    roles[DocumentPath] = "documentPath";
    return roles;
}

