#include "common.h"

class clone_IVRNotifications
{
public:
	THISCALL virtual EVRNotificationError CreateNotification( VROverlayHandle_t ulOverlayHandle, uint64_t ulUserValue, EVRNotificationType type, const char *pchText, EVRNotificationStyle style, const NotificationBitmap_t *pImage, VRNotificationId *pNotificationId ) = 0;
	THISCALL virtual EVRNotificationError RemoveNotification( VRNotificationId notificationId ) = 0;
};

class proxy_IVRNotifications : public clone_IVRNotifications
{
public:
	proxy_IVRNotifications(IVRNotifications* real) { realImpl = real; }

	THISCALL EVRNotificationError CreateNotification( VROverlayHandle_t ulOverlayHandle, uint64_t ulUserValue, EVRNotificationType type, const char *pchText, EVRNotificationStyle style, const NotificationBitmap_t *pImage, VRNotificationId *pNotificationId )
	{
		return realImpl->CreateNotification(ulOverlayHandle, ulUserValue, type, pchText, style, pImage, pNotificationId);
	}

	THISCALL EVRNotificationError RemoveNotification( VRNotificationId notificationId )
	{
		return realImpl->RemoveNotification(notificationId);
	}

private:
	IVRNotifications* realImpl;
};

IVRNotifications* getIVRNotificationsProxy(IVRNotifications* real)
{
	return (IVRNotifications*) new proxy_IVRNotifications(real);
}
