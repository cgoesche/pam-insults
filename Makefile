CC = gcc
CFLAGS = -fPIC -Wall -g -O2

MODULE = pam_insults
MODULE_VERSION = 0.1.0

PAM_MODULES_DIR := $(or $(wildcard /usr/lib64/security/.),/usr/lib/security/.)
MODULES_DIR = modules/
SOURCES_DIR = src/
MAN_DATABASE = /usr/share/man/man8/
MAN_DIR = man/

SOURCES = $(SOURCES_DIR)$(MODULE).c
OBJECTS = $(SOURCES:.c=.o)
SHARED_OBJECT = $(MODULES_DIR)$(MODULE).so
MANPAGE_GZ = $(MAN_DIR)$(MODULE).8.gz

all: $(SHARED_OBJECT) manpage

$(SHARED_OBJECT): $(OBJECTS)
	[ -d $(MODULES_DIR) ] || mkdir $(MODULES_DIR)
	$(CC) -shared -o $@ $^

$(OBJECTS): $(SOURCES)
	$(CC) $(CFLAGS) -c $< -o $@

manpage:
	asciidoctor -b manpage -a release-version=$(MODULE_VERSION) -a adjtime_path=/etc/adjtime $(MANPAGE_GZ:.gz=.adoc)
	gzip --suffix=.gz -f $(MAN_DIR)$(MODULE).8


install: $(SHARED_OBJECT) $(MANPAGE_GZ)
	sudo rm $(PAM_MODULES_DIR:.=)$(MODULE).so
	sudo cp $(SHARED_OBJECT) $(PAM_MODULES_DIR)
	sudo cp $(MANPAGE_GZ) $(MAN_DATABASE)

clean:
	rm -f $(OBJECTS) $(SHARED_OBJECT)


