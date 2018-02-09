/* ***** BEGIN LICENSE BLOCK *****
 * FW4SPL - Copyright (C) IRCAD, 2018.
 * Distributed under the terms of the GNU Lesser General Public License (LGPL) as
 * published by the Free Software Foundation.
 * ****** END LICENSE BLOCK ****** */

#include "visuOgreAdaptor/SFrustum.hpp"

#include "visuOgreAdaptor/SCamera.hpp"
#include "visuOgreAdaptor/SMaterial.hpp"

#include <arData/Camera.hpp>

#include <fwCom/Slots.hxx>

#include <fwData/Material.hpp>

#include <fwRenderOgre/helper/Scene.hpp>

#include <OgreCamera.h>
#include <OgreEntity.h>
#include <OgreMaterial.h>
#include <OgreMeshManager.h>

namespace visuOgreAdaptor
{

fwServicesRegisterMacro(::fwRenderOgre::IAdaptor, ::visuOgreAdaptor::SFrustum);

const ::fwCom::Slots::SlotKeyType SFrustum::s_UPDATE_VISIBILITY_SLOT = "updateVisibility";
const ::fwCom::Slots::SlotKeyType SFrustum::s_TOGGLE_VISIBILITY_SLOT = "toggleVisibility";

const std::string SFrustum::s_CAMERA_INPUT = "camera";
const std::string SFrustum::s_NEAR_CONFIG  = "near";
const std::string SFrustum::s_FAR_CONFIG   = "far";
const std::string SFrustum::s_COLOR_CONFIG = "color";

//-----------------------------------------------------------------------------

SFrustum::SFrustum() noexcept :
    m_ogreCamera(nullptr),
    m_visibility(true),
    m_near(0.f),
    m_far(0.f)
{
    newSlot(s_UPDATE_VISIBILITY_SLOT, &SFrustum::updateVisibility, this);
    newSlot(s_TOGGLE_VISIBILITY_SLOT, &SFrustum::toggleVisibility, this);
}

//-----------------------------------------------------------------------------

SFrustum::~SFrustum() noexcept
{
}

//------------------------------------------------------------------------------

void SFrustum::configuring()
{
    this->configureParams();

    const ConfigType config = this->getConfigTree().get_child("config.<xmlattr>");

    this->setTransformId(config.get<std::string>( ::fwRenderOgre::ITransformable::s_CONFIG_TRANSFORM,
                                                  this->getID() + "_transform"));

    m_near  = config.get<float>(s_NEAR_CONFIG, 0.f);
    m_far   = config.get<float>(s_FAR_CONFIG, 0.f);
    m_color = config.get< std::string >(s_COLOR_CONFIG, "#ff0000ff");
}

//-----------------------------------------------------------------------------

void SFrustum::starting()
{
    this->initialize();

    // Create material
    m_material = ::fwData::Material::New();
    m_material->diffuse()->setRGBA(m_color);

    ::visuOgreAdaptor::SMaterial::sptr materialAdaptor = this->registerService< ::visuOgreAdaptor::SMaterial >(
        "::visuOgreAdaptor::SMaterial");
    materialAdaptor->registerInOut(m_material, ::visuOgreAdaptor::SMaterial::s_MATERIAL_INOUT, true);
    materialAdaptor->setID(this->getID() + materialAdaptor->getID());
    materialAdaptor->setMaterialName(this->getID() + materialAdaptor->getID());
    materialAdaptor->setRenderService( this->getRenderService() );
    materialAdaptor->setLayerID(this->m_layerID);
    materialAdaptor->setShadingMode("ambient");
    materialAdaptor->setMaterialTemplateName(::fwRenderOgre::Material::DEFAULT_MATERIAL_TEMPLATE_NAME);
    materialAdaptor->start();
    materialAdaptor->update();

    // Create camera
    m_ogreCamera = this->getSceneManager()->createCamera(::Ogre::String(this->getID() + s_CAMERA_INPUT));
    m_ogreCamera->setPosition(::Ogre::Vector3(0, 0, 0));
    m_ogreCamera->setMaterial(materialAdaptor->getMaterial());
    m_ogreCamera->setDirection(::Ogre::Vector3(::Ogre::Real(0), ::Ogre::Real(0), ::Ogre::Real(1)));
    m_ogreCamera->setDebugDisplayEnabled(true);

    // Clipping
    if(m_near != 0.f)
    {
        m_ogreCamera->setNearClipDistance(m_near);
    }
    if(m_far != 0.f)
    {
        m_ogreCamera->setFarClipDistance(m_far);
    }

    // Set data to camera
    this->setOgreCamFromData();

    // Add camera to ogre scene
    ::Ogre::SceneNode* rootSceneNode = this->getSceneManager()->getRootSceneNode();
    ::Ogre::SceneNode* transNode     =
        ::fwRenderOgre::helper::Scene::getNodeById(this->getTransformId(), rootSceneNode);
    if (transNode == nullptr)
    {
        transNode = rootSceneNode->createChildSceneNode(this->getTransformId());
    }
    transNode->attachObject(m_ogreCamera);

    this->requestRender();
}

//-----------------------------------------------------------------------------

void SFrustum::updating()
{
    this->setOgreCamFromData();
    this->requestRender();
}

//-----------------------------------------------------------------------------

void SFrustum::stopping()
{
    this->unregisterServices();
    m_material = nullptr;
}

//-----------------------------------------------------------------------------

void SFrustum::setOgreCamFromData()
{
    const std::shared_ptr< const ::arData::Camera > camera = this->getInput< ::arData::Camera >(s_CAMERA_INPUT);
    if(camera != nullptr)
    {
        const double h    = static_cast<double>(camera->getHeight());
        const double fy   = static_cast<double>(camera->getFy());
        const double fovY = 2. * std::atan( h / (2. * fy));

        m_ogreCamera->setFOVy(::Ogre::Radian( ::Ogre::Real(fovY)));
        m_ogreCamera->setAspectRatio(::Ogre::Real(camera->getWidth()/camera->getHeight()));
        m_ogreCamera->setVisible(m_visibility);
    }
    else
    {
        SLM_WARN("the input '" + s_CAMERA_INPUT + "' is not set");
    }
}

//-----------------------------------------------------------------------------

void SFrustum::updateVisibility(bool isVisible)
{
    m_visibility = isVisible;
    this->updating();
}

//-----------------------------------------------------------------------------

void SFrustum::toggleVisibility()
{
    m_visibility = !m_visibility;
    this->updating();
}

//-----------------------------------------------------------------------------

} //visuOgreAdaptor