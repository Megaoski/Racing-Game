#include "Globals.h"
#include "Application.h"
#include "ModuleSceneIntro.h"
#include "Primitive.h"
#include "PhysBody3D.h"
#include "ModulePhysics3D.h"

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

	App->camera->Move(vec3(3.0f, 3.0f, 0.0f));
	App->camera->LookAt(vec3(0, 0, 0));

	CreateMap(vec3(0,0,0));

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
	Plane p(0, 1, 0, 0);
	p.axis = true;
	p.Render();

	for (p2List_item<Cube>* item = parts.getFirst(); item; item = item->next)
	{
		item->data.Render();
	}
	
	
	

	return UPDATE_CONTINUE;
}

void ModuleSceneIntro::OnCollision(PhysBody3D* body1, PhysBody3D* body2)
{
}


void ModuleSceneIntro::CreateMap(vec3 pos)
{
	Cube part1(20, 5, 130);
	part1.SetPos(0, 0, 60);
	part1.color = Grey;
	parts.add(part1);

	Cube part2(130, 5, 20);
	part2.SetPos(-55, 0, 130);
	part2.color = Grey;
	parts.add(part2);

	Cube part3(20, 5, 130);
	part3.SetPos(-130, 0, 75);
	part3.color = Grey;
	parts.add(part3);

	Cube part4(130, 5, 20);
	part4.SetPos(-65, 0,-15);
	part4.color = Grey;
	parts.add(part4);

}
