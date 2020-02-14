
#ifndef __SYMBOID_SDK_DOX_QT_DOCUMENT_H__
#define __SYMBOID_SDK_DOX_QT_DOCUMENT_H__

#include "sdk/dox-qt/defs.h"
#include <QObject>
#include "sdk/arch/mainobject.h"

class QDocument : public QObject
{
    Q_OBJECT
    QML_SINGLETON(Document)

public:
    QDocument(QObject* parent = Q_NULLPTR);
};

#endif // __SYMBOID_SDK_DOX_QT_DOCUMENT_H__
