
#ifndef __SYMBOID_SDK_DOX_QT_QRECENTDOXMODEL_H__
#define __SYMBOID_SDK_DOX_QT_QRECENTDOXMODEL_H__

#include "sdk/dox-qt/defs.h"
#include "sdk/dox-qt/qdocumentlistmodel.h"

class QRecentDoxModel : public QDocumentListModel
{
    Q_OBJECT
public:
    static constexpr const char* qml_name = "RecentDoxModel";
public:
    QRecentDoxModel(QObject* parent = Q_NULLPTR);
    ~QRecentDoxModel();

private:
    int mMaxDoxCount;

public:
    Q_INVOKABLE void add(const QString& title, const QString& filePath);
    Q_INVOKABLE void remove(const QString& filePath);
};

#endif // __SYMBOID_SDK_DOX_QT_QRECENTDOXMODEL_H__
