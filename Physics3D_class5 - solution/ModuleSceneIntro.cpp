#include "Globals.h"
#include "Application.h"
#include "ModuleSceneIntro.h"
#include "Primitive.h"
#include "PhysBody3D.h"
#include "ModulePhysics3D.h"
#include "ModulePlayer.h"
#include "PhysVehicle3D.h"


#define SIZE_ARRAY(_A_) (sizeof(_A_)/sizeof(_a_[0]))


ModuleSceneIntro::ModuleSceneIntro(Application* app, bool start_enabled) : Module(app, start_enabled)
{
}

ModuleSceneIntro::~ModuleSceneIntro()
{}

// Load assets
bool ModuleSceneIntro::Start()
{
	LOG("Loading Intro assets");
	bool ret = true;
	
	CreateMap();
	
	for (p2List_item<Cube>* item = parts.getFirst(); item; item = item->next)
	{
		App->physics->AddBody(item->data, 0);
	}

	
	
	return ret;
}

// Load assets
bool ModuleSceneIntro::CleanUp()
{
	LOG("Unloading Intro scene");

	return true;
}

// Update
update_status ModuleSceneIntro::Update(float dt)
{

	for (p2List_item<Cube>* item = parts.getFirst(); item; item = item->next)
	{
		item->data.Render();
		LOG("PINTA LAS ROADS");
	}
		

	return UPDATE_CONTINUE;
}

void ModuleSceneIntro::OnCollision(PhysBody3D* body1, PhysBody3D* body2)
{
	/*LOG("HIT!");*/
	if (sensors[0] == body1)
	{
		VehicleHasFallen();
	}

	for (int i = 1; i < 10; i++)
	{
		if (sensors[i] == body1)
		{
			Turbo();
		}
	}
}


Cube ModuleSceneIntro::CreateRamps(vec3 measures, vec3 position, float angle, const vec3 &u, Color color)
{	
	Cube example(measures.x, measures.y, measures.z);
	example.SetPos(position.x, position.y, position.z);
	example.SetRotation(angle, u);
	example.color = color;
	parts.add(example);
	LOG("CREA LA RAMPA");
	

	return example;
	
	
}


void ModuleSceneIntro::CreateRampSensors(Cube& cube, float mass, uint i, bool set_the_sensor)
{
	sensors[i] = App->physics->AddBody(cube, mass);
	sensors[i]->SetAsSensor(set_the_sensor);
	sensors[i]->collision_listeners.add(this);
}

Cube ModuleSceneIntro::CreateRoads(vec3 measures, vec3 position, Color color)
{
	Cube example(measures.x, measures.y, measures.z);
	example.SetPos(position.x, position.y,position.z);
	example.color = color;
	parts.add(example);

	return example;
}

void ModuleSceneIntro::CreateExternalSensors(Cube& cube, float mass, uint i, bool set_the_sensor, Color color)
{

	cube.color = color;
	parts.add(cube);

	sensors[i] = App->physics->AddBody(cube, mass);
	sensors[i]->SetAsSensor(set_the_sensor);
	sensors[i]->collision_listeners.add(this);

}

void ModuleSceneIntro::VehicleHasFallen()
{
	App->player->vehicle->SetTransform(IdentityMatrix.M);
	App->player->vehicle->SetPos(App->player->initial_pos.x, App->player->initial_pos.y, App->player->initial_pos.z);
	
	App->player->vehicle->body->setLinearVelocity(btVector3(0,0,0));
	App->player->vehicle->body->setAngularVelocity(btVector3(0, 0, 0));
	App->player->brake = BRAKE_POWER;
	
	
}

void ModuleSceneIntro::Turbo()
{
	App->player->vehicle->body->setLinearVelocity(btVector3(0, 10, 30));
	App->player->vehicle->body->setAngularVelocity(btVector3(0, 0, 0));
}

void ModuleSceneIntro::CreateMap()//need to minimize this function
{
	Cube bigsensor(1000, 1, 1300);
	bigsensor.SetPos(22, 0, 60);
	CreateExternalSensors(bigsensor, 0.0f, 0, true, Red);//using the first memeber of the sensors array. Use NoColor in case we want to hide it

	Cube ramp1 = CreateRamps({ 20, 3, 30 }, { 0, 5, 20 }, -12, { 1, 0, 0 }, Blue);
	CreateRampSensors(ramp1, 0.0f, 1, true);//First after the big sensor

	Cube road1 = CreateRoads({ 20, 5, 160 }, {0, 5, 75}, Grey);
	Cube road2 = CreateRoads({ 160, 5, 20 }, {-70, 5, 165 }, Grey);
	Cube road3 = CreateRoads({ 160, 5, 20 }, { -230, 5, 165 }, Grey);
	Cube road4 = CreateRoads({ 20, 5, 120 }, { -320, 5, 115 }, Grey);
	Cube road5 = CreateRoads({ 160, 5, 20 }, { -410, 5, 65 }, Grey);
	

}