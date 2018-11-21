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


#include "PrivateApi.h"


PrivateApi::PrivateApi()
{
    connect(m_settings.localesPtr(), &model::LocaleList::localeChanged,
            this, &PrivateApi::localeChanged);

    connect(&m_system, &model::System::appCloseRequested,
            this, &PrivateApi::appCloseRequested);

    /*connect(&m_providerman, &ProviderManager::gameCountChanged,
            &m_meta, &model::Meta::onGameCountUpdate);
    connect(&m_providerman, &ProviderManager::firstPhaseComplete,
            &m_meta, &model::Meta::onFirstPhaseCompleted);
    connect(&m_providerman, &ProviderManager::secondPhaseComplete,
            &m_meta, &model::Meta::onSecondPhaseCompleted);*/

    /*connect(&m_providerman, &ProviderManager::staticDataReady,
            this, &PrivateApi::onStaticDataLoaded);*/
    // partial QML reload
    connect(&m_meta, &model::Meta::qmlClearCacheRequested,
            this, &PrivateApi::qmlClearCacheRequested);
}
