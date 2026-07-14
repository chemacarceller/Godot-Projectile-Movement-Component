#include "ProjectileMovementComponent.h"
#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/variant/utility_functions.hpp>

using namespace godot;

// Registro de propiedades y métodos en el motor
void ProjectileMovementComponent::_bind_methods() {
    // Registro de métodos (requerido para las propiedades)
    ClassDB::bind_method(D_METHOD("set_IsEnabled", "value"), &ProjectileMovementComponent::set_is_enabled);
    ClassDB::bind_method(D_METHOD("get_IsEnabled"), &ProjectileMovementComponent::get_is_enabled);
    
    ClassDB::bind_method(D_METHOD("set_direction", "value"), &ProjectileMovementComponent::set_direction);
    ClassDB::bind_method(D_METHOD("get_direction"), &ProjectileMovementComponent::get_direction);
    
    ClassDB::bind_method(D_METHOD("set_speed", "value"), &ProjectileMovementComponent::set_speed);
    ClassDB::bind_method(D_METHOD("get_speed"), &ProjectileMovementComponent::get_speed);

    // Exponer propiedades al Inspector de Godot (@export)
    ClassDB::add_property("ProjectileMovementComponent", PropertyInfo(Variant::BOOL, "_IsEnabled"), "set_IsEnabled", "get_IsEnabled");
    ClassDB::add_property("ProjectileMovementComponent", PropertyInfo(Variant::VECTOR3, "direction"), "set_direction", "get_direction");
    ClassDB::add_property("ProjectileMovementComponent", PropertyInfo(Variant::FLOAT, "speed"), "set_speed", "get_speed");
}

// Constructor con valores por defecto
ProjectileMovementComponent::ProjectileMovementComponent() {
    _IsEnabled = true;
    direction = Vector3(0.0f, 0.0f, 0.0f);
    speed = 0.0f;
    _myActor = nullptr;
}

ProjectileMovementComponent::~ProjectileMovementComponent() {}

// Equivalente al bloque @onready de tu script
void ProjectileMovementComponent::_ready() {
    // Intenta obtener el nodo padre mapeado como un Area3D
    _myActor = Object::cast_to<Area3D>(get_parent());
    
    if (_myActor == nullptr) {
        UtilityFunctions::push_warning("ProjectileMovementComponent: El nodo padre no es un Area3D o es nulo.");
    }
}

// Procesamiento físico por cuadro
void ProjectileMovementComponent::_physics_process(double delta) {
    if (_IsEnabled && _myActor != nullptr) {
        Vector3 current_pos = _myActor->get_global_position();
        // En C++ delta es un double, realizamos la multiplicación escalar
        Vector3 new_pos = current_pos + (direction * speed * static_cast<float>(delta));
        _myActor->set_global_position(new_pos);
    }
}

// Implementación de Getters y Setters con la lógica de GDScript
void ProjectileMovementComponent::set_is_enabled(const bool value) {
    _IsEnabled = value;
}

bool ProjectileMovementComponent::get_is_enabled() const {
    return _IsEnabled;
}

void ProjectileMovementComponent::set_direction(const Vector3 value) {
    if (value != Vector3(0.0f, 0.0f, 0.0f)) {
        direction = value.normalized();
    }
}

Vector3 ProjectileMovementComponent::get_direction() const {
    return direction;
}

void ProjectileMovementComponent::set_speed(const float value) {
    speed = value;
}

float ProjectileMovementComponent::get_speed() const {
    return speed;
}
