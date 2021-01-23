
#include "sdk/hosting/setup.h"
#include "sdk/hosting/qappconfig.h"
#include <QProcess>
#include <QCoreApplication>
#include <QDebug>

QAppConfig::QAppConfig(QObject* parent) : QConfigNode(parent)
{
#ifndef Q_OS_WASM
    QSettings settings;
    ui()->loadFromSettings(&settings);
    software()->loadFromSettings(&settings);
#endif
}

QAppConfig::~QAppConfig()
{
#ifndef Q_OS_WASM
    QSettings settings;
    ui()->saveToSettings(&settings);
    software()->saveToSettings(&settings);
#endif
}

void QAppConfig::restartApp()
{
#if !defined(Q_OS_IOS) && !defined(Q_OS_WASM)
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
