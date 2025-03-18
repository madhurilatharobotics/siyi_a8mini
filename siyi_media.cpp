#include "soapH.h"

int __trt__GetServiceCapabilities(struct soap *soap,
                                  struct _trt__GetServiceCapabilities *trt__GetServiceCapabilities,
                                  struct _trt__GetServiceCapabilitiesResponse &trt__GetServiceCapabilitiesResponse)
{
    std::cout << "Function name: " << __func__ << std::endl;
    return SOAP_OK;
}

int __trt__GetVideoSources(struct soap *soap,
                           struct _trt__GetVideoSources *trt__GetVideoSources,
                           struct _trt__GetVideoSourcesResponse &trt__GetVideoSourcesResponse)
{
    std::cout << "Function name: " << __func__ << std::endl;
    tt__VideoSource *videoSource = soap_new_tt__VideoSource(soap);
    videoSource->Framerate = 30;

    videoSource->Resolution = soap_new_tt__VideoResolution(soap);
    videoSource->Resolution->Height = 720;
    videoSource->Resolution->Width = 1280;

    videoSource->token = "00000";

    videoSource->Imaging = soap_new_tt__ImagingSettings(soap);

    videoSource->Imaging->Brightness = soap_new_float(soap);
    *videoSource->Imaging->Brightness = 128;

    videoSource->Imaging->ColorSaturation = soap_new_float(soap);
    *videoSource->Imaging->ColorSaturation = 128;

    videoSource->Imaging->Contrast = soap_new_float(soap);
    *videoSource->Imaging->Contrast = 128;

    // *videoSource->Imaging->IrCutFilter = tt__IrCutFilterMode__OFF;

    // videoSource->Imaging->Sharpness = soap_new_float(soap);
    // *videoSource->Imaging->Sharpness = 128;

    // videoSource->Imaging->BacklightCompensation = soap_new_tt__BacklightCompensation(soap);
    // if (videoSource->Imaging->BacklightCompensation) {
    //     videoSource->Imaging->BacklightCompensation->Mode = tt__BacklightCompensationMode__OFF;
    //     videoSource->Imaging->BacklightCompensation->Level = 20;
    // }

    // videoSource->Imaging->WideDynamicRange = soap_new_tt__WideDynamicRange(soap);
    // if (videoSource->Imaging->WideDynamicRange) {
    //     videoSource->Imaging->WideDynamicRange->Mode = tt__WideDynamicMode__OFF;
    //     videoSource->Imaging->WideDynamicRange->Level = 20;
    // }

    // videoSource->Imaging->WhiteBalance = soap_new_tt__WhiteBalance(soap);
    // if (videoSource->Imaging->WhiteBalance) {
    //     videoSource->Imaging->WhiteBalance->Mode = tt__WhiteBalanceMode__AUTO;
    // }

    // // Add the video source to the response
    trt__GetVideoSourcesResponse.VideoSources.push_back(videoSource);

    std::cout << "Function name: " << __func__ << std::endl;
    return SOAP_OK;
}

int __trt__GetAudioSources(struct soap *soap,
                           struct _trt__GetAudioSources *trt__GetAudioSources,
                           struct _trt__GetAudioSourcesResponse &trt__GetAudioSourcesResponse)
{
    std::cout << "Function name: " << __func__ << std::endl;
    return SOAP_OK;
}

int __trt__GetAudioOutputs(struct soap *soap,
                           struct _trt__GetAudioOutputs *trt__GetAudioOutputs,
                           struct _trt__GetAudioOutputsResponse &trt__GetAudioOutputsResponse)
{
    std::cout << "Function name: " << __func__ << std::endl;
    return SOAP_OK;
}

int __trt__CreateProfile(struct soap *soap,
                         struct _trt__CreateProfile *trt__CreateProfile,
                         struct _trt__CreateProfileResponse &trt__CreateProfileResponse)
{
    std::cout << "Function name: " << __func__ << std::endl;
    return SOAP_OK;
}

int __trt__GetProfile(
    struct soap *soap,
    struct _trt__GetProfile *trt__GetProfile,
    struct _trt__GetProfileResponse &trt__GetProfileResponse)
{
    std::cout << "GetProfile called with token: " << trt__GetProfile->ProfileToken << std::endl;

    // Validate the provided ProfileToken
    if (trt__GetProfile->ProfileToken != std::string("token_profile"))
    {
        std::cout << "Error: Profile token not found: " << trt__GetProfile->ProfileToken << std::endl;
        return soap_sender_fault(soap, "Profile Not Found", "The requested profile token does not exist.");
    }

    // Create and populate the Profile
    tt__Profile *profile = soap_new_tt__Profile(soap);
    if (!profile)
    {
        std::cout << "Error creating a new Profile" << std::endl;
        return soap_sender_fault(soap, "Memory Allocation Failed", "Could not allocate memory for Profile");
    }
    
    profile->Name = "my_profile";
    profile->token = "token_profile";

    // VideoSourceConfiguration
    profile->VideoSourceConfiguration = soap_new_tt__VideoSourceConfiguration(soap);
    if (!profile->VideoSourceConfiguration)
    {
        std::cout << "Error creating a new Profile" << std::endl;
        return soap_sender_fault(soap, "Memory Allocation Failed", "Could not allocate VideoSourceConfiguration");
    }
    profile->VideoSourceConfiguration->Name = "VS_Name";
    profile->VideoSourceConfiguration->token = "00000";
    profile->VideoSourceConfiguration->SourceToken = "00000";
    profile->VideoSourceConfiguration->UseCount = 1;

    profile->VideoSourceConfiguration->Bounds = soap_new_tt__IntRectangle(soap);
    if (profile->VideoSourceConfiguration->Bounds)
    {
        profile->VideoSourceConfiguration->Bounds->x = 0;
        profile->VideoSourceConfiguration->Bounds->y = 0;
        profile->VideoSourceConfiguration->Bounds->height = 720;
        profile->VideoSourceConfiguration->Bounds->width = 1280;
    }

    // VideoEncoderConfiguration
    profile->VideoEncoderConfiguration = soap_new_tt__VideoEncoderConfiguration(soap);
    if (!profile->VideoEncoderConfiguration)
    {
        std::cout << "Error creating a new Profile" << std::endl;
        return soap_sender_fault(soap, "Memory Allocation Failed", "Could not allocate VideoEncoderConfiguration");
    }
    profile->VideoEncoderConfiguration->Name = "VE_Name1";
    profile->VideoEncoderConfiguration->token = "00000";
    profile->VideoEncoderConfiguration->UseCount = 2;
    profile->VideoEncoderConfiguration->Quality = 10;
    profile->VideoEncoderConfiguration->Encoding = tt__VideoEncoding__H264;

    // profile->VideoEncoderConfiguration->H264 = soap_new_tt__H264Configuration(soap);
    // profile->VideoEncoderConfiguration->H264->GovLength = 60;
    // profile->VideoEncoderConfiguration->H264->H264Profile = tt__H264Profile__High;

    profile->VideoEncoderConfiguration->Resolution = soap_new_tt__VideoResolution(soap);
    if (profile->VideoEncoderConfiguration->Resolution)
    {
        profile->VideoEncoderConfiguration->Resolution->Height = 720;
        profile->VideoEncoderConfiguration->Resolution->Width = 1280;
    }

    profile->VideoEncoderConfiguration->RateControl = soap_new_tt__VideoRateControl(soap);
    if (profile->VideoEncoderConfiguration->RateControl)
    {
        profile->VideoEncoderConfiguration->RateControl->FrameRateLimit = 30;
        profile->VideoEncoderConfiguration->RateControl->EncodingInterval = 1;
        profile->VideoEncoderConfiguration->RateControl->BitrateLimit = 500;
    }

    profile->fixed = (bool *)soap_malloc(soap, sizeof(bool));
    *profile->fixed = true;
    //ptz 
    profile->PTZConfiguration = soap_new_tt__PTZConfiguration(soap);
    profile->PTZConfiguration->token     = "PTZConf1";
    profile->PTZConfiguration->NodeToken = "PTZNode1";
    profile->PTZConfiguration->Name      = "My PTZ Config";
    profile->PTZConfiguration->UseCount  = 1;

    // Add the profile to the response
    trt__GetProfileResponse.Profile = profile;

    // Add the profile to the response
    trt__GetProfileResponse.Profile = profile;

    // std::cout << "Profile returned successfully" << std::endl;
    std::cout << "Function name: " << __func__ << std::endl;
    return SOAP_OK;
}

int __trt__GetProfiles(struct soap *soap,
                       struct _trt__GetProfiles *trt__GetProfiles,
                       struct _trt__GetProfilesResponse &trt__GetProfilesResponse)
{
    tt__Profile *profile = soap_new_tt__Profile(soap);

    if (!profile)
    {
        std::cout << "Error creating a new Profile" << std::endl;
        return soap_sender_fault(soap, "Memory Allocation Failed", "Could not allocate memory for Profile");
    }

    profile->Name = "my_profile";
    profile->token = "token_profile";

    profile->VideoSourceConfiguration = (struct tt__VideoSourceConfiguration *)soap_malloc(soap, sizeof(struct tt__VideoSourceConfiguration));
    profile->VideoSourceConfiguration = soap_new_tt__VideoSourceConfiguration(soap);

    profile->VideoSourceConfiguration->Name = "VS_Name";
    profile->VideoSourceConfiguration->token = "00000";
    profile->VideoSourceConfiguration->SourceToken = "00000";
    profile->VideoSourceConfiguration->UseCount = 2;

    profile->VideoSourceConfiguration->Bounds = soap_new_tt__IntRectangle(soap);
    profile->VideoSourceConfiguration->Bounds->x = 0;
    profile->VideoSourceConfiguration->Bounds->y = 0;
    profile->VideoSourceConfiguration->Bounds->height = 720;
    profile->VideoSourceConfiguration->Bounds->width = 1280;

    // Allocate memory for VideoEncoderConfiguration
    profile->VideoEncoderConfiguration = soap_new_tt__VideoEncoderConfiguration(soap);
    profile->VideoEncoderConfiguration->Name = "VE_Name1";
    profile->VideoEncoderConfiguration->token = "00000";
    profile->VideoEncoderConfiguration->UseCount = 1;
    profile->VideoEncoderConfiguration->Quality = 10;
    profile->VideoEncoderConfiguration->Encoding = tt__VideoEncoding__H264; // H.264 encoding

    // Allocate memory for Resolution and set values
    profile->VideoEncoderConfiguration->Resolution = soap_new_tt__VideoResolution(soap);
    if (!profile->VideoEncoderConfiguration->Resolution)
    {
        return soap_sender_fault(soap, "Memory Allocation Failed", "Could not allocate Resolution");
    }
    profile->VideoEncoderConfiguration->Resolution->Height = 720;
    profile->VideoEncoderConfiguration->Resolution->Width = 1280;

    // Allocate memory for RateControl and set values
    profile->VideoEncoderConfiguration->RateControl = soap_new_tt__VideoRateControl(soap);
    if (!profile->VideoEncoderConfiguration->RateControl)
    {
        return soap_sender_fault(soap, "Memory Allocation Failed", "Could not allocate RateControl");
    }
    profile->VideoEncoderConfiguration->RateControl->FrameRateLimit = 30;
    profile->VideoEncoderConfiguration->RateControl->EncodingInterval = 1;
    profile->VideoEncoderConfiguration->RateControl->BitrateLimit = 500;

    profile->fixed = (bool *)soap_malloc(soap, sizeof(bool));
    *profile->fixed = true;
    //ptz
    profile->PTZConfiguration = soap_new_tt__PTZConfiguration(soap);
    profile->PTZConfiguration->token     = "PTZConf1";
    profile->PTZConfiguration->NodeToken = "PTZNode1";
    profile->PTZConfiguration->Name      = "My PTZ Config";
    profile->PTZConfiguration->UseCount  = 1;

    trt__GetProfilesResponse.Profiles.push_back(profile);

    std::cout << "Function name: " << __func__ << std::endl;
    return SOAP_OK;
}

int __trt__AddVideoEncoderConfiguration(struct soap *soap,
                                        struct _trt__AddVideoEncoderConfiguration *trt__AddVideoEncoderConfiguration,
                                        struct _trt__AddVideoEncoderConfigurationResponse &trt__AddVideoEncoderConfigurationResponse)
{
    std::cout << "Function name: " << __func__ << std::endl;
    return SOAP_OK;
}

int __trt__AddVideoSourceConfiguration(struct soap *soap,
                                       struct _trt__AddVideoSourceConfiguration *trt__AddVideoSourceConfiguration,
                                       struct _trt__AddVideoSourceConfigurationResponse &trt__AddVideoSourceConfigurationResponse)
{
    std::cout << "Function name: " << __func__ << std::endl;
    return SOAP_OK;
}

int __trt__AddAudioEncoderConfiguration(struct soap *soap,
                                        struct _trt__AddAudioEncoderConfiguration *trt__AddAudioEncoderConfiguration,
                                        struct _trt__AddAudioEncoderConfigurationResponse &trt__AddAudioEncoderConfigurationResponse)
{
    std::cout << "Function name: " << __func__ << std::endl;
    return SOAP_OK;
}

int __trt__AddAudioSourceConfiguration(struct soap *soap,
                                       struct _trt__AddAudioSourceConfiguration *trt__AddAudioSourceConfiguration,
                                       struct _trt__AddAudioSourceConfigurationResponse &trt__AddAudioSourceConfigurationResponse)
{
    std::cout << "Function name: " << __func__ << std::endl;
    return SOAP_OK;
}

int __trt__AddPTZConfiguration(struct soap *soap,
                               struct _trt__AddPTZConfiguration *trt__AddPTZConfiguration,
                               struct _trt__AddPTZConfigurationResponse &trt__AddPTZConfigurationResponse)
{
    std::cout << "Function name: " << __func__ << std::endl;
    if (!trt__AddPTZConfiguration)
    {
        std::cerr << "Error: Invalid PTZ Configuration Request" << std::endl;
        return SOAP_FAULT;
    }

    // Check if ProfileToken is empty
    if (trt__AddPTZConfiguration->ProfileToken.empty())
    {
        std::cerr << "Error: ProfileToken is empty" << std::endl;
        return SOAP_FAULT;
    }

    // Access ProfileToken directly
    std::string profileToken = trt__AddPTZConfiguration->ProfileToken;
    
    std::cout << "Adding PTZ Configuration for Profile: " << profileToken << std::endl;
    return SOAP_OK;
}

int __trt__AddVideoAnalyticsConfiguration(struct soap *soap,
                                          struct _trt__AddVideoAnalyticsConfiguration *trt__AddVideoAnalyticsConfiguration,
                                          struct _trt__AddVideoAnalyticsConfigurationResponse &trt__AddVideoAnalyticsConfigurationResponse)
{
    std::cout << "Function name: " << __func__ << std::endl;
    return SOAP_OK;
}

int __trt__AddMetadataConfiguration(struct soap *soap,
                                    struct _trt__AddMetadataConfiguration *trt__AddMetadataConfiguration,
                                    struct _trt__AddMetadataConfigurationResponse &trt__AddMetadataConfigurationResponse)
{
    std::cout << "Function name: " << __func__ << std::endl;
    return SOAP_OK;
}

int __trt__AddAudioOutputConfiguration(struct soap *soap,
                                       struct _trt__AddAudioOutputConfiguration *trt__AddAudioOutputConfiguration,
                                       struct _trt__AddAudioOutputConfigurationResponse &trt__AddAudioOutputConfigurationResponse)
{
    std::cout << "Function name: " << __func__ << std::endl;
    return SOAP_OK;
}

int __trt__AddAudioDecoderConfiguration(struct soap *soap,
                                        struct _trt__AddAudioDecoderConfiguration *trt__AddAudioDecoderConfiguration,
                                        struct _trt__AddAudioDecoderConfigurationResponse &trt__AddAudioDecoderConfigurationResponse)
{
    std::cout << "Function name: " << __func__ << std::endl;
    return SOAP_OK;
}

int __trt__RemoveVideoEncoderConfiguration(struct soap *soap,
                                           struct _trt__RemoveVideoEncoderConfiguration *trt__RemoveVideoEncoderConfiguration,
                                           struct _trt__RemoveVideoEncoderConfigurationResponse &trt__RemoveVideoEncoderConfigurationResponse)
{
    std::cout << "Function name: " << __func__ << std::endl;
    return SOAP_OK;
}

int __trt__RemoveVideoSourceConfiguration(struct soap *soap,
                                          struct _trt__RemoveVideoSourceConfiguration *trt__RemoveVideoSourceConfiguration,
                                          struct _trt__RemoveVideoSourceConfigurationResponse &trt__RemoveVideoSourceConfigurationResponse)
{
    std::cout << "Function name: " << __func__ << std::endl;
    return SOAP_OK;
}

int __trt__RemoveAudioEncoderConfiguration(struct soap *soap,
                                           struct _trt__RemoveAudioEncoderConfiguration *trt__RemoveAudioEncoderConfiguration,
                                           struct _trt__RemoveAudioEncoderConfigurationResponse &trt__RemoveAudioEncoderConfigurationResponse)
{
    std::cout << "Function name: " << __func__ << std::endl;
    return SOAP_OK;
}

int __trt__RemoveAudioSourceConfiguration(struct soap *soap,
                                          struct _trt__RemoveAudioSourceConfiguration *trt__RemoveAudioSourceConfiguration,
                                          struct _trt__RemoveAudioSourceConfigurationResponse &trt__RemoveAudioSourceConfigurationResponse)
{
    std::cout << "Function name: " << __func__ << std::endl;
    return SOAP_OK;
}

int __trt__RemovePTZConfiguration(struct soap *soap,
                                  struct _trt__RemovePTZConfiguration *trt__RemovePTZConfiguration,
                                  struct _trt__RemovePTZConfigurationResponse &trt__RemovePTZConfigurationResponse)
{
    std::cout << "Function name: " << __func__ << std::endl;
    return SOAP_OK;
}

int __trt__RemoveVideoAnalyticsConfiguration(struct soap *soap,
                                             struct _trt__RemoveVideoAnalyticsConfiguration *trt__RemoveVideoAnalyticsConfiguration,
                                             struct _trt__RemoveVideoAnalyticsConfigurationResponse &trt__RemoveVideoAnalyticsConfigurationResponse)
{
    std::cout << "Function name: " << __func__ << std::endl;
    return SOAP_OK;
}

int __trt__RemoveMetadataConfiguration(struct soap *soap,
                                       struct _trt__RemoveMetadataConfiguration *trt__RemoveMetadataConfiguration,
                                       struct _trt__RemoveMetadataConfigurationResponse &trt__RemoveMetadataConfigurationResponse)
{
    std::cout << "Function name: " << __func__ << std::endl;
    return SOAP_OK;
}

int __trt__RemoveAudioOutputConfiguration(struct soap *soap,
                                          struct _trt__RemoveAudioOutputConfiguration *trt__RemoveAudioOutputConfiguration,
                                          struct _trt__RemoveAudioOutputConfigurationResponse &trt__RemoveAudioOutputConfigurationResponse)
{
    std::cout << "Function name: " << __func__ << std::endl;
    return SOAP_OK;
}

int __trt__RemoveAudioDecoderConfiguration(struct soap *soap,
                                           struct _trt__RemoveAudioDecoderConfiguration *trt__RemoveAudioDecoderConfiguration,
                                           struct _trt__RemoveAudioDecoderConfigurationResponse &trt__RemoveAudioDecoderConfigurationResponse)
{
    std::cout << "Function name: " << __func__ << std::endl;
    return SOAP_OK;
}
int __trt__DeleteProfile(struct soap *soap,
                         struct _trt__DeleteProfile *trt__DeleteProfile,
                         struct _trt__DeleteProfileResponse &trt__DeleteProfileResponse)
{
    std::cout << "Function name: " << __func__ << std::endl;
    return SOAP_OK;
}

int __trt__GetVideoSourceConfigurations(struct soap *soap,
                                        struct _trt__GetVideoSourceConfigurations *trt__GetVideoSourceConfigurations,
                                        struct _trt__GetVideoSourceConfigurationsResponse &trt__GetVideoSourceConfigurationsResponse)
{
    std::cout << "Function name: " << __func__ << std::endl;
    return SOAP_OK;
}

int __trt__GetVideoEncoderConfigurations(struct soap *soap,
                                         struct _trt__GetVideoEncoderConfigurations *trt__GetVideoEncoderConfigurations,
                                         struct _trt__GetVideoEncoderConfigurationsResponse &trt__GetVideoEncoderConfigurationsResponse)
{
    std::cout << "Function name: " << __func__ << std::endl;
    return SOAP_OK;
}

int __trt__GetAudioSourceConfigurations(struct soap *soap,
                                        struct _trt__GetAudioSourceConfigurations *trt__GetAudioSourceConfigurations,
                                        struct _trt__GetAudioSourceConfigurationsResponse &trt__GetAudioSourceConfigurationsResponse)
{
    std::cout << "Function name: " << __func__ << std::endl;
    return SOAP_OK;
}

int __trt__GetAudioEncoderConfigurations(struct soap *soap,
                                         struct _trt__GetAudioEncoderConfigurations *trt__GetAudioEncoderConfigurations,
                                         struct _trt__GetAudioEncoderConfigurationsResponse &trt__GetAudioEncoderConfigurationsResponse)
{
    std::cout << "Function name: " << __func__ << std::endl;
    return SOAP_OK;
}

int __trt__GetVideoAnalyticsConfigurations(struct soap *soap,
                                           struct _trt__GetVideoAnalyticsConfigurations *trt__GetVideoAnalyticsConfigurations,
                                           struct _trt__GetVideoAnalyticsConfigurationsResponse &trt__GetVideoAnalyticsConfigurationsResponse)
{
    std::cout << "Function name: " << __func__ << std::endl;
    return SOAP_OK;
}

int __trt__GetMetadataConfigurations(struct soap *soap,
                                     struct _trt__GetMetadataConfigurations *trt__GetMetadataConfigurations,
                                     struct _trt__GetMetadataConfigurationsResponse &trt__GetMetadataConfigurationsResponse)
{
    std::cout << "Function name: " << __func__ << std::endl;
    return SOAP_OK;
}

int __trt__GetAudioOutputConfigurations(struct soap *soap,
                                        struct _trt__GetAudioOutputConfigurations *trt__GetAudioOutputConfigurations,
                                        struct _trt__GetAudioOutputConfigurationsResponse &trt__GetAudioOutputConfigurationsResponse)
{
    std::cout << "Function name: " << __func__ << std::endl;
    return SOAP_OK;
}

int __trt__GetAudioDecoderConfigurations(struct soap *soap,
                                         struct _trt__GetAudioDecoderConfigurations *trt__GetAudioDecoderConfigurations,
                                         struct _trt__GetAudioDecoderConfigurationsResponse &trt__GetAudioDecoderConfigurationsResponse)
{
    std::cout << "Function name: " << __func__ << std::endl;
    return SOAP_OK;
}

int __trt__GetVideoSourceConfiguration(struct soap *soap,
                                       struct _trt__GetVideoSourceConfiguration *trt__GetVideoSourceConfiguration,
                                       struct _trt__GetVideoSourceConfigurationResponse &trt__GetVideoSourceConfigurationResponse)
{
    std::cout << "Function name: " << __func__ << std::endl;
    return SOAP_OK;
}

int __trt__GetVideoEncoderConfiguration(struct soap *soap,
                                        struct _trt__GetVideoEncoderConfiguration *trt__GetVideoEncoderConfiguration,
                                        struct _trt__GetVideoEncoderConfigurationResponse &trt__GetVideoEncoderConfigurationResponse)
{
    std::cout << "Function name: " << __func__ << std::endl;
    return SOAP_OK;
}

int __trt__GetAudioSourceConfiguration(struct soap *soap,
                                       struct _trt__GetAudioSourceConfiguration *trt__GetAudioSourceConfiguration,
                                       struct _trt__GetAudioSourceConfigurationResponse &trt__GetAudioSourceConfigurationResponse)
{
    std::cout << "Function name: " << __func__ << std::endl;
    return SOAP_OK;
}

int __trt__GetAudioEncoderConfiguration(struct soap *soap,
                                        struct _trt__GetAudioEncoderConfiguration *trt__GetAudioEncoderConfiguration,
                                        struct _trt__GetAudioEncoderConfigurationResponse &trt__GetAudioEncoderConfigurationResponse)
{
    std::cout << "Function name: " << __func__ << std::endl;
    return SOAP_OK;
}

int __trt__GetVideoAnalyticsConfiguration(struct soap *soap,
                                          struct _trt__GetVideoAnalyticsConfiguration *trt__GetVideoAnalyticsConfiguration,
                                          struct _trt__GetVideoAnalyticsConfigurationResponse &trt__GetVideoAnalyticsConfigurationResponse)
{
    std::cout << "Function name: " << __func__ << std::endl;
    return SOAP_OK;
}

int __trt__GetMetadataConfiguration(struct soap *soap,
                                    struct _trt__GetMetadataConfiguration *trt__GetMetadataConfiguration,
                                    struct _trt__GetMetadataConfigurationResponse &trt__GetMetadataConfigurationResponse)
{
    std::cout << "Function name: " << __func__ << std::endl;
    return SOAP_OK;
}

int __trt__GetAudioOutputConfiguration(struct soap *soap,
                                       struct _trt__GetAudioOutputConfiguration *trt__GetAudioOutputConfiguration,
                                       struct _trt__GetAudioOutputConfigurationResponse &trt__GetAudioOutputConfigurationResponse)
{
    std::cout << "Function name: " << __func__ << std::endl;
    return SOAP_OK;
}

int __trt__GetAudioDecoderConfiguration(struct soap *soap,
                                        struct _trt__GetAudioDecoderConfiguration *trt__GetAudioDecoderConfiguration,
                                        struct _trt__GetAudioDecoderConfigurationResponse &trt__GetAudioDecoderConfigurationResponse)
{
    std::cout << "Function name: " << __func__ << std::endl;
    return SOAP_OK;
}

int __trt__GetCompatibleVideoEncoderConfigurations(struct soap *soap,
                                                   struct _trt__GetCompatibleVideoEncoderConfigurations *trt__GetCompatibleVideoEncoderConfigurations,
                                                   struct _trt__GetCompatibleVideoEncoderConfigurationsResponse &trt__GetCompatibleVideoEncoderConfigurationsResponse)
{
    std::cout << "Function name: " << __func__ << std::endl;
    return SOAP_OK;
}

int __trt__GetCompatibleVideoSourceConfigurations(struct soap *soap,
                                                  struct _trt__GetCompatibleVideoSourceConfigurations *trt__GetCompatibleVideoSourceConfigurations,
                                                  struct _trt__GetCompatibleVideoSourceConfigurationsResponse &trt__GetCompatibleVideoSourceConfigurationsResponse)
{
    std::cout << "Function name: " << __func__ << std::endl;
    return SOAP_OK;
}

int __trt__GetCompatibleAudioEncoderConfigurations(struct soap *soap,
                                                   struct _trt__GetCompatibleAudioEncoderConfigurations *trt__GetCompatibleAudioEncoderConfigurations,
                                                   struct _trt__GetCompatibleAudioEncoderConfigurationsResponse &trt__GetCompatibleAudioEncoderConfigurationsResponse)
{
    std::cout << "Function name: " << __func__ << std::endl;
    return SOAP_OK;
}

int __trt__GetCompatibleAudioSourceConfigurations(struct soap *soap,
                                                  struct _trt__GetCompatibleAudioSourceConfigurations *trt__GetCompatibleAudioSourceConfigurations,
                                                  struct _trt__GetCompatibleAudioSourceConfigurationsResponse &trt__GetCompatibleAudioSourceConfigurationsResponse)
{
    std::cout << "Function name: " << __func__ << std::endl;
    return SOAP_OK;
}

int __trt__GetCompatibleVideoAnalyticsConfigurations(struct soap *soap,
                                                     struct _trt__GetCompatibleVideoAnalyticsConfigurations *trt__GetCompatibleVideoAnalyticsConfigurations,
                                                     struct _trt__GetCompatibleVideoAnalyticsConfigurationsResponse &trt__GetCompatibleVideoAnalyticsConfigurationsResponse)
{
    std::cout << "Function name: " << __func__ << std::endl;
    return SOAP_OK;
}

int __trt__GetCompatibleMetadataConfigurations(struct soap *soap,
                                               struct _trt__GetCompatibleMetadataConfigurations *trt__GetCompatibleMetadataConfigurations,
                                               struct _trt__GetCompatibleMetadataConfigurationsResponse &trt__GetCompatibleMetadataConfigurationsResponse)
{
    std::cout << "Function name: " << __func__ << std::endl;
    return SOAP_OK;
}

int __trt__GetCompatibleAudioOutputConfigurations(struct soap *soap,
                                                  struct _trt__GetCompatibleAudioOutputConfigurations *trt__GetCompatibleAudioOutputConfigurations,
                                                  struct _trt__GetCompatibleAudioOutputConfigurationsResponse &trt__GetCompatibleAudioOutputConfigurationsResponse)
{
    std::cout << "Function name: " << __func__ << std::endl;
    return SOAP_OK;
}

int __trt__GetCompatibleAudioDecoderConfigurations(struct soap *soap,
                                                   struct _trt__GetCompatibleAudioDecoderConfigurations *trt__GetCompatibleAudioDecoderConfigurations,
                                                   struct _trt__GetCompatibleAudioDecoderConfigurationsResponse &trt__GetCompatibleAudioDecoderConfigurationsResponse)
{
    std::cout << "Function name: " << __func__ << std::endl;
    return SOAP_OK;
}

int __trt__SetVideoSourceConfiguration(struct soap *soap,
                                       struct _trt__SetVideoSourceConfiguration *trt__SetVideoSourceConfiguration,
                                       struct _trt__SetVideoSourceConfigurationResponse &trt__SetVideoSourceConfigurationResponse)
{
    std::cout << "Function name: " << __func__ << std::endl;
    return SOAP_OK;
}

int __trt__SetVideoEncoderConfiguration(struct soap *soap,
                                        struct _trt__SetVideoEncoderConfiguration *trt__SetVideoEncoderConfiguration,
                                        struct _trt__SetVideoEncoderConfigurationResponse &trt__SetVideoEncoderConfigurationResponse)
{
    std::cout << "Function name: " << __func__ << std::endl;
    return SOAP_OK;
}

int __trt__SetAudioSourceConfiguration(struct soap *soap,
                                       struct _trt__SetAudioSourceConfiguration *trt__SetAudioSourceConfiguration,
                                       struct _trt__SetAudioSourceConfigurationResponse &trt__SetAudioSourceConfigurationResponse)
{
    std::cout << "Function name: " << __func__ << std::endl;
    return SOAP_OK;
}

int __trt__SetAudioEncoderConfiguration(struct soap *soap,
                                        struct _trt__SetAudioEncoderConfiguration *trt__SetAudioEncoderConfiguration,
                                        struct _trt__SetAudioEncoderConfigurationResponse &trt__SetAudioEncoderConfigurationResponse)
{
    std::cout << "Function name: " << __func__ << std::endl;
    return SOAP_OK;
}

int __trt__SetVideoAnalyticsConfiguration(struct soap *soap,
                                          struct _trt__SetVideoAnalyticsConfiguration *trt__SetVideoAnalyticsConfiguration,
                                          struct _trt__SetVideoAnalyticsConfigurationResponse &trt__SetVideoAnalyticsConfigurationResponse)
{
    std::cout << "Function name: " << __func__ << std::endl;
    return SOAP_OK;
}

int __trt__SetMetadataConfiguration(struct soap *soap,
                                    struct _trt__SetMetadataConfiguration *trt__SetMetadataConfiguration,
                                    struct _trt__SetMetadataConfigurationResponse &trt__SetMetadataConfigurationResponse)
{
    std::cout << "Function name: " << __func__ << std::endl;
    return SOAP_OK;
}

int __trt__SetAudioOutputConfiguration(struct soap *soap,
                                       struct _trt__SetAudioOutputConfiguration *trt__SetAudioOutputConfiguration,
                                       struct _trt__SetAudioOutputConfigurationResponse &trt__SetAudioOutputConfigurationResponse)
{
    std::cout << "Function name: " << __func__ << std::endl;
    return SOAP_OK;
}

int __trt__SetAudioDecoderConfiguration(struct soap *soap,
                                        struct _trt__SetAudioDecoderConfiguration *trt__SetAudioDecoderConfiguration,
                                        struct _trt__SetAudioDecoderConfigurationResponse &trt__SetAudioDecoderConfigurationResponse)
{
    std::cout << "Function name: " << __func__ << std::endl;
    return SOAP_OK;
}

int __trt__GetVideoSourceConfigurationOptions(struct soap *soap,
                                              struct _trt__GetVideoSourceConfigurationOptions *trt__GetVideoSourceConfigurationOptions,
                                              struct _trt__GetVideoSourceConfigurationOptionsResponse &trt__GetVideoSourceConfigurationOptionsResponse)
{
    std::cout << "Function name: " << __func__ << std::endl;
    return SOAP_OK;
}

int __trt__GetVideoEncoderConfigurationOptions(struct soap *soap,
                                               struct _trt__GetVideoEncoderConfigurationOptions *trt__GetVideoEncoderConfigurationOptions,
                                               struct _trt__GetVideoEncoderConfigurationOptionsResponse &trt__GetVideoEncoderConfigurationOptionsResponse)
{
    std::cout << "Function name: " << __func__ << std::endl;
    return SOAP_OK;
}

int __trt__GetAudioSourceConfigurationOptions(struct soap *soap,
                                              struct _trt__GetAudioSourceConfigurationOptions *trt__GetAudioSourceConfigurationOptions,
                                              struct _trt__GetAudioSourceConfigurationOptionsResponse &trt__GetAudioSourceConfigurationOptionsResponse)
{
    std::cout << "Function name: " << __func__ << std::endl;
    return SOAP_OK;
}
int __trt__GetAudioEncoderConfigurationOptions(struct soap *soap,
                                               struct _trt__GetAudioEncoderConfigurationOptions *trt__GetAudioEncoderConfigurationOptions,
                                               struct _trt__GetAudioEncoderConfigurationOptionsResponse &trt__GetAudioEncoderConfigurationOptionsResponse)
{
    std::cout << "Function name: " << __func__ << std::endl;
    return SOAP_OK;
}

int __trt__GetMetadataConfigurationOptions(struct soap *soap,
                                           struct _trt__GetMetadataConfigurationOptions *trt__GetMetadataConfigurationOptions,
                                           struct _trt__GetMetadataConfigurationOptionsResponse &trt__GetMetadataConfigurationOptionsResponse)
{
    std::cout << "Function name: " << __func__ << std::endl;
    return SOAP_OK;
}

int __trt__GetAudioOutputConfigurationOptions(struct soap *soap,
                                              struct _trt__GetAudioOutputConfigurationOptions *trt__GetAudioOutputConfigurationOptions,
                                              struct _trt__GetAudioOutputConfigurationOptionsResponse &trt__GetAudioOutputConfigurationOptionsResponse)
{
    std::cout << "Function name: " << __func__ << std::endl;
    return SOAP_OK;
}

int __trt__GetAudioDecoderConfigurationOptions(struct soap *soap,
                                               struct _trt__GetAudioDecoderConfigurationOptions *trt__GetAudioDecoderConfigurationOptions,
                                               struct _trt__GetAudioDecoderConfigurationOptionsResponse &trt__GetAudioDecoderConfigurationOptionsResponse)
{
    std::cout << "Function name: " << __func__ << std::endl;
    return SOAP_OK;
}

int __trt__GetGuaranteedNumberOfVideoEncoderInstances(struct soap *soap,
                                                      struct _trt__GetGuaranteedNumberOfVideoEncoderInstances *trt__GetGuaranteedNumberOfVideoEncoderInstances,
                                                      struct _trt__GetGuaranteedNumberOfVideoEncoderInstancesResponse &trt__GetGuaranteedNumberOfVideoEncoderInstancesResponse)
{
    std::cout << "Function name: " << __func__ << std::endl;
    return SOAP_OK;
}

int __trt__GetStreamUri(struct soap *soap,
                        struct _trt__GetStreamUri *trt__GetStreamUri,
                        struct _trt__GetStreamUriResponse &trt__GetStreamUriResponse)
{
    std::cout << "Function name: " << __func__ << std::endl;

    trt__GetStreamUriResponse.MediaUri = soap_new_tt__MediaUri(soap);
    if (!trt__GetStreamUriResponse.MediaUri)
    {
        return soap_sender_fault(soap, "Memory Allocation Failed", "Could not allocate memory for MediaUri");
    }

    trt__GetStreamUriResponse.MediaUri->Uri = "rtsp://192.168.2.25:8554/main.264";
    trt__GetStreamUriResponse.MediaUri->InvalidAfterConnect = false;
    trt__GetStreamUriResponse.MediaUri->InvalidAfterReboot = false;
    trt__GetStreamUriResponse.MediaUri->Timeout = "";

    std::cout << "GetStreamUri called: Returning URI 'rtsp://192.168.2.25:8554/main.264'" << std::endl;
    std::cout << "Function name: " << __func__ << std::endl;
    return SOAP_OK;
}

int __trt__StartMulticastStreaming(struct soap *soap,
                                   struct _trt__StartMulticastStreaming *trt__StartMulticastStreaming,
                                   struct _trt__StartMulticastStreamingResponse &trt__StartMulticastStreamingResponse)
{
    std::cout << "Function name: " << __func__ << std::endl;
    return SOAP_OK;
}

int __trt__StopMulticastStreaming(struct soap *soap,
                                  struct _trt__StopMulticastStreaming *trt__StopMulticastStreaming,
                                  struct _trt__StopMulticastStreamingResponse &trt__StopMulticastStreamingResponse)
{
    std::cout << "Function name: " << __func__ << std::endl;
    return SOAP_OK;
}

int __trt__SetSynchronizationPoint(struct soap *soap,
                                   struct _trt__SetSynchronizationPoint *trt__SetSynchronizationPoint,
                                   struct _trt__SetSynchronizationPointResponse &trt__SetSynchronizationPointResponse)
{
    std::cout << "Function name: " << __func__ << std::endl;
    return SOAP_OK;
}

int __trt__GetSnapshotUri(struct soap *soap,
                          struct _trt__GetSnapshotUri *trt__GetSnapshotUri,
                          struct _trt__GetSnapshotUriResponse &trt__GetSnapshotUriResponse)
{
    std::cout << "Function name: " << __func__ << std::endl;
    return SOAP_OK;
}

int __trt__GetVideoSourceModes(struct soap *soap,
                               struct _trt__GetVideoSourceModes *trt__GetVideoSourceModes,
                               struct _trt__GetVideoSourceModesResponse &trt__GetVideoSourceModesResponse)
{
    std::cout << "Function name: " << __func__ << std::endl;
    return SOAP_OK;
}

int __trt__SetVideoSourceMode(struct soap *soap,
                              struct _trt__SetVideoSourceMode *trt__SetVideoSourceMode,
                              struct _trt__SetVideoSourceModeResponse &trt__SetVideoSourceModeResponse)
{
    std::cout << "Function name: " << __func__ << std::endl;
    return SOAP_OK;
}

int __trt__GetOSDs(struct soap *soap,
                   struct _trt__GetOSDs *trt__GetOSDs,
                   struct _trt__GetOSDsResponse &trt__GetOSDsResponse)
{
    std::cout << "Function name: " << __func__ << std::endl;
    return SOAP_OK;
}

int __trt__GetOSD(struct soap *soap,
                  struct _trt__GetOSD *trt__GetOSD,
                  struct _trt__GetOSDResponse &trt__GetOSDResponse)
{
    std::cout << "Function name: " << __func__ << std::endl;
    return SOAP_OK;
}

int __trt__GetOSDOptions(struct soap *soap,
                         struct _trt__GetOSDOptions *trt__GetOSDOptions,
                         struct _trt__GetOSDOptionsResponse &trt__GetOSDOptionsResponse)
{
    std::cout << "Function name: " << __func__ << std::endl;
    return SOAP_OK;
}

int __trt__SetOSD(struct soap *soap,
                  struct _trt__SetOSD *trt__SetOSD,
                  struct _trt__SetOSDResponse &trt__SetOSDResponse)
{
    std::cout << "Function name: " << __func__ << std::endl;
    return SOAP_OK;
}

int __trt__CreateOSD(struct soap *soap,
                     struct _trt__CreateOSD *trt__CreateOSD,
                     struct _trt__CreateOSDResponse &trt__CreateOSDResponse)
{
    std::cout << "Function name: " << __func__ << std::endl;
    return SOAP_OK;
}

int __trt__DeleteOSD(struct soap *soap,
                     struct _trt__DeleteOSD *trt__DeleteOSD,
                     struct _trt__DeleteOSDResponse &trt__DeleteOSDResponse)
{
    std::cout << "Function name: " << __func__ << std::endl;
    return SOAP_OK;
}
