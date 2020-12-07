
#ifndef __SYMBOID_SDK_DOX_DOCUMENT_H__
#define __SYMBOID_SDK_DOX_DOCUMENT_H__

#include "sdk/dox/defs.h"
#include <QObject>
#include "sdk/controls/qjsonsyncnode.h"
#include "sdk/arch/modqt.h"
#include <QDir>

typedef QJsonSyncNode QDocumentNode;

class QDocument : public QJsonSyncFile
{
    Q_OBJECT
public:
    static constexpr const char* qml_name = "Document";
public:
    QDocument(QObject* parent = Q_NULLPTR);

public:
    Q_PROPERTY(QString title READ title WRITE setTitle NOTIFY titleChanged)
private:
    QString mTitle;
public:
    QString title() const;
    void setTitle(const QString& title);
signals:
    void titleChanged();

public:
    Q_INVOKABLE bool existsAnother();
    Q_INVOKABLE bool save();

signals:
    void loadCurrent();

private:
    static QString createFilePath(QString documentTitle);
public:
    static QString documentFolder();
    static constexpr const char* sFileExtension = ".sd";
};

#endif // __SYMBOID_SDK_DOX_DOCUMENT_H__
