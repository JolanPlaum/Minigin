#pragma once
// Includes
#include "Component.h"
#include <memory>
#include <string>

namespace dae
{
	// Class Forward Declarations
	class Texture2D;
	
	// Class Declaration
	class CTexture : public BehaviourComponent
	{
	public:
		// Constructors and Destructor
		CTexture() = default;
		virtual ~CTexture() = default;
		
		// Copy and Move semantics
		CTexture(const CTexture& other)					= delete;
		CTexture& operator=(const CTexture& other)		= delete;
		CTexture(CTexture&& other) noexcept				= delete;
		CTexture& operator=(CTexture&& other) noexcept	= delete;
	
		//---------------------------
		// Public Member Functions
		//---------------------------
		void Update() override {};

		void SetTexture(const std::string& filename);

		Texture2D& GetTexture() const { return *m_pTexture; }
	
	
	protected:
		// Member variables
		std::shared_ptr<Texture2D> m_pTexture{};
	
		//---------------------------
		// Protected Member Functions
		//---------------------------
	
	};
}

