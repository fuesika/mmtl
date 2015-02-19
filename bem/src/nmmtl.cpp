/*
 * FACILITY
 *    NMMTL
 * MODULE DESCRIPTION
 *    Contains main function for NMMTL program.
 * AUTHORS
 *    Kevin J. Buchs
 * CREATION DATE
 *    Mon Nov 25 15:56:48 1991
 * COPYRIGHT
 *    Copyright (C) 1991 by Mayo Foundation. All rights reserved.
 * FILES USED:
 *    Graphic file for node in design directory
 *    Electro results file
*/


/*
 *******************************************************************
 **  INCLUDE FILES
 *******************************************************************
 */

#include <limits.h>
#include <string.h>

#include "nmmtl.h"


/*
 *******************************************************************
 **  GLOBALS
 *******************************************************************
 */
extern FILE *plotFile; /* the file the field plot data will be written to */

FILE *dump_file;  /* a file for diagnostics */


/*
 * FUNCTION NAME
 *    main
 * FUNCTIONAL DESCRIPTION:
 *    The main function for NMMTL.
 * FORMAL PARAMETERS:
 *    int argc      count of command line arguments
 *    char **argv   array of command line arguments
 * RETURN VALUE
 *    0 if success, 1 if fail, other non-zero if status indicates.
*/
int main(int argc, char **argv) {
  /* local variables */
  int units;
  int cntr_seg; /* desired # segments on contours */
  int pln_seg; /* desired # segments on planes */
  float coupling; /* coupling length (icon attr.) */
  float risetime; /* signal risetime (icon attr.) */
  float conductivity; /* conductivity or converted surface */
                      /* resistance (icon attr.) */
  int gnd_planes; /* # ground planes in file (1 or 2 needed) */
  float top_ground_plane_thickness; /* icon attr. */
  float bottom_ground_plane_thickness; /* icon attr. */
  float half_minimum_dimension = -1.0; /* unset value */
  struct dielectric *dielectrics = NULL; /* points to lowest layer in list */
  struct contour *signals = NULL; /* 1st signal (lowest) read in */
  struct contour *sigs = NULL; /* 1st signal (lowest) read in */
  struct contour *groundwires = NULL; /* 1st ground wire read into list */
  int status;
  char filename[PATH_MAX];  /* base file name (without .graphic extension) */
  char filespec[PATH_MAX];    /* filespec for fopen() */
  int num_signals = 0;
  int num_grounds = 0;
  float **electrostatic_induction;
  float **inductance;
  float **Rdc;
  float *characteristic_impedance;
  float *propagation_velocity;
  float *equivalent_dielectric;
  float **forward_xtk;
  float **backward_xtk;
  FILE *output_file1;
  FILE *output_file2;
  bool element_dump = false;
  char ele_dmp_filename[PATH_MAX];
  FILE *retrieval_file;

  /* - - - - - - - - - -  INITIALIZATIONS - - - - - - - - - - - - - - - - */
  dump_file = fopen("nmmtl.dump","w");

  //  set line buffering on stdout and stderr so that
  //  we behave nicely when run at the end of a pipeline.
  setvbuf(stdout, NULL, _IOLBF, BUFSIZ);
  setvbuf(stderr, NULL, _IOLBF, BUFSIZ);

  // Processing command-line arguments
  for (int ii = 0; ii < argc; ii++) {
    switch (ii) {
      case 0:
        break;
      case 1:
        strcpy(filename, argv[1]);
        break;
      case 2:
        sscanf(argv[2], "%d", &cntr_seg);
        break;
      case 3:
        sscanf(argv[3],"%d", &pln_seg);
        break;
      case 4:
        strcpy(ele_dmp_filename, argv[4]);
        element_dump = true;
        break;
      default:
        printf("ERROR: list of input arguments too long.\n\n");
    }
  }

  if ((argc < 2) || (argc > 5)) {
    printf("MMTL_BEM is a tool for the characterization of transmission line cross-sections.\n\n");
    printf("usage: mmtl_bem geometry_fname [c_seg] [p_seg] [dump_fname]\n\n");
    printf("Without further options, MMTL_BEM prints this help and exists.\n\n");
    printf("  geometry_fname   geometry specification filename\n");
    printf("  c_seg            number of contour segments (optional)\n");
    printf("  p_seg            number of plane/dielectric segments (optional)\n");
    printf("  dump_fname       dump of previous run filename (optional, for advanced users)\n");
    return 0;
  }

  sprintf (filespec, "%s.dump", filename);
  printf ("Dump file of %s\n", filespec);
  dump_file = fopen(filespec,"w");

  sprintf (filespec,
     "File: %s   # contour segs: %d   # plane/diel segs: %d\n",
     filename, cntr_seg, pln_seg);

  /* are there elements to retrieve? - if not - then read graphic file and
     generate them */
  if (element_dump) {
    retrieval_file = fopen(ele_dmp_filename,"r");
    if (retrieval_file == NULL) {
      printf ("Retrieval file not found (%s)\n", ele_dmp_filename);
    } else {
      char string[256];
      strcpy(string,"retrieving signal names from: ");
      strcat(string,ele_dmp_filename);
      printf ("%s\n", string);
      nmmtl_retrieve(retrieval_file,
                     &cntr_seg,
                     &pln_seg,
                     &coupling,
                     &risetime,
                     &signals,
                     &num_signals,
                     NULL,NULL,NULL,NULL,NULL);
    }
  } else {
    /* - - - - - - - -  Read in data from the graphic file  - - - - - - - - */
    status = nmmtl_parse_xsctn(filename,
                               &cntr_seg,
                               &pln_seg,
                               &coupling,
                               &risetime,
                               &conductivity,
                               &half_minimum_dimension,
                               &gnd_planes,
                               &top_ground_plane_thickness,
                               &bottom_ground_plane_thickness,
                               &dielectrics,
                               &signals,
                               &groundwires,
                               &num_signals,
                               &num_grounds,
                               &units);

    struct dielectric *d_temp = dielectrics;
    printf ("---- Dielectrics ----\n");
    while ( d_temp != NULL ) {
      printf ("  (%g,%g) - (%g,%g)  permittivity: %g\n",
        d_temp->x0, d_temp->y0,
        d_temp->x1, d_temp->y1, d_temp->constant);
      d_temp = d_temp->next;
    }
    struct contour *c_temp = signals;
    struct polypoints *ptt;
    printf ("---- Conductors ----\n");
    while ( c_temp != NULL ) {
      printf ("%s  (%g,%g) - (%g,%g)  conductivity: %g  type: %c\n",
        c_temp->name, c_temp->x0, c_temp->y0,
        c_temp->x1, c_temp->y1, c_temp->conductivity, c_temp->primitive);
      ptt = c_temp->points;
      while ( ptt != NULL ) {
        printf (" (%g,%g) ", ptt->x, ptt->y);
        ptt = ptt->next;
      }
      printf ("\n");
      c_temp = c_temp->next;
    }
    c_temp = groundwires;
    printf ("---- GroundWires ----\n");
    while ( c_temp != NULL ) {
      printf ("  (%g,%g) - (%g,%g)  conductivity: %g  type: %c\n",
        c_temp->x0, c_temp->y0,
        c_temp->x1, c_temp->y1, c_temp->conductivity, c_temp->primitive);
      ptt = c_temp->points;
      while ( ptt != NULL ) {
        printf (" (%g,%g) ", ptt->x, ptt->y);
        ptt = ptt->next;
      }
      printf ("\n");
      c_temp = c_temp->next;
    }

    printf ("filename: %s\ncntr_seg: %d  pln_seg: %d  coupling: %g\n",
      filename, cntr_seg, pln_seg, coupling);
    printf ("risetime: %g  conductivity: %g\n",
      risetime, conductivity);
    printf ("half_min_dim: %g  grnd_planes: %d  top_grnd_thck: %f\n",
      half_minimum_dimension, gnd_planes, top_ground_plane_thickness);
    printf ("bot_grnd_thck: %g  num_sig: %d  num_grounds: %d\n",
      bottom_ground_plane_thickness, num_signals, num_grounds);
    printf ("units: %d\n", units);

    if (status != SUCCESS)
      return 0;

    /* - - - - - - - -  dump the geometry as read in  - - - - - - - - - */
    nmmtl_dump_geometry(cntr_seg, pln_seg, coupling, risetime, conductivity,
      half_minimum_dimension,
      gnd_planes, top_ground_plane_thickness,
      bottom_ground_plane_thickness, dielectrics,signals,
      groundwires);
  }

  /* - - - - - - - -  Allocate space for results  - - - - - - - - - */

  /* Are there elements to dump?   If not, proceed normally */
  if (!element_dump) {
    electrostatic_induction = (float **) dim2(num_signals,num_signals,sizeof(float));
    inductance = (float **) dim2(num_signals,num_signals,sizeof(float));
    characteristic_impedance = (float *)malloc(sizeof(float) * num_signals);
    propagation_velocity = (float *)malloc(sizeof(float) * num_signals);
    equivalent_dielectric = (float *)calloc(num_signals,sizeof(float));
    forward_xtk = (float **) dim2(num_signals,num_signals,sizeof(float));
    backward_xtk = (float **) dim2(num_signals,num_signals,sizeof(float));
    Rdc = (float **) dim2(num_signals,num_signals,sizeof(float));

    /*  Open MMTL results output file  */
    sprintf (filespec, "%s.result", filename);
    if ((output_file1 = fopen(filespec,"w")) == NULL) {
      //fatal error; could not open output file
      printf("Error: cannot open '%s' for output.\n", filespec);
      return 1;
    }

    /* print headers on the output file */
    /* pass in the number of pure ground wires plus one if an upper
       ground plane exists */
    nmmtl_output_headers(output_file1, filename,num_signals,
       num_grounds, gnd_planes,
       coupling,risetime,cntr_seg,pln_seg);

    sigs = signals;
    for (sigs = signals; sigs != NULL; sigs = sigs->next) {
      float cndvty = conductivity;
      if (sigs->conductivity != 0.0)
        cndvty = sigs->conductivity;
      fprintf (output_file1, "Conductivity %s = %g siemens/meter\n",
      sigs->name, cndvty);
    }

    /* only need a single output file - prompting interface may need two */
    output_file2 = (FILE *)NULL;
  }

  /* ------------------------ open the plot file -------------------------- */
  if (!element_dump) {
    sprintf (filespec, "%s.result_field_plot_data", filename);

    if ( (plotFile = fopen(filespec,"w")) == NULL ) {
      printf ("Error: cannot open plot file %s\n", filespec);
      return 0;  /* Fatal error; could not open output file */
    }

    plotFileInitialization(plotFile,units, gnd_planes,
         top_ground_plane_thickness,
         bottom_ground_plane_thickness);
  }

  //-- Sanity Check ------------------------------------------------------------
  //minimum frequency for valid computation
  nmmtl_sanity_minfreq(conductivity,
                       signals,
                       top_ground_plane_thickness,
                       bottom_ground_plane_thickness,
                       output_file1, output_file2);

  /* - - - - - - - - Calculate the Quasi-static Parameters - - - - - - - - */
  status = nmmtl_qsp_calculate(dielectrics,signals,groundwires,
             gnd_planes,half_minimum_dimension,
             cntr_seg,pln_seg,coupling,risetime,
             electrostatic_induction,
             inductance,characteristic_impedance,
             propagation_velocity,equivalent_dielectric,
             output_file1,output_file2);

  /* if we dumped the elements, then there is nothing more to do. */
  if (element_dump)
    return 0;

  /* if we failed to qsp_calculate,  then there is nothing more to do */
  if (status != SUCCESS) {
    fclose(output_file1);
    return 0;
  }

  /*           find the dc resistance */
  nmmtl_dc_resistance(conductivity, signals, Rdc, output_file1, output_file2);

  /* - - - - - - - - Calculate the Crosstalk   - - - - - - - - - */
  status = nmmtl_xtk_calculate(num_signals,
                               signals,
                               electrostatic_induction,
                               inductance,
                               coupling,
                               risetime,
                               propagation_velocity,
                               forward_xtk,
                               backward_xtk,
                               output_file1,
                               output_file2);
  if (status != SUCCESS) {
    fclose(output_file1);
    return 0;
  }

  fclose(output_file1);
  fclose(dump_file);

  printf ("\nMMTL is done\n");
  return 0;
}
