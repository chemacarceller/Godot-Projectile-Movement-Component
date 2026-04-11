class_name BasicProjectileMovementComponent extends Node

# Property to activate or deactivate the movement
@export var _isEnabled : bool = true

func set_IsEnabled(value : bool) -> void :
	_isEnabled = value

func get_IsEnabled() -> bool :
	return _isEnabled


## Direction in which the parentActor must move, it is normalized so that the speed works corrctly
@export var direction : Vector3 = Vector3.ZERO :
	set(value):
		if (value != Vector3.ZERO):
			direction = value.normalized()
	get():
		return direction

## Movement speed
@export var speed : float = 0.0


# Geting the actor this component is attached to
@onready var _myActor : Area3D = get_parent()


func _notification(what):
	if what == NOTIFICATION_WM_CLOSE_REQUEST:
		MyLogger.info("The projectile's movement closes", 'basic_projectile_movement.gd',34,true)

# Doing the signal conection
func _ready() -> void:
	MyLogger.info("The projectile's movement is created", 'basic_projectile_movement.gd',38,true)


# Moving the parent actor detecting a collision
func _physics_process(delta: float) -> void:
	# Only if it is enabled
	if _isEnabled and _myActor != null:
		_myActor.global_position += direction * speed * delta
