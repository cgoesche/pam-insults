CC = gcc
CFLAGS = -fPIC -Wall -g -O2

MODULE = pam_insults
VERSION = 0.2.1-beta

PAM_MODULES_DIR ?= $(or $(wildcard /usr/lib64/security/.),/usr/lib/security/.)
MODULES_DIR = modules/
SOURCES_DIR = src/
MAN_DATABASE ?= /usr/share/man/man8/
MAN_DIR = man/

SOURCES = $(SOURCES_DIR)$(MODULE).c
OBJECTS = $(SOURCES:.c=.o)
SHARED_OBJECT = $(MODULES_DIR)$(MODULE).so
MANPAGE_GZ = $(MAN_DIR)$(MODULE).8.gz

XGETTEXT = xgettext
XGETTEXT_FLAGS = -F -k_ -kN_ --copyright-holder="Christian Goeschel Ndjomouo" \
		"--msgid-bugs-address=https://github.com/cgoesche/pam-insults/issues" \
		--package-name=pam-insults --package-version=$(VERSION) \
		--language=C --add-comments


all: $(SHARED_OBJECT) manpage

$(SHARED_OBJECT): $(OBJECTS)
	[ -d $(MODULES_DIR) ] || mkdir $(MODULES_DIR)
	$(CC) -shared -o $@ $^

$(OBJECTS): $(SOURCES)
	$(CC) $(CFLAGS) -c $< -o $@

manpage:
	asciidoctor -b manpage -a release-version=$(VERSION) -a adjtime_path=/etc/adjtime $(MANPAGE_GZ:.gz=.adoc)
	gzip --suffix=.gz -f $(MAN_DIR)$(MODULE).8

update-pot:
	$(XGETTEXT) $(XGETTEXT_FLAGS) -o po/pam-insults.pot -f po/POTFILES.in

update-po:
	cd po/
	chmod +x pomgr.sh && ./pomgr.sh update-po
	cd ..

compile-po: update-po
	./pomgr.sh compile

install: $(SHARED_OBJECT) $(MANPAGE_GZ)
	[ ! -f $(PAM_MODULES_DIR:.=)$(MODULE).so ] || sudo rm $(PAM_MODULES_DIR:.=)$(MODULE).so
	sudo cp $(SHARED_OBJECT) $(PAM_MODULES_DIR)
	sudo cp $(MANPAGE_GZ) $(MAN_DATABASE)
	mandb

clean:
	rm -f $(OBJECTS) $(SHARED_OBJECT)


