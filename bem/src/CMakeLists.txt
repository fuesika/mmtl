
#----------------------------------------------------------------
#  The math library (math_library.cpp) makes calls to the NSWC
#  math library.  But since we only use a few of the hundreds
#  of modules in NSWC, we just include them here.  It saves
#  having a big library hanging around.
#----------------------------------------------------------------
set (src_fortran
  ext/fft.F
  ext/fmin.F
  ext/caxpy.F
  ext/cdivid.F
  ext/cdotc.F
  ext/cgedi.F
  ext/cgefa.F
  ext/cgesl.F
  ext/cmslv1.F
  ext/cmtms.F
  ext/cscal.F
  ext/cswap.F
  ext/dasum.F
  ext/daxpy.F
  ext/dcfact.F
  ext/dcminv.F
  ext/dcmslv.F
  ext/dcsol.F
  ext/ddot.F
  ext/dgeco.F
  ext/dgedi.F
  ext/dgefa.F
  ext/dgesl.F
  ext/dmslv.F
  ext/dpmpar.F
  ext/dscal.F
  ext/dswap.F
  ext/icamax.F
  ext/idamax.F
  ext/ipmpar.F
  ext/isamax.F
  ext/mslv.F
  ext/mtms.F
  ext/sasum.F
  ext/saxpy.F
  ext/sdot.F
  ext/sfft.F
  ext/sgeco.F
  ext/sgedi.F
  ext/sgefa.F
  ext/sgesl.F
  ext/spmpar.F
  ext/sscal.F
  ext/sswap.F
)

add_library (bem_libs STATIC
  #sources for fortran library
  ${src_fortran}
  )

## Configuration of Executables ################################################
# bem-binary
add_executable(${PROJECT_NAME} nmmtl.cpp
  assemble.cpp
  assemble_free_space.cpp
  dim2.cpp
  free2.cpp
  math_library.cpp
  nmmtl_add_to_sorted_list.cpp
  nmmtl_angle_of_intersection.cpp
  nmmtl_build_gnd_die_list.cpp
  nmmtl_charge.cpp
  nmmtl_charimp_propvel_calculate.cpp
  nmmtl_circle_segments.cpp
  nmmtl_combine_die.cpp
  nmmtl_containment.cpp
  nmmtl_dc_resistance.cpp
  nmmtl_det_arc_intersections.cpp
  nmmtl_det_intersections.cpp
  nmmtl_dump.cpp
  nmmtl_dump_geometry.cpp
  nmmtl_eval_circles.cpp
  nmmtl_eval_conductors.cpp
  nmmtl_eval_polygons.cpp
  nmmtl_eval_rectangles.cpp
  nmmtl_fill_die_gaps.cpp
  nmmtl_find_ground_planes.cpp
  nmmtl_find_nu.cpp
  nmmtl_form_die_subseg.cpp
  nmmtl_genel.cpp
  nmmtl_genel_ccs.cpp
  nmmtl_genel_cls.cpp
  nmmtl_genel_die.cpp
  nmmtl_genel_gnd.cpp
  nmmtl_intersections.cpp
  nmmtl_interval.cpp
  nmmtl_jacobian.cpp
  nmmtl_load.cpp
  nmmtl_merge_die_subseg.cpp
  nmmtl_new_die_seg.cpp
  nmmtl_nl_expand.cpp
  nmmtl_orphans.cpp
  nmmtl_output_headers.cpp
  nmmtl_output_matrices.cpp
  nmmtl_overlap_parallel_seg.cpp
  nmmtl_parse_xsctn.cpp
  nmmtl_qsp_calculate.cpp
  nmmtl_qsp_kernel.cpp
  nmmtl_retrieve.cpp
  nmmtl_set_offset.cpp
  nmmtl_shape.cpp
  nmmtl_sort_gnd_die_list.cpp
  nmmtl_spout_off.cpp
  nmmtl_unload.cpp
  nmmtl_write_plot_data.cpp
  nmmtl_xtk_calculate.cpp
  output_charimp_propvel.cpp
  output_crosstalk.cpp
  plotFileInitialization.cpp
  remove_all_spaces.cpp
  units.cpp
  )

target_link_libraries(${PROJECT_NAME} bem_libs)


# bem-binary: install path
install_programs(/bin FILES ${PROJECT_NAME})
