#ifndef electro_prototype_h
#define electro_prototype_h

// Common prototypes from the electro library routines

// This sample subroutine converts a from string (consisting of a floating
// point number and possibly a scale factor and units) to a to string (consisting
// only of units.
int conversion(char *from_string, char *to_string, double &scaled_number);

#endif
