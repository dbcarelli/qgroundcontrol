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
                    for(var i = 0; i < QGroundControl.dataStationManager.getDataStations().size(); i++) {
                        var o = QGroundControl.dataStationManager.getDataStations()[i]
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
                model:              QGroundControl.dataStationManager
                selectionMode:      SelectionMode.MultiSelection
                Layout.fillWidth:   true

                TableViewColumn {
                    title: qsTr("Id")
                    width: ScreenTools.defaultFontPixelWidth * 6
                    horizontalAlignment: Text.AlignHCenter
                    delegate : Text  {
                        horizontalAlignment: Text.AlignHCenter
                        text: {
                            var o = QGroundControl.dataStationManager.get(styleData.row)
                            return o ? o.id : ""
                        }
                    }
                }

                TableViewColumn {
                    title: qsTr("Date")
                    width: ScreenTools.defaultFontPixelWidth * 34
                    horizontalAlignment: Text.AlignHCenter
                    delegate : Text  {
                        text: {
                            var o = QGroundControl.dataStationManager.get(styleData.row)
                            if (o) {
                                //-- Have we received this entry already?
                                if(QGroundControl.dataStationManager.get(styleData.row).received) {
                                    var d = QGroundControl.dataStationManager.get(styleData.row).time
                                    if(d.getUTCFullYear() < 2010)
                                        return qsTr("Date Unknown")
                                    else
                                        return d.toLocaleString()
                                }
                            }
                            return ""
                        }
                    }
                }

                TableViewColumn {
                    title: qsTr("Size")
                    width: ScreenTools.defaultFontPixelWidth * 18
                    horizontalAlignment: Text.AlignHCenter
                    delegate : Text  {
                        horizontalAlignment: Text.AlignRight
                        text: {
                            var o = QGroundControl.dataStationManager.get(styleData.row)
                            return o ? o.sizeStr : ""
                        }
                    }
                }

                TableViewColumn {
                    title: qsTr("Status")
                    width: ScreenTools.defaultFontPixelWidth * 22
                    horizontalAlignment: Text.AlignHCenter
                    delegate : Text  {
                        horizontalAlignment: Text.AlignHCenter
                        text: {
                            var o = QGroundControl.dataStationManager.get(styleData.row)
                            return o ? o.status : ""
                        }
                    }
                }
            }

            Column {
                spacing:            _margin
                Layout.alignment:   Qt.AlignTop | Qt.AlignLeft

                QGCButton {
                    enabled:    !dataController.requestingList && !dataController.downloadingLogs
                    text:       qsTr("Refresh")
                    width:      _butttonWidth

                    onClicked: {
                        if (!QGroundControl.multiVehicleManager.activeVehicle || QGroundControl.multiVehicleManager.activeVehicle.isOfflineEditingVehicle) {
                            logDownloadPage.showMessage(qsTr("Log Refresh"), qsTr("You must be connected to a vehicle in order to download logs."), StandardButton.Ok)
                        } else {
                            dataController.refresh()
                        }
                    }
                }

                QGCButton {
                    enabled:    !dataController.requestingList && !dataController.downloadingLogs && tableView.selection.count > 0
                    text:       qsTr("Download")
                    width:      _butttonWidth
                    onClicked: {
                        //-- Clear selection
                        for(var i = 0; i < QGroundControl.dataStationManager.count; i++) {
                            var o = QGroundControl.dataStationManager.get(i)
                            if (o) o.selected = false
                        }
                        //-- Flag selected log files
                        tableView.selection.forEach(function(rowIndex){
                            var o = QGroundControl.dataStationManager.get(rowIndex)
                            if (o) o.selected = true
                        })
                        fileDialog.qgcView =        logDownloadPage
                        fileDialog.title =          qsTr("Select save directory")
                        fileDialog.selectExisting = true
                        fileDialog.folder =         QGroundControl.settingsManager.appSettings.telemetrySavePath
                        fileDialog.selectFolder =   true
                        fileDialog.openForLoad()
                    }

                    QGCFileDialog {
                        id: fileDialog

                        onAcceptedForLoad: {
                            dataController.download(file)
                            close()
                        }
                    }
                }

                QGCButton {
                    enabled:    !dataController.requestingList && !dataController.downloadingLogs && QGroundControl.dataStationManager.count > 0
                    text:       qsTr("Erase All")
                    width:      _butttonWidth
                    onClicked:  logDownloadPage.showDialog(eraseAllMessage,
                                                           qsTr("Delete All Log Files"),
                                                           logDownloadPage.showDialogDefaultWidth,
                                                           StandardButton.Yes | StandardButton.No)

                    Component {
                        id: eraseAllMessage

                        QGCViewMessage {
                            message:    qsTr("All log files will be erased permanently. Is this really what you want?")

                            function accept() {
                                logDownloadPage.hideDialog()
                                dataController.eraseAll()
                            }
                        }
                    }
                }

                QGCButton {
                    text:       qsTr("Cancel")
                    width:      _butttonWidth
                    enabled:    dataController.requestingList || dataController.downloadingLogs
                    onClicked:  dataController.cancel()
                }
            } // Column - Buttons
        } // RowLayout
    } // Component
} // AnalyzePage
