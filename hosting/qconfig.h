
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

class SDK_HOSTING_API QAbstractConfig : public QAbstractListModel
{
public:
    static constexpr const char* qml_name = "ConfigNode";

    Q_OBJECT
public:
    QAbstractConfig(QObject* parent);
    QAbstractConfig(const QString& id, QAbstractConfig* parentNode, const char* parentSignal = nullptr);

    Q_PROPERTY(QVariant value READ value WRITE setValue NOTIFY changed)
public:
    virtual QVariant value() const { return QVariant(); }
    virtual void setValue(const QVariant&) {}
signals:
    void changed();

public:
    Q_PROPERTY(QString id MEMBER mId CONSTANT)
private:
    const QString mId;

private:
    virtual int subConfigCount() const = 0;
    virtual const QAbstractConfig* subConfig(int index) const = 0;
    virtual QAbstractConfig* subConfig(int index) = 0;

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

    template <class Config, class ParentConfig, class... Params>
    static Config* createConfig(const QString& id, ParentConfig* parentConfig, const char* parentSignal, Params... params)
    {
        Config* config = new Config(id, parentConfig, parentSignal, params...);
        parentConfig->mSubConfigs.push_back(config);
        return config;
    }
};

template <class ItemConfig>
class QConfigContainer : public QAbstractConfig
{
public:
    QConfigContainer(QObject* parent)
        : QAbstractConfig(parent)
    {
    }
    QConfigContainer(const QString& id, QAbstractConfig* parentNode, const char* parentSignal)
        : QAbstractConfig(id, parentNode, parentSignal)
    {
    }

public:
    QVector<ItemConfig*> mSubConfigs;
public:
    int subConfigCount() const override
    {
        return mSubConfigs.size();
    }
    const ItemConfig* subConfig(int index) const override
    {
        return 0 <= index && index < mSubConfigs.size() ? mSubConfigs[index] : nullptr;
    }
    ItemConfig* subConfig(int index) override
    {
        return 0 <= index && index < mSubConfigs.size() ? mSubConfigs[index] : nullptr;
    }
};

class SDK_HOSTING_API QConfigNode : public QConfigContainer<QAbstractConfig>
{
public:
    QConfigNode(QObject* parent);
    QConfigNode(const QString& id, QAbstractConfig* parentNode, const char* parentSignal);
};

Q_DECLARE_METATYPE(QAbstractConfig*)
Q_DECLARE_METATYPE(const QAbstractConfig*)

template <typename ConfigValue>
class QConfigProperty : public QConfigNode
{
public:
    QConfigProperty(const QString& id, QAbstractConfig* parentNode, const char* parentSignal,
                    const ConfigValue& defaultValue)
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

#define Q_CONFIG_NODE_MEMBER(type,name,...) \
private: \
    type* _M_##name = createConfig<type>(#name,this,SIGNAL(name##Changed()),##__VA_ARGS__);

#define Q_CONFIG_NODE_INTERFACE(type,name) \
Q_PROPERTY(QAbstractConfig* name READ name NOTIFY name##Changed) \
Q_SIGNALS: \
    void name##Changed(); \
public: \
    type* name() const { return _M_##name; }

#define Q_CONFIG_NODE(type,name,...) \
    Q_CONFIG_NODE_INTERFACE(type,name) \
    Q_CONFIG_NODE_MEMBER(type,name,##__VA_ARGS__)

#define Q_CONFIG_PROPERTY(type,name,defaultValue) \
Q_PROPERTY(type name READ name WRITE name##Set NOTIFY name##Changed) \
Q_SIGNALS: \
    void name##Changed(); \
public: \
    type name() const { return _M_##name->configValue(); } \
    void name##Set(type value) { _M_##name->setConfigValue(value); } \
    Q_CONFIG_NODE_MEMBER(QConfigProperty<type>,name,defaultValue) \
public: \
Q_PROPERTY(QAbstractConfig* name##_node READ name##Node CONSTANT) \
    QAbstractConfig* name##Node() const { return _M_##name; }

#endif // __SYMBOID_SDK_HOSTING_QCONFIGNODE_H__
