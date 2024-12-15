#ifndef COLUMNVALVESVIEWMODEL_H
#define COLUMNVALVESVIEWMODEL_H

#include <QObject>
#include <QQmlEngine>
#include <QMetaObject>
#include <QVariant>
#include <QTimer>

#include "Types.h"  // Header file where the Types enum class is defined

// ViewModel class for managing the state and behavior of column valves
class ColumnValvesViewModel : public QObject
{
    Q_OBJECT

    // Property to expose the current state of the valves to QML
    Q_PROPERTY(Types::ValvesState::Value valvesState READ getValvesState WRITE setValvesState NOTIFY valvesStateChanged)

public:
    explicit ColumnValvesViewModel(QObject *parent = nullptr); // Constructor with an optional parent object

    // Q_INVOKABLE function to convert an enum value to a string representation
    Q_INVOKABLE QString valvesStateToString(Types::ValvesState::Value state) const {
        if (keyValues.contains(state)) {
            return keyValues[state]; // Return the corresponding string for the valve state
        }
        return "Unknown"; // Return "Unknown" if the state is not recognized
    };

    // Getter for the valvesState property
    Types::ValvesState::Value getValvesState() const;

    // Setter for the valvesState property
    void setValvesState(Types::ValvesState::Value state);

signals:
    // Signals to notify specific valve-related actions
    void closeValves();         // Emitted when closing the valves
    void openValves();          // Emitted when opening the valves
    void openingValves();       // Emitted when the valves are in the process of opening
    void closingValves();       // Emitted when the valves are in the process of closing
    void notAllowedValves();    // Emitted when the action is not allowed
    void valvesStateChanged();  // Emitted when the valve state changes

public slots:
    // Slots to handle valve-related actions
    void onCloseValves();       // Slot to handle closing valves
    void onOpenValves();        // Slot to handle opening valves
    void onNotAllowedValves();  // Slot to handle not allowed state
    void onClosingValves();     // Slot to handle valves in closing state
    void onOpeningValves();     // Slot to handle valves in opening state

private slots:
    void onTimerTimeout();      // Slot to handle timer timeout events

private:
    Types::ValvesState::Value m_valvesState; // Current state of the valves

    // Map to store the string representation of each valve state
    QMap<Types::ValvesState::Value, QString> keyValues = {
        {Types::ValvesState::Value::NotAllowed, "Closed"},
        {Types::ValvesState::Value::Closed, "Closed"},
        {Types::ValvesState::Value::Opened, "Opened"},
        {Types::ValvesState::Value::Closing, "Closing"},
        {Types::ValvesState::Value::Opening, "Opening"}
    };

    QTimer m_timer; // Timer for handling periodic tasks or state transitions
};

#endif // COLUMNVALVESVIEWMODEL_H
