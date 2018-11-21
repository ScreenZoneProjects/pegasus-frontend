// Pegasus Frontend
// Copyright (C) 2017-2018  Mátyás Mustoha
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


#pragma once

#include "model/general/Meta.h"
#include "model/general/System.h"
#include "model/settings/Settings.h"
#include "providers/ProviderManager.h"
#include "types/AppCloseType.h"

#include <QObject>


class PrivateApi : public QObject {
    Q_OBJECT

    Q_PROPERTY(model::Meta* meta READ meta CONSTANT)
    Q_PROPERTY(model::Settings* settings READ settings CONSTANT)
    Q_PROPERTY(model::System* system READ system CONSTANT)

public:
    PrivateApi();

    void startScanning();

public:
    model::Meta* meta() { return &m_meta; }
    model::Settings* settings() { return &m_settings; }
    model::System* system() { return &m_system; }

signals:
    void appCloseRequested(AppCloseType);
    void qmlClearCacheRequested();
    void localeChanged();

private slots:
    // internal communication
    //void onStaticDataLoaded(QVector<model::Collection*>, QVector<model::Game*>);

private:
    model::Meta m_meta;
    model::System m_system;
    model::Settings m_settings;

    ProviderManager m_providerman;
};
