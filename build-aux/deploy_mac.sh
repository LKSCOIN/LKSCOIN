#!/bin/bash
# Script name: deploy.sh

# Following environment variables must be defined:
# - QT_FRAMEWORK_PATH
# - QT_BIN_PATH
# - CERTIFICATE
# - FRAMEWORKS
# - BAD_FRAMEWORKS

export CERTIFICATE="xxxxxxxxxx"
export FRAMEWORKS="xxxxxxxxxxxxxxxxxx"

# retrieve bundle name from first parameter
BUNDLE_NAME=$1

# Run QT tool to deploy
#/usr/local/Cellar/qt/5.13.0/bin/macdeployqt $BUNDLE_NAME

# FIX ISSUE 6
# Please note that Qt5 frameworks have incorrect layout after SDK build, so this isn't just a problem with `macdeployqt` but whole framework assembly part.
# Present
#   QtCore.framework/
#       Contents/
#           Info.plist
#       QtCore    -> Versions/Current/QtCore
#       Versions/
#           Current -> 5
#           5/
#               QtCore
# After macdeployqt
#   QtCore.framework/
#       Resources/
#       Versions/
#           5/
#               QtCore
#
# Expected
#   QtCore.framework/
#       QtCore    -> Versions/Current/QtCore
#       Resources -> Versions/Current/Resources
#       Versions/
#           Current -> 5
#           5/
#               QtCore
#               Resources/
#                   Info.plist
# So in order to comply with expected layout: https://developer.apple.com/library/mac/documentation/MacOSX/Conceptual/BPFrameworks/Concepts/FrameworkAnatomy.html

#for CURRENT_FRAMEWORK in ${FRAMEWORKS}; do
#    echo "Processing framework: ${CURRENT_FRAMEWORK}"

#    echo "Deleting existing resource folder"
#    rmdir ${BUNDLE_NAME}/Contents/Frameworks/${CURRENT_FRAMEWORK}.framework/Resources

#    echo "create resource folder"
#    mkdir -p ${BUNDLE_NAME}/Contents/Frameworks/${CURRENT_FRAMEWORK}.framework/Versions/5/Resources

#    echo "create copy resource file"
#    cp /usr/local/Cellar/qt/5.13.0/lib/${CURRENT_FRAMEWORK}.framework/Contents/Info.plist $BUNDLE_NAME/Contents/Frameworks/${CURRENT_FRAMEWORK}.framework/Versions/5/Resources/

#    echo "create symbolic links"
#    ln -nfs 5                                     ${BUNDLE_NAME}/Contents/Frameworks/${CURRENT_FRAMEWORK}.framework/Versions/Current
#    ln -nfs Versions/Current/${CURRENT_FRAMEWORK} ${BUNDLE_NAME}/Contents/Frameworks/${CURRENT_FRAMEWORK}.framework/${CURRENT_FRAMEWORK}
#    ln -nfs Versions/Current/Resources            ${BUNDLE_NAME}/Contents/Frameworks/${CURRENT_FRAMEWORK}.framework/Resources
#done

# FIX ISSUE 7
echo "***** Correct Frameworks Info.plist file*****"

#for CURRENT_FRAMEWORK in ${BAD_FRAMEWORKS}; do
#    echo "Correcting bad framework Info.plist: ${CURRENT_FRAMEWORK}"
#    TMP=$(sed 's/_debug//g' ${BUNDLE_NAME}/Contents/Frameworks/${CURRENT_FRAMEWORK}.framework/Resources/Info.plist)
#    echo "$TMP" > ${BUNDLE_NAME}/Contents/Frameworks/${CURRENT_FRAMEWORK}.framework/Resources/Info.plist
#done

# SIGNING FIXED FRAMEWORK
CODESIGN_OPTIONS="--verbose=4"

#echo "******* Sign QtWebEngineProcess ***********"
#codesign --force --verify ${CODESIGN_OPTIONS} --sign "$CERTIFICATE" $BUNDLE_NAME/Contents/Frameworks/QtWebEngineCore.framework/Versions/Current/Helpers/QtWebEngineProcess.app
echo "******* Sign Frameworks-subApps ***********"
codesign --force --verify ${CODESIGN_OPTIONS} --sign "$CERTIFICATE" $BUNDLE_NAME/Contents/Frameworks/*.framework/Versions/*/*/*.app

echo "******* Signing Frameworks ***********"
for CURRENT_FRAMEWORK in ${FRAMEWORKS}; do

    mv $BUNDLE_NAME/Contents/Frameworks/${CURRENT_FRAMEWORK}.framework/Resources $BUNDLE_NAME/Contents/Frameworks/${CURRENT_FRAMEWORK}.framework/Versions/5/
    
    codesign --force --verify ${CODESIGN_OPTIONS} --sign "$CERTIFICATE" $BUNDLE_NAME/Contents/Frameworks/${CURRENT_FRAMEWORK}.framework/Versions/5/${CURRENT_FRAMEWORK}
done

# Sign plugins
echo "******* Signing Plugins ***********"
find Lks-Qt.app -name *.dylib | xargs -I $ codesign --force --verify --verbose --sign "${CERTIFICATE}" $
#codesign --force --verify ${CODESIGN_OPTIONS} --sign "${CERTIFICATE}" ${BUNDLE_NAME}/Contents/Plugins/*/*.dylib


# Sign bundle itself
echo "******* Signing Bundle ***********"
codesign --force --verify ${CODESIGN_OPTIONS} --sign "$CERTIFICATE" $BUNDLE_NAME

# Verify

echo "******* Verify Bundle ***********"
codesign --verify --deep ${CODESIGN_OPTIONS} $BUNDLE_NAME


echo "******* Verify Bundle using dpctl ***********"
spctl -a -vvvv $BUNDLE_NAME
