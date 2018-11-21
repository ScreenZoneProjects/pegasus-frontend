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

#include "model/gaming/GameListModel.h"

#include <QAbstractListModel>
#include <vector>

namespace modeldata { struct Collection; }


namespace model {
class CollectionListModel : public QAbstractListModel {
    Q_OBJECT

public:
    explicit CollectionListModel(std::vector<modeldata::Collection>& data, QObject* parent = nullptr);

    int rowCount(const QModelIndex& parent = QModelIndex()) const override;
    QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override;

private:
    enum Roles {
        Name = Qt::UserRole + 1,
        ShortName,
        Summary,
        Description,
        Games,
    };
    QHash<int, QByteArray> roleNames() const override;

private:
    std::vector<modeldata::Collection>* const m_data;
    std::vector<model::GameListModel*> m_gamelists; // FIXME: optimize this
};
} // namespace model
