#include "soapH.h"
#include "sdk.h" 
#include "soapStub.h"
#include "stdsoap2.h"
#include "stools.h"
#include "service_context.h"

SIYI_SDK camera("192.168.2.25", 37260);  


SOAP_FMAC5 int SOAP_FMAC6 __tptz__GetServiceCapabilities(struct soap *soap,
    struct _tptz__GetServiceCapabilities *req,
    struct _tptz__GetServiceCapabilitiesResponse &_tptz__GetServiceCapabilitiesResponse)
{
    _tptz__GetServiceCapabilitiesResponse.Capabilities = soap_new_tptz__Capabilities(soap,-1);
    _tptz__GetServiceCapabilitiesResponse.Capabilities->EFlip = soap_new_bool(soap,-1);
    *(_tptz__GetServiceCapabilitiesResponse.Capabilities->EFlip) = true;
    _tptz__GetServiceCapabilitiesResponse.Capabilities->Reverse = soap_new_bool(soap,-1);
    *(_tptz__GetServiceCapabilitiesResponse.Capabilities->Reverse) = true;
    _tptz__GetServiceCapabilitiesResponse.Capabilities->GetCompatibleConfigurations = soap_new_bool(soap,-1);
    *(_tptz__GetServiceCapabilitiesResponse.Capabilities->GetCompatibleConfigurations) = true;
    std::cout << "Function name: " << __func__ << std::endl;
    return SOAP_OK;
}


SOAP_FMAC5 int SOAP_FMAC6 __tptz__GetNodes(struct soap *soap,

    struct _tptz__GetNodes *_tptz__GetNodes,

    struct _tptz__GetNodesResponse &_tptz__GetNodesResponse)

{

    auto *ptzNode = soap_new_tt__PTZNode(soap, -1);

    ptzNode->Name = soap_new_std__string(soap, -1);

    if (ptzNode->Name) {  

        *(ptzNode->Name) = "PTZNode_Channel1";

    }
 
    ptzNode->token = "PTZNode1";  // Use a valid token
 
    ptzNode->HomeSupported = true;

    ptzNode->MaximumNumberOfPresets = 300;
 
    ptzNode->AuxiliaryCommands.push_back("IRLampOn");

    ptzNode->AuxiliaryCommands.push_back("IRLampOff");
 
    // Allocate PTZ spaces

    auto *space = soap_new_tt__PTZSpaces(soap, -1);

    // Pan-Tilt Absolute Space

    auto *panTiltSpace = soap_new_tt__Space2DDescription(soap, -1);

    panTiltSpace->URI = soap_strdup(soap, "http://www.onvif.org/ver20/tptz/PanTiltSpaces/PositionGenericSpace");

    panTiltSpace->XRange = soap_new_tt__FloatRange(soap, -1);

    panTiltSpace->XRange->Min = -1.0;

    panTiltSpace->XRange->Max = 1.0;

    panTiltSpace->YRange = soap_new_tt__FloatRange(soap, -1);

    panTiltSpace->YRange->Min = -1.0;

    panTiltSpace->YRange->Max = 1.0;

    space->AbsolutePanTiltPositionSpace.push_back(panTiltSpace);
 
    // Zoom Absolute Space

    auto *zoomSpace = soap_new_tt__Space1DDescription(soap, -1);

    zoomSpace->URI = soap_strdup(soap, "http://www.onvif.org/ver20/tptz/ZoomSpaces/PositionGenericSpace");

    zoomSpace->XRange = soap_new_tt__FloatRange(soap, -1);

    zoomSpace->XRange->Min = 0.0;

    zoomSpace->XRange->Max = 10.0;

    space->AbsoluteZoomPositionSpace.push_back(zoomSpace);
 
    // Assign spaces to PTZ node

    ptzNode->SupportedPTZSpaces = space;
 
    // Add to response

    _tptz__GetNodesResponse.PTZNode.push_back(ptzNode);
 
    return SOAP_OK;

}

 


SOAP_FMAC5 int  __tptz__GetNode(struct soap *soap,
    struct _tptz__GetNode *_tptz__GetNode,
    struct _tptz__GetNodeResponse &_tptz__GetNodeResponse)
{
    std::cout << "Function name: " << __func__ << std::endl;
    tt__PTZNode *ptzNode = soap_new_tt__PTZNode(soap, -1);
    
    ptzNode->Name = soap_new_std__string(soap, -1);
    if (ptzNode->Name) { 
        *(ptzNode->Name) = "PTZNode_Channel1";  
    }

 
    ptzNode->token = soap_strdup(soap, "00000");   
    ptzNode->HomeSupported = true;
    ptzNode->MaximumNumberOfPresets = 300;

    ptzNode->AuxiliaryCommands.push_back("IRLampOn");
    ptzNode->AuxiliaryCommands.push_back("IRLampOff");

    tt__PTZSpaces *space = soap_new_tt__PTZSpaces(soap, -1);

    tt__Space2DDescription *panTiltSpace = soap_new_tt__Space2DDescription(soap, -1);
    panTiltSpace->URI = soap_strdup(soap, "http://www.onvif.org/ver20/tptz/PanTiltSpaces/PositionGenericSpace");
    space->AbsolutePanTiltPositionSpace.push_back(panTiltSpace);

    tt__Space1DDescription *zoomSpace = soap_new_tt__Space1DDescription(soap, -1);
    zoomSpace->URI = soap_strdup(soap, "http://www.onvif.org/ver20/tptz/ZoomSpaces/PositionGenericSpace");
    space->AbsoluteZoomPositionSpace.push_back(zoomSpace);

    ptzNode->SupportedPTZSpaces = space;

    _tptz__GetNodeResponse.PTZNode = ptzNode;

    return SOAP_OK;
}

SOAP_FMAC5 int __tptz__GetConfigurations(
    struct soap *soap, 
    struct _tptz__GetConfigurations *_tptz__GetConfigurations,
    struct _tptz__GetConfigurationsResponse &tptz__GetConfigurationsResponse) 
{
    auto *config = soap_new_tt__PTZConfiguration(soap, -1);
    
config->Name = "PTZConfig_Channel1";
config->token = "00000";
config->UseCount = 3;


    // ✅ Pan-Tilt Limits
    config->PanTiltLimits = soap_new_tt__PanTiltLimits(soap, -1);
    config->PanTiltLimits->Range = soap_new_tt__Space2DDescription(soap, -1);
    config->PanTiltLimits->Range->XRange = soap_new_tt__FloatRange(soap, -1);
    config->PanTiltLimits->Range->XRange->Min = -1;
    config->PanTiltLimits->Range->XRange->Max = 1;
    config->PanTiltLimits->Range->YRange = soap_new_tt__FloatRange(soap, -1);
    config->PanTiltLimits->Range->YRange->Min = -1;
    config->PanTiltLimits->Range->YRange->Max = 1;

    // ✅ Zoom Limits
    config->ZoomLimits = soap_new_tt__ZoomLimits(soap, -1);
    config->ZoomLimits->Range = soap_new_tt__Space1DDescription(soap, -1);
    config->ZoomLimits->Range->XRange = soap_new_tt__FloatRange(soap, -1);
    config->ZoomLimits->Range->XRange->Min = 0;
    config->ZoomLimits->Range->XRange->Max = 1;

    // ✅ Default PTZ Speed
    config->DefaultPTZSpeed = soap_new_tt__PTZSpeed(soap, -1);
    config->DefaultPTZSpeed->PanTilt = soap_new_tt__Vector2D(soap, -1);
    config->DefaultPTZSpeed->PanTilt->x = 0.8;
    config->DefaultPTZSpeed->PanTilt->y = 0.8;
    config->DefaultPTZSpeed->Zoom = soap_new_tt__Vector1D(soap, -1);
    config->DefaultPTZSpeed->Zoom->x = 0.8;

    
    config->DefaultPTZTimeout = soap_new_xsd__duration(soap, -1);
    *(config->DefaultPTZTimeout) = "PT10S";

    
    config->DefaultAbsolutePantTiltPositionSpace = soap_new_std__string(soap, -1);
    *(config->DefaultAbsolutePantTiltPositionSpace) = "http://www.onvif.org/ver10/tptz/PanTiltSpaces/PositionGenericSpace";

    config->DefaultAbsoluteZoomPositionSpace = soap_new_std__string(soap, -1);
    *(config->DefaultAbsoluteZoomPositionSpace) = "http://www.onvif.org/ver10/tptz/ZoomSpaces/PositionGenericSpace";

    config->DefaultContinuousPanTiltVelocitySpace = soap_new_std__string(soap, -1);
    *(config->DefaultContinuousPanTiltVelocitySpace) = "http://www.onvif.org/ver10/tptz/PanTiltSpaces/VelocityGenericSpace";

    config->DefaultContinuousZoomVelocitySpace = soap_new_std__string(soap, -1);
    *(config->DefaultContinuousZoomVelocitySpace) = "http://www.onvif.org/ver10/tptz/ZoomSpaces/VelocityGenericSpace";

    config->DefaultRelativePanTiltTranslationSpace = soap_new_std__string(soap, -1);
    *(config->DefaultRelativePanTiltTranslationSpace) = "http://www.onvif.org/ver10/tptz/PanTiltSpaces/TranslationGenericSpace";

    config->DefaultRelativeZoomTranslationSpace = soap_new_std__string(soap, -1);
    *(config->DefaultRelativeZoomTranslationSpace) = "http://www.onvif.org/ver10/tptz/ZoomSpaces/TranslationGenericSpace";

    // Add PTZ Configuration to the Response
    tptz__GetConfigurationsResponse.PTZConfiguration.push_back(config);
    return SOAP_OK;
}

SOAP_FMAC5 int  __tptz__GetConfiguration(struct soap *soap,
    struct  _tptz__GetConfiguration *tptz__GetConfiguration,
    struct _tptz__GetConfigurationResponse &tptz__GetConfigurationResponse)
{
    auto *config = soap_new_tt__PTZConfiguration(soap, -1);
    config->Name = "PTZConfig_Channel1";
config->token = "00000";
config->UseCount = 3;


    config->PanTiltLimits = soap_new_tt__PanTiltLimits(soap, -1);
    config->PanTiltLimits->Range = soap_new_tt__Space2DDescription(soap, -1);
    config->PanTiltLimits->Range->XRange = soap_new_tt__FloatRange(soap, -1);
    config->PanTiltLimits->Range->XRange->Min = -1;
    config->PanTiltLimits->Range->XRange->Max = 1;
    config->PanTiltLimits->Range->YRange = soap_new_tt__FloatRange(soap, -1);
    config->PanTiltLimits->Range->YRange->Min = -1;
    config->PanTiltLimits->Range->YRange->Max = 1;

    config->ZoomLimits = soap_new_tt__ZoomLimits(soap, -1);
    config->ZoomLimits->Range = soap_new_tt__Space1DDescription(soap, -1);
    config->ZoomLimits->Range->XRange = soap_new_tt__FloatRange(soap, -1);
    config->ZoomLimits->Range->XRange->Min = 0;
    config->ZoomLimits->Range->XRange->Max = 1;

    config->DefaultPTZSpeed = soap_new_tt__PTZSpeed(soap, -1);
    config->DefaultPTZSpeed->PanTilt = soap_new_tt__Vector2D(soap, -1);
    config->DefaultPTZSpeed->PanTilt->x = 0.8;
    config->DefaultPTZSpeed->PanTilt->y = 0.8;
    config->DefaultPTZSpeed->Zoom = soap_new_tt__Vector1D(soap, -1);
    config->DefaultPTZSpeed->Zoom->x = 0.8;

    
    config->DefaultPTZTimeout = soap_new_xsd__duration(soap, -1);
    *(config->DefaultPTZTimeout) = "PT10S"; 

    
    config->DefaultAbsolutePantTiltPositionSpace = soap_new_std__string(soap, -1);
    *(config->DefaultAbsolutePantTiltPositionSpace) = "http://www.onvif.org/ver20/tptz/PanTiltSpaces/PositionGenericSpace";

    config->DefaultAbsoluteZoomPositionSpace = soap_new_std__string(soap, -1);
    *(config->DefaultAbsoluteZoomPositionSpace) = "http://www.onvif.org/ver20/tptz/ZoomSpaces/PositionGenericSpace";

    config->DefaultContinuousPanTiltVelocitySpace = soap_new_std__string(soap, -1);
    *(config->DefaultContinuousPanTiltVelocitySpace) = "http://www.onvif.org/ver20/tptz/PanTiltSpaces/VelocityGenericSpace";

    config->DefaultContinuousZoomVelocitySpace = soap_new_std__string(soap, -1);
    *(config->DefaultContinuousZoomVelocitySpace) = "http://www.onvif.org/ver20/tptz/ZoomSpaces/VelocityGenericSpace";

    config->DefaultRelativePanTiltTranslationSpace = soap_new_std__string(soap, -1);
    *(config->DefaultRelativePanTiltTranslationSpace) = "http://www.onvif.org/ver20/tptz/PanTiltSpaces/TranslationGenericSpace";

    config->DefaultRelativeZoomTranslationSpace = soap_new_std__string(soap, -1);
    *(config->DefaultRelativeZoomTranslationSpace) = "http://www.onvif.org/ver20/tptz/ZoomSpaces/TranslationGenericSpace";

    tptz__GetConfigurationResponse.PTZConfiguration=config;

    return SOAP_OK;
}

SOAP_FMAC5 int  __tptz__SetConfiguration(struct soap *soap,
    struct  _tptz__SetConfiguration *req,
    struct _tptz__SetConfigurationResponse &_tptz__SetConfigurationResponse)
{
    std::cout << "Function name: " << __func__ << std::endl;
    if (!req) {
        std::cerr << "Request object is null!" << std::endl;
        return soap_sender_fault(soap, "Invalid Request", "Request object is null");
    }

    // Validate PTZConfiguration
    if (!req->PTZConfiguration) {
        std::cerr << "PTZConfiguration is null!" << std::endl;
        return soap_sender_fault(soap, "Invalid Request", "PTZConfiguration is missing");
    }

    // ✅ Extract PTZ Configuration safely
    tt__PTZConfiguration *config = req->PTZConfiguration;
    if (!config) {
        std::cerr << "PTZ Configuration is null!" << std::endl;
        return soap_sender_fault(soap, "Invalid Configuration", "PTZ Configuration is missing");
    }

    // ✅ Corrected: Treat Name as a normal std::string, not a pointer
    if (!config->Name.empty()) {
        std::cout << "Setting PTZ Configuration Name: " << config->Name << std::endl;
    } else {
        std::cerr << "Configuration Name is empty!" << std::endl;
    }

    std::cout << "Token: " << config->token << std::endl;

    // ✅ Check Default PTZ Speed
    if (config->DefaultPTZSpeed) {
        if (config->DefaultPTZSpeed->PanTilt) {
            std::cout << "Default PanTilt Speed: X=" << config->DefaultPTZSpeed->PanTilt->x
                      << ", Y=" << config->DefaultPTZSpeed->PanTilt->y << std::endl;
        } else {
            std::cerr << "Default PanTilt Speed is null!" << std::endl;
        }

        if (config->DefaultPTZSpeed->Zoom) {
            std::cout << "Default Zoom Speed: " << config->DefaultPTZSpeed->Zoom->x << std::endl;
        } else {
            std::cerr << "Default Zoom Speed is null!" << std::endl;
        }
    } else {
        std::cerr << "Default PTZ Speed is null!" << std::endl;
    }

    return SOAP_OK;
}

SOAP_FMAC5 int  __tptz__GetConfigurationOptions(struct soap *soap,
    struct _tptz__GetConfigurationOptions *req,
    struct _tptz__GetConfigurationOptionsResponse &res)
{
    std::cout << "Function name: " << __func__ << std::endl;
    return SOAP_OK;
}

SOAP_FMAC5 int  __tptz__SendAuxiliaryCommand(struct soap *soap,
    struct _tptz__SendAuxiliaryCommand *req,
    struct _tptz__SendAuxiliaryCommandResponse &res)
{
    std::cout << "Function name: " << __func__ << std::endl;
    return SOAP_OK;
}

SOAP_FMAC5 int  __tptz__GetPresets(struct soap *soap,
    struct _tptz__GetPresets *req,
    struct _tptz__GetPresetsResponse &res)
{
    std::cout << "Function name: " << __func__ << std::endl;
    return SOAP_OK;
}


SOAP_FMAC5 int __tptz__SetPreset(struct soap *soap,
    struct _tptz__SetPreset *req,
    struct _tptz__SetPresetResponse &res)
{
    std::cout << "Function name: " << __func__ << std::endl;

    // Generate a preset token (Here, using a fixed token for example)
    std::string presetToken = req->PresetToken ? *req->PresetToken : "Preset1";
    res.PresetToken = soap_strdup(soap, presetToken.c_str());

    std::cout << "Preset set: " << presetToken << std::endl;

    return SOAP_OK;
}


SOAP_FMAC5 int  __tptz__RemovePreset(struct soap *soap,
    struct _tptz__RemovePreset *req,
    struct _tptz__RemovePresetResponse &res)
{
    std::cout << "Function name: " << __func__ << std::endl;
    return SOAP_OK;
}

SOAP_FMAC5 int  __tptz__GotoPreset(struct soap *soap,
    struct _tptz__GotoPreset *req,
    struct _tptz__GotoPresetResponse &res)
{
    if (!req->PresetToken.empty()) {
        std::cout << "Moving to Preset: " << req->PresetToken << std::endl;

        // Define preset positions manually (adjust values as per requirement)
        std::map<std::string, std::pair<float, float>> presetPositions = {
            {"preset1", {0.0, 0.0}},   // Example: center position
            {"preset2", {30.0, 10.0}}, // Example: right and slightly up
            {"preset3", {-30.0, -10.0}} // Example: left and slightly down
        };

        auto it = presetPositions.find(req->PresetToken);
        if (it != presetPositions.end()) {
            float pan_angle = it->second.first;
            float tilt_angle = it->second.second;

            if (!camera.set_gimbal_angles(pan_angle, tilt_angle)) {
                std::cerr << "Failed to move to preset: " << req->PresetToken << std::endl;
                return SOAP_FAULT;
            }
        } else {
            std::cerr << "Invalid Preset Token: " << req->PresetToken << std::endl;
            return SOAP_FAULT;
        }
    } else {
        std::cerr << "Preset Token is empty!" << std::endl;
        return SOAP_FAULT;
    }
    return SOAP_OK;
}

SOAP_FMAC5 int  __tptz__ContinuousMove(struct soap *soap,
    struct _tptz__ContinuousMove *tptz__ContinuousMove,
    struct _tptz__ContinuousMoveResponse &response)
{
    std::cout << "Function name: " << __func__ << std::endl;


    if (tptz__ContinuousMove->Velocity && tptz__ContinuousMove->Velocity->PanTilt) {
        float pan_speed = tptz__ContinuousMove->Velocity->PanTilt->x;
        float tilt_speed = tptz__ContinuousMove->Velocity->PanTilt->y;

        std::cout << "Received PTZ move command - Pan: " << pan_speed << ", Tilt: " << tilt_speed << std::endl;

        // Call your SDK function to move the gimbal
        if (!camera.set_gimbal_speed(pan_speed * 10, tilt_speed * 10)) {
            std::cerr << "Failed to send PTZ move command!" << std::endl;
            return SOAP_FAULT;
        }
    }

    return SOAP_OK;
}

SOAP_FMAC5 int  __tptz__AbsoluteMove(struct soap *soap,
    struct _tptz__AbsoluteMove *req,
    struct _tptz__AbsoluteMoveResponse &res)
{
    std::cout << "Function name: " << __func__ << std::endl;
    if (req->Position && req->Position->PanTilt) {
        float pan = req->Position->PanTilt->x;
        float tilt = req->Position->PanTilt->y;
        float zoom = req->Position->Zoom ? req->Position->Zoom->x : 0.0f;

        std::cout << "Absolute Move - Pan: " << pan << ", Tilt: " << tilt << ", Zoom: " << zoom << std::endl;

        // Using set_gimbal_angle (Modify if needed)
        if (!camera.set_gimbal_angles(pan, tilt)) {
            std::cerr << "Failed to execute absolute move!" << std::endl;
            return SOAP_FAULT;
        }
        
    } else {
        std::cerr << "Invalid AbsoluteMove parameters!" << std::endl;
        return SOAP_FAULT;
    }
    return SOAP_OK;
}

SOAP_FMAC5 int  __tptz__RelativeMove(struct soap *soap,
    struct _tptz__RelativeMove *,
    struct _tptz__RelativeMoveResponse &res)
{
    std::cout << "Function name: " << __func__ << std::endl;
    return SOAP_OK;
}

SOAP_FMAC5 int   __tptz__GetPresetTours(struct soap *soap,
    struct _tptz__GetPresetTours *req,
    struct _tptz__GetPresetToursResponse &res)
{
    std::cout << "Function name: " << __func__ << std::endl;
    return SOAP_OK;
}

SOAP_FMAC5 int  __tptz__Stop(struct soap *soap,
    struct _tptz__Stop *req,
    struct _tptz__StopResponse &res)
{
    std::cout << "Function name: " << __func__ << std::endl;
    return SOAP_OK;
}

SOAP_FMAC5 int  __tptz__GeoMove(struct soap *soap,
    struct _tptz__GeoMove *req,
    struct _tptz__GeoMoveResponse &res)
{
    std::cout << "Function name: " << __func__ << std::endl;
     
    return SOAP_OK;
}

SOAP_FMAC5 int   __tptz__MoveAndStartTracking(
    struct soap *soap,
   struct  _tptz__MoveAndStartTracking *req,
   struct  _tptz__MoveAndStartTrackingResponse &res)
{
    return SOAP_OK;
}

SOAP_FMAC5 int SOAP_FMAC6 __tptz__GetStatus(struct soap *soap,
    struct _tptz__GetStatus *tptz__GetStatus,
    struct _tptz__GetStatusResponse &tptz__GetStatusResponse)
{
    auto *status = soap_new_tt__PTZStatus(soap, -1);
    status->Position = soap_new_tt__PTZVector(soap, -1);
    status->Position->PanTilt = soap_new_tt__Vector2D(soap, -1);
    status->Position->PanTilt->x = 0.0;  // Default position
    status->Position->PanTilt->y = 0.0;
    status->Position->Zoom = soap_new_tt__Vector1D(soap, -1);
    status->Position->Zoom->x = 1.0;  // Default zoom
 
    tptz__GetStatusResponse.PTZStatus = status;
 
    return SOAP_OK;
}

SOAP_FMAC5 int  __tptz__GotoHomePosition(struct soap *soap,
    struct _tptz__GotoHomePosition *_tptz__GotoHomePosition,
    struct _tptz__GotoHomePositionResponse &tptz__GotoHomePositionResponse)
{
    std::cout << "Function name: " << __func__ << std::endl;
    if (!camera.set_gimbal_angles(0, 0)) {
        std::cerr << "Failed to move gimbal to home position using set_gimbal_angles!" << std::endl;
        return SOAP_FAULT;
    }
    return SOAP_OK;
}

SOAP_FMAC5 int  __tptz__SetHomePosition(struct soap *soap,
    struct _tptz__SetHomePosition *_tptz__SetHomePosition,
    struct _tptz__SetHomePositionResponse &_tptz__SetHomePositionResponse)
{
    std::cout << "Function name: " << __func__ << std::endl;
    if (!camera.request_gimbal_center()) {
        std::cerr << "Failed to set home position!" << std::endl;
        return SOAP_FAULT;
    }
    return SOAP_OK;
}


SOAP_FMAC5 int __tptz__GetPresetTour(struct soap *soap,
    struct _tptz__GetPresetTour *_tptz__GetPresetTour,
    struct _tptz__GetPresetTourResponse &_tptz__GetPresetTourResponse)
{
    std::cout << "Function name: " << __func__ << std::endl;
    return SOAP_OK;
}

SOAP_FMAC5 int  __tptz__GetPresetTourOptions(struct soap *soap,
    struct _tptz__GetPresetTourOptions *_tptz__GetPresetTourOptions,
    struct _tptz__GetPresetTourOptionsResponse &_tptz__GetPresetTourOptionsResponse)
{
    std::cout << "Function name: " << __func__ << std::endl;
    return SOAP_OK;
}

SOAP_FMAC5 int  __tptz__CreatePresetTour(struct soap *soap,
    struct _tptz__CreatePresetTour *_tptz__CreatePresetTour,
    struct _tptz__CreatePresetTourResponse &_tptz__CreatePresetTourResponse)
{
    std::cout << "Function name: " << __func__ << std::endl;
    return SOAP_OK;
}

SOAP_FMAC5 int  __tptz__ModifyPresetTour(struct soap *soap,
    struct _tptz__ModifyPresetTour *_tptz__ModifyPresetTour,
    struct _tptz__ModifyPresetTourResponse &_tptz__ModifyPresetTourResponse)
{
    std::cout << "Function name: " << __func__ << std::endl;
    return SOAP_OK;
}

SOAP_FMAC5 int  __tptz__OperatePresetTour(struct soap *soap,
    struct _tptz__OperatePresetTour *_tptz__OperatePresetTour,
    struct _tptz__OperatePresetTourResponse &_tptz__OperatePresetTourResponse)
{
    std::cout << "Function name: " << __func__ << std::endl;
    return SOAP_OK;
}

SOAP_FMAC5 int __tptz__RemovePresetTour(struct soap *soap,
    struct _tptz__RemovePresetTour *_tptz__RemovePresetTour,
    struct _tptz__RemovePresetTourResponse &_tptz__RemovePresetTourResponse)
{
    std::cout << "Function name: " << __func__ << std::endl;
    return SOAP_OK;
}

SOAP_FMAC5 int  __tptz__GetCompatibleConfigurations(struct soap *soap,
    struct _tptz__GetCompatibleConfigurations *_tptz__GetCompatibleConfigurations,
    struct _tptz__GetCompatibleConfigurationsResponse &_tptz__GetCompatibleConfigurationsResponse)
{
    std::cout << "Function name: " << __func__ << std::endl;
    return SOAP_OK;
}

