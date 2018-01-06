#pragma once
#include "Module.h"
#include "Globals.h"
#include "p2Point.h"

struct PhysVehicle3D;

#define MAX_ACCELERATION 1000.0f
#define TURN_DEGREES 15.0f * DEGTORAD
#define BRAKE_POWER 1000.0f

struct Turbos
{
	Cube cube;
	PhysBody3D* body;
};

class ModulePlayer : public Module
{
public:
	ModulePlayer(Application* app, bool start_enabled = true);
	virtual ~ModulePlayer();

	bool Start();
	update_status Update(float dt);
	bool CleanUp();
	

public:
	vec3 initial_pos;//Initial position for the vehicle
	PhysVehicle3D* vehicle;
	float turn;
	float acceleration;
	float brake;
	int cameracounter = 0;
	

	p2List<Turbos> turbos; //for render

	Turbos FirstTurbo;
	Turbos DeadFloor;
};