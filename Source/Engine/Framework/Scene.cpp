#include "Scene.h"
#include "Actor.h"
#include "../Core/StringHelper.h"
#include "../Renderer/Renderer.h"

namespace viper {
	/// <summary>
	/// Updates all actors in the scene by advancing their state based on the elapsed time.
	/// </summary>
	/// <param name="dt">The time elapsed since the last update, in seconds.</param>
	void Scene::Update(float dt) {
		// update all actors
		for (auto& actor : m_actors) {
			actor->Update(dt);
		}

		// remove destroyed actors
		for (auto iter = m_actors.begin(); iter != m_actors.end(); ) {
			if ((*iter)->destroyed) {
				iter = m_actors.erase(iter);
			}
			else {
				iter++;
			}
		}

		// check for collisions
		for (auto& actorA : m_actors) {
			for (auto& actorB : m_actors) {
				if (actorA == actorB || (actorA->destroyed || actorB->destroyed)) continue;

				float distance = (actorA->transform.position - actorB->transform.position).Length();
				if (distance <= actorA->GetRadius() + actorB->GetRadius()) {
					actorA->OnCollision(actorB.get());
					actorB->OnCollision(actorA.get());
				}
			}
		}

	}

	/// <summary>
	/// Draws all actors in the scene using the specified renderer.
	/// </summary>
	/// <param name="renderer">The renderer used to draw the actors.</param>
	void Scene::Draw(Renderer& renderer) {
		for (auto& actor : m_actors) {
			actor->Draw(renderer);
		}
	}

	/// <summary>
	/// Adds an actor to the scene by transferring ownership of the actor.
	/// </summary>
	/// <param name="actor">A unique pointer to the actor to be added. Ownership of the actor is transferred to the scene.</param>
	void Scene::AddActor(std::unique_ptr<Actor> actor)
	{
		actor->scene = this;
		m_actors.push_back(std::move(actor));
	}

	void Scene::RemoveAllActors()
	{
		m_actors.clear();
	}
}