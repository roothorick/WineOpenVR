#include "common.h"

// For whatever reason, this one doesn't have an accessor like the others.
// This function will be duplicated in each object, but that's okay; only one will ever be used.
__attribute__((visibility ("hidden"))) IVRNotifications* VRNotifications()
{
	static IVRNotifications* ret = NULL;
	EVRInitError err;
	if(ret == NULL) ret = (IVRNotifications*) VR_GetGenericInterface("IVRNotifications_002", &err);
	return ret;
}

namespace fns_IVRNotifications
{
	inline EVRNotificationError CreateNotification( VROverlayHandle_t ulOverlayHandle, uint64_t ulUserValue, EVRNotificationType type, const char *pchText, EVRNotificationStyle style, const NotificationBitmap_t *pImage, VRNotificationId *pNotificationId )
	{
		return VRNotifications()->CreateNotification(ulOverlayHandle, ulUserValue, type, pchText, style, pImage, pNotificationId);
	}

	inline EVRNotificationError RemoveNotification( VRNotificationId notificationId )
	{
		return VRNotifications()->RemoveNotification(notificationId);
	}
}
