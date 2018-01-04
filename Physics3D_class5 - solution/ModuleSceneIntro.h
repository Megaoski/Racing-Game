#pragma once
#include "Module.h"
#include "p2DynArray.h"
#include "Globals.h"
#include "Primitive.h"




struct PhysBody3D;
struct PhysMotor3D;


class ModuleSceneIntro : public Module
{
public:
	ModuleSceneIntro(Application* app, bool start_enabled = true);
	~ModuleSceneIntro();

	bool Start();
	update_status Update(float dt);
	bool CleanUp();

	void OnCollision(PhysBody3D* body1, PhysBody3D* body2);
	void CreateMap();
	/*Cube*/ void CreateRamps(/*float w, float h, float d, float x, float y, float z, int angle, vec3 rotation, Color color*/);
	void CreateRampSensors(Cube& cube, float mass, uint i, bool set_the_sensor);
	void CreateExternalSensors();
	void VehicleHasFallen();
	void Turbo();

public:
	

	PhysBody3D* pb_chassis;
	Cube p_chassis;

	PhysBody3D* pb_wheel;
	Cylinder p_wheel;

	PhysBody3D* pb_wheel2;
	Cylinder p_wheel2;

	PhysMotor3D* left_wheel;
	PhysMotor3D* right_wheel;

	//-----------------------------
	p2List<Cube> parts;
	p2List<Cube> ramps;
	

	PhysBody3D* sensors[10]; // array para los sensores de las rampas

	Cube bigsensorino;
	PhysBody3D* bigsensor;

	
	

};
