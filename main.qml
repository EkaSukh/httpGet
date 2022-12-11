import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Controls 2.15
import QtCharts 2.2


ApplicationWindow {
    width: 500
    height: 500
    visible: true
    title: qsTr("Tags Chart")

    TextArea{
        id: topText
        width: parent.width
        height:30
        anchors.top: parent.top
        text: "Chose a tag to get time statistic from https://stakoverflow.com"
    }

    Button{
        id:buttonCpp
        width:150
        height: 50
        text: "CPP"
        anchors.top:parent.top
        anchors.topMargin: 32
        anchors.left: parent.left
        anchors.leftMargin: 20
        onClicked: classH.setTagCpp()

    }

    Button{
        id:buttonQt
        width:150
        height: 50
        text: "Qt"
        anchors.top:parent.top
        anchors.topMargin: 32
        anchors.left: buttonCpp.right
        anchors.leftMargin: 5
        onClicked: classH.setTagQt()

    }

    Button{
        id:buttonDeskTop
        width:150
        height: 50
        text: "DeskTop"
        anchors.top:parent.top
        anchors.topMargin: 32
        anchors.left: buttonQt.right
        anchors.leftMargin: 5
        onClicked: classH.setTagDesktop()
    }

    TextArea{
        id: periodsText
        width: parent.width
        height:30
        anchors.top: buttonDeskTop.bottom
        anchors.topMargin: 10
        text: "Chose a period of time:"
    }

    Button{
        id:buttonWeek
        width: 100
        height: 50
        text: "Week"
        anchors.top:buttonDeskTop.bottom
        anchors.topMargin: 45
        anchors.left: parent.left
        anchors.leftMargin: 33
        onClicked: {
            classH.setPeriodWeek()
            classH.getFile()
        }
    }

    Button{
        id:buttonMonth
        width: 100
        height: 50
        text: "One month"
        anchors.top:buttonDeskTop.bottom
        anchors.topMargin: 45
        anchors.left: buttonWeek.right
        anchors.leftMargin: 5
        onClicked: {
            classH.setPeriodMonthOne()
            classH.getFile()
        }
    }

    Button{
        id:buttonThreeMonth
        width: 100
        height: 50
        text: "Three month"
        anchors.top:buttonDeskTop.bottom
        anchors.topMargin: 45
        anchors.left: buttonMonth.right
        anchors.leftMargin: 5
        onClicked: {
            classH.setPeriodMonthThree()
            classH.getFile()
        }
    }

    Button{
        id:buttonSixMonth
        width: 100
        height: 50
        text: "Six month"
        anchors.top:buttonDeskTop.bottom
        anchors.topMargin: 45
        anchors.left: buttonThreeMonth.right
        anchors.leftMargin: 5
        onClicked: {
            classH.setPeriodMonthSix()
            classH.getFile()
        }
    }


         function setLine() {
            while(lineSeries1.count >0){
             lineSeries1.remove(0);
            }
            var N = classH.lengthOfVector
            for(var i = 0; i < N; ++i){
                lineSeries1.append(classH.getValue(i).x, classH.getValue(i).y)
            }

            axisY.max = classH.maximumTotal
            axisY.min = classH.minimumTotal
            axisX.max = classH.maximumTime
            axisX.min = 1

            chart.title = classH.setLegend
            lineSeries1.name = classH.setLine
        }



         Connections{
             target: classH
              function onVectorChanged() {
                 setLine();
             }
         }

    ChartView {
    id: chart
    title: classH.setLegend
    width:480
    height: 300
    backgroundColor: "#dbd1bd"
    anchors.bottom: parent.bottom
    anchors.bottomMargin: 5
    anchors.left:parent.left
    anchors.leftMargin:10

    antialiasing: true
    visible:true

    ValueAxis{
        id: axisY
        min: 0
        max: 200.0
        gridVisible:true
        color:"#050505"
        labelsColor:"black"
        labelFormat: "%.0i"
    }

    ValueAxis{
        id: axisX
        min: 0
        max: 20.0
        gridVisible:true
        color:"#050505"
        labelsColor:"black"
        labelFormat: "%.0i"
    }

    LineSeries {
        id:lineSeries1
        name: classH.setLine
        axisX: axisX
        axisY: axisY

    }

    }

}




