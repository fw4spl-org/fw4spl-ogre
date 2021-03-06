/* ***** BEGIN LICENSE BLOCK *****
 * FW4SPL - Copyright (C) IRCAD, 2014-2018.
 * Distributed under the terms of the GNU Lesser General Public License (LGPL) as
 * published by the Free Software Foundation.
 * ****** END LICENSE BLOCK ****** */

#pragma once

#include "fwRenderOgre/config.hpp"

#include <fwData/Color.hpp>
#include <fwData/Image.hpp>
#include <fwData/TransformationMatrix3D.hpp>

#include <OGRE/OgreColourValue.h>
#include <OGRE/OgreImage.h>
#include <OGRE/OgrePixelFormat.h>
#include <OGRE/OgreRoot.h>
#include <OGRE/OgreTexture.h>
#include <OGRE/Overlay/OgreOverlaySystem.h>

#include <string>

fwCorePredeclare((fwRenderOgre)(factory)(R2VBRenderable))

namespace fwRenderOgre
{
namespace factory
{
class R2VBRenderable;
class Text;
}
namespace vr
{
class GridProxyGeometryFactory;
}
namespace compositor
{
class MaterialMgrListener;
}
}

namespace fwRenderOgre
{
/**
 * @brief Provide some Ogre general functions for FW4SPL
 */
class FWRENDEROGRE_CLASS_API Utils
{
public:

    /**
     * @brief Utils::addRessourcesPath
     *        Add a path to load Ogre ressources from a specific path.
     *        You must edit the ressource.cfg file for each Bundle containing specific resources
     *        In this case, you can call this method in the Plugin.cpp file of this Bundle
     * @param path Relative path to the ressource.cfg file from a specific Bundle
     */
    FWRENDEROGRE_API static void addResourcesPath(const ::boost::filesystem::path& path);

    /**
     * @brief getOgreRoot
     * @return OgreRoot, if it doesn't exist initialise Ogre Root and default Ogre behavior
     */
    FWRENDEROGRE_API static ::Ogre::Root* getOgreRoot();

    /**
     * @brief destroy the OgreRoot
     */
    FWRENDEROGRE_API static void destroyOgreRoot();

    /**
     * @brief Convert an fw4spl image data into an ogre image
     * @param imageFw The FW4SPL Image to convert
     * @return Ogre image
     */
    FWRENDEROGRE_API static ::Ogre::Image convertToOgreImage( const ::fwData::Image::csptr imageFw);

    /**
     * @brief Convert an Ogre texture into a fw4spl image data
     */
    FWRENDEROGRE_API static void convertFromOgreTexture( ::Ogre::TexturePtr _texture,
                                                         const ::fwData::Image::sptr _imageFw,
                                                         bool flip = false);

    /**
     * @brief getPixelFormatOgre
     * @param imageFw The FW4SPL Image
     * @return Pixel format of a fwData::Image
     */
    FWRENDEROGRE_API static ::Ogre::PixelFormat getPixelFormatOgre( ::fwData::Image::csptr imageFw );

    /**
     * @brief set the pixel format of an image from an Ogre pixel format
     * @param _image The FW4SPL Image
     * @param _format Pixel format of Ogre
     */
    FWRENDEROGRE_API static void setPixelFormatFromOgre( ::fwData::Image::sptr _image, ::Ogre::PixelFormat _format );

    /**
     * @brief loadOgreTexture
     * @param _image The FW4SPL Image to convert
     * @param _texture The target texture
     * @param _texType Type of the texture (::Ogre::TEX_TYPE_2D, ::Ogre::TEX_TYPE_3D, ...)
     * @param _dynamic
     */
    FWRENDEROGRE_API static void loadOgreTexture(const fwData::Image::csptr& _image, ::Ogre::TexturePtr _texture,
                                                 ::Ogre::TextureType _texType, bool _dynamic);

    /**
     * @brief convertImageForNegato
     * @param[out] _textureThe target texture
     * @param[in] _image The FW4SPL Image to convert
     * @return
     */
    FWRENDEROGRE_API static void convertImageForNegato(::Ogre::Texture* _texture, const ::fwData::Image::sptr& _image );

    /**
     * @brief allocateTexture
     *
     * @param[out] _texture The target texture
     * @param[in] _width width of the texture
     * @param[in] _height height of the texture
     * @param[in] _depth depth of the texture
     * @param[in] _format pixel format
     * @param[in] _texType texture type (::OGRE::TEX_TYPE_2D, TEX_TYPE_3D, ...)
     * @param[in] _dynamic true if the image has to be modified frequently
     * @return
     */
    FWRENDEROGRE_API static void allocateTexture(::Ogre::Texture* _texture, size_t _width, size_t _height,
                                                 size_t _depth, ::Ogre::PixelFormat _format,
                                                 ::Ogre::TextureType _texType, bool _dynamic);

    FWRENDEROGRE_API static ::Ogre::OverlaySystem* getOverlaySystem();

    /**
     * @brief convertOgreColorToFwColor
     * @param[in] _ogreColor Color to convert into a f4s color
     * @return The converted f4s color
     */
    FWRENDEROGRE_API static ::fwData::Color::sptr convertOgreColorToFwColor(const Ogre::ColourValue& _ogreColor);

    /// Creates an ogre matrix from a f4s matrix.
    FWRENDEROGRE_API static ::Ogre::Matrix4 convertTM3DToOgreMx(const ::fwData::TransformationMatrix3D::csptr& _tm3d);

    /// Copies an ogre matrix to a f4s matrix.
    FWRENDEROGRE_API static void copyOgreMxToTM3D(const ::Ogre::Matrix4& _mx,
                                                  const ::fwData::TransformationMatrix3D::sptr& _tm3d);

private:

    /// Parses all resources.cfg files and adds resource locations to the resource group manager.
    static void loadResources();

    /**
     * @brief Copies an ogre config stream and turns paths absolute.
     *
     * @param[in] key Path parameter name whose value needs to be absolute.
     * @param[in] input Input stream, must be from an ogre configuration file.
     * @param[out] output Output stream, where the new config is copied to.
     * @return whether or not the key was found in the input.
     */
    static bool makePathsAbsolute(const std::string& key, std::istream& input, std::ostream& output);

    static ::Ogre::OverlaySystem* s_overlaySystem;

    static ::fwRenderOgre::factory::R2VBRenderable* s_R2VBRenderableFactory;
    static ::fwRenderOgre::factory::Text* s_textFactory;
    static ::fwRenderOgre::vr::GridProxyGeometryFactory* s_gridProxyGeometryFactory;
    static ::fwRenderOgre::compositor::MaterialMgrListener* s_oitMaterialListener;
};

} // namespace fwRenderOgre
