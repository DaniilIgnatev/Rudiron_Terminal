import QtQuick 2.6
import QtQml 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12
import QtQuick.Window 2.2

import com.VM 1.0

Rectangle{
    id: root
    property LogVM vm

    onVmChanged: {
        scroll.ScrollBar.vertical.position = 0
        vm.logAppended.connect ((appendedLog) => {
                                    textEdit.text += appendedLog
                                })

        vm.logReplaced.connect ((newLog) => {
                                    textEdit.text = newLog
                                    if (vm.optionsModel.outputModel.autoScroll){
                                        var inc = textEdit.lineCount / 1000
                                        if (inc > 0.1){
                                            inc = 0.1
                                        }
                                        console.log(inc)

                                        scroll.ScrollBar.vertical.position = 0.9 + inc
                                    }
                                })
    }

    color: "#1d2125"

    ScrollView{
        id: scroll

        anchors.fill: parent

        clip: true

        ScrollBar.vertical.policy: ScrollBar.AsNeeded
        ScrollBar.horizontal.policy: ScrollBar.AsNeeded

        TextEdit {
            id: textEdit

            leftPadding: 5
            topPadding: 5
            rightPadding: 10
            bottomPadding: 10

            readOnly: true
            wrapMode: Text.NoWrap
            renderType: Text.QtRendering
            selectByKeyboard: true
            selectByMouse: true

            color: "#d1d5da"
            font.letterSpacing: 0.5
            font.pointSize: Qt.platform.os === "windows" ? 10 : 12
            selectionColor: "#0664d3"
            selectedTextColor: "#ffffff"

            textFormat: Text.PlainText

            onHeightChanged: {
                if (root.vm && root.vm.optionsModel.outputModel.autoScroll){
                    scroll.ScrollBar.vertical.position = 1
                }
            }
        }
    }
}



/*##^##
Designer {
    D{i:0;autoSize:true;height:480;width:640}D{i:2}D{i:1}
}
##^##*/
