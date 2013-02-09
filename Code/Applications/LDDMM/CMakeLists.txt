#
# Add the LDDM application
#
set(libraries ${FFTW_LIB} ${ITK_LIBRARIES})
add_clp_application(LDDMM LDDMM ${libraries})
