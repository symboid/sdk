
#include "sdk/basics/frontend/jsonobject.h"

namespace Sf {

JsonProperty::JsonProperty(const char* propertyName, JsonObject* parent, const char* changeSignal)
    : mName(propertyName)
{
    if (parent)
    {
        parent->mProperties.push_back(this);
        connect(this, SIGNAL(valueChanged()), parent, changeSignal);
        connect(this, SIGNAL(valueChanged()), parent, SIGNAL(valueChanged()));
    }
}

JsonObject::JsonObject(QObject* parent)
    : QObject(parent)
{
}

QJsonValue JsonObject::toJsonValue() const
{
    QJsonObject jsonObject;
    JsonProperty* property = nullptr;
    foreach (property, mProperties)
    {
        jsonObject[property->mName] = property->toJsonValue();
    }
    return jsonObject;
}

void JsonObject::parseJsonObject(const QJsonObject& jsonObject)
{
    JsonProperty* property = nullptr;
    foreach (property, mProperties)
    {
        *property = jsonObject[property->mName];
    }
}

} // namespace Sf
