/* ***** BEGIN LICENSE BLOCK *****
 * FW4SPL - Copyright (C) IRCAD, 2017.
 * Distributed under the terms of the GNU Lesser General Public License (LGPL) as
 * published by the Free Software Foundation.
 * ****** END LICENSE BLOCK ****** */

#ifndef __FWRENDEROGRE_MATERIAL_HPP__
#define __FWRENDEROGRE_MATERIAL_HPP__

#include "fwRenderOgre/config.hpp"

#include <fwData/Material.hpp>
#include <fwData/Mesh.hpp>

#include <OGRE/OgreAxisAlignedBox.h>
#include <OGRE/OgreMaterial.h>

namespace fwRenderOgre
{

class R2VBRenderable;

/**
 * @brief   Manages a generic material
 */
class FWRENDEROGRE_CLASS_API Material
{
public:
    typedef std::unique_ptr<Material> uptr;

    /// Name of the default used as a base for the instance created by this adaptor
    FWRENDEROGRE_API static const std::string DEFAULT_MATERIAL_TEMPLATE_NAME;

    /// Constructor
    FWRENDEROGRE_API Material(const std::string& _name, const std::string& _templateName);

    /// Destructor
    FWRENDEROGRE_API ~Material();

    /// Updates material options mode (standard, point normals or cells normals)
    FWRENDEROGRE_API void updateOptionsMode(int _optionsMode );

    /// Updates material polygon mode (surface, point or wireframe)
    FWRENDEROGRE_API void updatePolygonMode( int _polygonMode );

    /// Update material shading mode (flat/gouraud/phong) in fixed function pipeline
    FWRENDEROGRE_API void updateShadingMode(int _shadingMode, int _numLights, bool _hasDiffuseTexture,
                                            bool useTextureAlpha);

    /// Update material color in fixed function pipeline
    FWRENDEROGRE_API void updateRGBAMode( ::fwData::Material::sptr fw_material );

    void setHasMeshNormal(bool hasMeshNormal);
    void setHasVertexColor(bool hasMeshNormal);
    void setHasPrimitiveColor(bool hasMeshNormal, const std::string& textureName);
    void setPrimitiveType(::fwData::Mesh::CellTypesEnum _type);

    void setMeshBoundingBox(const ::Ogre::AxisAlignedBox& _bbox);

    /// Set the diffuse texture
    FWRENDEROGRE_API void setDiffuseTexture(const ::Ogre::TexturePtr& _texture);

    /// Set scene size factor
    void setSceneSizeFactor(float sceneSizeFactor);

private:

    /// Remove a rendering pass in all techniques on the current material
    void removePass(const std::string& _name);

    /// Remove all techniques related to order independent transparency support
    /// Each time we have to modify the shader programs, we clean everything
    /// and we let the MaterialMgrListener generate the techniques from the basic techniques defined in the .material
    void cleanTransparencyTechniques();

    /// Associated Ogre material
    ::Ogre::MaterialPtr m_material;

    /// Defines if the associated mesh has a normal layer
    bool m_hasMeshNormal;

    /// Defines if the associated mesh has a a per vertex color layer
    bool m_hasVertexColor;

    /// Defines if the associated mesh has a a per primitive color layer
    bool m_hasPrimitiveColor;

    /// Primitive type of the associated mesh
    ::fwData::Mesh::CellTypesEnum m_primitiveType;

    /// Name of the texture used to store per-primitive color
    std::string m_perPrimitiveColorTextureName;

    /// Bounding box of the mesh
    ::Ogre::AxisAlignedBox m_meshBoundingBox;

    /// Factor used to modify normals length or billboards size
    float m_sceneSizeFactor { 1.f };

    /// Name of the material template
    std::string m_templateName;
};

//------------------------------------------------------------------------------

inline void Material::setHasMeshNormal(bool _hasMeshNormal)
{
    m_hasMeshNormal = _hasMeshNormal;
}

//------------------------------------------------------------------------------

inline void Material::setHasVertexColor(bool _hasVertexColor)
{
    m_hasVertexColor = _hasVertexColor;
}

//------------------------------------------------------------------------------

inline void Material::setHasPrimitiveColor(bool _hasPrimitiveColor, const std::string& _textureName)
{
    m_hasPrimitiveColor            = _hasPrimitiveColor;
    m_perPrimitiveColorTextureName = _textureName;
}

//------------------------------------------------------------------------------

inline void Material::setPrimitiveType(::fwData::Mesh::CellTypesEnum _type)
{
    m_primitiveType = _type;
}

//------------------------------------------------------------------------------

inline void Material::setMeshBoundingBox(const Ogre::AxisAlignedBox& _bbox)
{
    m_meshBoundingBox = _bbox;
}
//-----------------------------------------------------------------------------

inline void Material::setSceneSizeFactor(float sceneSizeFactor)
{
    m_sceneSizeFactor = sceneSizeFactor;
}

//------------------------------------------------------------------------------

} // namespace fwRenderOgre

#endif // __FWRENDEROGRE_MATERIAL_HPP__
