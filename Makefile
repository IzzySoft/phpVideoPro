# Makefile for phpVideoPro
# $Id$

DESTDIR=
prefix=/usr/local
datarootdir=$(DESTDIR)$(prefix)/share
datadir=$(datarootdir)/phpvideopro
docdir=$(datarootdir)/doc/phpvideopro
INSTALL=install
INSTALL_PROGRAM=$(INSTALL)
INSTALL_DATA=$(INSTALL) -m 644

WEBROOT=$(DESTDIR)/var/www
LINKTO=$(WEBROOT)/phpvideopro

install: installdirs
	$(INSTALL_DATA) doc/* $(docdir)
	$(INSTALL_DATA) .htaccess $(datadir)
	cp -pr * $(datadir)
	rm -f $(datadir)/Makefile
	rm -rf $(datadir)/doc
	if [ ! -e $(LINKTO) ]; then ln -s $(datadir) $(LINKTO); fi

installdirs:
	mkdir -p $(datadir)
	mkdir -p $(docdir)
	if [ ! -e $(WEBROOT) ]; then mkdir -p $(WEBROOT); fi

uninstall:
	rm -rf $(datadir)
	rm -rf $(docdir)

