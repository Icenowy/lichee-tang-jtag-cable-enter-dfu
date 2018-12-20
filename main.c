#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include <libusb.h>

int main()
{
	int ret, transferred;
	struct libusb_device_handle *devh = NULL;

	ret = libusb_init(NULL);
	if (ret)
		return 1;

	devh = libusb_open_device_with_vid_pid(NULL, 0x0547, 0x1002);
	if (!devh)
		return 2;

	ret = libusb_claim_interface(devh, 0);
	if (ret)
		return 3;

	uint8_t data[2] = {0x5a, 0xa5};

	ret = libusb_bulk_transfer(devh, 8, (void *)data, sizeof(data), &transferred, 1000);
	if (ret)
		return 4;

	libusb_close(devh);
	libusb_exit(NULL);
}
