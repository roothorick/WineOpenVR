#include "common.h"

#ifndef ABIVER
#error "No ABIVER?"
#endif

#define CLONECLASS__(token_) clone_IVRNotifications_ ## token_
#define CLONECLASS_(token) CLONECLASS__(token)
#define CLONECLASS CLONECLASS_(ABITOKEN)
#define PROXYCLASS__(token_) proxy_IVRNotifications_ ## token_
#define PROXYCLASS_(token) PROXYCLASS__(token)
#define PROXYCLASS PROXYCLASS_(ABITOKEN)
#define GETTER__(token_) getIVRNotificationsProxy_ ## token_
#define GETTER_(token) GETTER__(token)
#define GETTER GETTER_(ABITOKEN)

// For whatever reason, this one doesn't have an accessor like the others.
// This function will be duplicated in each object, but that's okay; only one will ever be used.
__attribute__((visibility ("hidden"))) IVRNotifications* VRNotifications()
{
	static IVRNotifications* ret = NULL;
	EVRInitError err;
	if(ret == NULL) ret = (IVRNotifications*) VR_GetGenericInterface("IVRNotifications_002", &err);
	return ret;
}

class CLONECLASS
{
public:
	WOVR_ENTRY virtual EVRNotificationError CreateNotification( VROverlayHandle_t ulOverlayHandle, uint64_t ulUserValue, EVRNotificationType type, const char *pchText, EVRNotificationStyle style, const NotificationBitmap_t *pImage, VRNotificationId *pNotificationId ) = 0;
	WOVR_ENTRY virtual EVRNotificationError RemoveNotification( VRNotificationId notificationId ) = 0;
};

class PROXYCLASS : public CLONECLASS
{
public:
	WOVR_ENTRY EVRNotificationError CreateNotification( VROverlayHandle_t ulOverlayHandle, uint64_t ulUserValue, EVRNotificationType type, const char *pchText, EVRNotificationStyle style, const NotificationBitmap_t *pImage, VRNotificationId *pNotificationId )
	{
		TRACE("");
		return VRNotifications()->CreateNotification(ulOverlayHandle, ulUserValue, type, pchText, style, pImage, pNotificationId);
	}

	WOVR_ENTRY EVRNotificationError RemoveNotification( VRNotificationId notificationId )
	{
		TRACE("");
		return VRNotifications()->RemoveNotification(notificationId);
	}
};

IVRNotifications* GETTER ()
{
	return (IVRNotifications*) new PROXYCLASS ();
}
