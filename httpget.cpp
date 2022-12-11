#include <QtCore>
#include <QtNetwork>
#include <QJsonObject>
#include <QJsonDocument>

#include <iostream>
#include "httpget.h"


HttpGet::HttpGet(QObject *parent)
    : QObject(parent)
{    
    std::cerr << "Do the object\n";
    start = QDate::currentDate();
    fileName = "./data/file";
    minX = 0;
    maxX = 0;
    tag = "UNDEFINED";
    line = "undefined";
}

void HttpGet::resetFileName(){
    fileName = "./data/file";
}

void HttpGet::setTagCpp()
{
    std::cerr << "setting cpp tag\n";    
    querryLine = "https://api.stackexchange.com/2.3/questions?order=desc&sort=activity&tagged=cpp&site=stackoverflow&filter=total&fromdate=";
    resetFileName();
    fileName.append("_Cpp_");
    tag = "tNumber of questionsfor a tag \"cpp\"";
}
void HttpGet::setTagQt()
{
    std::cerr << "setting qt tag\n";
    querryLine = "https://api.stackexchange.com/2.3/questions?order=desc&sort=activity&tagged=qt&site=stackoverflow&filter=total&fromdate=";
    resetFileName();
    fileName.append("_Qt_");
    tag = "Number of questionsfor a tag \"Qt\"";
}
void HttpGet::setTagDesktop()
{
    std::cerr << "setting desktop tag\n";
    querryLine = "https://api.stackexchange.com/2.3/questions?order=desc&sort=activity&tagged=desktop&site=stackoverflow&filter=total&fromdate=";
    resetFileName();
    fileName.append("_Desktop_");
    tag = "Number of questionsfor a tag \"Desctop\"";
}

QDate HttpGet::nextDateOnWeekPeriod(QDate start)
{
    std::cerr << "calling \'nextDateOnWeekPeriod\' function\n";

    return start.addDays(onWeek);
}
QDate HttpGet::nextDateOnMonthOnePeriod(QDate start)
{
    std::cerr << "calling \'nextDateOnMonthPeriod\' function\n";

    return start.addDays(onMonth);
}
QDate HttpGet::nextDateOnMonthThreePeriod(QDate start)
{
    std::cerr << "calling \'nextDateOnMonthThreePeriod\' function\n";

    return start.addDays(onThreeMonth);
}
QDate HttpGet::nextDateOnMonthSixPeriod(QDate start)
{
    std::cerr << "calling \'nextDateOnMonthSixPeriod\' function\n";

    return start.addMonths(onSixMonth);
}

QString HttpGet::appendDatesToQuerryLine()
{
    std::cerr << "Appending dates to the querry: ";

    //переводим даты в формат строки
    startDateISO = start.toString(Qt::ISODate);
    nextDateISO = nextDatePoint.toString(Qt::ISODate);

    //добавляем даты к строке запроса для его фомирования
    QString newQuerry = querryLine;
    newQuerry.append(startDateISO);
    newQuerry.append("&todate=");
    newQuerry.append(nextDateISO);
    std::cerr << "\"" << newQuerry.toStdString() << "\"\n";

    return newQuerry;
}

void HttpGet::setPeriodWeek()
{
    std::cerr << "start \"setPeriodWeek\"\n";

    fileName.append("1wk");
    start = QDate::currentDate();

    std::cerr << "start::current::time " << start.toString().toStdString();

    period = week;
    timeStep = onWeek;
    line = "period of week with time step = 1 day";
    //смещаемся на 8 дней назад
    //шаг один день
    start = start.addDays(-7);
    nextDatePoint = nextDateOnWeekPeriod(start);

    std::cerr << "start " << start.toString().toStdString()<<"\n";
    std::cerr << "nextDatePoint " << nextDatePoint.toString().toStdString()<<"\n";    
    std::cerr << "stop \"setPeriodWeek\"\n";
}
void HttpGet::setPeriodMonthOne()
{
    std::cerr << "start \"setPeriodMonthOne\"\n";

    fileName.append("1mn");
    start = QDate::currentDate();

    std::cerr << "start::current::time " << start.toString().toStdString();

    period = month;
    timeStep = onMonth;
    line = "period of one month with time step = 7 days";
    //смещаемся на 1 месяца назад
    //шаг семь дней
    start = start.addMonths(-1);
    //start = start.addDays(-7);
    nextDatePoint = nextDateOnMonthOnePeriod(start);

    std::cerr << "start " << start.toString().toStdString()<<"\n";
    std::cerr << "nextDatePoint " << nextDatePoint.toString().toStdString()<<"\n";    
    std::cerr << "stop \"setPeriodMonthOne\"\n";
}
void HttpGet::setPeriodMonthThree()
{
    std::cerr << "start \"setPeriodMonthThree\"\n";

    fileName.append("3mn");
    start = QDate::currentDate();

    std::cerr << "start::current::time " << start.toString().toStdString();

    period = threemonth;
    timeStep = onThreeMonth;
    line = "period of three month with time step = 10 days";
    //смещаемся на 4 месяцев назад
    //шаг десять дней
    start = start.addMonths(-3);
    //start = start.addDays(-10);
    nextDatePoint = nextDateOnMonthThreePeriod(start);

    std::cerr << "start " << start.toString().toStdString()<<"\n";
    std::cerr << "nextDatePoint " << nextDatePoint.toString().toStdString()<<"\n";   
    std::cerr << "stop \"setPeriodMonthThree\"\n";
}
void HttpGet::setPeriodMonthSix()
{
    std::cerr << "start \"setPeriodMonthSix\"\n";

    fileName.append("6mn");
    start = QDate::currentDate();

    std::cerr << "start::current::time " << start.toString().toStdString();

    period = sixmonth;
    timeStep = onSixMonth;
    line = "period of six month with time step = 1 month";
    //смещаемся на 7 месяцев назад
    //шаг один месяц
    start = start.addMonths(-6);
    nextDatePoint = nextDateOnMonthSixPeriod(start);

    std::cerr << "start " << start.toString().toStdString()<<"\n";
    std::cerr << "nextDatePoint " << nextDatePoint.toString().toStdString()<<"\n";    
    std::cerr << "stop \"setPeriodMonthSix\"\n";
}

void HttpGet::setNextDatePoint()
{
    std::cerr << "start \"setNextDatePoint\"\n";

    switch(period){
        case(week):{
            nextDatePoint = nextDateOnWeekPeriod(start);
            break;
        }
        case(month):{
            nextDatePoint = nextDateOnMonthOnePeriod(start);
            break;
        }
        case(threemonth):{
            nextDatePoint = nextDateOnMonthThreePeriod(start);
            break;
        }
        case(sixmonth):{
            nextDatePoint = nextDateOnMonthSixPeriod(start);
            break;
        }
        default:{
        std::cerr << "Do default\n";
        nextDatePoint = nextDateOnMonthOnePeriod(start);
        }
    }

    std::cerr << "stop \"setNextDatePoint\"\n";
}


void HttpGet::getFile()
{
    std::cerr << "Enter \"getFile\"\n";
    //это структура для процесса отладки, вкоторой можно хранить дату
    QMap<QDate, int> setOfQuerries;

    //очищаем вектор от предыдущих значений
    dataVector.clear();

    QDate cur = QDate::currentDate();
    std::cerr << "Current date: " << cur.toString().toStdString() << "\n";    

    double time = 1;
    minX = time;
    int i=0;
    //запускаем цикл на запрос
    while(nextDatePoint <= cur){
        std::cerr << "step " <<++i <<" in while()\n";

        QString querryUrl = appendDatesToQuerryLine();
        QUrl url(querryUrl);

        if (!url.isValid()) {
            std::cerr << "Error: Invalid URL" << std::endl;
            return;
        }

        //делаем запрос
        netReply = netManager.get(QNetworkRequest(url));
        QEventLoop process;
        connect(netReply, SIGNAL(finished()), &process, SLOT(quit()));
        process.exec();

        //конвертируем результат в строку
        QByteArray btsReply = netReply->readAll();
        QString strReply(btsReply);
        std::cerr << "the reply string is " << strReply.toStdString() << "\n";

        //а теперь читаем как JSon
        QJsonDocument jDoc = QJsonDocument::fromJson(strReply.toUtf8());
        QJsonObject jSon =jDoc.object();

        //извлекаем количество запросов и кладем в контейнер
        int i = jSon["total"].toInt();
        //контейнер для отладочной информации
        setOfQuerries.insert(nextDatePoint,i);

        QPointF pointValue;
        pointValue.setX(time);
        pointValue.setY(i);
        //контейнер для вывода в график приложения
        dataVector.append(pointValue);
        //обновляем время на следующий шаг
        time += timeStep;

        //формируем новые даты и новую ссылку на запрос
        start = nextDatePoint;
        setNextDatePoint();       

        std::cerr << "New start " << start.toString().toStdString() << "\n";
        std::cerr << "New next " << nextDatePoint.toString().toStdString() << "\n";
    }

    //это будет крайнее правое значение на оси Ох времени
    maxX = time - timeStep;


    //это отладочная структура, она позволяет конролировать дату запроса для отладочной информации
    std::map<QDate, int> stdSetOfQueries = setOfQuerries.toStdMap();
    for(auto element: stdSetOfQueries){
        std::cerr << element.first.toString(Qt::ISODate).toStdString() << " " << element.second;
    }

    //Это вывод в отладочные сообщения значений вектора, который будет использоваться для построения графика
    std::cerr << "\nThis is vector of results:\n";
    for(auto element:dataVector){
        std::cerr << element.x() << " " << element.y() << "\n";
    }

    //вектор заполнен и можно переходить к построению графика, эмитируем сигнал для слоя QML
    emit vectorChanged();

}

//функция для передачи максиального значения на оси запросов Oy, используется в слое QML
double HttpGet::maximumTotal(){
    int maxTotal = dataVector.takeFirst().y();
    for(auto element: dataVector){
        if(element.y() > maxTotal){
            maxTotal = element.y();
        }
    }
    std::cerr << "maximumTotal returns " << maxTotal << "\n";

    return maxTotal;
}

//функция для передачи минимального значения на оси запросов Oy, используется в слое QML
double HttpGet::minimumTotal(){
    int minTotal = dataVector.takeFirst().y();
    for(auto element: dataVector){
        if(element.y() < minTotal){
            minTotal = element.y();
        }
    }
    std::cerr << "minimumTotal returns " << minTotal << "\n";

    return minTotal;
}

//функция для передачи минимального значения на оси времени, используется в слое QML
double HttpGet::getMinTime(){
    std::cerr << "minimumTime returns " << minX << "\n";
    return minX;
}

//функция для передачи максимального значения на оси времени, используется в слое QML
double HttpGet::getMaxTime(){
    std::cerr << "maximumTime returns " << maxX << "\n";
    return maxX;
}

//функция для определения длины вектора, используется в слое QML
int HttpGet::lengthOfVector(){
    return static_cast<int>(dataVector.size());
}

//функция для передачи значения вектора по индексу, используется в слое QML
QPointF HttpGet::getValue(int i){
    QPointF tmp(0,0);
    if(i < 0 || i >= dataVector.size()){
        return tmp;
    }
    return dataVector[i];
}

//функция для задания текста легенды поля графика
QString HttpGet::setLegend(){
    return tag;
}

//функция для задания текста имени линии графика
QString HttpGet::setLine(){
    return line;
}


