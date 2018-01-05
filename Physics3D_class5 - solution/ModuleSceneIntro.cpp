#include "Globals.h"
#include "Application.h"
#include "ModuleSceneIntro.h"
#include "Primitive.h"
#include "PhysBody3D.h"
#include "ModulePhysics3D.h"
#include "ModulePlayer.h"
#include "PhysVehicle3D.h"
#include "ModuleAudio.h"


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

	App->audio->PlayMusic("music/freestyla.ogg");
	
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
		/*LOG("PINTA LAS ROADS");*/
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

	if (body1->type == Turbo && body2 == pb_wheel2)
	{
		App->player->jump = true;
		LOG("HIT!");
	}
	
	/*for (int i = 1; i < 10; i++)
	{
		if (sensors[i] == body1 && App->player->jump == true)
		{
			Turbo();
		}
	}*/
	
}


Cube ModuleSceneIntro::CreateRamps(vec3 measures, vec3 position, float angle, const vec3 &u, Color color)
{	
	Cube example(measures.x, measures.y, measures.z);
	example.SetPos(position.x, position.y, position.z);
	example.SetRotation(angle, u);
	example.color = color;
	parts.add(example);
	/*LOG("CREA LA RAMPA");*/
	

	return example;
	
	
}


Cube ModuleSceneIntro::CreateRoadSensors(vec3 measures, vec3 position, Color color)
{
	Cube example(measures.x, measures.y, measures.z);
	example.SetPos(position.x, position.y, position.z);
	example.color = color;
	parts.add(example);

	
	PhysBody3D* pbody = App->physics->AddBody(example, 0, Type::Turbo);
	pbody->SetAsSensor(true);
	pbody->collision_listeners.add(this);
	

	

	return example;
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



void ModuleSceneIntro::CreateMap()//need to minimize this function
{
	Cube bigsensor(1000, 1, 1300);
	bigsensor.SetPos(22, 0, 60);
	CreateExternalSensors(bigsensor, 0.0f, 0, true, Red);//using the first member of the sensors array. Use NoColor in case we want to hide it

	/*Cube firstturbo(40, 5, 20);
	firstturbo.SetPos(-115, 5, 165);
	CreateExternalSensors(firstturbo, 0.0f, 1, true, Green);*/
	Cube firstturbo = CreateRoadSensors({ 40, 5, 20 }, {-115, 5, 165}, Green);

	Cube secondturbo(20, 5, 40);
	secondturbo.SetPos(-200, 5, 220);
	CreateExternalSensors(secondturbo, 0.0f, 2, true, Green);

	Cube ramp1 = CreateRamps({ 20, 3, 20 }, { 20, 10, 20 }, -12, { 1, 0, 0 }, Blue);
	//CreateRoadSensors(ramp1, 0.0f, 1, true);//First after the big sensor

	
	
	Cube road1 = CreateRoads({ 20, 5, 160 }, { 0, 5, 75 }, Grey);
	Cube road2 = CreateRoads({ 100, 5, 20 }, { -45, 5, 165 }, Grey);
	Cube road3 = CreateRoads({ 160, 5, 20 }, { -230, 5, 165 }, Grey);
	Cube road4 = CreateRoads({ 20, 5, 120 }, { -320, 5, 115 }, Grey);
	Cube road5 = CreateRoads({ 160, 5, 20 }, { -410, 5, 65 }, Grey);
	Cube road6 = CreateRoads({ 20, 5, 300 }, { -500, 5, 205 }, Grey);
	Cube road7 = CreateRoads({ 300, 5, 20 }, { -360, 5, 365 }, Grey);
	Cube road8 = CreateRoads({ 20, 5, 135 }, { -200, 5, 310 }, Grey);
	Cube road9 = CreateRoads({20, 5, 250}, {-200, 5, 0}, Grey);
	Cube road10 = CreateRoads({160, 5, 20}, {-100, 5, -100}, Grey);
	

}