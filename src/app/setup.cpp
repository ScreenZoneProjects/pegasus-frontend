// Pegasus Frontend
// Copyright (C) 2017  Mátyás Mustoha
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program. If not, see <http://www.gnu.org/licenses/>.


#include "setup.h"

#include "Api.h"
#include "FrontendLayer.h"
#include "GamepadAxisNavigation.h"
#include "ProcessLauncher.h"
#include "ScriptRunner.h"
#include "platform/PowerCommands.h"

#include <QCoreApplication>
#include <QDebug>
#include <QDir>
#include <QFile>
#include <QGamepadKeyNavigation>
#include <QGamepadManager>
#include <QQmlEngine>
#include <QRegularExpression>
#include <QStandardPaths>
#include <QTextStream>


namespace {

void mapGamepadToKeyboard()
{
    static QGamepadKeyNavigation padkeynav;
    static GamepadAxisNavigation padaxisnav;

    padkeynav.setButtonAKey(Qt::Key_Return);
    padkeynav.setButtonBKey(Qt::Key_Escape);
    padkeynav.setButtonXKey(Qt::Key_Control);
    padkeynav.setButtonL1Key(Qt::Key_A);
    padkeynav.setButtonR1Key(Qt::Key_D);
    padkeynav.setButtonL2Key(Qt::Key_PageUp);
    padkeynav.setButtonR2Key(Qt::Key_PageDown);

    QObject::connect(QGamepadManager::instance(), &QGamepadManager::gamepadAxisEvent,
                     &padaxisnav, &GamepadAxisNavigation::onAxisEvent);
}

void setupControlsChangeScripts()
{
    const auto callback = [](){
        using ScriptEvent = ScriptRunner::EventType;

        ScriptRunner::findAndRunScripts(ScriptEvent::CONFIG_CHANGED);
        ScriptRunner::findAndRunScripts(ScriptEvent::CONTROLS_CHANGED);
    };

    QObject::connect(QGamepadManager::instance(), &QGamepadManager::axisConfigured, callback);
    QObject::connect(QGamepadManager::instance(), &QGamepadManager::buttonConfigured, callback);
}

} // namespace

void setupGamepad()
{
    mapGamepadToKeyboard();
    setupControlsChangeScripts();
}

void registerAPIClasses()
{
    constexpr auto API_URI = "Pegasus.Model";

    const QString error_msg = QObject::tr("Sorry, you cannot create this type in QML.");

    qmlRegisterUncreatableType<Types::Collection>(API_URI, 0, 7, "Collection", error_msg);
    qmlRegisterUncreatableType<Types::CollectionList>(API_URI, 0, 7, "CollectionList", error_msg);
    qmlRegisterUncreatableType<Types::Game>(API_URI, 0, 2, "Game", error_msg);
    qmlRegisterUncreatableType<Types::GameList>(API_URI, 0, 6, "GameList", error_msg);
    qmlRegisterUncreatableType<Types::GameAssets>(API_URI, 0, 2, "GameAssets", error_msg);
    qmlRegisterUncreatableType<Types::Locale>(API_URI, 0, 6, "Locale", error_msg);
    qmlRegisterUncreatableType<Types::LocaleList>(API_URI, 0, 6, "LocaleList", error_msg);
    qmlRegisterUncreatableType<Types::Theme>(API_URI, 0, 6, "Theme", error_msg);
    qmlRegisterUncreatableType<Types::ThemeList>(API_URI, 0, 6, "ThemeList", error_msg);
}

void connectAndStartEngine(ApiObject& api, FrontendLayer& frontend, ProcessLauncher& launcher)
{
    // the following communication is required because process handling
    // and destroying/rebuilding the frontend stack are asynchronous tasks;
    // see the relevant classes

    QObject::connect(&api, &ApiObject::prepareLaunch,
                     &frontend, &FrontendLayer::teardown);

    QObject::connect(&frontend, &FrontendLayer::teardownComplete,
                     &api, &ApiObject::onReadyToLaunch);

    QObject::connect(&api, &ApiObject::executeLaunch,
                     &launcher, &ProcessLauncher::launchGame);

    QObject::connect(&launcher, &ProcessLauncher::processFinished,
                     &api, &ApiObject::onGameFinished);

    QObject::connect(&api, &ApiObject::restoreAfterGame,
                     &frontend, &FrontendLayer::rebuild);

    // special commands
    QObject::connect(&api, &ApiObject::qmlClearCacheRequested,
                     &frontend, &FrontendLayer::clearCache);

    // close the app on quit request
    QObject::connect(&api, &ApiObject::appCloseRequested, onAppClose);

    // start the engine
    frontend.rebuild(&api);
    api.startScanning();
}

void onAppClose(AppCloseType type)
{
    using ScriptEvent = ScriptRunner::EventType;

    ScriptRunner::findAndRunScripts(ScriptEvent::QUIT);
    switch (type) {
        case AppCloseType::REBOOT:
            ScriptRunner::findAndRunScripts(ScriptEvent::REBOOT);
            break;
        case AppCloseType::SHUTDOWN:
            ScriptRunner::findAndRunScripts(ScriptEvent::SHUTDOWN);
            break;
        default: break;
    }

    qInfo().noquote() << QObject::tr("Closing Pegasus, goodbye!");

    QCoreApplication::quit();
    switch (type) {
        case AppCloseType::REBOOT:
            platform::power::reboot();
            break;
        case AppCloseType::SHUTDOWN:
            platform::power::shutdown();
            break;
        default: break;
    }
}
