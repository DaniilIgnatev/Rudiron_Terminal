import QtQuick 2.6
import QtQml 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12
import QtQuick.Window 2.2

import com.VM 1.0

Rectangle{
    id: root
    property LogVM vm

    function initialize(){
        scroll.ScrollBar.vertical.position = 0
        vm.logAppended.connect ((appendedLog) => {
                                    _text.text += appendedLog
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
            id: _text

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
            selectionColor: "#0664d3"
            selectedTextColor: "#ffffff"

            textFormat: Text.PlainText
            font.family: "Segoe UI"


            onHeightChanged: {
                scroll.ScrollBar.vertical.position = 1
            }
        }
    }
}



/*##^##
Designer {
    D{i:0;autoSize:true;height:480;width:640}D{i:2}D{i:1}
}
##^##*/
