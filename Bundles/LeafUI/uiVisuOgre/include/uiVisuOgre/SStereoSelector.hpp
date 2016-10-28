/* ***** BEGIN LICENSE BLOCK *****
 * FW4SPL - Copyright (C) IRCAD, 2014-2016.
 * Distributed under the terms of the GNU Lesser General Public License (LGPL) as
 * published by the Free Software Foundation.
 * ****** END LICENSE BLOCK ****** */

#ifndef __UIVISUOGRE_SSTEREOSELECTOR_HPP__
#define __UIVISUOGRE_SSTEREOSELECTOR_HPP__

#include <gui/editor/IEditor.hpp>
#include <fwRenderOgre/Layer.hpp>
#include <fwRenderOgre/compositor/ChainManager.hpp>

#include <QObject>
#include <QPointer>
#include <QComboBox>

#include <vector>

#include "uiVisuOgre/config.hpp"

namespace uiVisuOgre
{

/**
 * @brief   Allows to select the stereo mode of an Ogre Compositor
 */
class UIVISUOGRE_CLASS_API SStereoSelector : public QObject,
                                             public ::gui::editor::IEditor
{
Q_OBJECT

public:

    fwCoreServiceClassDefinitionsMacro ( (SStereoSelector)(::gui::editor::IEditor) );


    /// Constructor.
    UIVISUOGRE_API SStereoSelector() throw();

    /// Destructor. Does nothing
    UIVISUOGRE_API virtual ~SStereoSelector() throw();

protected:

    /**
     * @brief method description:
     * @code{.xml}
        <service uid="SStereoSelectorInstance" impl="::uiVisuOgre::SStereoSelector" type="::gui::editor::IEditor">
             <parameter>param</parameter>
        </service>
       @endcode
     * - \b Parameter : parameter description.
     */
    UIVISUOGRE_API virtual void configuring()  throw ( ::fwTools::Failed );

    /// Sets the connections and the UI elements
    UIVISUOGRE_API virtual void starting()  throw ( ::fwTools::Failed );

    /// Destroys the connections and cleans the container
    UIVISUOGRE_API virtual void stopping()  throw ( ::fwTools::Failed );

    /// Does nothing
    UIVISUOGRE_API virtual void updating() throw ( ::fwTools::Failed );

private Q_SLOTS:

    /// Slot: called when a layer is selected
    /// Sets the current layer
    void onSelectedLayerItem(int index);

    /// Slot: called when a mode is selected
    void onSelectedModeItem(int index);

private:

    /// Retrieves all the layers from the application thanks to the render services
    void refreshRenderers();

    QPointer<QComboBox> m_layersBox;
    QPointer<QComboBox> m_modeBox;

    std::vector< ::fwRenderOgre::Layer::wptr > m_layers;
    ::fwRenderOgre::Layer::wptr m_currentLayer;
};

} // uiVisuOgre

#endif // __UIVISUOGRE_SSTEREOSELECTOR_HPP__