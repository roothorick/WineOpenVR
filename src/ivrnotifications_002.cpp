#include "ivrnotifications.h"

class clone_IVRNotifications_002
{
public:
	WOVR_ENTRY virtual EVRNotificationError CreateNotification( VROverlayHandle_t ulOverlayHandle, uint64_t ulUserValue, EVRNotificationType type, const char *pchText, EVRNotificationStyle style, const NotificationBitmap_t *pImage, VRNotificationId *pNotificationId ) = 0;
	WOVR_ENTRY virtual EVRNotificationError RemoveNotification( VRNotificationId notificationId ) = 0;
};

class proxy_IVRNotifications_002 : public clone_IVRNotifications_002
{
public:
	WOVR_ENTRY EVRNotificationError CreateNotification( VROverlayHandle_t ulOverlayHandle, uint64_t ulUserValue, EVRNotificationType type, const char *pchText, EVRNotificationStyle style, const NotificationBitmap_t *pImage, VRNotificationId *pNotificationId )
	{
		return fns_IVRNotifications::CreateNotification(ulOverlayHandle, ulUserValue, type, pchText, style, pImage, pNotificationId);
	}

	WOVR_ENTRY EVRNotificationError RemoveNotification( VRNotificationId notificationId )
	{
		return fns_IVRNotifications::RemoveNotification(notificationId);
	}
};

IVRNotifications* getIVRNotificationsProxy_002()
{
	return (IVRNotifications*) new proxy_IVRNotifications_002();
}
