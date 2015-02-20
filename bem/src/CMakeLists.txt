
#----------------------------------------------------------------
#  The math library (math_library.cpp) makes calls to the NSWC
#  math library.  But since we only use a few of the hundreds
#  of modules in NSWC, we just include them here.  It saves
#  having a big library hanging around.
#----------------------------------------------------------------
set (src_fortran
  ext/fmin.F
  ext/ipmpar.F
  ext/isamax.F
  ext/mslv.F
  ext/sasum.F
  ext/saxpy.F
  ext/sdot.F
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
  nmmtl_output_charimp_propvel.cpp
  nmmtl_output_crosstalk.cpp
  nmmtl_output_headers.cpp
  nmmtl_output_matrices.cpp
  nmmtl_overlap_parallel_seg.cpp
  nmmtl_parse_xsctn.cpp
  nmmtl_qsp_calculate.cpp
  nmmtl_qsp_kernel.cpp
  nmmtl_retrieve.cpp
  nmmtl_sanity_minfreq.cpp
  nmmtl_set_offset.cpp
  nmmtl_shape.cpp
  nmmtl_sort_gnd_die_list.cpp
  nmmtl_unload.cpp
  nmmtl_write_plot_data.cpp
  nmmtl_xtk_calculate.cpp
  plotFileInitialization.cpp
  remove_all_spaces.cpp
  units.cpp
  )

target_link_libraries(${PROJECT_NAME} bem_libs)


# bem-binary: install path
install_programs(/bin FILES ${PROJECT_NAME})
