import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Controls 2.15

import "../components"

import Vacuum 1.0
import com.enums 1.0

Window {
    width: 640
    height: 480
    visible: true
    title: qsTr("Hello World") // The title of the window
    color: "#12222d" // Background color of the window

    ColumnValvesViewModel {
        id: columnValvesViewModel // ViewModel object for column valves
    }

    Rectangle
    {
        id: valve
        width: 400
        height: 50
        color:"#344550" // Background color for the rectangle representing the valve
        anchors.centerIn: parent // Centers the rectangle in the parent
        radius: 5 // Rounded corners for the rectangle

        Text {
            text:"Column Valves " + columnValvesViewModel.valvesStateToString(columnValvesViewModel.valvesState) // Displays the valve state as a string
            anchors.verticalCenter: parent.verticalCenter // Vertically centers the text
            anchors.left: parent.left
            anchors.leftMargin: 20 // Adds 20-pixel margin from the left
            color:"white" // Text color
            font.pixelSize: 16 // Font size of the text
        }

        Image {
            anchors.verticalCenter: parent.verticalCenter // Vertically centers the image
            anchors.right: valveButton.left // Aligns the image to the left of the button
            anchors.rightMargin: 5 // Adds a 5-pixel margin between the image and the button
            source: "qrc:/assets/information.svg" // Source of the image
            width: 24 // Width of the image
            height: 24 // Height of the image
            visible: [Enums.NotAllowed, Enums.Closing, Enums.Opening].includes(columnValvesViewModel.valvesState) // Image visibility depends on specific valve states
        }

        TextButton{
            id: valveButton
            buttonState: ![Enums.NotAllowed, Enums.Closing, Enums.Opening].includes(columnValvesViewModel.valvesState) // Determines if the button is active or disabled
            buttonText: columnValvesViewModel.valvesState === Enums.Closed
                        ? "Open" :columnValvesViewModel.valvesState === Enums.NotAllowed
                          ? "Open" : "Close" // Sets the button text based on the valve state
            onButtonClicked: {
                if(columnValvesViewModel.valvesState === Enums.Closed){
                    columnValvesViewModel.onOpeningValves(); // Triggers the valve opening action if the valve is closed
                }
                else if(columnValvesViewModel.valvesState === Enums.Opened){
                    columnValvesViewModel.onClosingValves(); // Triggers the valve closing action if the valve is open
                }
            }
        }
    }
}
