
# Raspberrypi only need gles2
PACKAGECONFIG_GL = "gles2"
PACKAGECONFIG_DISTRO = "linuxfb gles2 eglfs accessibility sql-sqlite"
PACKAGECONFIG_append = " accessibility eglfs fontconfig gles2 linuxfb tslib sql-sqlite2"

QT5_WEBENGINE_PKGS = " \
    qtwebengine-dev \
    qtwebengine-mkspecs \
    qtwebengine \
"

IMAGE_INSTALL += " \
    ${QT5_WEBENGINE_PKGS} \
"

do_configure_prepend_rpi() {
    sed -i 's!load(qt_config)!!' ${S}/mkspecs/linux-oe-g++/qmake.conf

    cat >> ${S}/mkspecs/linux-oe-g++/qmake.conf <<EOF

QMAKE_LIBS_EGL         += -lGLESv2 -lGLES_CM -lsrv_um -lusc -lEGL -lIMGegl
QMAKE_LIBS_OPENGL_ES2  += -lGLESv2 -lGLES_CM -lsrv_um -lusc -lEGL -lIMGegl
load(qt_config)

EOF
}
