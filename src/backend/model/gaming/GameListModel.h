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

#include "AssetListModel.h"

#include <QAbstractListModel>
#include <vector>

namespace modeldata { struct Game; }


namespace model {
class GameListModel : public QAbstractListModel {
    Q_OBJECT

public:
    GameListModel(std::vector<modeldata::Game*>& data, QObject* parent = nullptr);

    int rowCount(const QModelIndex& parent = QModelIndex()) const override;
    QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override;

private:
    enum Roles {
        Title = Qt::UserRole + 1,
        Summary,
        Description,

        Developer,
        Publisher,
        Genre,
        DeveloperList,
        PublisherList,
        GenreList,

        PlayerCount,
        Rating,
        Release,
        ReleaseYear,
        ReleaseMonth,
        ReleaseDay,

        Favorite,
        PlayCount,
        PlayTime,
        LastPlayed,

        Assets,
    };
    QHash<int, QByteArray> roleNames() const override;

private:
    std::vector<modeldata::Game*>* const m_data;
    std::vector<model::AssetListModel*> m_assets; // FIXME: optimize this
};
} // namespace model

//Q_DECLARE_METATYPE(model::GameListModel*)
