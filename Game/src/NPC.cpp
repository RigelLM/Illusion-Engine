#include "NPC.h"


NPC::NPC()
{

}

void NPC::LoadAssets()
{

}

void NPC::OnUpdate(Illusion::Timestep ts)
{

}

void NPC::OnRender()
{

}

void NPC::OnEvent(Illusion::Event& e)
{
	Illusion::EventDispatcher dispatcher(e);
	dispatcher.Dispatch<Illusion::KeyPressedEvent>(ENGINE_BIND_EVENT_FN(NPC::OnKeyPressed));
}

bool NPC::OnKeyPressed(Illusion::KeyPressedEvent& e)
{
	return false;
}