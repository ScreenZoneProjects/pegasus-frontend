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


#include "Api.h"

#include <QtConcurrent/QtConcurrent>


PublicApi::PublicApi(QObject* parent)
    : QObject(parent)
    /*, m_launch_collection(nullptr)
    , m_launch_game(nullptr)
    , m_providerman(this)*/
    , m_collections(m_dataset.m_collections)
{
    /*connect(&m_filters, &model::Filters::filtersChanged,
            this, &PublicApi::onFiltersChanged);

    connect(&m_collections, &model::CollectionList::gameLaunchRequested,
            this, &PublicApi::onLaunchRequested);
    connect(&m_collections, &model::CollectionList::gameFavoriteChanged,
            this, &PublicApi::onGameFavoriteChanged);*/
}
/*
void PublicApi::startScanning()
{
    m_providerman.startSearch();
}

void PublicApi::onStaticDataLoaded(QVector<model::Collection*> collections, QVector<model::Game*> games)
{
    m_collections.setModelData(std::move(collections), std::move(games));
    m_meta.onUiReady();
}

void PublicApi::onLaunchRequested(model::Collection* coll, model::Game* game)
{
    // avoid launch spamming
    if (m_launch_game)
        return;

    m_launch_collection = coll;
    m_launch_game = game;

    emit launchGame(m_launch_collection, m_launch_game);
}

void PublicApi::onGameLaunchOk()
{
    Q_ASSERT(m_launch_game);

    m_providerman.onGameLaunched(m_launch_collection, m_launch_game);
}

void PublicApi::onGameLaunchError()
{
    Q_ASSERT(m_launch_collection);
    Q_ASSERT(m_launch_game);

    // TODO: show error
    m_launch_collection = nullptr;
    m_launch_game = nullptr;
}

void PublicApi::onGameFinished()
{
    Q_ASSERT(m_launch_collection);
    Q_ASSERT(m_launch_game);

    m_providerman.onGameFinished(m_launch_collection, m_launch_game);

    m_launch_collection = nullptr;
    m_launch_game = nullptr;
}

void PublicApi::onGameFavoriteChanged()
{
    m_providerman.onGameFavoriteChanged(m_collections.allGames());
}

void PublicApi::onFiltersChanged()
{
    for (model::Collection* const collection : m_collections.collections())
        collection->gameListMut().applyFilters(m_filters);
}
*/
