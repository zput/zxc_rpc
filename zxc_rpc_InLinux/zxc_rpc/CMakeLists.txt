
include_directories(${PROJECT_SOURCE_DIR}/zxc_rpc ) 

add_library(zxc_rpc STATIC
        RpcError.h
        Exception.h
        util.h
        server/BaseServer.cc server/BaseServer.h
        server/RpcServer.cc server/RpcServer.h
        server/RpcService.cc server/RpcService.h
        server/Procedure.cc server/Procedure.h 
	#	client/BaseClient.cc client/BaseClient.h
		)
target_link_libraries(zxc_rpc zxc_net zxc_json)


install(TARGETS zxc_rpc DESTINATION lib)



set(HEADERS
        util.h
        server/RpcServer.h
        server/BaseServer.h
        server/Procedure.h
        server/RpcService.h
        client/BaseClient.h)
install(FILES ${HEADERS} DESTINATION include)

# add_subdirectory(stub)










