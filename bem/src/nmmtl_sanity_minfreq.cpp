/*
 * Prints the minimum frequency for obtaining an accurate AC resistance from the
 * perturbation technique and the correct inductance based only on the external
 * inductance with regard to minimum conductor dimensions.
 */

#include "nmmtl.h"

void nmmtl_sanity_minfreq(double the_conductivity,
         CONTOURS_P signals,
         double top_ground_plane_thickness,
         double bottom_ground_plane_thickness,
         FILE *output_file1,
         FILE *output_file2) {
  CONTOURS_P item;
  double minimumDimension = DBL_MAX;
  double minimumFrequency;
  double tmp;
  double minfreq;
  double conductivity = the_conductivity;

  //search for the minimum dimension
  if (top_ground_plane_thickness < minimumDimension)
    minimumDimension = top_ground_plane_thickness;
  if (bottom_ground_plane_thickness < minimumDimension)
    minimumDimension = bottom_ground_plane_thickness;

  for (item = signals; item != NULL; item = item->next) {
    if (item->conductivity != 0.0)
      conductivity = item->conductivity;

    switch (item->primitive) {
    case RECTANGLE:
      if ((item->y1 - item->y0) < minimumDimension)
        minimumDimension = item->y1 - item->y0;
      break;
    case CIRCLE:
      if ((2. * item->x1) < minimumDimension)
        minimumDimension = 2. * item->x1;
      break;
    case POLYGON:
      if ((item->y1 - item->y0) < minimumDimension)
        minimumDimension = item->y1 - item->y0;
      break;
    }
  }

  //write out messages.
  tmp =  PI * minimumDimension / 10.;
  minimumFrequency = 1.0 / (4.0e-7 * conductivity * pow(tmp, 2));
  minfreq = minimumFrequency/1e6 + 1.0;
  printf ("%f MHz is the minimum frequency for the surface current assumptions for this cross section\n", minfreq);
  if (output_file1 != NULL)
    fprintf(output_file1, "Note: minimum frequency for surface current assumptions is %f MHz.", minfreq);
  if (output_file2 != NULL)
    fprintf(output_file2, "Note: minimum frequency for surface current assumptions is %f MHz.", minfreq);
}

