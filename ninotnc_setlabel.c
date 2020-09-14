/* ninotnc_setlabel.c, Boone, 09/13/20
   Set manufacturer and product labels for USB CDC */

/* Modifications:
   09/13/20 Boone      Initial coding
   End Modifications */

#include <hidapi/hidapi.h>
#include <libmcp2221.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void setl_abort(char *errmsg)
{
	puts(errmsg);
	mcp2221_exit();
	exit(22);
}

void unpack(uint16_t *instr, unsigned char *outstr)
{
	int i;

	for (i = 0; i < 64, instr[i] != 0; i++)
	{
		if (instr[i] < 256)
			outstr[i] = (unsigned char)instr[i];
		else
			break;
	}
}

void pack(unsigned char *instr, uint16_t *outstr)
{
	int i;

	for (i = 0; i < 64, instr[i] != 0; i++)
	{
		outstr[i] = (uint16_t)instr[i];
	}
}

void hexdump_w(uint16_t *instr)
{
	unsigned char *c;
	int i;

	c = (unsigned char *)instr;
	i = 0;
	while (i < 64)
	{
		printf("%02x ", *c);
		c++;
		i++;
	}
	puts("");
	puts("");
}

int main(int argc, char *argv[])
{
	int devcount;
	int enumerate;
	mcp2221_error err;
	hid_device *hidh;
	int hres;
	mcp2221_t *mdev;
	wchar_t *nada;
	unsigned char newmfg[] = "TARPN                           ";
	unsigned char newprod[] = "N9600A NinoTNC                  ";
	unsigned char usbbuf_c[64];
	uint16_t usbbuf_w[64];

/* Setup */

	nada = NULL;

	hres = hid_init();
	err = mcp2221_init();
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

/* Manufacturer label */

	memset(usbbuf_c, (unsigned char)0, sizeof(usbbuf_c));
	memset(usbbuf_w, (uint16_t)0, sizeof(usbbuf_w));

	err = mcp2221_loadManufacturer(mdev, (wchar_t *)usbbuf_w);
	if (err)
		setl_abort("Unable to read manufacturer label, aborting");
	unpack(usbbuf_w, usbbuf_c);
	printf("Manufacturer label was [%s]\n", usbbuf_c);

	memset(usbbuf_c, (unsigned char)0, sizeof(usbbuf_c));
	memset(usbbuf_w, (uint16_t)0, sizeof(usbbuf_w));

	pack(newmfg, usbbuf_w);
	err = mcp2221_saveManufacturer(mdev, (wchar_t *)usbbuf_w);
	if (err)
		setl_abort("Setting manufacturer label failed, aborting");
	else
		puts("Manufacturer label set");

/* Product label */

	memset(usbbuf_c, (unsigned char)0, sizeof(usbbuf_c));
	memset(usbbuf_w, (uint16_t)0, sizeof(usbbuf_w));

	err = mcp2221_loadProduct(mdev, (wchar_t *)usbbuf_w);
	if (err)
		setl_abort("Unable to read product label, aborting");
	unpack(usbbuf_w, usbbuf_c);
	printf("Product label was [%s]\n", usbbuf_c);

	memset(usbbuf_c, (unsigned char)0, sizeof(usbbuf_c));
	memset(usbbuf_w, (uint16_t)0, sizeof(usbbuf_w));

	pack(newprod, usbbuf_w);
	err = mcp2221_saveProduct(mdev, (wchar_t *)usbbuf_w);
	if (err)
		setl_abort("Setting product label failed, aborting");
	else
		puts("Product label set");

/* All done */

	mcp2221_exit();
	exit(0);
}

/*

=================
Before labels set
=================

[3501171.909765] usb 1-1.6: new full-speed USB device number 35 using ehci-pci
[3501172.022462] usb 1-1.6: New USB device found, idVendor=04d8, idProduct=00dd, bcdDevice= 1.00
[3501172.022468] usb 1-1.6: New USB device strings: Mfr=1, Product=2, SerialNumber=0
[3501172.022470] usb 1-1.6: Product: MCP2221 USB-I2C/UART Combo
[3501172.022473] usb 1-1.6: Manufacturer: Microchip Technology Inc.
[3501172.023495] cdc_acm 1-1.6:1.0: ttyACM0: USB ACM device
[3501172.025454] hid-generic 0003:04D8:00DD.001C: hiddev0,hidraw3: USB HID v1.11 Device [Microchip Technology Inc. MCP2221 USB-I2C/UART Combo] on usb-0000:00:1a.0-1.6/input2

================
After labels set
================

[3548077.218862] usb 1-1.3: new full-speed USB device number 51 using ehci-pci
[3548077.331687] usb 1-1.3: New USB device found, idVendor=04d8, idProduct=00dd, bcdDevice= 1.00
[3548077.331692] usb 1-1.3: New USB device strings: Mfr=1, Product=2, SerialNumber=3
[3548077.331695] usb 1-1.3: Product: N9600A NinoTNC  
[3548077.331697] usb 1-1.3: Manufacturer: TARPN           
[3548077.331699] usb 1-1.3: SerialNumber: 0001401082
[3548077.332370] cdc_acm 1-1.3:1.0: ttyACM0: USB ACM device
[3548077.334201] hid-generic 0003:04D8:00DD.002C: hiddev0,hidraw3: USB HID v1.11 Device [TARPN            N9600A NinoTNC  ] on usb-0000:00:1a.0-1.3/input2

*/
