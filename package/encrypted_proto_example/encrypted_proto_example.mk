################################################################################
#
# Encrypted protocol example
#
################################################################################

ENCRYPTED_PROTO_EXAMPLE_VERSION = 1.0.0
ENCRYPTED_PROTO_EXAMPLE_OVERRIDE_SRCDIR = $(TOPDIR)/package/encrypted_proto_example/src
ENCRYPTED_PROTO_EXAMPLE_SITE = https://google.com
ENCRYPTED_PROTO_EXAMPLE_LICENSE = BSD

define ENCRYPTED_PROTO_EXAMPLE_BUILD_CMDS
    $(MAKE) $(CMAKE_OPTS) -C $(@D) all
endef

define ENCRYPTED_PROTO_EXAMPLE_INSTALL_TARGET_CMDS
    $(MAKE) -C $(@D) DESTDIR=$(TARGET_DIR) install
endef

define ENCRYPTED_PROTO_EXAMPLE_CLEAN_CMDS
    $(MAKE) -C $(@D) clean
endef

$(eval $(cmake-package))
