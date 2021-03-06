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

#include "AndroidAppsMetadata.h"
#include "providers/Provider.h"


namespace providers {
namespace android {

class AndroidAppsProvider : public Provider {
    Q_OBJECT

public:
    AndroidAppsProvider(QObject* parent = nullptr);

    void findLists(HashMap<QString, modeldata::Game>&,
                   HashMap<QString, modeldata::Collection>&,
                   HashMap<QString, std::vector<QString>>&) final;
    void findStaticData(HashMap<QString, modeldata::Game>&,
                        const HashMap<QString, modeldata::Collection>&,
                        const HashMap<QString, std::vector<QString>>&) final;

private:
    Metadata m_metadata;
};

} // namespace android
} // namespace providers
