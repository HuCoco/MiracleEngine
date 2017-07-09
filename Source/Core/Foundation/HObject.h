#pragma once
#include <Independent/Platform/PreCompileHeader.h>
#include <Core/Foundation/HName.h>

NAMESPACE_MENGINE_BEGIN

class HObject
{
public:

	enum class HObjectType : _U8
	{
		GRAPHICS_OBJECT,
		GAME_OBJECT,
		GAME_COMPONENT,
		GAME_WORLD
	};

	HObject(HObjectType a_Type);
	HObject(HObjectType a_Type, const std::string& a_Name);
	~HObject();

	void SetName(const std::string& a_Name);
	void SetName(const HName& a_Name);
	inline HName GetName() const;
	inline HObjectType GetObjectType() const;
	// todo.
	//virtual void Serialize();
	//virtual void Deserialize();

protected:
	HName m_Name;
	HObjectType m_Type;
};


inline HName HObject::GetName() const
{
	return m_Name;
}

inline HObject::HObjectType HObject::GetObjectType() const
{
	return m_Type;
}

NAMESPACE_MENGINE_END