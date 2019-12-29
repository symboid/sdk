
#ifndef __SYMBOID_SDK_BASICS_FRONTEND_JSONOBJECT_H__
#define __SYMBOID_SDK_BASICS_FRONTEND_JSONOBJECT_H__

#include "sdk/basics/defs.h"
#include <QObject>
#include <QJsonObject>
#include <QSharedPointer>
#include <QVariant>
#include <QVector>

namespace Sf {

class JsonObject;

struct JsonProperty : QObject
{
    Q_OBJECT
protected:
    JsonProperty(const char* propertyName, JsonObject* parent, const char* changeSignal);
signals:
    void valueChanged();
public:
    const QString mName;
    virtual QJsonValue toJsonValue() const = 0;
    virtual void operator=(const QJsonValue&) = 0;
};

class JsonObject : public QObject, public QJsonObject
{
    Q_OBJECT

public:
    explicit JsonObject(QObject* parent = nullptr);

signals:
    void valueChanged();

public:
    QJsonValue toJsonValue() const;
    void parseJsonObject(const QJsonObject& jsonObject);
    inline QJsonObject toJsonObject() const
    {
        return toJsonValue().toObject();
    }
    inline void copy(const JsonObject* src)
    {
        parseJsonObject(src->toJsonObject());
    }

    QVector<JsonProperty*> mProperties;
};

template <typename Value>
struct JsonValue : JsonProperty
{
    JsonValue(const char* propertyName, JsonObject* parent, const char* changeSignal, const Value& initValue)
        : JsonProperty(propertyName, parent, changeSignal)
        , mIsProxy(false)
        , mValue(new Value(initValue))
    {
    }
    JsonValue(const char* propertyName, JsonObject* parent, const char* changeSignal, Value* valueRef)
        : JsonProperty(propertyName, parent, changeSignal)
        , mIsProxy(true)
        , mValue(valueRef)
    {
    }
    ~JsonValue()
    {
        if (!mIsProxy)
        {
            delete mValue;
        }
    }
    void set(const Value& rhs)
    {
        if (*mValue != rhs)
        {
            *mValue = rhs;
            emit valueChanged();
        }
    }
    JsonValue& operator=(const Value& rhs)
    {
        this->set(rhs);
        return *this;
    }
    operator Value() const { return this->get(); }
    Value get() const { return *mValue; }

    void operator=(const QJsonValue& rhs) override
    {
        this->set(rhs.toVariant().value<Value>());
    }
    QJsonValue toJsonValue() const override { return QJsonValue::fromVariant(QVariant::fromValue(*mValue)); }
private:
    const bool mIsProxy;
protected:
    Value* mValue;
};

template <class ObjectValue>
struct JsonObjectPtr : JsonValue<ObjectValue*>
{
    JsonObjectPtr(const char* propertyName, JsonObject* parent, const char* changeSignal)
        : JsonValue<ObjectValue*>(propertyName, parent, changeSignal, new ObjectValue)
    {
        QObject::connect(*this->mValue, SIGNAL(valueChanged()), this, SIGNAL(valueChanged()));
    }
    void set(ObjectValue* const& rhs)
    {
        ObjectValue*& thisObject = *this->mValue;
        if (thisObject != rhs)
        {
            delete thisObject;
            thisObject = rhs;
            emit this->valueChanged();
        }
    }
    void operator=(const QJsonValue& rhs) override
    {
        this->get()->parseJsonObject(rhs.toObject());
    }
    QJsonValue toJsonValue() const override
    {
        return this->get()->toJsonValue();
    }
    JsonObjectPtr& operator=(const JsonObjectPtr& rhs)
    {
        this->get()->copy(rhs);
        return *this;
    }
    ObjectValue* operator->() { return this->get(); }
    const ObjectValue* operator->() const { return this->get(); }
};

} //  namespace Sf

#define SF_PROPERTY(ifaceType, implType, name) \
    public: \
        Q_PROPERTY(ifaceType name READ name##Get WRITE name##Set NOTIFY name##Changed) \
    public: \
        implType name; \
        ifaceType name##Get() const { return name.get(); } \
        void name##Set(ifaceType name##Value) { name.set(name##Value); }

#define SF_JSON_PROPERTY(type, name) SF_PROPERTY(type, Sf::JsonValue<type>, name)
#define SF_JSON_PROP_OBJ(type, name) SF_PROPERTY(type*, Sf::JsonObjectPtr<type>, name)

#define sf_property_init(name, initValue) name(#name, this, SIGNAL(name##Changed()), initValue)
#define sf_prop_obj_init(name) name(#name, this, SIGNAL(name##Changed()))

#endif // __SYMBOID_SDK_BASICS_FRONTEND_JSONOBJECT_H__
