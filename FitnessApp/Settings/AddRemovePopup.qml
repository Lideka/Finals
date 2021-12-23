import QtQuick 2.0
import QtQuick.Controls 2.0

import Settings 1.0

Item {
   width: secondWindowWidth
   height: secondWindowHeight

   ComboBox {
      id: elementTypeCB

      y: topBar.height + 20

      anchors.horizontalCenter: parent.horizontalCenter

      model: ["Exercise", "Dish"]

      onCurrentIndexChanged: {
         if(currentIndex == 0)
            Settings.isExerciseSelected = true
         else
            Settings.isExerciseSelected = false
      }
   }


   //Name
   Text {
      id: name

      anchors.top: elementTypeCB.bottom
      anchors.topMargin: 15
      anchors.horizontalCenter: parent.horizontalCenter

      text: "Name:"
   }

   TextField {
      id: nameTextField

      anchors.top: name.bottom
      anchors.topMargin: 5
      anchors.horizontalCenter: parent.horizontalCenter
   }

   //Calories
   Text {
      id: calories

      anchors.top: nameTextField.bottom
      anchors.topMargin: 20
      anchors.horizontalCenter: parent.horizontalCenter

      text: "Calories:"
   }

   TextField {
      id: caloriesTextField

      anchors.top: calories.bottom
      anchors.topMargin: 5
      anchors.horizontalCenter: parent.horizontalCenter
   }

   //Description
   Text {
      id: description

      anchors.top: caloriesTextField.bottom
      anchors.topMargin: 20
      anchors.horizontalCenter: parent.horizontalCenter

      text: "Description:"
   }

   Rectangle{
      id: descriptionTextField
      width:200
      height: 200

      anchors.top: description.bottom
      anchors.topMargin: 5
      anchors.horizontalCenter: parent.horizontalCenter

      border.width: 1

      TextArea {
         id: descriptionTextArea

         anchors.fill: parent
      }
   }


   Button {
      id: addElementButton

      text: "Add"

      anchors.top: descriptionTextField.bottom
      anchors.topMargin: 10

      anchors.horizontalCenter: parent.horizontalCenter

      onClicked: {
         if(nameTextField.text == "" || caloriesTextField.text == "" || descriptionTextField.text == "")
            gui.showMessagePopup("Error!", "All of the fields must be filled out!")
         else
            Settings.addElement(nameTextField.text, caloriesTextField.text, descriptionTextArea.text)
      }
   }
}

