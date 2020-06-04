
#ifndef _SYMBOID_SDK_HOSTING_QCONFIGNODE_H_
#define _SYMBOID_SDK_HOSTING_QCONFIGNODE_H_

#include "sdk/hosting/defs.h"
#include "sdk/arch/mainobject.h"
#include <QObject>
#include "sdk/uicontrols-qt/listpropertyadapter.h"
#include <QMetaType>

template <typename Type>
inline bool config_property_equals(const Type& lhs, const Type& rhs);

template <>
inline bool config_property_equals<double>(const double& lhs, const double& rhs)
{
    return lhs - rhs < 0.0001;
}

template <typename Type>
inline bool config_property_equals(const Type& lhs, const Type& rhs)
{
    return lhs == rhs;
}

#define Q_CONFIG_PROPERTY(type,name,defaultValue) \
Q_PROPERTY(type name MEMBER name WRITE set_##name NOTIFY name##Changed) \
Q_SIGNALS: \
    void name##Changed(); \
private: \
    const type name##Default = defaultValue; \
    type name = defaultValue; \
    void set_##name(type value) \
    { \
        if (!config_property_equals(name, value)) \
        { \
            name = value; \
            emit name##Changed(); \
            setPropertyModified(#name, !config_property_equals(name, name##Default)); \
        } \
    }

#define Q_CONFIG_PROPERTY_NODE(name) Q_CONFIG_PROPERTY(QConfigNode*,name, nullptr)

class QConfigNode : public QObject
{
    Q_OBJECT
public:
    static constexpr const char* qml_name = "ConfigNode";
public:
    QConfigNode(QObject* parent = Q_NULLPTR);

protected:
    void setPropertyModified(const QString& propertyName, bool isModified);
public:
    bool isPropertyModified(const QString& propertyName) const;
};

class QConfig : public QConfigNode, public ListPropertyAdapter<QConfig, QConfigNode>
{
    Q_OBJECT
//    Q_CLASSINFO("DefaultProperty", "subConfigs")
    QML_SINGLETON(Config)
public:
    QConfig(QObject* parent = Q_NULLPTR);

public:
    Q_PROPERTY(QQmlListProperty<QConfigNode> subConfigs READ subConfigs NOTIFY subConfigsChanged)
protected:
    QQmlListProperty<QConfigNode> subConfigs();
signals:
    void subConfigsChanged();

public:
    void addSubConfig(QConfigNode* subConfig);
};

Q_DECLARE_METATYPE(QConfigNode*)

#endif // _SYMBOID_SDK_HOSTING_QCONFIGNODE_H_
