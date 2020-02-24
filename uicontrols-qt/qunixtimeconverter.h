
#ifndef __SYMBOID_SDK_UICONTROLS_QT_QUNIXTIMECONVERTER_H__
#define __SYMBOID_SDK_UICONTROLS_QT_QUNIXTIMECONVERTER_H__

#include <QObject>

class QUnixTimeConverter : public QObject
{
    Q_OBJECT

public:
    static constexpr const char* qml_name = "UnixTimeConverter";

public:
    explicit QUnixTimeConverter(QObject* parent = Q_NULLPTR);

public:
    Q_PROPERTY(int year MEMBER mYear WRITE setYear NOTIFY yearChanged)
    Q_PROPERTY(int month MEMBER mMonth WRITE setMonth NOTIFY monthChanged)
    Q_PROPERTY(int day MEMBER mDay WRITE setDay NOTIFY dayChanged)
    Q_PROPERTY(int hour MEMBER mHour WRITE setHour NOTIFY hourChanged)
    Q_PROPERTY(int minute MEMBER mMinute WRITE setMinute NOTIFY minuteChanged)
    Q_PROPERTY(int second MEMBER mSecond WRITE setSecond NOTIFY secondChanged)
private:
    int mYear, mMonth, mDay, mHour, mMinute, mSecond;
    void setYear(int year);
    void setMonth(int month);
    void setDay(int day);
    void setHour(int hour);
    void setMinute(int minute);
    void setSecond(int second);
signals:
    void yearChanged();
    void monthChanged();
    void dayChanged();
    void hourChanged();
    void minuteChanged();
    void secondChanged();

public:
    Q_PROPERTY(int unixTime READ unixTime WRITE setUnixTime NOTIFY unixTimeChanged)
private:
    qint64 unixTime() const;
    void setUnixTime(qint64 unixTime);
signals:
    void unixTimeChanged();
};

#endif // __SYMBOID_SDK_UICONTROLS_QT_QUNIXTIMECONVERTER_H__
