#ifndef PROJECTILE_MOVEMENT_COMPONENT_H
#define PROJECTILE_MOVEMENT_COMPONENT_H

// This is a custom movement component for translating a Node3D object in Godot
// It allows you to specify a speed and the direction, and it will translate the parent Node3D accordingly
#include <godot_cpp/classes/node.hpp>
#include <godot_cpp/classes/node3d.hpp>

// Using the godot namespace to avoid prefixing all Godot classes with 'godot::'
using namespace godot;

// The class inherits from Node, allowing it to be added as a child to any Node in the scene tree
class ProjectileMovementComponent : public Node {

    // Macro to register the class with Godot's type system
    GDCLASS(ProjectileMovementComponent, Node)

    private:

        // Underscored private variable for exported variables (following Godot's convention)

        // Indicates if the component is enabled or not
        bool _isEnabled = true;

        // Speed ​​at which the projectile moves
        float _speed = 0.0f;

        // Private variables for internal use without exposing to Godot not underscored 

        // Indicates the direction in which the projectile will move
        Vector3 direction = Vector3(0.0f, 0.0f, 0.0f);

        // Node3D object to which this component has been linked
        Node3D *parentActor = nullptr;


    protected:

        // Method to bind properties and methods to Godot   
        static void _bind_methods();

    public:

        // Constructor and destructor
        ProjectileMovementComponent();
        ~ProjectileMovementComponent();

        // Overridden methods from Node
        void _ready() override;
        void _physics_process(double delta) override;
        void _notification(int what);

        // Getters and setters for the properties
        void set_enabled(const bool value);
        bool is_enabled() const;

        void set_direction(const Vector3 value);
        Vector3 get_direction() const;

        void set_speed(const float value);
        float get_speed() const;
};

#endif
