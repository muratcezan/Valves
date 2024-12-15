import QtQuick 2.15
import QtQuick.Controls 1.4
import QtQuick.Controls.Styles 1.4

// Custom Button Component with a clickable signal and customizable style
Button {
    // Property to control the button's enabled state
    property bool buttonState
    property string buttonText

    // Unique identifier for the button
    id: textButton
    width: 100
    height: 30
    enabled: buttonState // Bind the button's enabled property to buttonState
    anchors.verticalCenter: parent.verticalCenter // Center the button vertically
    anchors.right: parent.right // Align the button to the right of its parent
    anchors.rightMargin: 20 // Add margin to the right


    // Custom signal emitted when the button is clicked
    signal buttonClicked()

    // Define the button's visual style
    style: ButtonStyle {
        // Background configuration for the button
        background: Rectangle {
            width: textButton.width // Sync width with the button
            height: textButton.height // Sync height with the button
            color: "#476273" // Background color
            radius: 8 // Rounded corners
        }

        // Label configuration for the button text
        label: Label {
            text: buttonText
            anchors.fill: parent // Fill the label to the parent rectangle
            horizontalAlignment: Text.AlignHCenter // Center text horizontally
            verticalAlignment: Text.AlignVCenter // Center text vertically
            font.pixelSize: 14 // Font size
            color: "white" // Text color
            opacity: textButton.enabled ? 1 : 0.33 // Adjust opacity based on enabled state
        }
    }

    // Emit the custom signal when the button is clicked
    onClicked: buttonClicked()
}
