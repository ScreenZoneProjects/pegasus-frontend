#pragma once

#include "utils/MoveOnly.h"

#include <QFileInfo>
#include <QString>


namespace modeldata {
struct GameEntry {
    explicit GameEntry(QFileInfo);

    QString name;
    QString launch_cmd;
    QString launch_workdir;

    MOVE_ONLY(GameEntry)

private:
    const QFileInfo m_fileinfo;
};
} // namespace
