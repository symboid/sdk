
#include "sdk/dox/setup.h"
#include "sdk/dox/qdocumentfoldermodel.h"
#include "sdk/dox/document.h"
#include <QFileInfo>

QDocumentFolderModel::QDocumentFolderModel(QObject* parent)
    : QDocumentListModel(parent)
    , mFilterText("")
{
    QStringList documentNameFilters(QString("*") + QDocument::sFileExtension);
    mCurrentFolder.setNameFilters(documentNameFilters);
    mCurrentFolder.setFilter(QDir::Files | QDir::NoDot | QDir::NoDotDot);
    mCurrentFolder.setSorting(QDir::Name | QDir::LocaleAware | QDir::IgnoreCase | QDir::DirsFirst);
    connect(this, SIGNAL(currentFolderChanged()), this, SLOT(updateDocumentList()));

    QString docDir(QDocument::documentFolder());
    log_info << "Documents folder = '"<< docDir << "'";
    setCurrentFolder(docDir);

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
    clearItems();
    for (QFileInfo docFileInfo : docFileInfoList)
    {
        QDocument document;
        document.setFilePath(docFileInfo.filePath());
        document.load();
        const QString title = document.title();

        if (filterExpression.exactMatch(title))
        {
            Items::iterator before = mItems.end();
            while (before != mItems.begin() &&
                   title.localeAwareCompare((*(before-1))->mDocumentTitle) < 0)
            {
                --before;
            }
            QDocumentInfo* documentInfo = new QDocumentInfo(this);
            documentInfo->mDocumentTitle = title;
            documentInfo->mDocumentPath = docFileInfo.filePath();
            mItems.insert(before, documentInfo);
        }
    }
    endResetModel();
}

bool QDocumentFolderModel::removeDocument(int documentIndex)
{
    bool successRemove = false;
    if (0 <= documentIndex && documentIndex < mItems.size())
    {
        QFileInfo documentFileInfo(mItems.at(documentIndex)->mDocumentPath);
        if (documentFileInfo.dir().remove(documentFileInfo.fileName()))
        {
            beginResetModel();
            mItems.removeAt(documentIndex);
            endResetModel();
            successRemove = true;
            emit documentRemoved(documentFileInfo.absoluteFilePath());
        }
    }
    return successRemove;
}
