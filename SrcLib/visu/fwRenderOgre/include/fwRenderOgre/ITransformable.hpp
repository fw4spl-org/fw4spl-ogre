/* ***** BEGIN LICENSE BLOCK *****
 * FW4SPL - Copyright (C) IRCAD, 2014-2018.
 * Distributed under the terms of the GNU Lesser General Public License (LGPL) as
 * published by the Free Software Foundation.
 * ****** END LICENSE BLOCK ****** */

#pragma once

#include "fwRenderOgre/config.hpp"
#include "fwRenderOgre/IAdaptor.hpp"
#include "fwRenderOgre/SRender.hpp"

#include <OgreMatrix4.h>

namespace fwRenderOgre
{

/**
 * @brief Must be inherited by all classes containing a transformation matrix
 */
class FWRENDEROGRE_CLASS_API ITransformable
{
public:
    /**
     * @brief Get the Ogre identifier of the transform in the scene manager.
     * @return This transform service Id
     */
    FWRENDEROGRE_API ::fwRenderOgre::SRender::OgreObjectIdType getTransformId() const;

    /**
     * @brief Set the Ogre identifier of the transform in the scene manager.
     * @param newId The new transform service Id
     */
    FWRENDEROGRE_API void setTransformId(::fwRenderOgre::SRender::OgreObjectIdType newId);

    /**
     * @brief getParentTransformUID
     * @return This parent transform service UID
     */
    FWRENDEROGRE_API ::fwRenderOgre::SRender::OgreObjectIdType getParentTransformId() const;

    /**
     * @brief setParentTransformId
     * @param newId This new parent transform service UID
     */
    FWRENDEROGRE_API void setParentTransformId(::fwRenderOgre::SRender::OgreObjectIdType newId);

    FWRENDEROGRE_API static const std::string s_CONFIG_TRANSFORM;

protected:
    /// Ogre transformation of this service
    ::Ogre::Affine3 m_ogreTransform;
    /// Attached transform service
    ::fwRenderOgre::IAdaptor::wptr m_transformService;

    /// This transform identifier
    ::fwRenderOgre::SRender::OgreObjectIdType m_transformId;
    /// This parent transform identifier
    ::fwRenderOgre::SRender::OgreObjectIdType m_parentTransformId;
};

} //namespace fwRenderOgre
