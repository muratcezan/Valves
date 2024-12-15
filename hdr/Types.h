#ifndef TYPES_H
#define TYPES_H

#include <QObject>
#include <QMetaEnum>
#include <QDebug>

// Define a namespace to logically group related enums and functionalities
namespace Types {

// Nested namespace to encapsulate ValvesState-specific enumerations
namespace ValvesState {

Q_NAMESPACE // Marks this namespace for integration with Qt's meta-object system

// Enum class representing different states of a valve
enum class Value
{
    NotAllowed, // Valve action is not allowed
    Closed,     // Valve is in a closed state
    Opened,     // Valve is in an opened state
    Closing,    // Valve is currently in the process of closing
    Opening     // Valve is currently in the process of opening
};
Q_ENUM_NS(Value) // Makes the enum accessible to Qt's meta-object system (e.g., for use in QML)

} // namespace ValvesState
} // namespace Types

#endif // TYPES_H
