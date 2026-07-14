#include "register_types.h"
#include "ProjectileMovementComponent.h"

using namespace godot;

void initialize_ProjectileMovementComponent(ModuleInitializationLevel p_level) {
    if (p_level != MODULE_INITIALIZATION_LEVEL_SCENE) {
        return;
    }

    // We registered our personalized class
    ClassDB::register_class<ProjectileMovementComponent>();
}

void uninitialize_ProjectileMovementComponent(ModuleInitializationLevel p_level) {
    if (p_level != MODULE_INITIALIZATION_LEVEL_SCENE) {
        return;
    }
}

extern "C" {
    GDExtensionBool GDE_EXPORT
    ProjectileMovementComponent_init(GDExtensionInterfaceGetProcAddress p_get_proc_address, const GDExtensionClassLibraryPtr p_library, GDExtensionInitialization*r_initialization) {
        godot::GDExtensionBinding::InitObject init_obj(p_get_proc_address,p_library, r_initialization);
        init_obj.register_initializer(initialize_ProjectileMovementComponent);
        init_obj.register_terminator(uninitialize_ProjectileMovementComponent);
        init_obj.set_minimum_library_initialization_level(MODULE_INITIALIZATION_LEVEL_SCENE);
        return init_obj.init();
    }
}