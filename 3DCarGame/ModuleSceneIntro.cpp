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

	App->camera->Move(vec3(1.0f, 1.0f, 0.0f));
	App->camera->LookAt(vec3(0, 0, 0));
	App->audio->PlayMusic("audio/music.ogg");
	
	CreateMap();
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

	dark_floor.Render();
	for (p2List_item<Cube>* item = road.getFirst(); item; item = item->next)
	{
		item->data.Render();
	}
	for (p2List_item<Fan>* item = fan.getFirst(); item; item = item->next)
	{
		btQuaternion quat = item->data.body_cube2->GetRotation();
		quat = quat.normalized();
		float angle = 2 * acos(quat.w()) * 180 / 3.14;
		float den = sqrt(1 - quat.w() *quat.w());
		item->data.cube2.SetRotation(angle, { quat.x() / den,quat.y() / den,quat.z() / den });
		item->data.cube2.SetPos(item->data.body_cube2->GetPos().x(), item->data.body_cube2->GetPos().y(), item->data.body_cube2->GetPos().z());
		item->data.cube2.Render();
	}

	return UPDATE_CONTINUE;
}

void ModuleSceneIntro::OnCollision(PhysBody3D* body1, PhysBody3D* body2)
{
	if (body1->type == Floor)
	{
		App->player->RespawnCar();	
	}
}

void ModuleSceneIntro:: CreateMap() {

	CreateLowerLimit(1000, 1, 1000, 0, 4.5f, 0 ,Black);
	//1st line
	CreateNormalFloor(10, ROAD_HEIGHT, 180.f, 0, 10, 80 ,ROAD_COLOR);
	CreateFan(0, 24, 30);

	CreateFan(0, 24, 50);
	CreateFan(0, 24, 70);

	

	
	//2nd line
	CreateNormalFloor(190, ROAD_HEIGHT, 10, -90, 10, 175, ROAD_COLOR);

	//3rd line
	CreateNormalFloor(10, ROAD_HEIGHT, 40.f, -180, 10, 160, ROAD_COLOR);
	
	//4th line
	CreateNormalFloor(60, ROAD_HEIGHT, 10.f, -145, 10, 145, ROAD_COLOR);

	//5th line
	CreateNormalFloor(10, ROAD_HEIGHT, 60.f, -120, 10, 120, ROAD_COLOR);

	//6th line
	CreateNormalFloor(60, ROAD_HEIGHT, 10.f, -145, 10, 85, ROAD_COLOR);

	//7th line
	CreateNormalFloor(10, ROAD_HEIGHT, 40.f, -180, 10, 70, ROAD_COLOR);

	//8th line
	CreateNormalFloor(80, ROAD_HEIGHT, 10.f, -145, 10, 50, ROAD_COLOR);

	//9th line
	CreateNormalFloor(10, ROAD_HEIGHT, 160.f, -110, 10, -25, ROAD_COLOR);
}

void ModuleSceneIntro::CreateNormalFloor(float width, float height, float large, float x, float y, float z, Color color)
{
	Cube ret(width, height, large);
	ret.SetPos(x, y, z);
	ret.color = ROAD_COLOR;

	road.add(ret);

	App->physics->AddBody(ret, 0);
}

void ModuleSceneIntro::CreateRamp(float width, float height, float large, float x, float y, float z, float degree, vec3 axis, Color color) {
	Cube ret(width, height, large);
	ret.SetPos(x, y, z);
	ret.color = color;
	ret.SetRotation(degree, axis);

	road.add(ret);

	App->physics->AddBody(ret, 0);
}

void ModuleSceneIntro::CreateLowerLimit(float width, float height, float large, float x, float y, float z, Color color) {
	Cube ret(width, height, large);
	ret.SetPos(x, y, z);
	ret.color = color;


	road.add(ret);
	
	PhysBody3D* pbody = App->physics->AddBody(ret, 0, SceneObjectType::Floor);
	pbody->SetSensor();
	pbody->collision_listeners.add(this);
}
void ModuleSceneIntro::CreateGoal(float x, float y, float z, bool isgoal) {

	Cube ret(0.3f, 20, 20);
	ret.SetPos(x, y, z);

	SceneObjectType type;

	if (isgoal) {
		type = Goal;
	}
	else {
		type = LapSensor;
	}
	PhysBody3D* pbody = App->physics->AddBody(ret, 0, type);

	pbody->SetSensor();
	pbody->collision_listeners.add(this);
}

void ModuleSceneIntro::CreateFan(float x, float y, float z, Color color) {

	Cube c(1, 1, 1);
	c.SetPos(x, y, z);
	PhysBody3D* c_body = App->physics->AddBody(c, 0);

	Cube c2(0.1f, 9.5f, 1);
	c2.SetPos(x + 2, y, z);
	PhysBody3D* c2_body = App->physics->AddBody(c2, 1000, SceneObjectType::Floor);
	c2.color = Blue;
	

	App->physics->AddConstraintHinge(*c_body, *c2_body, { 0,0,0 }, { 0,8,0 }, { 0,0,1 }, { 1,0,0 }, true);

	Fan bl(c, c2, c_body, c2_body);
	fan.add(bl);
}
