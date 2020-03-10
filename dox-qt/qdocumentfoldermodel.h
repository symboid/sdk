
#ifndef __SYMBOID_SDK_DOX_QDOCUMENTFOLDERMODEL_H__
#define __SYMBOID_SDK_DOX_QDOCUMENTFOLDERMODEL_H__

#include "sdk/dox-qt/defs.h"
#include <QAbstractListModel>
#include <QDir>

class QDocumentFolderModel : public QAbstractListModel
{
    Q_OBJECT
public:
    static constexpr const char* qml_name = "DocumentFolderModel";
public:
    QDocumentFolderModel(QObject* parent = Q_NULLPTR);

public:
    int rowCount(const QModelIndex& index = QModelIndex()) const override;
    QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override;

public:
    enum Roles
    {
        DocumentTitle = Qt::UserRole,
        DocumentPath,
    };
    Q_ENUM(Roles)
    QHash<int, QByteArray> roleNames() const override;

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

private:
    struct DocumentInfo
    {
        QString mTitle;
        QString mPath;
    };
    QList<DocumentInfo> mDocumentList;
public slots:
    Q_INVOKABLE void updateDocumentList();
};

#endif // __SYMBOID_SDK_DOX_QDOCUMENTFOLDERMODEL_H__
