#include "Material.h"

bluefir::graphics::Material::Material(Shader * shader) : shader_(shader)
{
}

bluefir::graphics::Material::~Material()
{
	attributes.clear();
}
