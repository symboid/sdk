
#include "sdk/dox-qt/setup.h"
#include "sdk/dox-qt/qdocumentfoldermodel.h"
#include "sdk/dox-qt/document.h"

QDocumentFolderModel::QDocumentFolderModel(QObject* parent)
    : QDocumentListModel(parent)
    , mFilterText("")
{
    QStringList documentNameFilters(QString("*") + QDocument::sFileExtension);
    mCurrentFolder.setNameFilters(documentNameFilters);
    mCurrentFolder.setFilter(QDir::Files | QDir::NoDot | QDir::NoDotDot);
    mCurrentFolder.setSorting(QDir::Name | QDir::LocaleAware | QDir::IgnoreCase | QDir::DirsFirst);
    connect(this, SIGNAL(currentFolderChanged()), this, SLOT(updateDocumentList()));

    setCurrentFolder(QDocument::documentFolder());

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
