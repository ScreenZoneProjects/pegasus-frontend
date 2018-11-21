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


#pragma once

#include "DataSet.h"
#include "model/gaming/CollectionListModel.h"
#include "model/gaming/GameListModel.h"
// #include "model/gaming/Filters.h"
#include "model/general/Keys.h"

#include <QFutureWatcher>
#include <QObject>
#include <QQmlListProperty>


/// Provides data access for QML
///
/// Provides an API for the frontend layer, to allow accessing every public
/// property of the backend from QML.
class PublicApi : public QObject {
    Q_OBJECT

    // subcomponents

    //Q_PROPERTY(model::Filters* filters READ filters CONSTANT)
    Q_PROPERTY(model::Keys* keys READ keys CONSTANT)
    Q_PROPERTY(model::CollectionListModel* collections READ collections CONSTANT)

    // retranslate on locale change
    Q_PROPERTY(QString tr READ emptyString NOTIFY localeChanged)

public:
    explicit PublicApi(QObject* parent = nullptr);

public:
    // subcomponents
    //model::Filters* filters() { return &m_filters; }
    model::Keys* keys() { return &m_keys; }
    model::CollectionListModel* collections() { return &m_collections; }

signals:
    // game launching
    //void launchGame(const model::Collection*, const model::Game*);

    // triggers translation update
    void localeChanged();

public slots:
    // game launch communication
    void onGameFinished();
    void onGameLaunchOk();
    void onGameLaunchError();

private slots:
    // internal communication
    //void onLaunchRequested(model::Collection*, model::Game*);
    void onFiltersChanged();
    void onGameFavoriteChanged();

private:
    //model::Filters m_filters;
    model::Keys m_keys;
    model::CollectionListModel m_collections;

    // game launching
    //model::Collection* m_launch_collection;
    //model::Game* m_launch_game;

    // used to trigger re-rendering of texts on locale change
    QString emptyString() const { return QString(); }

    DataSet m_dataset;
};
