#pragma once
#include <glm/glm.hpp>
namespace gfx {
class Material {
  public:
	Material() { };
	~Material() {
	};
	//Getters
	std::string& GetName() {
		return m_Name;
	}

    std::string GetAlbedoTexture()					{
		return m_AlbedoTexture;
	}
    std::string GetNormalTexture()					{
		return m_NormalTexture;
	}
    std::string GetRoughnessTexture()					{
		return m_RoughnessTexture;
	}
    std::string GetMetalTexture()						{
		return m_MetalTexture;
	}
	//Setters
    void SetName(const std::string& name)						{
		m_Name = name;
	}
    void SetAlbedoTexture	( const std::string& tex)		{
		m_AlbedoTexture = tex;
	}
    void SetNormalTexture	( const std::string& tex)		{
		m_NormalTexture = tex;
	}
    void SetRoughnessTexture( const std::string& tex)		{
		m_RoughnessTexture = tex;
	}
    void SetMetalTexture	( const std::string& tex)		{
		m_MetalTexture = tex;
	}
  private:
    std::string m_AlbedoTexture	= "";
    std::string m_NormalTexture = "";
    std::string m_RoughnessTexture = "";
    std::string m_MetalTexture = "";
	std::string m_Name = "";
};
}
