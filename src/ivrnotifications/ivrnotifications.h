#include "common.h"

#ifndef ABIVER
#error "No ABIVER?"
#endif

#define CLONECLASS__(abiver_) clone_IVRNotifications_ ## abiver_
#define CLONECLASS_(abiver) CLONECLASS__(abiver)
#define CLONECLASS CLONECLASS_(ABIVER)
#define PROXYCLASS__(abiver_) proxy_IVRNotifications_ ## abiver_
#define PROXYCLASS_(abiver) PROXYCLASS__(abiver)
#define PROXYCLASS PROXYCLASS_(ABIVER)
#define GETTER__(abiver_) getIVRNotificationsProxy_ ## abiver_
#define GETTER_(abiver) GETTER__(abiver)
#define GETTER GETTER_(ABIVER)

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
		return VRNotifications()->CreateNotification(ulOverlayHandle, ulUserValue, type, pchText, style, pImage, pNotificationId);
	}

	WOVR_ENTRY EVRNotificationError RemoveNotification( VRNotificationId notificationId )
	{
		return VRNotifications()->RemoveNotification(notificationId);
	}
};

IVRNotifications* GETTER ()
{
	return (IVRNotifications*) new PROXYCLASS ();
}
