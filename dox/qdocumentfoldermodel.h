
#ifndef __SYMBOID_SDK_DOX_QDOCUMENTFOLDERMODEL_H__
#define __SYMBOID_SDK_DOX_QDOCUMENTFOLDERMODEL_H__

#include "sdk/dox/defs.h"
#include "sdk/dox/qdocumentlistmodel.h"
#include <QDir>

class QDocumentFolderModel : public QDocumentListModel
{
    Q_OBJECT
public:
    static constexpr const char* qml_name = "DocumentFolderModel";
public:
    QDocumentFolderModel(QObject* parent = Q_NULLPTR);

public:
    Q_PROPERTY(QString currentFolder READ currentFolder WRITE setCurrentFolder NOTIFY currentFolderChanged)
private:
    QDir mCurrentFolder;
    QString currentFolder() const;
    void setCurrentFolder(const QString& currentFolder);
signals:
    void currentFolderChanged();

public:
    Q_PROPERTY(QString filterText MEMBER mFilterText WRITE setFilterText NOTIFY filterTextChanged)
private:
    QString mFilterText;
    void setFilterText(const QString& filterText);
signals:
    void filterTextChanged();

public slots:
    Q_INVOKABLE void updateDocumentList();
    Q_INVOKABLE bool removeDocument(int documentIndex, bool withModelReset = true);
    Q_INVOKABLE bool removeSelectedDocuments();
signals:
    void documentRemoved(const QString& documentPath);
};

#endif // __SYMBOID_SDK_DOX_QDOCUMENTFOLDERMODEL_H__
