#pragma once
namespace engine {

	class GameObject;

	class Component
	{
	protected:
		GameObject* m_parent = nullptr;

	public:
		Component();
		Component(const Component&);
		virtual ~Component();

		void SetParent(GameObject* parent);
	};
}
