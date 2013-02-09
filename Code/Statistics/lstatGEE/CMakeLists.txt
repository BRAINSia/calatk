project(lstatGEE)

#
# Add the lstatGEE application
#

if(USE_BOOST)
  set(libraries ${ITK_LIBRARIES} ${BOOST_LIBRARIES})
else(USE_BOOST)
  set(libraries ${ITK_LIBRARIES})
endif(USE_BOOST)

# Need to manually set up CLP here, because we have multiple source files

set(appName lstatGEE)
set(mainFile lstatGEE)

# if we're coming from application off, force this application to compile
if(NOT COMPILE_APPLICATIONS)
  set(force_application${appName} ON CACHE INTERNAL "temp variable for application switches" FORCE)
endif(NOT COMPILE_APPLICATIONS)

# set up the option and mark it as advanced
mark_as_advanced( compile_${appName} )
option(compile_${appName} "Compile ${appName}" ON)

# only turn the test on if COMPILE_APPLICATIONS was just turned on
if(COMPILE_APPLICATIONS)
  if(force_application${appName})
    set(compile_${appName} ON CACHE BOOL "Compile ${appName}" FORCE)
    set(force_application${appName} OFF CACHE INTERNAL "temp variable for application switches" FORCE)
  endif(force_application${appName})

  if(COMPILE_CLP_MODULES)
    if(compile_${appName})
      set(CLP ${mainFile})
      set( ${CLP}_SOURCE ${CLP}.cxx )
      GENERATECLP(${CLP}_SOURCE ${CLP}.xml "")

      # compile the program

  #    add_executable(${appName} ${CLP}.cxx surallfileM10Y06_MN_JP.cpp pxanalyse_MN.cpp GEEutil_MN.cpp)
      add_executable(${appName} ${CLP}.cxx surallfileM10Y06_MN_JP.cpp GEEutil_MN.cpp)
      target_link_libraries( ${appName} CALATK ${libraries})

    endif(compile_${appName})
  endif(COMPILE_CLP_MODULES)

  # if COMPILE_APPLICATIONS is off, force the test to turn on next time COMPILE_APPLICATIONS is turned on
else(COMPILE_APPLICATIONS)
  set(compile_${appName} OFF CACHE BOOL "Compile ${appName}" FORCE)
endif(COMPILE_APPLICATIONS)

#add_executable(tstMatrix tstMatrixLogExp.cxx)

