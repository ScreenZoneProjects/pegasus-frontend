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


#include <QtTest/QtTest>

#include "model/gaming/Game.h"
#include "model/gaming/Collection.h"
#include "model/gaming/CollectionList.h"


class test_CollectionList : public QObject {
    Q_OBJECT

private slots:
    void empty();

    void addPlatform();

    void indexChange();
    void indexChange_data();

    void indexIncDecEmpty();
    void indexIncDec();
    void indexIncDec_data();

private:
    const model::Collection* const null_coll = static_cast<model::Collection*>(nullptr); // Qt 5.7
};

void test_CollectionList::empty()
{
    model::CollectionList list;

    QCOMPARE(list.property("current").value<model::Collection*>(), null_coll);
    QCOMPARE(list.property("index").toInt(), -1);
    QCOMPARE(list.property("count").toInt(), 0);
}

void test_CollectionList::addPlatform()
{
    QVector<model::Collection*> collections = {
        new model::Collection(modeldata::Collection("coll1")),
        new model::Collection(modeldata::Collection("coll2")),
    };
    QVector<model::Game*> games = {
        new model::Game(modeldata::Game(QFileInfo("dummy1"))),
        new model::Game(modeldata::Game(QFileInfo("dummy2"))),
    };
    collections.at(0)->setGameList({ games.at(0) });
    collections.at(1)->setGameList({ games.at(1) });


    model::CollectionList list;
    QSignalSpy spy_current(&list, &model::CollectionList::currentChanged);
    QSignalSpy spy_game(&list, &model::CollectionList::currentGameChanged);
    QVERIFY(spy_current.isValid());
    QVERIFY(spy_game.isValid());
    QTest::ignoreMessage(QtInfoMsg, QRegularExpression("\\d+ games found"));
    list.setModelData(std::move(collections), std::move(games));


    QCOMPARE(list.property("current").value<model::Collection*>(), list.collections().first());
    QCOMPARE(list.property("index").toInt(), 0);
    QCOMPARE(list.property("count").toInt(), 2);
    QCOMPARE(spy_current.count(), 1);
    QCOMPARE(spy_game.count(), 1);
}

void test_CollectionList::indexChange()
{
    // prepare

    QVector<model::Collection*> collections = {
        new model::Collection(modeldata::Collection("coll1")),
        new model::Collection(modeldata::Collection("coll2")),
    };
    QVector<model::Game*> games = {
        new model::Game(modeldata::Game(QFileInfo("dummy1"))),
        new model::Game(modeldata::Game(QFileInfo("dummy2"))),
    };
    collections.at(0)->setGameList({ games.at(0) });
    collections.at(1)->setGameList({ games.at(1) });

    model::CollectionList list;
    QSignalSpy spy_current(&list, &model::CollectionList::currentChanged);
    QSignalSpy spy_game(&list, &model::CollectionList::currentGameChanged);
    QVERIFY(spy_current.isValid());
    QVERIFY(spy_game.isValid());
    QTest::ignoreMessage(QtInfoMsg, QRegularExpression("\\d+ games found"));
    list.setModelData(std::move(collections), std::move(games));

    QVERIFY(list.property("count").toInt() == 2);
    QVERIFY(list.property("index").toInt() == 0);
    QVERIFY(spy_current.count() == 1);
    QVERIFY(spy_game.count() == 1);

    // test

    QFETCH(int, target);
    QFETCH(int, expected);
    if (target != expected)
        QTest::ignoreMessage(QtWarningMsg, QRegularExpression("Invalid collection index.*"));

    list.setProperty("index", target);

    QCOMPARE(list.property("index").toInt(), expected);
    QCOMPARE(spy_current.count(), expected == 0 ? 1 : 2);
    QCOMPARE(spy_game.count(), expected == 0 ? 1 : 2);

    // check pointer
    auto current_ptr = list.property("current").value<model::Collection*>();
    if (expected == -1) {
        QCOMPARE(current_ptr, null_coll);
    }
    else {
        Q_ASSERT(0 <= expected && expected < list.collections().count());
        QCOMPARE(current_ptr, list.collections().at(expected));
    }
}

void test_CollectionList::indexChange_data()
{
    QTest::addColumn<int>("target");
    QTest::addColumn<int>("expected");

    QTest::newRow("same") << 0 << 0;
    QTest::newRow("different") << 1 << 1;
    QTest::newRow("undefined (-1)") << -1 << -1;
    QTest::newRow("out of range (pos)") << 999 << 0;
    QTest::newRow("out of range (neg)") << -999 << 0;
}

void test_CollectionList::indexIncDecEmpty()
{
    model::CollectionList list;
    QVERIFY(list.property("index").toInt() == -1);

    // increment empty -> stays -1
    QMetaObject::invokeMethod(&list, "incrementIndex", Qt::DirectConnection);
    QCOMPARE(list.property("index").toInt(), -1);

    // decrement empty -> stays -1
    QMetaObject::invokeMethod(&list, "decrementIndex", Qt::DirectConnection);
    QCOMPARE(list.property("index").toInt(), -1);
}

void test_CollectionList::indexIncDec_data()
{
    QTest::addColumn<int>("start_idx");
    QTest::addColumn<QString>("metacall");
    QTest::addColumn<int>("expected_idx");

    QTest::newRow("increment regular") << 0 << "incrementIndex" << 1;
    QTest::newRow("increment last") << 1 << "incrementIndex" << 0;
    QTest::newRow("decrement regular") << 1 << "decrementIndex" << 0;
    QTest::newRow("decrement first") << 0 << "decrementIndex" << 1;
    QTest::newRow("increment regular, no wrap") << 0 << "incrementIndexNoWrap" << 1;
    QTest::newRow("increment last, no wrap") << 1 << "incrementIndexNoWrap" << 1;
    QTest::newRow("decrement regular, no wrap") << 1 << "decrementIndexNoWrap" << 0;
    QTest::newRow("decrement first, no wrap") << 0 << "decrementIndexNoWrap" << 0;
}

void test_CollectionList::indexIncDec()
{
    QVector<model::Collection*> collections = {
        new model::Collection(modeldata::Collection("coll1")),
        new model::Collection(modeldata::Collection("coll2")),
    };
    QVector<model::Game*> games = {
        new model::Game(modeldata::Game(QFileInfo("dummy1"))),
        new model::Game(modeldata::Game(QFileInfo("dummy2"))),
    };
    collections.at(0)->setGameList({ games.at(0) });
    collections.at(1)->setGameList({ games.at(1) });

    model::CollectionList list;
    QTest::ignoreMessage(QtInfoMsg, QRegularExpression("\\d+ games found"));
    list.setModelData(std::move(collections), std::move(games));

    QFETCH(int, start_idx);
    QFETCH(QString, metacall);
    QFETCH(int, expected_idx);

    list.setProperty("index", start_idx);
    QVERIFY(list.property("index").toInt() == start_idx);

    QMetaObject::invokeMethod(&list, metacall.toStdString().c_str(), Qt::DirectConnection);
    QCOMPARE(list.property("index").toInt(), expected_idx);
}


QTEST_MAIN(test_CollectionList)
#include "test_CollectionList.moc"
