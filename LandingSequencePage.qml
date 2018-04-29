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
    id:                 landingSequencePage
    pageComponent:      pageComponent
    pageName:           qsTr("Landing Sequence Page")
    pageDescription:    qsTr("Use this page to select landing patterns from a predefined set.")

    property real _margin:          ScreenTools.defaultFontPixelWidth
    property real _butttonWidth:    ScreenTools.defaultFontPixelWidth * 10

    QGCPalette { id: palette; colorGroupEnabled: enabled }

    Component {
        id: pageComponent

        RowLayout {
            width:  availableWidth
            height: availableHeight

            Connections {
                target: QGroundControl.landingSequenceManager
            }

            TableView {
                id: tableView
                anchors.top:        parent.top
                anchors.bottom:     parent.bottom

                model:              QGroundControl.landingSequenceManager.landingSequences
                selectionMode:      SelectionMode.SingleSelection
                Layout.fillWidth:   true
                onActivated: QGroundControl.landingSequenceManager.toggleActive(tableView.currentRow)

                TableViewColumn {
                    title: qsTr("ID")
                    width: ScreenTools.defaultFontPixelWidth * 6
                    horizontalAlignment: Text.AlignHCenter
                    delegate : Text  {
                        horizontalAlignment: Text.AlignHCenter
                        text: {
                            var o = QGroundControl.landingSequenceManager.landingSequences[styleData.row]
                            return o ? o.id : ""

                        }
                    }
                }

                TableViewColumn {
                    title: qsTr("Description")
                    width: ScreenTools.defaultFontPixelWidth * 18
                    horizontalAlignment: Text.AlignHCenter
                    delegate : Text  {
                        horizontalAlignment: Text.AlignHCenter
                        text: {
                            var o = QGroundControl.landingSequenceManager.landingSequences[styleData.row]
                            console.info(o.description)
                            return o ? o.description : ""
                        }
                    }
                }

                TableViewColumn {
                    title: qsTr("Active")
                    width: ScreenTools.defaultFontPixelWidth * 12
                    horizontalAlignment: Text.AlignHCenter
                    delegate : Text  {
                        horizontalAlignment: Text.AlignHCenter
                        text: {
                            return QGroundControl.landingSequenceManager.landingSequences[styleData.row].active;
                        }
                    }
                }
            }
            Column {
                spacing:            _margin
                Layout.alignment:   Qt.AlignTop | Qt.AlignLeft

                QGCButton {
                    enabled:    true
                    text:       qsTr("Edit Description")
                    width:      _butttonWidth

                    onClicked: {
                        descripDialog.open()

                    }
                    Dialog {
                        id: descripDialog
                        visible: false
                        standardButtons: StandardButton.Ok | StandardButton.Cancel
                        onAccepted: {QGroundControl.landingSequenceManager.setDescription(tableView.currentRow,descriptionAnswer.text)}
                        ColumnLayout {
                            id: columnDescrip
                            width: parent ? parent.width : 100
                            Label {
                                text: "Enter the new description for the selected landing pattern."
                                Layout.columnSpan: 2
                                Layout.fillWidth: true
                                wrapMode: Text.WordWrap
                            }
                            RowLayout {
                                Layout.alignment: Qt.AlignHCenter
                                TextField {
                                    id: descriptionAnswer
                                }
                            }
                        }
                    }
                }
                QGCButton {
                    enabled:    true
                    text:       qsTr("Save File")
                    width:      _butttonWidth

                    onClicked: {
                        saveDialog.open()
                    }
                    Dialog {
                        id: saveDialog
                        visible: false
                        standardButtons: StandardButton.Ok | StandardButton.Cancel
                        onAccepted: {QGroundControl.landingSequenceManager.saveToFile("/QGroundControl/landingsequences.json")
                                    saveDialog.close()}
                        onRejected: saveDialog.close()
                        ColumnLayout {
                            id: columnSave
                            width: parent ? parent.width : 100
                            Label {
                                text: "Are you sure you want to save to file? This will overwrite the file."
                                Layout.columnSpan: 2
                                Layout.fillWidth: true
                                wrapMode: Text.WordWrap
                            }
                        }
                    }
                }
            } // Column - Buttons
        } // RowLayout
    } // Component
} // AnalyzePage
