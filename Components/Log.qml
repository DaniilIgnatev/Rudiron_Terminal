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
                                var newText = textEdit.text

                                if (removedLog !== ""){
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

                                    if (slice_from){
                                        newText = newText.slice(slice_from)
                                    }
                                    else{
                                        slice_from = removedLog.length
                                        newText = newText.slice(slice_from)
                                    }
                                }

                                if (textEdit.text.charAt(0) == '\n'){
                                    newText = newText.substring(1)
                                }

                                let currentText = textEdit.text
                                newText += appendedLog
                                textEdit.text = newText
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

        vm.output("Добро пожаловать! Версия: " + Qt.application.version + "\n")
    }

    color: "#1d2125"

    ScrollView{
        id: scroll

        anchors.fill: parent
        hoverEnabled: true
        enabled: true

        clip: true

        ScrollBar.vertical.policy: ScrollBar.AsNeeded
        ScrollBar.horizontal.policy: ScrollBar.AsNeeded

        contentWidth: textEdit.width
        contentHeight: textEdit.height

        Text {
            id: textEdit

            leftPadding: 5
            topPadding: 5
            rightPadding: 5
            bottomPadding: 0

            wrapMode: Text.NoWrap
            font.family: "Arial"
            renderType: Text.QtRendering

            color: "#d1d5da"
            font.letterSpacing: 0.5
            font.pointSize: Qt.platform.os === "windows" ? 10 : 12

            textFormat: Text.PlainText

            onContentHeightChanged: {
                if (root.vm && root.vm.optionsModel.outputModel.autoScroll){
                    scroll.ScrollBar.vertical.position = 1
                }

                textEdit.height = textEdit.contentHeight + topPadding
            }
        }
    }
}



/*##^##
Designer {
    D{i:0;autoSize:true;height:480;width:640}
}
##^##*/
