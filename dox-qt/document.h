
#ifndef __SYMBOID_SDK_DOX_QT_DOCUMENT_H__
#define __SYMBOID_SDK_DOX_QT_DOCUMENT_H__

#include "sdk/dox-qt/defs.h"
#include <QObject>
#include "sdk/uicontrols-qt/qjsonsyncnode.h"
#include "sdk/arch/modqt.h"

typedef QJsonSyncNode QDocumentNode;

class QDocument : public QDocumentNode
{
    Q_OBJECT
public:
    static constexpr const char* qml_name = "Document";
public:
    QDocument(QObject* parent = Q_NULLPTR);

public:
    Q_PROPERTY(QString title MEMBER mTitle WRITE setTitle NOTIFY titleChanged)
private:
    QString mTitle;
    void setTitle(const QString& title);
signals:
    void titleChanged();

public:
    Q_PROPERTY(QString filePath MEMBER mFilePath WRITE setFilePath NOTIFY filePathChanged)
private:
    QString mFilePath;
    void setFilePath(const QString& filePath);
signals:
    void filePathChanged();

public:
    Q_INVOKABLE bool load();
    Q_INVOKABLE bool save();

signals:
    void loadStarted();
    void loadFinished();
    void loadFailed();

signals:
    void loadCurrent();

public:
    static constexpr const char* sFileExtension = ".sd";
    static QString systemFolder();
};


#endif // __SYMBOID_SDK_DOX_QT_DOCUMENT_H__
