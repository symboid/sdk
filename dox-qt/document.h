
#ifndef __SYMBOID_SDK_DOX_QT_DOCUMENT_H__
#define __SYMBOID_SDK_DOX_QT_DOCUMENT_H__

#include "sdk/dox-qt/defs.h"
#include <QObject>
#include "sdk/arch/mainobject.h"

class QDocument : public QObject
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
};

#endif // __SYMBOID_SDK_DOX_QT_DOCUMENT_H__
