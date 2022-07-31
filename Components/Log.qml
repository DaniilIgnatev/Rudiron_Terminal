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
        vm.logAdded.connect((appendedLog, removedLog) => {
                                var slice_from = removedLog.length
                                while (slice_from > 0){
                                    if (textEdit.text.charAt(slice_from) !== "\n"){
                                        slice_from -= 1
                                    }
                                    else{
                                        slice_from += 1
                                        break
                                    }
                                }

//                                var textEdit_bufer = textEdit.text + appendedLog
//                                textEdit_bufer = textEdit_bufer.slice(slice_from)
//                                textEdit.text = textEdit_bufer
                                textEdit.text += appendedLog
                                textEdit.text = textEdit.text.slice(slice_from)
                                textEdit.height = textEdit.contentHeight
                            })

        vm.logReplaced.connect((newLog) => {
                                   textEdit.text = newLog
                                   if (newLog === ""){
                                       scroll.ScrollBar.vertical.position = 0
                                   }
                                   else{
                                       if (vm.optionsModel.outputModel.autoScroll){
                                           textEdit.height = textEdit.height + 1
                                           textEdit.height = textEdit.height - 1
                                       }
                                   }
                               })

        vm.output("Добро пожаловать! Версия: " + Qt.application.version)
    }

    color: "#1d2125"

    ScrollView{
        id: scroll

        anchors.fill: parent

        clip: true

        ScrollBar.vertical.policy: ScrollBar.AsNeeded
        ScrollBar.horizontal.policy: ScrollBar.AsNeeded

        contentWidth: textEdit.width
        contentHeight: textEdit.height

        TextEdit {
            id: textEdit

            leftPadding: 5
            topPadding: 5
            rightPadding: 10
            bottomPadding: 10

            readOnly: true
            wrapMode: Text.NoWrap
            font.family: "Arial"
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
