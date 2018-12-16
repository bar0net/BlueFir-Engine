#include "Material.h"

#include "BaseMacros.h"

bluefir::graphics::Material::Material(Shader * shader) : shader_(shader)
{
}

bluefir::graphics::Material::~Material()
{
	attributes.clear();
}
