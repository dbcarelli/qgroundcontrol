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
    pageName:           qsTr("Data Station Manager")
    pageDescription:    qsTr("Log Download allows you to download binary log files from your vehicle. Click Refresh to get list of available logs.")//change code

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
                onDataStationsChanged: {
                    tableView.selection.clear()

                    for(var i = 0; i < QGroundControl.dataStationManager.dataStations.size(); i++) {
                        var o = QGroundControl.dataStationManager.dataStations.at(i)
                        if (o && o.selected) {
                            tableView.selection.select(i, i)
                        }
                    }
                }
            }

            TableView {
                id: tableView
                anchors.top:        parent.top
                anchors.bottom:     parent.bottom
                model:              QGroundControl.dataStationManager.dataStations
                selectionMode:      SelectionMode.MultiSelection
                Layout.fillWidth:   true
                onActivated: QGroundControl.dataStationManager.toggleActive(tableView.currentRow)
                TableViewColumn {
                    title: qsTr("Id")
                    width: ScreenTools.defaultFontPixelWidth * 6
                    horizontalAlignment: Text.AlignHCenter
                    delegate : Text  {
                        horizontalAlignment: Text.AlignHCenter
                        text: {
                            var o = QGroundControl.dataStationManager.dataStations[styleData.row]
                            return o ? o.id : ""
                        }
                    }
                }

                TableViewColumn {
                    title: qsTr("Longitude")
                    width: ScreenTools.defaultFontPixelWidth * 18
                    horizontalAlignment: Text.AlignHCenter
                    delegate : Text  {
                        text: {
                            var o = QGroundControl.dataStationManager.dataStations[styleData.row]
                            return o ? o.lon : ""
                        }
                    }
                }

                TableViewColumn {
                    title: qsTr("Latitude")
                    width: ScreenTools.defaultFontPixelWidth * 18
                    horizontalAlignment: Text.AlignHCenter
                    delegate : Text  {
                        text: QGroundControl.dataStationManager.dataStations[styleData.row].lat;
                    }
                }

            }

            Column {
                spacing:            _margin
                Layout.alignment:   Qt.AlignTop | Qt.AlignLeft

                QGCButton {
                    enabled:    1==1
                    text:       qsTr("Refresh")
                    width:      _butttonWidth

                    onClicked: {
                        console.info(QGroundControl.dataStationManager.dataStations[0].lat)
                    }
                }
            } // Column - Buttons
        } // RowLayout
    } // Component
} // AnalyzePage
