
#ifndef __SYMBOID_SDK_BASICS_FRONTEND_ARCCOORD_H__
#define __SYMBOID_SDK_BASICS_FRONTEND_ARCCOORD_H__

#include "sdk/basics/frontend/jsonobject.h"
#include "sdk/basics/arccoord.h"

Q_DECLARE_METATYPE(Sy::ArcDegree)

namespace Sf {

class ArcCoord : public JsonObject, public Sy::ArcCoord
{
    Q_OBJECT

public:
    explicit ArcCoord(QObject* parent = nullptr)
        : JsonObject(parent)
        , Sy::ArcCoord(0.0)
        , sf_property_init(degree, & mDegree)
        , sf_property_init(minute, & mMinute)
        , sf_property_init(second, & mSecond)
    {
    }

signals:
    void degreeChanged();
    void minuteChanged();
    void secondChanged();

    SF_JSON_PROPERTY(int, degree)
    SF_JSON_PROPERTY(int, minute)
    SF_JSON_PROPERTY(Sy::ArcDegree, second)
};

} // namespace Sf

#endif // __SYMBOID_SDK_BASICS_FRONTEND_ARCCOORD_H__
