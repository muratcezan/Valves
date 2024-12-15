#include <QThread>

#include "hdr/columnvalvesviewmodel.h"

// Constructor for initializing the ColumnValvesViewModel
ColumnValvesViewModel::ColumnValvesViewModel(QObject *parent)
    : QObject(parent), m_valvesState(Types::ValvesState::Value::Closed) // Initial valve state is "Closed"
{
    // Connect signals to their corresponding slots for valve actions
    connect(this, &ColumnValvesViewModel::openingValves, this, &ColumnValvesViewModel::onOpeningValves);
    connect(this, &ColumnValvesViewModel::closingValves, this, &ColumnValvesViewModel::onClosingValves);
    connect(this, &ColumnValvesViewModel::notAllowedValves, this, &ColumnValvesViewModel::onNotAllowedValves);

    // Connect timer timeout signal to the appropriate slot
    connect(&m_timer, &QTimer::timeout, this, &ColumnValvesViewModel::onTimerTimeout);

    // Set the timer to single-shot mode, meaning it will trigger only once when started
    m_timer.setSingleShot(true);
}

// Getter for retrieving the current valve state
Types::ValvesState::Value ColumnValvesViewModel::getValvesState() const {
    return m_valvesState;
}

// Setter for updating the valve state and emitting the state change signal
void ColumnValvesViewModel::setValvesState(Types::ValvesState::Value state) {
    if (m_valvesState != state) { // Update only if the state has changed
        m_valvesState = state;
        emit valvesStateChanged(); // Notify QML or other listeners about the state change
    }
}

// Slot to handle logic for closing the valves
void ColumnValvesViewModel::onCloseValves() {
    setValvesState(Types::ValvesState::Value::Closed); // Update the state to "Closed"
    emit closeValves(); // Emit signal to indicate the valves are closed
}

// Slot to handle logic for opening the valves
void ColumnValvesViewModel::onOpenValves() {
    setValvesState(Types::ValvesState::Value::Opened); // Update the state to "Opened"
    emit openValves(); // Emit signal to indicate the valves are opened
}

// Slot to handle the "NotAllowed" state for the valves
void ColumnValvesViewModel::onNotAllowedValves() {
    setValvesState(Types::ValvesState::Value::NotAllowed); // Update the state to "NotAllowed"
    m_timer.start(3000); // Start a 3-second timer
}

// Slot to handle the "Closing" state for the valves
void ColumnValvesViewModel::onClosingValves() {
    setValvesState(Types::ValvesState::Value::Closing); // Update the state to "Closing"
    m_timer.start(3000); // Start a 3-second timer
}

// Slot to handle the "Opening" state for the valves
void ColumnValvesViewModel::onOpeningValves() {
    setValvesState(Types::ValvesState::Value::Opening); // Update the state to "Opening"
    m_timer.start(3000); // Start a 3-second timer
}

// Slot triggered when the timer times out
void ColumnValvesViewModel::onTimerTimeout() {
    // Change the valve state based on the current state after the timer duration
    if (m_valvesState == Types::ValvesState::Value::Opening) {
        setValvesState(Types::ValvesState::Value::Opened); // If opening, transition to "Opened"
        emit openValves(); // Emit signal for valves being opened
    } else if (m_valvesState == Types::ValvesState::Value::Closing) {
        setValvesState(Types::ValvesState::Value::NotAllowed); // If closing, transition to "NotAllowed"
        emit notAllowedValves(); // Emit signal for "NotAllowed" state
    } else if (m_valvesState == Types::ValvesState::Value::NotAllowed) {
        setValvesState(Types::ValvesState::Value::Closed); // If "NotAllowed", transition to "Closed"
        emit closeValves(); // Emit signal for valves being closed
    }
}
