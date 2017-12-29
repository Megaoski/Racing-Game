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

	

	CreateMap(vec3(0,0,0));

	//Creating the big ground sensor 
	sensorino.size = vec3(100, 1, 130);
	sensorino.SetPos(22,0,60);

	sensor = App->physics->AddBody(sensorino, 0.0f);
	sensor->SetAsSensor(true);
	sensor->collision_listeners.add(this);
	
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
	/*Plane p(0, 1, 0, 0);
	p.axis = true;
	p.Render();
*/
	sensorino.color = Red;//Comment to hide the big sensor
	sensorino.Render();

	for (p2List_item<Cube>* item = parts.getFirst(); item; item = item->next)
	{
		item->data.Render();
	}
	
	
	

	return UPDATE_CONTINUE;
}

void ModuleSceneIntro::OnCollision(PhysBody3D* body1, PhysBody3D* body2)
{
	/*LOG("HIT!");*/
	if (sensor == body1)
	{
		VehicleHasFallen();
	}
}


void ModuleSceneIntro::CreateMap(vec3 pos)
{
	Cube part1(20, 5, 130);
	part1.SetPos(0, 5, 60);
	part1.color = Grey;
	parts.add(part1);

	Cube part2(130, 5, 20);
	part2.SetPos(-55, 5, 130);
	part2.color = Grey;
	parts.add(part2);

	Cube part3(20, 5, 130);
	part3.SetPos(-130, 5, 75);
	part3.color = Grey;
	parts.add(part3);

	Cube part4(130, 5, 20);
	part4.SetPos(-65, 5,-15);
	part4.color = Grey;
	parts.add(part4);

}

void ModuleSceneIntro::VehicleHasFallen()
{
	App->player->vehicle->SetTransform(IdentityMatrix.M);
	App->player->vehicle->SetPos(App->player->initial_pos.x, App->player->initial_pos.y, App->player->initial_pos.z);
	
	App->player->vehicle->body->setLinearVelocity(btVector3(0,0,0));
	App->player->vehicle->body->setAngularVelocity(btVector3(0, 0, 0));
	App->player->brake = BRAKE_POWER;
	
	
}