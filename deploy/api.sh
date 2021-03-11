#!/bin/bash

source $(dirname "$0")/../../build/deploy/unix/api.sh

REL_OUTPUT_DIR=$1
REL_ARCHIVE_DIR=$2

ComponentApiBegin sdk $REL_OUTPUT_DIR $REL_ARCHIVE_DIR
ModuleApi arch
ModuleApi network
ModuleApi controls
ModuleApi hosting
ModuleApi dox
#FileApi $COMPONENT_NAME/defs.h
ComponentApiEnd

