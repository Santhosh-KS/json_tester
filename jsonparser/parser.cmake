PROJECT(jsonparser)
SET(SRC jsonparser/main.cpp
        jsonparser/generic_json_parser.cpp)

SET(BIN jsonParser)
SET(INC /home/santhosh/work/rapidjson/include/rapidjson)

INCLUDE_DIRECTORIES(${INC})

ADD_EXECUTABLE(${BIN} ${SRC})


#TARGET_LINK_LIBRARIES(${BIN})  
