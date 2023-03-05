#pragma once
#include "Scene.h"
#include "GameObject.h"

namespace dae
{
	namespace TestSceneGraph
	{
		void LoadScene(Scene& scene)
		{
			// Test SetParent on 2 objects not part of a scene
			auto go1 = std::make_shared<GameObject>();
			auto go2 = std::make_shared<GameObject>();
			go1->SetParent(nullptr);	// nullptr without having a parent
			go1->SetParent(go2);	// object without having a parent
			go1->SetParent(nullptr);	// nullptr while having a parent

			// Test SetParent on a root object in a scene
			scene.Add(go2);
			go1->SetParent(go2);	// object without having a parent with object in scene
			go1->SetParent(nullptr);	// nullptr while having a parent inside a scene
			go2->SetParent(nullptr);	// nullptr as root of scene
			scene.RemoveAll();
			scene.Add(go1);
			go1->SetParent(go2);	// object as root of scene with object outside scene
			go1->SetParent(nullptr);	// nullptr while having a parent
			go2->SetParent(nullptr);	// nullptr without having a parent
			scene.RemoveAll();

			// Test SetParent on a child object in a scene
			go2->SetParent(go1);
			scene.Add(go1);
			auto go3 = std::make_shared<GameObject>();
			go3->SetParent(go2);	// object without having a parent with child object in scene
			go3->SetParent(go1);	// root parent while having a child of the root as a parent in scene
			go3->SetParent(go2);	// object that is a child of the same root parent object in scene
			scene.RemoveAll();
		}
	}
}