#include "ProjectileMovementComponent.h"

// It provides the interface to ClassDB, Godot's internal database of all registered classes
#include <godot_cpp/core/class_db.hpp>

using namespace godot;


void ProjectileMovementComponent::_bind_methods() {
    
    // Record of methods for Godot to see
    ClassDB::bind_method(D_METHOD("set_enabled", "value"), &ProjectileMovementComponent::set_enabled);
    ClassDB::bind_method(D_METHOD("is_enabled"), &ProjectileMovementComponent::is_enabled);
    
    ClassDB::bind_method(D_METHOD("set_direction", "value"), &ProjectileMovementComponent::set_direction);
    ClassDB::bind_method(D_METHOD("get_direction"), &ProjectileMovementComponent::get_direction);
    
    ClassDB::bind_method(D_METHOD("set_speed", "value"), &ProjectileMovementComponent::set_speed);
    ClassDB::bind_method(D_METHOD("get_speed"), &ProjectileMovementComponent::get_speed);

    // Exporting properties (equivalent to @export)
    ADD_PROPERTY(PropertyInfo(Variant::BOOL, "_isEnabled"), "set_enabled", "is_enabled");
    ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "_speed"), "set_speed", "get_speed");
}


// Constructor and Destructor
ProjectileMovementComponent::ProjectileMovementComponent() {}

ProjectileMovementComponent::~ProjectileMovementComponent() {}


// Called when the node enters the scene tree for the first time.
void ProjectileMovementComponent::_ready() {
    
    // Equivalent to @onready var parentActor = get_parent()
    parentActor = Object::cast_to<Node3D>(get_parent());
}

void ProjectileMovementComponent::_physics_process(double delta) {

    if (_isEnabled && parentActor != nullptr) {

        Vector3 current_pos = parentActor->get_global_position();

        // In C++, delta is a double; we perform the scalar multiplication.
        Vector3 new_pos = current_pos + (direction * _speed * static_cast<float>(delta));
        parentActor->set_global_position(new_pos);
    }
}


// This method is called when the node receives a notification. In this case, it listens for the NOTIFICATION_WM_CLOSE_REQUEST notification, which is sent when the window is requested to close. When this notification is received, the component calls queue_free() to free itself from memory, ensuring proper cleanup.
void ProjectileMovementComponent::_notification(int p_what) {

    // Handle the close request notification to ensure that the node is properly freed when the window is closed. This prevents potential memory leaks and ensures that the component is cleaned up correctly when the game is exited.
    if (p_what == NOTIFICATION_WM_CLOSE_REQUEST) {

        if (parentActor != nullptr) {

            // Get the unique ID that Godot assigned to this instance
            uint64_t instance_id = parentActor->get_instance_id();

            // Check with ObjectDB if that instance still exists in memory
            if (ObjectDB::get_instance(ObjectID(instance_id)) != nullptr) {

                // Free the node when the window close request is received. This ensures that the component is properly cleaned up and does not persist in memory after the game is closed.
                parentActor->queue_free();
                parentActor = nullptr;
            }
        }
    }
}