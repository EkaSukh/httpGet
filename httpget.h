#ifndef HTTPGET_H
#define HTTPGET_H

#include <QFile>
#include <QNetworkAccessManager>
#include <QUrl>
#include <QDate>
#include <QPointF>

//class QUrl;

class HttpGet : public QObject
{
    Q_OBJECT

    Q_PROPERTY(double maximumTotal READ maximumTotal CONSTANT)
    Q_PROPERTY(double minimumTotal READ minimumTotal CONSTANT)
    Q_PROPERTY(double maximumTime READ getMaxTime CONSTANT)
    Q_PROPERTY(double minimumTime READ getMinTime CONSTANT)
    Q_PROPERTY(int lengthOfVector READ lengthOfVector CONSTANT)
    Q_PROPERTY(QString setLegend READ setLegend CONSTANT)
    Q_PROPERTY(QString setLine READ setLine CONSTANT)

public:
    HttpGet(QObject *parent = 0);

public slots:
    Q_INVOKABLE void getFile();

    Q_INVOKABLE void setTagCpp();
    Q_INVOKABLE void setTagQt();
    Q_INVOKABLE void setTagDesktop();

    Q_INVOKABLE void setPeriodWeek();
    Q_INVOKABLE void setPeriodMonthOne();
    Q_INVOKABLE void setPeriodMonthThree();
    Q_INVOKABLE void setPeriodMonthSix();

    Q_INVOKABLE double maximumTotal();
    Q_INVOKABLE double minimumTotal();
    Q_INVOKABLE int lengthOfVector();
    Q_INVOKABLE QPointF getValue(int i);
    Q_INVOKABLE double getMinTime();
    Q_INVOKABLE double getMaxTime();
    Q_INVOKABLE QString setLegend();
    Q_INVOKABLE QString setLine();

signals:
    void vectorChanged();

private slots:
    //void httpDone(bool error);
    QDate nextDateOnWeekPeriod(QDate start);
    QDate nextDateOnMonthOnePeriod(QDate start);
    QDate nextDateOnMonthThreePeriod(QDate start);
    QDate nextDateOnMonthSixPeriod(QDate start);

    void setNextDatePoint();
    QString appendDatesToQuerryLine();
    void resetFileName();
private:
    QNetworkAccessManager netManager;
    QNetworkReply *netReply;
    QString querryLine;

    //variable to set legend in ChartView
    QString tag;
    //variable to set line's name in ChartView
    QString line;


    enum timePeriod {week, month, threemonth, sixmonth};
    timePeriod period;
    enum stepOnPeriod{onWeek = 1, onMonth = 7, onThreeMonth = 10, onSixMonth = 1};
    stepOnPeriod timeStep;

    double minX;
    double maxX;

    //enum stepInDays {one, seven, ten, thirty};
    QDate start;
    QDate nextDatePoint;

    QString startDateISO;
    QString nextDateISO;
    QString fileName;

    QVector<QPointF> dataVector;
};

//"https://api.stackexchange.com/2.3/questions?order=desc&sort=activity&tagged=qt&site=stackoverflow&filter=total&fromdate=2022-02-01&todate=2022-02-28";
#endif
