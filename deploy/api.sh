#!/bin/bash

source $(dirname "$0")/../../build/deploy/unix/api.sh

OUTPUT_DIR=$1
ARCHIVE_DIR=$2

ComponentApiBegin sdk $OUTPUT_DIR $ARCHIVE_DIR
ModuleApi arch
ModuleApi network
ModuleApi controls
ModuleApi hosting
ModuleApi dox
FileApi $COMPONENT_NAME/defs.h
