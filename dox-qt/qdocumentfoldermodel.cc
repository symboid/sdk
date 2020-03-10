
#include "sdk/dox-qt/setup.h"
#include "sdk/dox-qt/qdocumentfoldermodel.h"
#include "sdk/dox-qt/document.h"

QDocumentFolderModel::QDocumentFolderModel(QObject* parent)
    : QAbstractListModel(parent)
    , mFilterText("")
{
    QStringList documentNameFilters(QString("*") + QDocument::sFileExtension);
    mCurrentFolder.setNameFilters(documentNameFilters);
    mCurrentFolder.setFilter(QDir::Files | QDir::NoDot | QDir::NoDotDot);
    mCurrentFolder.setSorting(QDir::Name | QDir::LocaleAware | QDir::IgnoreCase | QDir::DirsFirst);
    connect(this, SIGNAL(currentFolderChanged()), this, SLOT(updateDocumentList()));

    setCurrentFolder(QDocument::systemFolder());

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
    mCurrentFolder.refresh();
    QRegExp filterExpression(QString(".*") + mFilterText + ".*", Qt::CaseInsensitive);
    QFileInfoList docFileInfoList = mCurrentFolder.entryInfoList();
    mDocumentList.clear();
    for (QFileInfo docFileInfo : docFileInfoList)
    {
        QDocument document;
        document.setFilePath(docFileInfo.filePath());
        document.load();
        const QString title = document.title();

        if (filterExpression.exactMatch(title))
        {
            DocumentInfo documentInfo;
            documentInfo.mTitle = title;
            documentInfo.mPath = docFileInfo.filePath();

            QList<DocumentInfo>::iterator before = mDocumentList.end();
            while (before != mDocumentList.begin() &&
                   title.localeAwareCompare((before-1)->mTitle) < 0)
            {
                --before;
            }
            mDocumentList.insert(before, documentInfo);
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

