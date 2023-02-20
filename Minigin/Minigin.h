#pragma once
#include <string>
#include <functional>

namespace dae
{
	class Minigin
	{
	public:
		explicit Minigin(const std::string& dataPath);
		~Minigin();

		Minigin(const Minigin& other)				= delete;
		Minigin(Minigin&& other)					= delete;
		Minigin& operator=(const Minigin& other)	= delete;
		Minigin& operator=(Minigin&& other)			= delete;

		void Run();
		void LoadGame() const;
	};
}