#!/bin/bash
echo "Generating Doxygen Documentation..."
doxygen
if [ $? -ne 0 ]; then
    echo "❌ Error: Doxygen documentation Checking failed. Aborting commit."
    exit 1
fi
echo "Ok!"