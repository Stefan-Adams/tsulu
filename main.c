#include <stdio.h>
#include <getopt.h>
#include <usb.h>

#include "main.h"
#include "lib_uproar.h"

int main(int argc, char **argv)
{
	int x;
	char c;

	int retval;
	char *devstr;

	retval = Uproar_initialize();
	if ( retval < 0 ) {
		fprintf ( stderr, "\n\nNO MP3 DEVICE FOUND.\n\n" );
		exit ( -1 );
	}

	devstr = Uproar_get_device_info();
	if ( devstr == 0 ) {
		fprintf ( stderr, "\n\nNO MP3 DEVICE STRING.\n\n" );
		exit ( -1 );
	}
	Uproar_load_playlist();

	while ( (c=getopt(argc, argv, "acD:fhlnT:")) != EOF ) {
		switch ( c ) {
		case 'a':
			printf("%d\n", Uproar_get_available());
			break;
		case 'c':
			printf("%d\n", Uproar_get_capacity());
			break;
		case 'n':
			printf("%d\n", Uproar_num_tracks());
			break;
		case 'l':
			for ( x=1; x<=Uproar_num_tracks(); x++ ) {
				int filesize;
				printf("%d (%d): %s\n", x, filesize, Uproar_get_track_info(x-1, &filesize));
			}
			break;
		case 'f':
			if ( !Uproar_reformat_memory() )
				printf("Formatted successfully!\n");
			break;
		case 'D':
			if ( atoi(optarg) < 1 || atoi(optarg) > Uproar_num_tracks() )
				printf("0\n", atoi(optarg));
			else
				if ( !Uproar_delete_track(atoi(optarg)-1) )
					printf("%d\n", atoi(optarg));
			break;
		case 'T':
			if ( !Uproar_download(optarg) ) printf("%s\n", optarg);
			break;
		case 'h':
		default:
			printf("usage: sulu [-acD:fhlnT:]\n");
			printf("  a\tShow available space\n");
			printf("  c\tShow capacity\n");
			printf("  D n\tDelete track n\n");
			printf("  f\tFormat device\n");
			printf("  h\tShow this help message\n");
			printf("  l\tList track sizes and names\n");
			printf("  n\tShow number of tracks\n");
			printf("  T s\tTransfer file\n");
		}
	}

	return 0;
}
