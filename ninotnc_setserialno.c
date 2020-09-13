/* ninotnc_setserialno.c, Boone, 09/13/20
   Turn on serial number reporting for USB CDC */

/* Modifications:
   09/13/20 Boone      Initial coding
   End Modifications */

#include <hidapi/hidapi.h>
#include <libmcp2221.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
	int devcount;
	int enumerate;
	mcp2221_error err;
	hid_device *hidh;
	int hres;
	mcp2221_t *mdev;
	wchar_t *nada;

	nada = NULL;

	hres = hid_init();
	devcount = mcp2221_find(0x4d8, 0x00dd, nada, nada, nada);
	if (devcount == 1)
	{
		printf("Found %d devices.\n", devcount);
	}
	else
	{
		printf("Found %d devices, aborting.\n", devcount);
		mcp2221_exit();
		exit(22);
	}
	mdev = mcp2221_open();
	err = mcp2221_loadSerialEnumerate(mdev, &enumerate);
	if (err)
	{
		puts("Unable to read serial enumerate setting, aborting");
		mcp2221_exit();
		exit(22);
	}
	printf("Enumerate setting was %d\n", enumerate);
	enumerate = 1;
	err = mcp2221_saveSerialEnumerate(mdev, enumerate);
	if (err)
	{
		puts("Turning on serial enumerate failed");
		mcp2221_exit();
		exit(22);
	}
	else
	{
		puts("Success!");
	}

	mcp2221_exit();
	exit(0);
}

/*

===============================
Before serial enumerate enabled
===============================

[3501171.909765] usb 1-1.6: new full-speed USB device number 35 using ehci-pci
[3501172.022462] usb 1-1.6: New USB device found, idVendor=04d8, idProduct=00dd, bcdDevice= 1.00
[3501172.022468] usb 1-1.6: New USB device strings: Mfr=1, Product=2, SerialNumber=0
[3501172.022470] usb 1-1.6: Product: MCP2221 USB-I2C/UART Combo
[3501172.022473] usb 1-1.6: Manufacturer: Microchip Technology Inc.
[3501172.023495] cdc_acm 1-1.6:1.0: ttyACM0: USB ACM device
[3501172.025454] hid-generic 0003:04D8:00DD.001C: hiddev0,hidraw3: USB HID v1.11 Device [Microchip Technology Inc. MCP2221 USB-I2C/UART Combo] on usb-0000:00:1a.0-1.6/input2

==============================
After serial enumerate enabled
==============================

[3516507.236459] usb 1-1.3: new full-speed USB device number 41 using ehci-pci
[3516507.349556] usb 1-1.3: New USB device found, idVendor=04d8, idProduct=00dd, bcdDevice= 1.00
[3516507.349563] usb 1-1.3: New USB device strings: Mfr=1, Product=2, SerialNumber=3
[3516507.349565] usb 1-1.3: Product: MCP2221 USB-I2C/UART Combo
[3516507.349568] usb 1-1.3: Manufacturer: Microchip Technology Inc.
[3516507.349570] usb 1-1.3: SerialNumber: 0001401082
[3516507.350221] cdc_acm 1-1.3:1.0: ttyACM0: USB ACM device
[3516507.352188] hid-generic 0003:04D8:00DD.0023: hiddev0,hidraw3: USB HID v1.11 Device [Microchip Technology Inc. MCP2221 USB-I2C/UART Combo] on usb-0000:00:1a.0-1.3/input2

*/
