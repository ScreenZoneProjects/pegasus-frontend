#include "GameEntry.h"


namespace modeldata {

GameEntry::GameEntry(QFileInfo finfo)
    : name(finfo.completeBaseName())
    , m_fileinfo(std::move(finfo))
{}

} // namespace
