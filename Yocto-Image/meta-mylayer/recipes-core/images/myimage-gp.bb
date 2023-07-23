#This image is based on core-image-base
include recipes-core/images/core-image-base.bb

# The resulting SDK will include the required development tools for cross-compiling a Qt application
inherit populate_sdk_qt5

# Only produce the "rpi-sdimg" image format
IMAGE_FSTYPES = "rpi-sdimg"

#Add support for ssh and tools-sdk you will find the rest in core-image class
IMAGE_FEATURES += "ssh-server-dropbear"

#Add python3 and its packages
IMAGE_INSTALL += "python3 python3-pip python3-modules"

#Add nano and git
IMAGE_INSTALL += "nano git"

#Add our apps
IMAGE_INSTALL += "cardashboard"
IMAGE_INSTALL += "lanedetection"
IMAGE_INSTALL += "trafficsigns"
IMAGE_INSTALL += "trafficlights"
IMAGE_INSTALL += "vehicledetection"
IMAGE_INSTALL += "pedestrian"


#Add support for  OpenCV and Camera
IMAGE_INSTALL += "ffmpeg"
IMAGE_INSTALL += "gstreamer1.0 gstreamer1.0-libav gstreamer1.0-plugins-base gstreamer1.0-meta-base gstreamer1.0-plugins-bad gstreamer1.0-plugins-ugly gstreamer1.0-plugins-good"
IMAGE_INSTALL += "fswebcam"
IMAGE_INSTALL += "v4l-utils"
IMAGE_INSTALL += "userland"
IMAGE_INSTALL += "weston weston-init"
MACHINE_FEATURES:append = " xf86-video-fbdev"

#Add support for wifi and bluetooth
IMAGE_INSTALL += "linux-firmware-bcm43430"

#Use network manager
IMAGE_INSTALL += "networkmanager networkmanager-bash-completion networkmanager-nmtui"

#Add kernel modules
IMAGE_INSTALL += "dht11km"

# Remove old builds
RM_OLD_IMAGE = "1"

# Customize the splash screen or disable
IMAGE_FEATURES:remove = "splash"



