
typedef struct {
	  unsigned char data[8];
} st_am2321;

st_am2321 am2321();

void print_am2321( st_am2321 measured );
short __am2321_temperature( st_am2321 measured );
short am2321_temperature_integral( st_am2321 measured ) ;
short am2321_temperature_fraction( st_am2321 measured );

short __am2321_humidity( st_am2321 measured );
short am2321_humidity_integral( st_am2321 measured ) ;
short am2321_humidity_fraction( st_am2321 measured );
