
#include "sdk/dox-qt/setup.h"
#include "sdk/dox-qt/qrecentdoxmodel.h"
#include <QStandardPaths>
#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include "sdk/dox-qt/document.h"
#include "sdk/arch/log.h"

QRecentDoxModel::QRecentDoxModel(QObject* parent)
    : QDocumentListModel(parent)
    , mMaxDoxCount(10)
{
    QFile fileShadow(QStandardPaths::locate(QStandardPaths::CacheLocation, "recent_dox.json"));
    if (fileShadow.open(QFile::ReadOnly))
    {
        QJsonDocument fileJson = QJsonDocument::fromJson(fileShadow.readAll());
        const QJsonArray recentDoxRefs = fileJson.array();
        for (QJsonValue recentDoxRef : recentDoxRefs)
        {
            const QString recentDoxPath(recentDoxRef.toString());
            QScopedPointer<QDocument> document(new QDocument);
            document->setFilePath(recentDoxPath);
            if (document->load())
            {
                QDocumentInfo* documentInfo = new QDocumentInfo(this);
                documentInfo->mDocumentPath = recentDoxPath;
                documentInfo->mDocumentTitle = document->title();
                mItems.push_back(documentInfo);
            }
            else
            {
                log_warning << "Recently loaded document '" << recentDoxPath.toStdString() << "' not found!";
            }
        }
    }
}

QRecentDoxModel::~QRecentDoxModel()
{
    QFile fileShadow(QStandardPaths::writableLocation(QStandardPaths::CacheLocation) + "/recent_dox.json");
    if (fileShadow.open(QFile::WriteOnly))
    {
        QJsonDocument fileJson;
        QJsonArray recentDoxRefs;
        for (QDocumentInfo* documentInfo : mItems)
        {
            QJsonObject recentDoxPath;
            recentDoxRefs.append(documentInfo->mDocumentPath);
        }
        fileJson.setArray(recentDoxRefs);
        fileShadow.write(fileJson.toJson());
    }
}

void QRecentDoxModel::add(const QString& title, const QString& filePath)
{
    QDocumentInfo* documentInfo = new QDocumentInfo(this);
    documentInfo->mDocumentTitle = title;
    documentInfo->mDocumentPath = filePath;
    Items::iterator documentRef = std::find_if(mItems.begin(), mItems.end(),
        [filePath](const QDocumentInfo* documentInfo)->bool
        { return documentInfo->mDocumentPath == filePath; }
    );
    beginResetModel();
    if (documentRef != mItems.end())
    {
        mItems.erase(documentRef);
    }
    mItems.push_front(documentInfo);
    if (mItems.size() > mMaxDoxCount)
    {
        mItems.pop_back();
    }
    endResetModel();
}

void QRecentDoxModel::remove(const QString& filePath)
{
    Items::iterator documentRef = std::find_if(mItems.begin(), mItems.end(),
        [filePath](const QDocumentInfo* documentInfo)->bool
        { return documentInfo->mDocumentPath == filePath; }
    );
    if (documentRef != mItems.end())
    {
        beginResetModel();
        mItems.erase(documentRef);
        endResetModel();
    }
}
