
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
                DocumentInfo documentInfo;
                documentInfo.mPath = recentDoxPath;
                documentInfo.mTitle = document->title();
                mDocumentList.push_back(documentInfo);
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
        for (DocumentInfo documentInfo : mDocumentList)
        {
            QJsonObject recentDoxPath;
            recentDoxRefs.append(documentInfo.mPath);
        }
        fileJson.setArray(recentDoxRefs);
        fileShadow.write(fileJson.toJson());
    }
}

void QRecentDoxModel::add(const QString& title, const QString& filePath)
{
    DocumentInfo documentInfo;
    documentInfo.mTitle = title;
    documentInfo.mPath = filePath;
    QList<DocumentInfo>::iterator documentRef = std::find_if(mDocumentList.begin(), mDocumentList.end(),
            [filePath](const DocumentInfo& documentInfo)->bool{return documentInfo.mPath == filePath;});
    beginResetModel();
    if (documentRef != mDocumentList.end())
    {
        mDocumentList.erase(documentRef);
    }
    mDocumentList.push_front(documentInfo);
    if (mDocumentList.size() > mMaxDoxCount)
    {
        mDocumentList.pop_back();
    }
    endResetModel();
}

void QRecentDoxModel::remove(const QString& filePath)
{
    QList<DocumentInfo>::iterator documentRef = std::find_if(mDocumentList.begin(), mDocumentList.end(),
            [filePath](const DocumentInfo& documentInfo)->bool{return documentInfo.mPath == filePath;});
    if (documentRef != mDocumentList.end())
    {
        beginResetModel();
        mDocumentList.erase(documentRef);
        endResetModel();
    }
}
