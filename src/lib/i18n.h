#ifndef _I18N_H
#define _I18N_H

#include <libintl.h>

#define _DOMAINNAME "pam-insults"
#define _LOCALEDIR "/usr/share/locale"
#define _(msgid) dgettext(_DOMAINNAME, msgid)
#define N_(msgid) msgid

#endif /* _I18N_H */