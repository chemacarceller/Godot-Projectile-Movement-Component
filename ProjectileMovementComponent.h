// projectile_movement.h
#ifndef PROJECTILE_MOVEMENT_COMPONENT_H
#define PROJECTILE_MOVEMENT_COMPONENT_H

#include <godot_cpp/classes/node.hpp>
#include <godot_cpp/classes/area3d.hpp>
#include <godot_cpp/variant/vector3.hpp>

// Using the godot namespace to avoid prefixing all Godot classes with 'godot::'
using namespace godot;

class ProjectileMovementComponent : public Node {

    GDCLASS(ProjectileMovementComponent, Node)

    private:

        bool _IsEnabled;
        Vector3 direction;
        float speed;
        Area3D *_myActor;

    protected:
        static void _bind_methods();

    public:
        ProjectileMovementComponent();
        ~ProjectileMovementComponent();

        // Métodos de ciclo de vida de Godot
        void _ready() override;
        void _physics_process(double delta) override;

        // Getters y Setters
        void set_is_enabled(const bool value);
        bool get_is_enabled() const;

        void set_direction(const Vector3 value);
        Vector3 get_direction() const;

        void set_speed(const float value);
        float get_speed() const;
};

#endif // BASIC_PROJECTILE_MOVEMENT_COMPONENT_H
