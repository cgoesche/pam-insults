CC = gcc
CFLAGS = -fPIC -Wall -g -O2

PACKAGE_NAME = pam-insults
PACKAGE_VERSION = $(shell head -n1 VERSION)

PAM_MODULE_NAME = pam_insults
PAM_MODULES_DIR ?= $(or $(wildcard /usr/lib64/security/.),/usr/lib/security/.)
MODULES_DIR = modules
SOURCES_DIR = src
MAN_DATABASE ?= /usr/share/man/man8
MAN_DIR = man

SOURCES = $(SOURCES_DIR)/$(PAM_MODULE_NAME).c
OBJECTS = $(SOURCES:.c=.o)
SHARED_OBJECT = $(MODULES_DIR)/$(PAM_MODULE_NAME).so
MANPAGE_GZ = $(MAN_DIR)/$(PAM_MODULE_NAME).8.gz

PO_DIR = po

all: $(SHARED_OBJECT) manpage

$(SHARED_OBJECT): $(OBJECTS)
	[ -d $(MODULES_DIR) ] || mkdir $(MODULES_DIR)
	$(CC) -shared -o $@ $^

$(OBJECTS): $(SOURCES)
	$(CC) $(CFLAGS) -c $< -o $@

manpage:
	asciidoctor -b manpage -a release-version=$(PACKAGE_VERSION) -a adjtime_path=/etc/adjtime $(MANPAGE_GZ:.gz=.adoc)
	gzip --suffix=.gz -f $(MAN_DIR)/$(PAM_MODULE_NAME).8

install: $(SHARED_OBJECT) $(MANPAGE_GZ)
	[ ! -f $(PAM_MODULES_DIR:.=)/$(PAM_MODULE_NAME).so ] || sudo rm $(PAM_MODULES_DIR:.=)/$(PAM_MODULE_NAME).so
	sudo cp $(SHARED_OBJECT) $(PAM_MODULES_DIR)
	sudo cp $(MANPAGE_GZ) $(MAN_DATABASE)
	sudo mandb

clean:
	rm -f $(OBJECTS) $(SHARED_OBJECT)
