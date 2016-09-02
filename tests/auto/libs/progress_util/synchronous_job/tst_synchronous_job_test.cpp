#include <QString>
#include <QtTest>

#include <progress_util/synchronous_job.h>
#include <QCoreApplication>

Q_DECLARE_METATYPE(ProgressUtil::SynchronousJobResponse::ResponseStatus)

class SynchronousJobTest : public QObject
{
    Q_OBJECT

public:
    SynchronousJobTest();

private Q_SLOTS:
    void initTestCase();
    void cleanupTestCase();

    void testResponseStatus_data();
    void testResponseStatus();

    void testExitCode_data();
    void testExitCode();

    void testStdOut_data();
    void testStdOut();

    void testStdErr_data();
    void testStdErr();

private:
    QString build_mode_;
    QString end_of_line_terminator_;
};

SynchronousJobTest::SynchronousJobTest()
{
}

void SynchronousJobTest::initTestCase()
{
    QDir::setCurrent(QCoreApplication::applicationDirPath());

#ifdef QT_DEBUG
    build_mode_ = "debug";
#else
    build_mode_ = "release";
#endif

#ifdef Q_OS_WIN
    end_of_line_terminator_ = "\r\n";
#else
    end_of_line_terminator_ = "\n";
#endif
}

void SynchronousJobTest::cleanupTestCase()
{
}

void SynchronousJobTest::testResponseStatus_data()
{
    QTest::addColumn<QString>("program");
    QTest::addColumn<QStringList>("args");
    QTest::addColumn<ProgressUtil::SynchronousJobResponse::ResponseStatus>("response_status");

    QTest::newRow("normal")
            << "../../program_normal/"+build_mode_+"/program_normal"
            << QStringList()
            << ProgressUtil::SynchronousJobResponse::NormalFinished;
    QTest::newRow("none zero program")
            << "../../program_nonzero_exitcode/"+build_mode_+"/program_nonzero_exitcode"
            << QStringList()
            << ProgressUtil::SynchronousJobResponse::NormalFinished;
    QTest::newRow("crash")
            << "../../program_crash/"+build_mode_+"/program_crash"
            << QStringList()
            << ProgressUtil::SynchronousJobResponse::ErrorFinished;
    QTest::newRow("non exist program")
            << "non-exist-program"
            << QStringList()
            << ProgressUtil::SynchronousJobResponse::FailedToStart;
}

void SynchronousJobTest::testResponseStatus()
{
    QFETCH(QString, program);
    QFETCH(QStringList, args);
    QFETCH(ProgressUtil::SynchronousJobResponse::ResponseStatus, response_status);
    ProgressUtil::SynchronousJob job;
    ProgressUtil::SynchronousJobResponse response = job.run(program, args);
    QCOMPARE(response.status_, response_status);
}

void SynchronousJobTest::testExitCode_data()
{
    QTest::addColumn<QString>("program");
    QTest::addColumn<QStringList>("args");
    QTest::addColumn<int>("exit_code");

    QTest::newRow("normal")
            << "../../program_normal/"+build_mode_+"/program_normal"
            << QStringList()
            << 0;
    QTest::newRow("none zero program")
            << "../../program_nonzero_exitcode/"+build_mode_+"/program_nonzero_exitcode"
            << QStringList()
            << 1;
    QTest::newRow("crash")
            << "../../program_crash/"+build_mode_+"/program_crash"
            << QStringList()
            << -1;
    QTest::newRow("non exist program")
            << "non-exist-program"
            << QStringList()
            << -1;
}

void SynchronousJobTest::testExitCode()
{
    QFETCH(QString, program);
    QFETCH(QStringList, args);
    QFETCH(int, exit_code);
    ProgressUtil::SynchronousJob job;
    ProgressUtil::SynchronousJobResponse response = job.run(program, args);
    QCOMPARE(response.exit_code_, exit_code);
}

void SynchronousJobTest::testStdOut_data()
{
    QTest::addColumn<QString>("program");
    QTest::addColumn<QStringList>("args");
    QTest::addColumn<QString>("std_out");

    QTest::newRow("normal")
            << "../../program_normal/"+build_mode_+"/program_normal"
            << QStringList()
            << "";
    QTest::newRow("none zero program")
            << "../../program_nonzero_exitcode/"+build_mode_+"/program_nonzero_exitcode"
            << QStringList()
            << "";
    QTest::newRow("crash")
            << "../../program_crash/"+build_mode_+"/program_crash"
            << QStringList()
            << "";
    QTest::newRow("non exist program")
            << "non-exist-program"
            << QStringList()
            << "";
    QTest::newRow("program_output")
            << "../../program_output/"+build_mode_+"/program_output"
            << QStringList()
            << "std output for program_output:" + end_of_line_terminator_
               + "Hello, this is a test."+ end_of_line_terminator_;
}

void SynchronousJobTest::testStdOut()
{
    QFETCH(QString, program);
    QFETCH(QStringList, args);
    QFETCH(QString, std_out);
    ProgressUtil::SynchronousJob job;
    ProgressUtil::SynchronousJobResponse response = job.run(program, args);
    QCOMPARE(response.std_out_, std_out);
}

void SynchronousJobTest::testStdErr_data()
{
    QTest::addColumn<QString>("program");
    QTest::addColumn<QStringList>("args");
    QTest::addColumn<QString>("std_err");

    QTest::newRow("normal")
            << "../../program_normal/"+build_mode_+"/program_normal"
            << QStringList()
            << "";
    QTest::newRow("none zero program")
            << "../../program_nonzero_exitcode/"+build_mode_+"/program_nonzero_exitcode"
            << QStringList()
            << "";
    QTest::newRow("crash")
            << "../../program_crash/"+build_mode_+"/program_crash"
            << QStringList()
            << "";
    QTest::newRow("non exist program")
            << "non-exist-program"
            << QStringList()
            << "";
    QTest::newRow("program_output")
            << "../../program_output/"+build_mode_+"/program_output"
            << QStringList()
            << "std error output for program_output:" + end_of_line_terminator_
               + "Hello, this is a test."+ end_of_line_terminator_;
}

void SynchronousJobTest::testStdErr()
{
    QFETCH(QString, program);
    QFETCH(QStringList, args);
    QFETCH(QString, std_err);
    ProgressUtil::SynchronousJob job;
    ProgressUtil::SynchronousJobResponse response = job.run(program, args);
    QCOMPARE(response.std_err_, std_err);
}

QTEST_MAIN(SynchronousJobTest)

#include "tst_synchronous_job_test.moc"
