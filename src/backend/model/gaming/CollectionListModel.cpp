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


#include "CollectionListModel.h"

#include "LocaleUtils.h"
#include "modeldata/gaming/Collection.h"

#include <QDebug>


namespace model {
CollectionListModel::CollectionListModel(std::vector<modeldata::Collection>& data, QObject *parent)
    : QAbstractListModel(parent)
    , m_data(&data)
{
    m_gamelists.reserve(data.size());
    for (modeldata::Collection& coll : data)
        m_gamelists.emplace_back(new model::GameListModel(coll.games, this));
}

int CollectionListModel::rowCount(const QModelIndex& parent) const
{
    // NOTE by Qt:
    // For list models only the root node (an invalid parent) should return the list's size. For all
    // other (valid) parents, rowCount() should return 0 so that it does not become a tree model.
    if (parent.isValid())
        return 0;

    return static_cast<int>(m_data->size());
}

QVariant CollectionListModel::data(const QModelIndex& index, int role) const
{
    if (!index.isValid())
        return QVariant();

    const auto row = static_cast<size_t>(index.row());
    if (m_data->size() <= row) {
        qWarning().noquote() << tr_log("Collection index #%1 is invalid").arg(row);
        return QVariant();
    }

    const modeldata::Collection& cell = m_data->at(row);
    switch (role) {
        case Roles::Name:
            return cell.name;
        case Roles::ShortName:
            return cell.shortName();
        case Roles::Summary:
            return cell.summary;
        case Roles::Description:
            return cell.description;
        case Roles::Games:
            return QVariant::fromValue<model::GameListModel*>(m_gamelists.at(row));
    }

    return QVariant();
}

QHash<int, QByteArray> CollectionListModel::roleNames() const
{
    return {
        { Roles::Name, "name" },
        { Roles::ShortName, "shortName" },
        { Roles::Summary, "summary" },
        { Roles::Description, "description" },
    };
}
} // namespace model
