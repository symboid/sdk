
#ifndef __SYMBOID_SDK_HOSTING_QCONFIGNODE_H__
#define __SYMBOID_SDK_HOSTING_QCONFIGNODE_H__

#include "sdk/hosting/defs.h"
#include "sdk/arch/mainobject.h"
#include <QObject>
#include <QVector>
#include <QMetaType>
#include <QVariant>
#include <QAbstractListModel>

class QConfigNode : public QAbstractListModel
{
public:
    static constexpr const char* qml_name = "ConfigNode";

    Q_OBJECT
public:
    QConfigNode();
    QConfigNode(const QString& name, QConfigNode* parentNode, const char* parentSignal = nullptr);
public:
    Q_PROPERTY(QString name MEMBER mName CONSTANT)
    const QString mName;

    Q_PROPERTY(QVariant value READ configValue NOTIFY changed)
public:
    virtual QVariant configValue() const { return QVariant::fromValue(const_cast<QConfigNode*>(this)); }
signals:
    void changed();

private:
    QVector<QConfigNode*> mSubConfigs;
public:
    int subConfigCount() const;
    const QConfigNode* subConfig(int index) const;
    QConfigNode* subConfig(int index);

public:
    enum Roles
    {
        NameRole = Qt::UserRole,
        ValueRole,
        ItemRole,
    };
    Q_ENUM(Roles)
    QHash<int, QByteArray> roleNames() const override;
    int rowCount(const QModelIndex& index = QModelIndex()) const override;
    QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override;
};

Q_DECLARE_METATYPE(QConfigNode*)
Q_DECLARE_METATYPE(const QConfigNode*)

template <typename ConfigValue>
class QConfigProperty : public QConfigNode
{
public:
    QConfigProperty(QConfigNode* parentNode, const char* parentSignal,
                    const QString& name, const ConfigValue& defaultValue)
        : QConfigNode(name, parentNode, parentSignal)
        , mValue(defaultValue)
    {
    }
private:
    ConfigValue mValue;
public:
    ConfigValue value() const
    {
        return mValue;
    }
    void setValue(ConfigValue value)
    {
        if (mValue != value)
        {
            mValue = value;
            emit changed();
        }
    }
    QVariant configValue() const override { return QVariant(mValue); }
};

#define Q_CONFIG_PROPERTY(type,name,defaultValue,title) \
Q_PROPERTY(type name READ name##Get WRITE name##Set NOTIFY name##Changed) \
Q_SIGNALS: \
    void name##Changed(); \
private: \
    QConfigProperty<type>* name = new QConfigProperty<type>(this,SIGNAL(name##Changed()),title,defaultValue); \
    type name##Get() const { return name->value(); } \
    void name##Set(type value) { name->setValue(value); }

#define Q_CONFIG_NODE(type,name) \
    Q_PROPERTY(QConfigNode* name READ name##Get NOTIFY name##Changed) \
    Q_SIGNALS: \
        void name##Changed(); \
    private: \
        QConfigNode* name = new type(this,SIGNAL(name##Changed())); \
        QConfigNode* name##Get() const { return name; }

#endif // __SYMBOID_SDK_HOSTING_QCONFIGNODE_H__
