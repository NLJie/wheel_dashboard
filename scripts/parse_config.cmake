# parse_config.cmake
function(parse_config CONFIG_FILE)
    file(READ ${CONFIG_FILE} CONFIG_CONTENT)

    # 查找每一行的配置项，并设置对应的宏定义
    foreach(line ${CONFIG_CONTENT})
        string(REGEX MATCH "CONFIG_(.*)=y" MATCHED ${line})
        if(MATCHED)
            string(REGEX REPLACE "CONFIG_(.*)=y" "\\1" CONFIG_OPTION ${MATCHED})
            # 设置为编译选项
            add_definitions(-D${CONFIG_OPTION}=1)
        endif()

        string(REGEX MATCH "CONFIG_(.*)=n" MATCHED ${line})
        if(MATCHED)
            string(REGEX REPLACE "CONFIG_(.*)=n" "\\1" CONFIG_OPTION ${MATCHED})
            # 设置为编译选项
            add_definitions(-D${CONFIG_OPTION}=0)
        endif()
    endforeach()
endfunction()
