// Pegasus Frontend
// Copyright (C) 2018  Mátyás Mustoha
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

#include "utils/FwdDeclModelData.h"
#include "utils/HashMap.h"

#include <QObject>


namespace providers {
namespace steam {

class Gamelist : public QObject {
    Q_OBJECT

public:
    explicit Gamelist(QObject* parent);

    void find(HashMap<QString, modeldata::Game>& games,
              HashMap<QString, modeldata::Collection>& collections,
              HashMap<QString, std::vector<QString>>& collection_childs);

signals:
    void gameCountChanged(int count);

private:
    QStringList m_installdirs;
};

} // namespace steam
} // namespace providers
