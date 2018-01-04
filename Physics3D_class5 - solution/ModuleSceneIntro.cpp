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

	//Creating the big ground sensor NEEDS TO BE IN ANOTHER FUNCTION TO BE CLEAN
	bigsensorino.size = vec3(1000, 1, 1300);
	bigsensorino.SetPos(22,0,60);

	bigsensor = App->physics->AddBody(bigsensorino, 0.0f);
	bigsensor->SetAsSensor(true);
	bigsensor->collision_listeners.add(this);

	
	
	for (p2List_item<Cube>* item = parts.getFirst(); item; item = item->next)
	{
		App->physics->AddBody(item->data, 0);
	}

	for (p2List_item<Cube>* item = ramps.getFirst(); item; item = item->next)
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
	bigsensorino.color = Red;//Comment to hide the big sensor
	bigsensorino.Render();


	for (p2List_item<Cube>* item = parts.getFirst(); item; item = item->next)
	{
		item->data.Render();
	}
	
	for (p2List_item<Cube>* item = ramps.getFirst(); item; item = item->next)
	{
		LOG("PINTA LA RAMPA");
		item->data.Render();
	}
	
	

	return UPDATE_CONTINUE;
}

void ModuleSceneIntro::OnCollision(PhysBody3D* body1, PhysBody3D* body2)
{
	/*LOG("HIT!");*/
	if (bigsensor == body1)
	{
		VehicleHasFallen();
	}

	if (sensors[0] == body1)
	{
		Turbo();
	}
}


void ModuleSceneIntro::CreateMap()//need to minimize this function
{

	//Cube ramp1 = CreateRamps(20, 3, 30, 0, 5, 20, -12, (1, 0, 0), Blue);
	//CreateRampSensors(ramp1, 0.0f, 0, true);//First of the sensor array

	Cube part1(20, 5, 160);
	part1.SetPos(0, 5, 75);
	part1.color = Grey;
	parts.add(part1);

	Cube part2(160, 5, 20);
	part2.SetPos(-70, 5, 165);
	part2.color = Grey;
	parts.add(part2);

	Cube part3(160, 5, 20);
	part3.SetPos(-230, 5, 165);
	part3.color = Grey;
	parts.add(part3);

	Cube part4(20, 5, 120);
	part4.SetPos(-320, 5, 115);
	part4.color = Grey;
	parts.add(part4);

	Cube part5(160, 5, 20);
	part5.SetPos(-410, 5, 65);
	part5.color = Grey;
	parts.add(part5);
	
	
}

void ModuleSceneIntro::CreateRamps(/*float w, float h, float d, float x, float y, float z, int angle, vec3 rotation, Color color*/)
{
	Cube ramp1(20, 3, 30);
	ramp1.SetPos(0, 5, 20);
	ramp1.SetRotation(-12, vec3(1, 0, 0));
	ramp1.color = Blue;
	ramps.add(ramp1);//adding ramp to the list
	CreateRampSensors(ramp1, 0, 0, true);
	/*LOG("CREA LA RAMPA");
	Cube example(w, h, d);
	example.SetPos(x, y, z);
	example.SetRotation(angle,(rotation.x, rotation.y, rotation.z));
	example.color = color;
	ramps.add(example);*/

	/*App->physics->AddBody(example, 0);*/
	
	/*return example;*/
}

void ModuleSceneIntro::CreateRampSensors(Cube& cube, float mass, uint i, bool set_the_sensor)
{
	sensors[i] = App->physics->AddBody(cube, mass);
	sensors[i]->SetAsSensor(set_the_sensor);
	sensors[i]->collision_listeners.add(this);
}

void ModuleSceneIntro::CreateExternalSensors()
{
	

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

