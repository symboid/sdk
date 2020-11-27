
#ifndef __SYMBOID_SDK_HOSTING_QCONFIGNODE_H__
#define __SYMBOID_SDK_HOSTING_QCONFIGNODE_H__

#include "sdk/hosting/defs.h"
#include "sdk/arch/mainobject.h"
#include <QObject>
#include <QVector>
#include <QMetaType>
#include <QVariant>
#include <QAbstractListModel>
#include <QSettings>

class SDK_HOSTING_API QConfigNode : public QAbstractListModel
{
public:
    static constexpr const char* qml_name = "ConfigNode";

    Q_OBJECT
public:
    QConfigNode(QObject* parent = nullptr);
    QConfigNode(const QString& id, QConfigNode* parentNode, const char* parentSignal = nullptr);

    Q_PROPERTY(QVariant value READ value WRITE setValue NOTIFY changed)
public:
    virtual QVariant value() const { return QVariant(); }
    virtual void setValue(const QVariant&) {}
signals:
    void changed();

private:
    const QString mId;
    QVector<QConfigNode*> mSubConfigs;
public:
    int subConfigCount() const;
    const QConfigNode* subConfig(int index) const;
    QConfigNode* subConfig(int index);

public:
    enum Roles
    {
        ValueRole,
        ItemRole,
    };
    Q_ENUM(Roles)
    QHash<int, QByteArray> roleNames() const override;
    int rowCount(const QModelIndex& index = QModelIndex()) const override;
    QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override;

protected:
    QString configPath(const QString& parentConfigPath) const;
public:
    virtual void loadFromSettings(QSettings* settings, const QString& parentConfigPath = "");
    virtual void saveToSettings(QSettings* settings, const QString& parentConfigPath = "");
};

Q_DECLARE_METATYPE(QConfigNode*)
Q_DECLARE_METATYPE(const QConfigNode*)

template <typename ConfigValue>
class QConfigProperty : public QConfigNode
{
public:
    QConfigProperty(QConfigNode* parentNode, const char* parentSignal,
                    const QString& id, const ConfigValue& defaultValue)
        : QConfigNode(id, parentNode, parentSignal)
        , mDefaultValue(defaultValue)
        , mValue(mDefaultValue)
    {
    }
private:
    const ConfigValue mDefaultValue;
    ConfigValue mValue;
public:
    ConfigValue configValue() const
    {
        return mValue;
    }
    void setConfigValue(const ConfigValue& value)
    {
        if (mValue != value)
        {
            mValue = value;
            emit changed();
        }
    }
    QVariant value() const override { return configValue(); }
    void setValue(const QVariant& value) override
    {
        setConfigValue(value.value<ConfigValue>());
    }
    void loadFromSettings(QSettings* settings, const QString& parentConfigPath = "") override
    {
        const QString path(configPath(parentConfigPath));
        if (settings && settings->contains(path)) {
            QVariant valueVariant = settings->value(path);
            if (valueVariant.isValid())
            {
                setValue(valueVariant);
            }
        }
    }
    void saveToSettings(QSettings* settings, const QString& parentConfigPath = "") override
    {
        if (mValue != mDefaultValue)
        {
            settings->setValue(configPath(parentConfigPath), QVariant(mValue));
        }
        else
        {
            settings->remove(configPath(parentConfigPath));
        }
    }
};

#define Q_CONFIG_PROPERTY(type,name,defaultValue) \
Q_PROPERTY(type name READ name WRITE name##Set NOTIFY name##Changed) \
Q_SIGNALS: \
    void name##Changed(); \
private: \
    QConfigProperty<type>* _M_##name = new QConfigProperty<type>(this,SIGNAL(name##Changed()),#name,defaultValue); \
public: \
    type name() const { return _M_##name->configValue(); } \
    void name##Set(type value) { _M_##name->setConfigValue(value); } \
Q_PROPERTY(QConfigNode* name##_node READ name##Node CONSTANT) \
    QConfigNode* name##Node() const { return _M_##name; }

#define Q_CONFIG_NODE_INTERFACE(type,name) \
    Q_PROPERTY(QConfigNode* name READ name NOTIFY name##Changed) \
    Q_SIGNALS: \
        void name##Changed(); \
    public: \
        type* name() const { return _M_##name; }

#define Q_CONFIG_NODE(type,name) \
    Q_CONFIG_NODE_INTERFACE(type,name) \
    private: \
        type* _M_##name = new type(#name,this,SIGNAL(name##Changed())); \

#endif // __SYMBOID_SDK_HOSTING_QCONFIGNODE_H__
