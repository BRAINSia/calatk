#
# Add the Geometric Metamorphosis application
#
set(libraries ${FFTW_LIB} ${ITK_LIBRARIES})
add_clp_application(GeometricMetamorphosis GeometricMetamorphosis ${libraries})
