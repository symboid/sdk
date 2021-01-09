
#include "sdk/hosting/setup.h"
#include "sdk/hosting/qappconfig.h"
#include <QProcess>
#include <QCoreApplication>
#include <QDebug>

QAppConfig::QAppConfig(QObject* parent) : QConfigNode(parent)
{
    QSettings settings;
    ui()->loadFromSettings(&settings);
    software()->loadFromSettings(&settings);
}

QAppConfig::~QAppConfig()
{
    QSettings settings;
    ui()->saveToSettings(&settings);
    software()->saveToSettings(&settings);
}

void QAppConfig::restartApp()
{
#ifndef Q_OS_IOS
    QSettings settings;
    ui()->saveToSettings(&settings);
    software()->saveToSettings(&settings);

    QProcess* newAppProcess = new QProcess(this);
    const QString appFilePath = QCoreApplication::applicationFilePath();
    newAppProcess->setProgram(appFilePath);
    bool startSuccess = newAppProcess->startDetached();
    newAppProcess->deleteLater();
    if (startSuccess)
    {
        QCoreApplication::quit();
    }
#endif
}
