
project( proyecto_movimiento )
message( "Configuring subproject application:  ${PROJECT_NAME} " )

file(GLOB SOURCES "*.cpp" )
file(GLOB HEADERS "*.h" )

include_directories( ${OpenCV_INCLUDE_DIRS} )
 
add_executable( ${PROJECT_NAME}  
				${HEADERS} 
				${SOURCES})
				
target_link_libraries( ${PROJECT_NAME} 
                       ${OpenCV_LIBS} )
                           