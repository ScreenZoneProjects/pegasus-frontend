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


#include "GameListModel.h"

#include "LocaleUtils.h"
#include "modeldata/gaming/Game.h"

#include <QDebug>


namespace {
QString joined_list(const QStringList& list)
{
    return list.join(QLatin1String(", "));
}
} // namespace


namespace model {
GameListModel::GameListModel(std::vector<modeldata::Game*>& data, QObject* parent)
    : QAbstractListModel(parent)
    , m_data(&data)
{
    m_assets.reserve(data.size());
    for (modeldata::Game* const game : data)
        m_assets.emplace_back(new model::AssetListModel(&game->assets, this));
}

int GameListModel::rowCount(const QModelIndex& parent) const
{
    // NOTE by Qt:
    // For list models only the root node (an invalid parent) should return the list's size. For all
    // other (valid) parents, rowCount() should return 0 so that it does not become a tree model.
    if (parent.isValid())
        return 0;

    return static_cast<int>(m_data->size());
}

QVariant GameListModel::data(const QModelIndex& index, int role) const
{
    if (!index.isValid())
        return QVariant();

    const auto row = static_cast<size_t>(index.row());
    if (m_data->size() <= row) {
        qWarning().noquote() << tr_log("Game index #%1 is invalid").arg(row);
        return QVariant();
    }

    const modeldata::Game& cell = *m_data->at(row);
    switch (role) {
        case Roles::Title:
            return cell.title;
        case Roles::Summary:
            return cell.summary;
        case Roles::Description:
            return cell.description;
        case Roles::Developer:
            return joined_list(cell.developers);
        case Roles::Publisher:
            return joined_list(cell.publishers);
        case Roles::Genre:
            return joined_list(cell.genres);
        case Roles::DeveloperList:
            return cell.developers;
        case Roles::PublisherList:
            return cell.publishers;
        case Roles::GenreList:
            return cell.genres;
        case Roles::PlayerCount:
            return cell.player_count;
        case Roles::Rating:
            return cell.rating;
        case Roles::Release:
            return cell.release_date;
        case Roles::ReleaseYear:
            return cell.release_date.year();
        case Roles::ReleaseMonth:
            return cell.release_date.month();
        case Roles::ReleaseDay:
            return cell.release_date.day();
        case Roles::Favorite:
            return cell.is_favorite;
        case Roles::PlayCount:
            return cell.playcount;
        case Roles::PlayTime:
            return cell.playtime;
        case Roles::LastPlayed:
            return cell.last_played;
        case Roles::Assets:
            return QVariant::fromValue<model::AssetListModel*>(m_assets.at(row));
    }

    return QVariant();
}

QHash<int, QByteArray> GameListModel::roleNames() const
{
    return {
        { Roles::Title, "name" },
        { Roles::Summary, "summary" },
        { Roles::Description, "description" },
        { Roles::Developer, "developer" },
        { Roles::Publisher, "publisher" },
        { Roles::Genre, "genre" },
        { Roles::DeveloperList, "developerList" },
        { Roles::PublisherList, "publisherList" },
        { Roles::GenreList, "genreList" },
        { Roles::PlayerCount, "playerCount" },
        { Roles::Rating, "rating" },
        { Roles::Release, "release" },
        { Roles::ReleaseYear, "releaseYear" },
        { Roles::ReleaseMonth, "releaseMonth" },
        { Roles::ReleaseDay, "releaseDay" },
        { Roles::Favorite, "favorite" },
        { Roles::PlayCount, "playCount" },
        { Roles::PlayTime, "playTime" },
        { Roles::LastPlayed, "lastPlayed" },
        { Roles::Assets, "assets" },
    };
}
} // namespace model
