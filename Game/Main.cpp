#include "Engine.h"
#include <iostream>

class Singleton
{
public:
	//dtor
	~Singleton() { std::cout << "dtor\n"; }
	//copy ctor
	Singleton(const Singleton& other) = delete;
	//assignment operator
	Singleton& operator = (const Singleton& other) = delete;
	//assignment ctor

	void Say() { std::cout << "AAAAAAA\n"; }

	static Singleton& Instance()
	{
		static Singleton instance;
		return instance;
	}

private:
	//ctor
	Singleton() { std::cout << "ctor\n"; }
};

void f()
{
	static int c = 0;
	c++;
	std::cout << c << std::endl;
}

int main()
{
	f();
	f();
	f();
	f();

	Singleton::Instance().Say();

	jemgine::InitializeMemory();
	jemgine::SetFilePath("../Assets");

	//initialize jemgine engine
	//renderer.Initialize();
	jemgine::g_inputSystem.Initialize();
	jemgine::g_renderer.Initialize();
	jemgine::g_audioSystem.Initialize();
	jemgine::g_resources.Initialize();

	jemgine::Engine::Instance().Register();

	jemgine::g_renderer.CreateWindow("EV3RY  BUDDY  'S FAVORITE [[Number 1 Rated Salesman1997]]", 800, 600);
	jemgine::g_renderer.SetClearColor(jemgine::Color{ 10, 10, 10, 255 });
	std::cout << "HEY EVERY       !\nIT'S ME, SPAMTON G. SPAMTON!" << std::endl;

	//load assets
	//std::shared_ptr<jemgine::Texture> texture = std::make_shared<jemgine::Texture>();
	//texture->Create(jemgine::g_renderer, "Textures/Spaceship.png");
	std::shared_ptr<jemgine::Texture> texture = jemgine::g_resources.Get<jemgine::Texture>("textures/spaceship.png", &jemgine::g_renderer);
	std::shared_ptr<jemgine::Model> model = jemgine::g_resources.Get<jemgine::Model>("Models/player.txt");
	std::shared_ptr<jemgine::Model> model2 = jemgine::g_resources.Get<jemgine::Model>("Models/player.txt");

	jemgine::g_audioSystem.AddAudio("laser", "Audio/laser.wav");

	//create actors
	jemgine::Transform transform{ { 400, 300 }, 0, { 3, 3 } };
	//std::unique_ptr<jemgine::Actor> actor = std::make_unique<jemgine::Actor>(transform);
	std::unique_ptr<jemgine::Actor> actor = jemgine::Factory::Instance().Create<jemgine::Actor>("Actor");
	actor->m_transform = transform;
	jemgine::Scene scene;
	std::unique_ptr<jemgine::Component> pcomponent = jemgine::Factory::Instance().Create<jemgine::Component>("PlayerComponent");
	actor->AddComponent(std::move(pcomponent));

	//std::unique_ptr<jemgine::SpriteComponent> scomponent = std::make_unique<jemgine::SpriteComponent>();

	//scomponent->m_texture = texture;
	//actor->AddComponent(std::move(scomponent));

	std::unique_ptr<jemgine::AudioComponent> acomponent = std::make_unique<jemgine::AudioComponent>();
	acomponent->m_soundName = "laser";
	actor->AddComponent(std::move(acomponent));

	std::unique_ptr<jemgine::Component> phcomponent = jemgine::Factory::Instance().Create<jemgine::Component>("PhysicsComponent");
	actor->AddComponent(std::move(phcomponent));

	std::unique_ptr<jemgine::ModelComponent> mcomponent = std::make_unique<jemgine::ModelComponent>();
	mcomponent->m_model = model;
	actor->AddComponent(std::move(mcomponent));


	//child actor
	jemgine::Transform transformC{ { 10, 10 }, 0, { 1, 1 } };
	std::unique_ptr<jemgine::Actor> child = std::make_unique<jemgine::Actor>(transformC);

	std::unique_ptr<jemgine::ModelComponent> mcomponentC = std::make_unique<jemgine::ModelComponent>();
	mcomponentC->m_model = model;
	child->AddComponent(std::move(mcomponentC));

	actor->AddChild(std::move(child));

	scene.Add(std::move(actor));
	
	float angle = 0;

	bool quit = false;
	while (!quit)
	{
		//update (engine)
		jemgine::g_time.Tick();
		jemgine::g_inputSystem.Update();
		jemgine::g_audioSystem.Update();


		if (jemgine::g_inputSystem.GetKeyDown(jemgine::key_escape)) quit = true;

		//update game objects

		scene.Update();

		//render
		jemgine::g_renderer.BeginFrame();

		angle += 360.0f * jemgine::g_time.deltaTime;

		scene.Draw(jemgine::g_renderer);
		//jemgine::g_renderer.Draw(texture, { 200, 150 }, angle, { 1, 1 }, {0.5f, 1.0f});

		jemgine::g_renderer.EndFrame();
	}
	jemgine::g_renderer.Shutdown();

	jemgine::g_audioSystem.Shutdown();
}