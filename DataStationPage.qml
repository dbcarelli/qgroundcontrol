/****************************************************************************
 *
 *   (c) 2009-2016 QGROUNDCONTROL PROJECT <http://www.qgroundcontrol.org>
 *
 * QGroundControl is licensed according to the terms in the file
 * COPYING.md in the root of the source code directory.
 *
 ****************************************************************************/

import QtQuick              2.3
import QtQuick.Controls     1.2
import QtQuick.Dialogs      1.2
import QtQuick.Layouts      1.2

import QGroundControl               1.0
import QGroundControl.Palette       1.0
import QGroundControl.Controls      1.0
import QGroundControl.Controllers   1.0
import QGroundControl.ScreenTools   1.0

AnalyzePage {
    id:                 dataStationPage
    pageComponent:      pageComponent
    pageName:           qsTr("Data Station Page")
    pageDescription:    qsTr("Temp Description")

    property real _margin:          ScreenTools.defaultFontPixelWidth
    property real _butttonWidth:    ScreenTools.defaultFontPixelWidth * 10

    QGCPalette { id: palette; colorGroupEnabled: enabled }

    Component {
        id: pageComponent

        RowLayout {
            width:  availableWidth
            height: availableHeight

            Connections {
                target: QGroundControl.dataStationManager
//                onDataStationsChanged: {
////                    ListView.forceLayout()
//                }
            }

            TableView {
                id: tableView
                anchors.top:        parent.top
                anchors.bottom:     parent.bottom
                model:              QGroundControl.dataStationManager.getNumOfDataStations()//what the hell is this? It works, but not sure why
                selectionMode:      SelectionMode.MultiSelection//perhaps should be single
                Layout.fillWidth:   true
                TableViewColumn {
                    title: qsTr("Id")
                    width: ScreenTools.defaultFontPixelWidth * 6
                    horizontalAlignment: Text.AlignHCenter
                    delegate : Text  {
                        horizontalAlignment: Text.AlignHCenter
                        text: {
                            if(styleData.row<QGroundControl.dataStationManager.getNumOfDataStations() && QGroundControl.dataStationManager.getNumOfDataStations()>0  && styleData.row>=0){
                                return QGroundControl.dataStationManager.getId(styleData.row)
                            }
                            else{
                                return ""
                            }
                        }
                    }
                }

                TableViewColumn {
                    title: qsTr("Longitude")
                    width: ScreenTools.defaultFontPixelWidth * 18
                    horizontalAlignment: Text.AlignHCenter
                    delegate : Text  {
                        horizontalAlignment: Text.AlignRight
                        text: {
                            if(styleData.row<QGroundControl.dataStationManager.getNumOfDataStations() && QGroundControl.dataStationManager.getNumOfDataStations()>0 && styleData.row>=0){
                                return QGroundControl.dataStationManager.getLon(styleData.row)
                            }
                            else{
                               return ""
                            }
                        }
                    }
                }

                TableViewColumn {
                    title: qsTr("Latitude")
                    width: ScreenTools.defaultFontPixelWidth * 18
                    horizontalAlignment: Text.AlignHCenter
                    delegate : Text  {
                        horizontalAlignment: Text.AlignRight
                        text: {
                            if(styleData.row<QGroundControl.dataStationManager.getNumOfDataStations() && QGroundControl.dataStationManager.getNumOfDataStations()>0 && styleData.row>=0){
                                return QGroundControl.dataStationManager.getLat(styleData.row)
                            }
                            else{
                                return ""
                            }
                        }
                    }
                }
                TableViewColumn {
                    title: qsTr("Active")
                    width: ScreenTools.defaultFontPixelWidth * 6
                    horizontalAlignment: Text.AlignHCenter
                    delegate : Text  {
                        horizontalAlignment: Text.AlignHCenter
                        text: {
                            if(styleData.row<QGroundControl.dataStationManager.getNumOfDataStations() && QGroundControl.dataStationManager.getNumOfDataStations()>0 && styleData.row>=0){
                                return QGroundControl.dataStationManager.isActive(styleData.row)
                            }
                            else{
                                return ""
                            }
                        }
                    }
                }
            }

            Column {
                spacing:            _margin
                Layout.alignment:   Qt.AlignTop | Qt.AlignLeft

                QGCButton {
                    enabled:    tableView.currentRow>=0 && tableView.currentRow < QGroundControl.dataStationManager.getNumOfDataStations()
                    text:       qsTr("Delete")
                    width:      _butttonWidth

                    onClicked: {
                        QGroundControl.dataStationManager.deleteStation(tableView.currentRow)
                    }
                }
                QGCButton {
                    enabled:    tableView.currentRow>=0 && tableView.currentRow < QGroundControl.dataStationManager.getNumOfDataStations()
                    text:       qsTr("Toggle")
                    width:      _butttonWidth

                    onClicked: {
                         QGroundControl.dataStationManager.toggleActive(tableView.currentRow)
                    }
                }
                QGCButton {
                    enabled:    true
                    text:       qsTr("Add Data Station")
                    width:      _butttonWidth

                    onClicked: {
                         QGroundControl.dataStationManager.initializeDS()
                    }
                }
            } // Column - Buttons
        } // RowLayout
    } // Component
} // AnalyzePage
