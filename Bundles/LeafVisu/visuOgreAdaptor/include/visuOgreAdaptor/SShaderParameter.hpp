/* ***** BEGIN LICENSE BLOCK *****
 * FW4SPL - Copyright (C) IRCAD, 2014-2017.
 * Distributed under the terms of the GNU Lesser General Public License (LGPL) as
 * published by the Free Software Foundation.
 * ****** END LICENSE BLOCK ****** */

#ifndef __VISUOGREADAPTOR_SSHADERPARAMETER_HPP__
#define __VISUOGREADAPTOR_SSHADERPARAMETER_HPP__

#include "visuOgreAdaptor/config.hpp"
#include "visuOgreAdaptor/IParameter.hpp"

namespace visuOgreAdaptor
{

/**
 * @brief   Send a FW4SPL data as a shader parameter
 *
 *
 * Send parameters to vertex and fragment shaders
 *
 * @code{.xml}
        <service uid="paramAdaptor" class="::visuOgreAdaptor::SShaderParameter">
            <config materialAdaptor="mtlAdaptorUID" parameter="u_value" shaderType="fragment" />
        </service>
       @endcode
 *  - \b materialName (mandatory) : the name of the associated Ogre material
 *  - \b parameter (mandatory) : name of the shader parameter to set
 *  - \b technique (optional) : name of the technique, default to the first in the material
 *  - \b shaderType (optional) : the type of the shader (vertex, geometry, fragment). Default to vertex.
 */
class VISUOGREADAPTOR_CLASS_API SShaderParameter : public ::visuOgreAdaptor::IParameter
{

public:

    fwCoreServiceClassDefinitionsMacro( (SShaderParameter)(::visuOgreAdaptor::IParameter) );

    /// Constructor.
    VISUOGREADAPTOR_API SShaderParameter() noexcept;

    /// Destructor. Does nothing
    VISUOGREADAPTOR_API virtual ~SShaderParameter() noexcept;

    /// Set the value of the member m_materialName.
    VISUOGREADAPTOR_API void setMaterialName(const std::string& matName);

protected:

    /// Configure the adaptor
    VISUOGREADAPTOR_API virtual void configuring();
    /// Do nothing
    VISUOGREADAPTOR_API virtual void starting();
    /// Do nothing
    VISUOGREADAPTOR_API virtual void stopping();
    /// Do nothing
    VISUOGREADAPTOR_API virtual void swapping();

private:

    /// Material name
    std::string m_materialName;
};

} // visuOgreAdaptor

#endif // __VISUOGREADAPTOR_SSHADERPARAMETER_HPP__
