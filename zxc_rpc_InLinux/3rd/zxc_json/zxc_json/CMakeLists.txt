# add_library(zxc_json STATIC
        # Exception.h
        # FileReadStream.h FileWriteStream.h
        # StringReadStream.h StringWriteStream.h
        # Reader.cc Reader.h
        # Writer.cc Writer.h
        # Value.cc Value.h
        # Document.h
        # noncopyable.h
        # PrettyWriter.h)

include_directories(${PROJECT_SOURCE_DIR}/zxc_json )		
		
		
aux_source_directory(.  SOURCE_FILES)
add_library(zxc_json STATIC ${SOURCE_FILES} )   



install(TARGETS zxc_json DESTINATION lib)

set(HEADERS
        Document.h
        Exception.h
        FileReadStream.h
        FileWriteStream.h
        noncopyable.h
        PrettyWriter.h
        Reader.h
        StringReadStream.h
        StringWriteStream.h
        Value.h
        Writer.h
        )
install(FILES ${HEADERS} DESTINATION include)




