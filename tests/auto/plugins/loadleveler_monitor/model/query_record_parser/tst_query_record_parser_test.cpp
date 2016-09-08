#include <QString>
#include <QtTest>
#include <QFile>
#include <QTextStream>

#include <loadleveler_monitor/model/query_record_parser.h>

using namespace LoadLevelerMonitor::Model;

class QueryRecordParserTest : public QObject
{
    Q_OBJECT

public:
    QueryRecordParserTest();

private Q_SLOTS:
    void initTestCase();
    void cleanupTestCase();

    void testTableRecordParser_data();
    void testTableRecordParser();

    void testDetailLabelParser_data();
    void testDetailLabelParser();
};

QueryRecordParserTest::QueryRecordParserTest()
{
}

void QueryRecordParserTest::initTestCase()
{
}

void QueryRecordParserTest::cleanupTestCase()
{
}

void QueryRecordParserTest::testTableRecordParser_data()
{
    QTest::addColumn<QString>("line");
    QTest::addColumn<int>("begin_pos");
    QTest::addColumn<int>("end_pos");
    QTest::addColumn<QString>("value");

    QString llq_default_record_1{"cma20n01.2877442.0       nwp_pd      9/7  16:00 R  100 serial_op    cma18n06   "};

    QTest::newRow("llq.default.1.id")
        << llq_default_record_1
        << 0
        << 24
        << "cma20n01.2877442.0";

    QTest::newRow("llq.default.1.owner")
        << llq_default_record_1
        << 25
        << 35
        << "nwp_pd";

    QTest::newRow("llq.default.1.query_date")
        << llq_default_record_1
        << 36
        << 47
        << "9/7  16:00";

    QTest::newRow("llq.default.1.status")
        << llq_default_record_1
        << 48
        << 50
        << "R";

    QTest::newRow("llq.default.1.pri")
        << llq_default_record_1
        << 51
        << 54
        << "100";

    QTest::newRow("llq.default.1.class")
        << llq_default_record_1
        << 55
        << 67
        << "serial_op";

    QTest::newRow("llq.default.1.running_on")
        << llq_default_record_1
        << 68
        << 79
        << "cma18n06";

    QString llq_default_record_2{"cma19n04.2882382.0       typ_xp      9/8  01:06 I  50  minijob      (alloc)    "};
    QTest::newRow("llq.default.2.id")
        << llq_default_record_2
        << 0
        << 24
        << "cma19n04.2882382.0";

    QTest::newRow("llq.default.2.owner")
        << llq_default_record_2
        << 25
        << 35
        << "typ_xp";

    QTest::newRow("llq.default.2.query_date")
        << llq_default_record_2
        << 36
        << 47
        << "9/8  01:06";

    QTest::newRow("llq.default.2.status")
        << llq_default_record_2
        << 48
        << 50
        << "I";

    QTest::newRow("llq.default.2.pri")
        << llq_default_record_2
        << 51
        << 54
        << "50";

    QTest::newRow("llq.default.2.class")
        << llq_default_record_2
        << 55
        << 67
        << "minijob";

    QTest::newRow("llq.default.2.running_on")
        << llq_default_record_2
        << 68
        << 79
        << "(alloc)";


    QString llq_default_record_3{"cma20n02.2881165.2       wind_ex     9/8  01:00 C  50  normal1                 "};
    QTest::newRow("llq.default.3.id")
        << llq_default_record_3
        << 0
        << 24
        << "cma20n02.2881165.2";

    QTest::newRow("llq.default.3.owner")
        << llq_default_record_3
        << 25
        << 35
        << "wind_ex";

    QTest::newRow("llq.default.3.query_date")
        << llq_default_record_3
        << 36
        << 47
        << "9/8  01:00";

    QTest::newRow("llq.default.3.status")
        << llq_default_record_3
        << 48
        << 50
        << "C";

    QTest::newRow("llq.default.3.pri")
        << llq_default_record_3
        << 51
        << 54
        << "50";

    QTest::newRow("llq.default.3.class")
        << llq_default_record_3
        << 55
        << 67
        << "normal1";

    QTest::newRow("llq.default.3.running_on")
        << llq_default_record_3
        << 68
        << 79
        << "";
}

void QueryRecordParserTest::testTableRecordParser()
{
    QFETCH(QString, line);
    QFETCH(int, begin_pos);
    QFETCH(int, end_pos);
    QFETCH(QString, value);

    QueryRecordParser *table_record_parser = new QueryTableRecordParser{begin_pos, end_pos};
    QString parsed_value = table_record_parser->parse(line);
    QCOMPARE(parsed_value, value);
}

void QueryRecordParserTest::testDetailLabelParser_data()
{
    QTest::addColumn<QStringList>("lines");
    QTest::addColumn<QString>("label");
    QTest::addColumn<QString>("value");

    // llq
    QString serial_job_running_file_path = QFINDTESTDATA("data/detail_query/llq/serial_job_running.txt");

    QFile serial_job_running_file(serial_job_running_file_path);
    if(serial_job_running_file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QStringList lines;
        QTextStream in(&serial_job_running_file);
        while (!in.atEnd())
        {
            lines << in.readLine();
        }
        serial_job_running_file.close();

        QTest::newRow("llq.serial_job.running.job_step_id")
                <<lines
                << "Job Step Id"
                << "cma20n04.2882680.0";

        QTest::newRow("llq.serial_job.running.job_step_id")
                <<lines
                << "Cmd"
                << "/cma/g1/nwp/SMSOUT/gmf_grapes_gfs_v2_0/grapes_global/12/post/postp_240.job1";

        QTest::newRow("llq.serial_job.running.job_step_id")
                <<lines
                << "Queue Date"
                << "Thu Sep  8 00:09:02 2016";

        QTest::newRow("llq.serial_job.running.job_step_id")
                <<lines
                << "Cpus Per Core"
                << "0";

        QTest::newRow("llq.serial_job.running.job_step_id")
                <<lines
                << "Task Affinity"
                << "";
    }

    // llclass
    QString minijob_file_path = QFINDTESTDATA("data/detail_query/llclass/minijob.txt");

    QFile minijobjob_file(minijob_file_path);
    if(minijobjob_file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QStringList lines;
        QTextStream in(&minijobjob_file);
        while (!in.atEnd())
        {
            lines << in.readLine();
        }
        minijobjob_file.close();

        QTest::newRow("llclass.minijob.wall_clock_limit")
                <<lines
                << "Wall_clock_limit"
                << "01:00:10, 01:00:00 (3610 seconds, 3600 seconds)";

        QTest::newRow("llclass.minijob.exclude_users")
                <<lines
                << "Exclude_Users"
                << "";

        QTest::newRow("llclass.minijob.free_slots")
                <<lines
                << "Free_slots"
                << "384";

        QTest::newRow("llclass.minijob.user_default")
                <<lines
                << "User default"
                << "maxidle(-1) maxqueued(-1) maxjobs(-1) max_total_tasks(-1)";
    }

}

void QueryRecordParserTest::testDetailLabelParser()
{
    QFETCH(QStringList, lines);
    QFETCH(QString, label);
    QFETCH(QString, value);

    QueryRecordParser *record_parser = new DetailLabelParser(label);
    QString parsed_value = record_parser->parse(lines);
    QCOMPARE(parsed_value, value);
}

QTEST_APPLESS_MAIN(QueryRecordParserTest)

#include "tst_query_record_parser_test.moc"
