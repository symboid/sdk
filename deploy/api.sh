#!/bin/bash

COMPONENT_NAME=sdk
ARCHIVE_NAME=$COMPONENT_NAME-api.tar.gz
	
function FolderApi
{
    FOLDER_PATH=$1
    tar --append --file=$ARCHIVE_NAME --include='*.h' $FOLDER_PATH
}

# !include ..\..\build\deploy\nsis\api.nsh

# !insertmacro ComponentApiBegin sdk
# !insertmacro ModuleApi arch
# !insertmacro ModuleApi network
# !insertmacro ModuleApi controls
# !insertmacro ModuleApi hosting
# !insertmacro ModuleApi dox
# !insertmacro FileApi defs.h
