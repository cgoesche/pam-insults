/*
pam_insults module

Copyright © 2025 Christian Goeschel Ndjomouo <cgoesc2@wgu.edu>

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/
#include <libintl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <time.h>

#include <security/pam_modules.h>

#include "lib/insults.h"

#define min(a, b) (((a) < (b)) ? (a) : (b))
#define _ARG_VALUE_LENGTH 32

enum {
        _QUIET_MODE = 1
};

struct ctrl {
        int is_quiet_mode;                              // is quiet mode enabled ?
        char *insult_type;                              // which type of insult, 'soft', 'hard' or 'unhinged' ?
        char *insult;                                   // pointer to the selected insult
};

static inline const char * 
get_pam_arg_value(const char *str, const char *prefix) 
{
        size_t prefix_len = strlen(prefix);

        return strncmp(str, prefix, prefix_len) ? NULL : str + prefix_len;
}

static inline void 
parse_pam_args(struct ctrl *c, int argc, const char **argv)
{
        if (argc >= 1) {
                for (size_t i = 0; i < argc; i++) {
                        const char *str;

                        if (strcmp(argv[i], "quiet") == 0) {
                                c->is_quiet_mode = _QUIET_MODE;
                                break;
                        } 
                        else if ((str = get_pam_arg_value(argv[i], "type=")) != NULL) {
                                strcpy(c->insult_type, str);
                                continue;
                        }
                }
        }
}

static inline void
set_insult(struct ctrl *c, const char insult_list[][_MAX_INSULT_LENGTH], size_t list_len) 
{       
        size_t i;
        srand(time(NULL));

        i = rand() % list_len;

        if (i >= 0 && i <= list_len){
                strcpy(c->insult, _(insult_list[i]));
        } else {
                strcpy(c->insult, _DEFAULT_INSULT); 
        }
} 

static void 
insult(int argc, const char **argv)
{
        size_t size;
        struct ctrl c;
        c.is_quiet_mode = !_QUIET_MODE;
        c.insult_type = (char *)malloc(_ARG_VALUE_LENGTH);
        c.insult = (char *)malloc(_MAX_INSULT_LENGTH);

        // Enable localization of insults via gettext
        bindtextdomain(_DOMAINNAME, _LOCALEDIR);
        textdomain(_DOMAINNAME);

        parse_pam_args(&c, argc, argv);

        // No need to proceed further if 'quiet' has been passed to the module
        if (c.is_quiet_mode == _QUIET_MODE)
                return;

        if (strcmp(c.insult_type, "soft") == 0) {
                size = _NUM_OF_INSULTS(_soft_insults);
                set_insult(&c, _soft_insults, size);
        }
        else if (strcmp(c.insult_type, "hard") == 0) {
                size = _NUM_OF_INSULTS(_hard_insults);
                set_insult(&c, _hard_insults, size);
        } 
        else if (strcmp(c.insult_type, "unhinged") == 0) {
                size = _NUM_OF_INSULTS(_unhinged_insults);
                set_insult(&c, _unhinged_insults, size);
        }
        else {
                size = _NUM_OF_INSULTS(_soft_insults);
                set_insult(&c, _soft_insults, size);
        }

        fprintf(stderr, "%s\n", c.insult);

        free(c.insult_type);
        free(c.insult);
}

// PAM function definitions
//
// authentication management functions
int 
pam_sm_authenticate(pam_handle_t *pamh, int flags, int argc, const char **argv)
{
        insult(argc, argv);
        return PAM_AUTH_ERR;
}

int 
pam_sm_setcred(pam_handle_t *pamh, int flags, int argc, const char **argv)
{
        insult(argc, argv);
        return PAM_CRED_ERR;
}

// account management function
int 
pam_sm_acct_mgmt(pam_handle_t *pamh, int flags, int argc, const char **argv)
{
        insult(argc, argv);
        return PAM_AUTH_ERR;
}

// password management function
int 
pam_sm_chauthtok(pam_handle_t *pamh, int flags, int argc, const char **argv)
{
        insult(argc, argv);
        return PAM_AUTHTOK_ERR;
}

// session management functions
int
pam_sm_open_session(pam_handle_t *pamh, int flags, int argc, const char **argv)
{
        return PAM_IGNORE;
}

int
pam_sm_close_session(pam_handle_t *pamh, int flags, int argc, const char **argv)
{
        return PAM_IGNORE;
}
